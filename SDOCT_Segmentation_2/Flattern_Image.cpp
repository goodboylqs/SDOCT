//------------------------����ƽͼƬ������----------------------------
//���ܣ�������������ж���������ϣ���������ϵ�������ƽͼƬ
//ʱ�䣺2017.1.8  00:16
//˵����
//״̬�����
//�޸ļ�¼��
//����޸�ʱ�䣺
#include"Bmp.h"
int Cal(int x,double xishu[3])
{
	return round(xishu[2] * x * x + xishu[1] * x + xishu[0]);
}
void Flattern(IMAGEDATA **IMG_DATA,Point BrightPixel[BMP_WIDTH])
{
	//�������
	double *xishu,xishus[3];
	xishu = Fit(BrightPixel);
	xishus[0] = *(xishu + 1);
	xishus[1] = *(xishu + 2);
	xishus[2] = *(xishu + 3);
	std::cout << "xishu:" << xishus[0] << " " << xishus[1] 
	<< " " << xishus[2] << std::endl;

	//�������Ч��
	/*
	for (int i = 0; i < BMP_WIDTH; ++i)
	{
		int y = Cal(i, xishus) / 2;
		if (y > 1024 || y < 1)continue;
		IMG_DATA[y - 1][i].blue = 255;
		IMG_DATA[y - 1][i].green = 255;
		IMG_DATA[y - 1][i].red = 255;
		if(y > 700 && y < 800)
		std::cout << y << "," << i << std::endl;
	}
	*/

	//����ͼƬ��ƽ��������ϵ����ߣ���-b/2aΪ��͵�ĺ����������ƽ
	double lowest_x = xishus[1] / (2 * xishus[2] * (-1));
	double lowest_y = Cal(int(lowest_x), xishus) / 2;
//	std::cout << lowest_x << "," << lowest_y << std::endl;
	for (int i = 0; i < BMP_WIDTH; ++i)
	{
		int y = Cal(i, xishus) / 2;
		if (y > 1024 || y < 1)continue;
		IMG_DATA[y - 1][i].blue = 255;
		IMG_DATA[y - 1][i].green = 255;
		IMG_DATA[y - 1][i].red = 255;

//		std::cout << y << "," << lowest_y << std::endl;
		int height_distance = abs(y - (int)lowest_y);
//		std::cout << height_distance << std::endl;
		
		for (int j = height_distance; j < BMP_HEIGHT; ++j)   //ÿһ������ƽ��height_distance����λ
		{	
			IMG_DATA[j - height_distance][i] = IMG_DATA[j][i];
		}
	}
}