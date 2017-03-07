//----------------------------【程序说明】-------------------------
//文件名：BmpRead.cpp
//功能：读取存储在文件中的bmp文件
//起始时间：2016.12.26  Lqs
//状态：加入读取和写入彩色图的处理 ----- 2016.12.28
//关连文件：Bmp.h
//说明：1)要根据读取的图片先设定正确的BMP_WIDTH和BMP_HEIGHT的值,BMP_WIDTH等在头文件中
//		定义
//		2)本程序只能读取灰度图
//		3)图像数组的定义为IMG_DATA[BMP_HEIGHT][BMP_WIDTH]，为了方便逐列计数而不是逐行
//		  所以第二个元素为横坐标，第一个元素为纵坐标，进行曲线拟合时要注意
//修改记录：
//最后修改时间：
//------------------------------------------------------------------
//------------------------【头文件】--------------------------------------
#include"Bmp.h"
//------------------------------------------------------------------------


//----------------------【全局变量】--------------------------------------
BITMAPFILEHEADER strHead;
BITMAPINFOHEADER strInfo;
RGBQUAD strPla[256];   //256调色板
					   //------------------------------------------------------------------------
using namespace std;

//--------------------------【文件名读取】--------------------------------
//描述：从输入流中获取要读取的bmp文件的文件名，存储到参数数组中
//返回值：读取成功返回1，失败返回0
//int GetBmpNameByInput(char BmpName[LENGTH_NAME_BMP])       //从输入流中获取bmp文件名
//{
//	char BmpPath[LENGTH_NAME_BMP];
//	cout << "输入读取图片路径：" << endl;
//	cin >> BmpPath;
//	return 0;
//}
//------------------------------------------------------------------------
//---------------------------【文件名读取】--------------------------------
//描述：从文件中读取要读取的bmp文件的文件名，存储到参数数组中
//返回值：成功返回1，失败返回0
//状态：完成
//修改记录：
//最后修改时间：
int GetBmpNameByFile(char BmpName[LENGTH_NAME_BMP])        //获取文件名存储到数组中
{
	FILE *names;
	errno_t err = fopen_s(&names, "C:\\Users\\luanqingshan123\\Desktop\\SDOCT\\BmpNames.txt", "r");
	if (err != 0)
	{
		cout << "文件打开失败" << endl;
		return 0;
	}
	
	int err1 = fscanf_s(names, "%s", BmpName, sizeof(char) * LENGTH_NAME_BMP);
	cout << "读取到文件：" << BmpName << endl;
	
	return 1;
}
//---------------------------------------------------------------------------------------
//---------------------【bmp文件读取】---------------------------------------------------
//描述：读取bmp文件到数组IMG_DATA中
//返回值：成功返回1，失败返回0
//状态：完成
//修改记录：
//最后修改时间：
int ReadBmp(char BmpName[LENGTH_NAME_BMP], IMAGEDATA** IMG_DATA)    //读取图片信息
{
	FILE *fpr;//指向读取文件的指针

	fopen_s(&fpr, BmpName, "rb");
	if (fpr == NULL)
	{
		cout << "文件" << BmpName << "打开失败" << endl;
		return 0;
	}

	//检查文件类型是否为bmp
	WORD bfType;
	fread(&bfType, sizeof(WORD), 1, fpr);
	if (bfType != 0x4d42)
	{
		cout << "文件" << BmpName << "不是bmp图像" << endl;
		return 0;
	}

	//读取文件头信息
	fread(&strHead, sizeof(BITMAPFILEHEADER), 1, fpr);
	fread(&strInfo, sizeof(BITMAPINFOHEADER), 1, fpr);
	//读取调色板
	for (unsigned int nCounti = 0; nCounti<strInfo.biClrUsed; nCounti++)
	{
		fread((char *)&(strPla[nCounti].rgbBlue), sizeof(BYTE), 1, fpr);
		fread((char *)&(strPla[nCounti].rgbGreen), sizeof(BYTE), 1, fpr);
		fread((char *)&(strPla[nCounti].rgbRed), sizeof(BYTE), 1, fpr);
		fread((char *)&(strPla[nCounti].rgbReserved), sizeof(BYTE), 1, fpr);
	}

	//读取像素信息
	for (int i = 0; i < BMP_HEIGHT; ++i)
	{
		for (int j = 0; j < BMP_WIDTH; ++j)
		{
			fread(&(IMG_DATA[i][j]), sizeof(IMAGEDATA), 1, fpr);
		}
	}

	//测试读取结果，正式版要注释掉
	//for (int i = 40; i < 80; ++i)
	//{		
	//	for (int j = 200; j < 250; ++j)
	//	{
	//		cout << (int)IMG_DATA[i][j].blue << " ";
	//	}
	//}

	return 1;
}
//-------------------------------------------------------------------------------
//---------------------------【初始化数组】--------------------------------------
//描述：初始化保存像素数据的数组
//返回值：无返回值
//状态：完成
//修改记录：
//最后修改时间：2016.12.28
void InitialBmp(IMAGEDATA **IMG_DATA)
{
	for (int i = 0; i < BMP_HEIGHT; ++i)
	{
		for (int j = 0; j < BMP_WIDTH; ++j)
		{
			IMG_DATA[i][j].blue = 0;
			IMG_DATA[i][j].green = 0;
			IMG_DATA[i][j].red = 0;
		}
	}
}
//-------------------------------------------------------------------------------

