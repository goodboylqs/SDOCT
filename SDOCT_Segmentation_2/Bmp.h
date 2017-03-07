#pragma once
#pragma once
//----------------------------【文件说明】-----------------------------
//文件名:Bmp.h
//功能：存储bmp文件结构信息，声明读取bmp文件的函数
//起始时间：2016.12.26  Lqs
//状态：
//		1）待补充双边滤波以及曲线拟合的函数声明2016.12.27 15：51
//关连文件：BmpRead.cpp
//说明：一定要指定正确的BMP_WIDTH和BMP_HEIGHT不然会导致文件损坏
//修改记录：
//最后修改时间：
//----------------------------------------------------------------------
//头文件包含部分
#include "stdlib.h"
#include "math.h"
#include <iostream>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef long LONG;

//位图文件头定义;
//其中不包含文件类型信息（由于结构体的内存结构决定，
//要是加了的话将不能正确读取文件信息）
typedef struct  tagBITMAPFILEHEADER {
	//WORD bfType;//文件类型，必须是0x424D，即字符“BM”
	DWORD bfSize;//文件大小
	WORD bfReserved1;//保留字
	WORD bfReserved2;//保留字
	DWORD bfOffBits;//从文件头到实际位图数据的偏移字节数
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
	DWORD biSize;//信息头大小
	LONG biWidth;//图像宽度
	LONG biHeight;//图像高度
	WORD biPlanes;//位平面数，必须为1
	WORD biBitCount;//每像素位数
	DWORD  biCompression; //压缩类型
	DWORD  biSizeImage; //压缩图像大小字节数
	LONG  biXPelsPerMeter; //水平分辨率
	LONG  biYPelsPerMeter; //垂直分辨率
	DWORD  biClrUsed; //位图实际用到的色彩数
	DWORD  biClrImportant; //本位图中重要的色彩数
}BITMAPINFOHEADER; //位图信息头定义

typedef struct tagRGBQUAD {
	BYTE rgbBlue; //该颜色的蓝色分量
	BYTE rgbGreen; //该颜色的绿色分量
	BYTE rgbRed; //该颜色的红色分量
	BYTE rgbReserved; //保留值
}RGBQUAD;//调色板定义

		 //----------------------【宏定义】----------------------------------------
#define PI 3.14159    //圆周率
#define LENGTH_NAME_BMP 80   //bmp文件名字的最大长度
#define BMP_WIDTH 512
#define BMP_HEIGHT 1024
		 //------------------------------------------------------------------------


		 //像素信息
typedef struct tagIMAGEDATA
{
	BYTE blue;
	BYTE green;
	BYTE red;
}IMAGEDATA;

struct Point
{
	int x, y;
};
//-------------------------------【函数声明】------------------------------
int GetBmpNameByFile(char BmpName[LENGTH_NAME_BMP]);
int ReadBmp(char BmpName[LENGTH_NAME_BMP], IMAGEDATA** IMG_DATA);
void InitialBmp(IMAGEDATA** IMG_DATA);
void BrightestPixel_And_LowerNoise(IMAGEDATA **IMG_DATA,Point *BrightPixel);
double* Fit(Point BrightPixel[BMP_WIDTH]);
void Flattern(IMAGEDATA **IMG_DATA, Point BrightPixel[BMP_WIDTH]);
void Assign_Weight(IMAGEDATA **IMG_DATA);
//-------------------------------------------------------------------------

