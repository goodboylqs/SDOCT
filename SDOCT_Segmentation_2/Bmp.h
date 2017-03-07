#pragma once
#pragma once
//----------------------------���ļ�˵����-----------------------------
//�ļ���:Bmp.h
//���ܣ��洢bmp�ļ��ṹ��Ϣ��������ȡbmp�ļ��ĺ���
//��ʼʱ�䣺2016.12.26  Lqs
//״̬��
//		1��������˫���˲��Լ�������ϵĺ�������2016.12.27 15��51
//�����ļ���BmpRead.cpp
//˵����һ��Ҫָ����ȷ��BMP_WIDTH��BMP_HEIGHT��Ȼ�ᵼ���ļ���
//�޸ļ�¼��
//����޸�ʱ�䣺
//----------------------------------------------------------------------
//ͷ�ļ���������
#include "stdlib.h"
#include "math.h"
#include <iostream>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef long LONG;

//λͼ�ļ�ͷ����;
//���в������ļ�������Ϣ�����ڽṹ����ڴ�ṹ������
//Ҫ�Ǽ��˵Ļ���������ȷ��ȡ�ļ���Ϣ��
typedef struct  tagBITMAPFILEHEADER {
	//WORD bfType;//�ļ����ͣ�������0x424D�����ַ���BM��
	DWORD bfSize;//�ļ���С
	WORD bfReserved1;//������
	WORD bfReserved2;//������
	DWORD bfOffBits;//���ļ�ͷ��ʵ��λͼ���ݵ�ƫ���ֽ���
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
	DWORD biSize;//��Ϣͷ��С
	LONG biWidth;//ͼ����
	LONG biHeight;//ͼ��߶�
	WORD biPlanes;//λƽ����������Ϊ1
	WORD biBitCount;//ÿ����λ��
	DWORD  biCompression; //ѹ������
	DWORD  biSizeImage; //ѹ��ͼ���С�ֽ���
	LONG  biXPelsPerMeter; //ˮƽ�ֱ���
	LONG  biYPelsPerMeter; //��ֱ�ֱ���
	DWORD  biClrUsed; //λͼʵ���õ���ɫ����
	DWORD  biClrImportant; //��λͼ����Ҫ��ɫ����
}BITMAPINFOHEADER; //λͼ��Ϣͷ����

typedef struct tagRGBQUAD {
	BYTE rgbBlue; //����ɫ����ɫ����
	BYTE rgbGreen; //����ɫ����ɫ����
	BYTE rgbRed; //����ɫ�ĺ�ɫ����
	BYTE rgbReserved; //����ֵ
}RGBQUAD;//��ɫ�嶨��

		 //----------------------���궨�塿----------------------------------------
#define PI 3.14159    //Բ����
#define LENGTH_NAME_BMP 80   //bmp�ļ����ֵ���󳤶�
#define BMP_WIDTH 512
#define BMP_HEIGHT 1024
		 //------------------------------------------------------------------------


		 //������Ϣ
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
//-------------------------------������������------------------------------
int GetBmpNameByFile(char BmpName[LENGTH_NAME_BMP]);
int ReadBmp(char BmpName[LENGTH_NAME_BMP], IMAGEDATA** IMG_DATA);
void InitialBmp(IMAGEDATA** IMG_DATA);
void BrightestPixel_And_LowerNoise(IMAGEDATA **IMG_DATA,Point *BrightPixel);
double* Fit(Point BrightPixel[BMP_WIDTH]);
void Flattern(IMAGEDATA **IMG_DATA, Point BrightPixel[BMP_WIDTH]);
void Assign_Weight(IMAGEDATA **IMG_DATA);
//-------------------------------------------------------------------------