//------------------------【bmp图像保存】----------------------------------------
//描述：将存储在数组中的数据保存到bmp文件中
//参数：IMAGEDATA IMG_DATA[BMP_WIDTH][BMP_HEIGHT]
//返回值：成功1，失败0
//状态：完成
//修改记录：
//最后修改时间：2016.12.28
int SaveBmp(char BmpName[LENGTH_NAME_BMP], IMAGEDATA** IMG_DATA)
{
	FILE *fpw;

	//创建bmp文件
	fopen_s(&fpw, BmpName, "wb");
	if (fpw == NULL)
	{
		cout << "文件" << BmpName << "创建失败" << endl;
		return 0;
	}

	//保存文件头
	WORD bfType_w = 0x4d42;
	fwrite(&bfType_w, 1, sizeof(WORD), fpw);
	//fpw +=2;
	fwrite(&strHead, 1, sizeof(tagBITMAPFILEHEADER), fpw);
	strInfo.biWidth = BMP_WIDTH;
	strInfo.biHeight = BMP_HEIGHT;
	fwrite(&strInfo, 1, sizeof(tagBITMAPINFOHEADER), fpw);
	//保存调色板数据
	for (unsigned int nCounti = 0; nCounti<strInfo.biClrUsed; nCounti++)
	{
		fwrite(&strPla[nCounti].rgbBlue, 1, sizeof(BYTE), fpw);
		fwrite(&strPla[nCounti].rgbGreen, 1, sizeof(BYTE), fpw);
		fwrite(&strPla[nCounti].rgbRed, 1, sizeof(BYTE), fpw);
		fwrite(&strPla[nCounti].rgbReserved, 1, sizeof(BYTE), fpw);
	}

	//保存像素数据
	for (int i = 0; i < BMP_HEIGHT; ++i)
	{
		for (int j = 0; j < BMP_WIDTH; ++j)
		{
			fwrite(&(IMG_DATA[i][j]), sizeof(IMAGEDATA), 1, fpw);
		}
	}

	return 1;
}
//------------------------------------------------------------------------------
//----------------------【测试部分】--------------------------------------------
//描述：调用函数并测试函数功能，在正式版中要注释掉

int main()
{
	char BmpName[LENGTH_NAME_BMP];        //存储从文件中读取到的文件名
	IMAGEDATA **IMG_DATA;

	IMG_DATA = (IMAGEDATA **)malloc(sizeof(IMAGEDATA*) * BMP_HEIGHT);
	for (int i = 0; i < BMP_HEIGHT; ++i)
	{
		IMG_DATA[i] = (IMAGEDATA *)malloc(sizeof(IMAGEDATA) * BMP_WIDTH);
	}

	if (IMG_DATA == NULL)
	{
		cout << "内存不足！" << endl;
		exit(0);
	}
	for (int i = 0; i < BMP_HEIGHT; ++i)
	{
		if (IMG_DATA[i] == NULL)
		{
			cout << "内存不足！" << endl;
			exit(0);
		}
	}

	Point *BrightPixel = (Point*)malloc(sizeof(Point) * BMP_WIDTH);
	if (BrightPixel == NULL)
	{
		std::cout << "内存不足，无法分配存储最亮点空间数组！" << std::endl;
	}

		if (!GetBmpNameByFile(BmpName))           //读取文件名到数组中
		{
			exit(0);
		}
		InitialBmp(IMG_DATA);
		ReadBmp(BmpName,IMG_DATA);                     //读取bmp文件像素到数组中

	//测试读取结果，正式版要注释掉
	//	for (int i = 40; i < 80; ++i)
	//	{
	//		for (int j = 30; j < 50; ++j)
	//		{
	//			cout << (int)IMG_DATA[i][j].blue << " ";
	//		}
	//	}

	//	cout << "输入新建文件名：";
	//	cin >> BmpName;
		
		//找到最亮点并去噪
		
		BrightestPixel_And_LowerNoise(IMG_DATA,BrightPixel);
		memset(BmpName, 0, LENGTH_NAME_BMP);
		strcpy_s(BmpName, "AfterLowerNoise.bmp");
		cout << "保存到文件" << BmpName << endl;
		SaveBmp(BmpName, IMG_DATA);
		
		//拟合曲线并拉平图片
		Flattern(IMG_DATA, BrightPixel);
		memset(BmpName, 0, LENGTH_NAME_BMP);
		strcpy_s(BmpName, "AfterFlattern.bmp");
		cout << "保存到文件" << BmpName << endl;
		SaveBmp(BmpName, IMG_DATA);  

		//自动初始化端点
		//int *start_pos, *end_pos;
		//测试，先设置初始化端点为[300,0]，每次横坐标加10，大于700结束
		Assign_Weight(IMG_DATA);
		memset(BmpName, 0, LENGTH_NAME_BMP);
		strcpy_s(BmpName, "AfterAssignWeight.bmp");
		cout << "保存到文件" << BmpName << endl;
		SaveBmp(BmpName, IMG_DATA);


	//释放内存
	for (int i = 0; i < BMP_HEIGHT; ++i)
	{
		free(IMG_DATA[i]);
	}
	free(IMG_DATA);
	free(BrightPixel);

	return 0;
}

//-------------------------------------------------------------------------