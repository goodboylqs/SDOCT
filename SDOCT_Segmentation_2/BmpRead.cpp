//----------------------------������˵����-------------------------
//�ļ�����BmpRead.cpp
//���ܣ���ȡ�洢���ļ��е�bmp�ļ�
//��ʼʱ�䣺2016.12.26  Lqs
//״̬�������ȡ��д���ɫͼ�Ĵ��� ----- 2016.12.28
//�����ļ���Bmp.h
//˵����1)Ҫ���ݶ�ȡ��ͼƬ���趨��ȷ��BMP_WIDTH��BMP_HEIGHT��ֵ,BMP_WIDTH����ͷ�ļ���
//		����
//		2)������ֻ�ܶ�ȡ�Ҷ�ͼ
//		3)ͼ������Ķ���ΪIMG_DATA[BMP_HEIGHT][BMP_WIDTH]��Ϊ�˷������м�������������
//		  ���Եڶ���Ԫ��Ϊ�����꣬��һ��Ԫ��Ϊ�����꣬�����������ʱҪע��
//�޸ļ�¼��
//����޸�ʱ�䣺
//------------------------------------------------------------------
//------------------------��ͷ�ļ���--------------------------------------
#include"Bmp.h"
//------------------------------------------------------------------------


//----------------------��ȫ�ֱ�����--------------------------------------
BITMAPFILEHEADER strHead;
BITMAPINFOHEADER strInfo;
RGBQUAD strPla[256];   //256��ɫ��
					   //------------------------------------------------------------------------
using namespace std;

//--------------------------���ļ�����ȡ��--------------------------------
//���������������л�ȡҪ��ȡ��bmp�ļ����ļ������洢������������
//����ֵ����ȡ�ɹ�����1��ʧ�ܷ���0
//int GetBmpNameByInput(char BmpName[LENGTH_NAME_BMP])       //���������л�ȡbmp�ļ���
//{
//	char BmpPath[LENGTH_NAME_BMP];
//	cout << "�����ȡͼƬ·����" << endl;
//	cin >> BmpPath;
//	return 0;
//}
//------------------------------------------------------------------------
//---------------------------���ļ�����ȡ��--------------------------------
//���������ļ��ж�ȡҪ��ȡ��bmp�ļ����ļ������洢������������
//����ֵ���ɹ�����1��ʧ�ܷ���0
//״̬�����
//�޸ļ�¼��
//����޸�ʱ�䣺
int GetBmpNameByFile(char BmpName[LENGTH_NAME_BMP])        //��ȡ�ļ����洢��������
{
	FILE *names;
	errno_t err = fopen_s(&names, "C:\\Users\\luanqingshan123\\Desktop\\SDOCT\\BmpNames.txt", "r");
	if (err != 0)
	{
		cout << "�ļ���ʧ��" << endl;
		return 0;
	}
	
	int err1 = fscanf_s(names, "%s", BmpName, sizeof(char) * LENGTH_NAME_BMP);
	cout << "��ȡ���ļ���" << BmpName << endl;
	
	return 1;
}
//---------------------------------------------------------------------------------------
//---------------------��bmp�ļ���ȡ��---------------------------------------------------
//��������ȡbmp�ļ�������IMG_DATA��
//����ֵ���ɹ�����1��ʧ�ܷ���0
//״̬�����
//�޸ļ�¼��
//����޸�ʱ�䣺
int ReadBmp(char BmpName[LENGTH_NAME_BMP], IMAGEDATA** IMG_DATA)    //��ȡͼƬ��Ϣ
{
	FILE *fpr;//ָ���ȡ�ļ���ָ��

	fopen_s(&fpr, BmpName, "rb");
	if (fpr == NULL)
	{
		cout << "�ļ�" << BmpName << "��ʧ��" << endl;
		return 0;
	}

	//����ļ������Ƿ�Ϊbmp
	WORD bfType;
	fread(&bfType, sizeof(WORD), 1, fpr);
	if (bfType != 0x4d42)
	{
		cout << "�ļ�" << BmpName << "����bmpͼ��" << endl;
		return 0;
	}

	//��ȡ�ļ�ͷ��Ϣ
	fread(&strHead, sizeof(BITMAPFILEHEADER), 1, fpr);
	fread(&strInfo, sizeof(BITMAPINFOHEADER), 1, fpr);
	//��ȡ��ɫ��
	for (unsigned int nCounti = 0; nCounti<strInfo.biClrUsed; nCounti++)
	{
		fread((char *)&(strPla[nCounti].rgbBlue), sizeof(BYTE), 1, fpr);
		fread((char *)&(strPla[nCounti].rgbGreen), sizeof(BYTE), 1, fpr);
		fread((char *)&(strPla[nCounti].rgbRed), sizeof(BYTE), 1, fpr);
		fread((char *)&(strPla[nCounti].rgbReserved), sizeof(BYTE), 1, fpr);
	}

	//��ȡ������Ϣ
	for (int i = 0; i < BMP_HEIGHT; ++i)
	{
		for (int j = 0; j < BMP_WIDTH; ++j)
		{
			fread(&(IMG_DATA[i][j]), sizeof(IMAGEDATA), 1, fpr);
		}
	}

	//���Զ�ȡ�������ʽ��Ҫע�͵�
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
//---------------------------����ʼ�����顿--------------------------------------
//��������ʼ�������������ݵ�����
//����ֵ���޷���ֵ
//״̬�����
//�޸ļ�¼��
//����޸�ʱ�䣺2016.12.28
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

//------------------------��bmpͼ�񱣴桿----------------------------------------
//���������洢�������е����ݱ��浽bmp�ļ���
//������IMAGEDATA IMG_DATA[BMP_WIDTH][BMP_HEIGHT]
//����ֵ���ɹ�1��ʧ��0
//״̬�����
//�޸ļ�¼��
//����޸�ʱ�䣺2016.12.28
int SaveBmp(char BmpName[LENGTH_NAME_BMP], IMAGEDATA** IMG_DATA)
{
	FILE *fpw;

	//����bmp�ļ�
	fopen_s(&fpw, BmpName, "wb");
	if (fpw == NULL)
	{
		cout << "�ļ�" << BmpName << "����ʧ��" << endl;
		return 0;
	}

	//�����ļ�ͷ
	WORD bfType_w = 0x4d42;
	fwrite(&bfType_w, 1, sizeof(WORD), fpw);
	//fpw +=2;
	fwrite(&strHead, 1, sizeof(tagBITMAPFILEHEADER), fpw);
	strInfo.biWidth = BMP_WIDTH;
	strInfo.biHeight = BMP_HEIGHT;
	fwrite(&strInfo, 1, sizeof(tagBITMAPINFOHEADER), fpw);
	//�����ɫ������
	for (unsigned int nCounti = 0; nCounti<strInfo.biClrUsed; nCounti++)
	{
		fwrite(&strPla[nCounti].rgbBlue, 1, sizeof(BYTE), fpw);
		fwrite(&strPla[nCounti].rgbGreen, 1, sizeof(BYTE), fpw);
		fwrite(&strPla[nCounti].rgbRed, 1, sizeof(BYTE), fpw);
		fwrite(&strPla[nCounti].rgbReserved, 1, sizeof(BYTE), fpw);
	}

	//������������
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
//----------------------�����Բ��֡�--------------------------------------------
//���������ú��������Ժ������ܣ�����ʽ����Ҫע�͵�

int main()
{
	char BmpName[LENGTH_NAME_BMP];        //�洢���ļ��ж�ȡ�����ļ���
	IMAGEDATA **IMG_DATA;

	IMG_DATA = (IMAGEDATA **)malloc(sizeof(IMAGEDATA*) * BMP_HEIGHT);
	for (int i = 0; i < BMP_HEIGHT; ++i)
	{
		IMG_DATA[i] = (IMAGEDATA *)malloc(sizeof(IMAGEDATA) * BMP_WIDTH);
	}

	if (IMG_DATA == NULL)
	{
		cout << "�ڴ治�㣡" << endl;
		exit(0);
	}
	for (int i = 0; i < BMP_HEIGHT; ++i)
	{
		if (IMG_DATA[i] == NULL)
		{
			cout << "�ڴ治�㣡" << endl;
			exit(0);
		}
	}

	Point *BrightPixel = (Point*)malloc(sizeof(Point) * BMP_WIDTH);
	if (BrightPixel == NULL)
	{
		std::cout << "�ڴ治�㣬�޷�����洢������ռ����飡" << std::endl;
	}

		if (!GetBmpNameByFile(BmpName))           //��ȡ�ļ�����������
		{
			exit(0);
		}
		InitialBmp(IMG_DATA);
		ReadBmp(BmpName,IMG_DATA);                     //��ȡbmp�ļ����ص�������

	//���Զ�ȡ�������ʽ��Ҫע�͵�
	//	for (int i = 40; i < 80; ++i)
	//	{
	//		for (int j = 30; j < 50; ++j)
	//		{
	//			cout << (int)IMG_DATA[i][j].blue << " ";
	//		}
	//	}

	//	cout << "�����½��ļ�����";
	//	cin >> BmpName;
		
		//�ҵ������㲢ȥ��
		
		BrightestPixel_And_LowerNoise(IMG_DATA,BrightPixel);
		memset(BmpName, 0, LENGTH_NAME_BMP);
		strcpy_s(BmpName, "AfterLowerNoise.bmp");
		cout << "���浽�ļ�" << BmpName << endl;
		SaveBmp(BmpName, IMG_DATA);
		
		//������߲���ƽͼƬ
		Flattern(IMG_DATA, BrightPixel);
		memset(BmpName, 0, LENGTH_NAME_BMP);
		strcpy_s(BmpName, "AfterFlattern.bmp");
		cout << "���浽�ļ�" << BmpName << endl;
		SaveBmp(BmpName, IMG_DATA);  

		//�Զ���ʼ���˵�
		//int *start_pos, *end_pos;
		//���ԣ������ó�ʼ���˵�Ϊ[300,0]��ÿ�κ������10������700����
		Assign_Weight(IMG_DATA);
		memset(BmpName, 0, LENGTH_NAME_BMP);
		strcpy_s(BmpName, "AfterAssignWeight.bmp");
		cout << "���浽�ļ�" << BmpName << endl;
		SaveBmp(BmpName, IMG_DATA);


	//�ͷ��ڴ�
	for (int i = 0; i < BMP_HEIGHT; ++i)
	{
		free(IMG_DATA[i]);
	}
	free(IMG_DATA);
	free(BrightPixel);

	return 0;
}

//-------------------------------------------------------------------------