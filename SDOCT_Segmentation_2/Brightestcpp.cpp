#include"Bmp.h"
//------------------------����ÿһ�������㲢ȥ�뺯����----------------------------
//���ܣ���ÿһ�������㣬�����õ�����ȵ������,������������Բ��������㣬���ǳ�����
//		��ͼƬ����ʾʱ��������������ȵ������
//ʱ�䣺2017.1.8  00:16
//˵��������ͼƬ����Ѱ��ÿһ�е������㣬Ȼ��������ĻҶ�ֵ���Ϊ255�����浽ͼƬ�У�
//		��ͼƬ�еİ׵㼴ÿһ�е������㣬�۲��������λ���Ƿ���Ԥ����������ֲ��������㸽��
//״̬�����
//�޸ļ�¼��
//����޸�ʱ�䣺2017.2.28
void BrightestPixel_And_LowerNoise(IMAGEDATA **IMG_DATA,Point *BrightPixel)
{
	int index_x = 0, index_y = 0,max_pixel;
	for (int i = 0; i < BMP_WIDTH; ++i)
	{
		max_pixel = IMG_DATA[0][i].blue;
		for (int j = 0; j < BMP_HEIGHT; ++j)
		{
			if (max_pixel < IMG_DATA[j][i].blue)
			{
				max_pixel = IMG_DATA[j][i].blue;
				index_x = j;
				index_y = i;
			}
		}
		std::cout << index_x << "," << index_y << std::endl;
		BrightPixel[i].x = index_x;               //��¼����������
		BrightPixel[i].y = index_y;
	}

	//ȥ������
	for (int i = 1; i < BMP_WIDTH; ++i)
	{
		if (BrightPixel[i].x - BrightPixel[i - 1].x > 20)
		{
//			std::cout << "��������" << std::endl;
			int tmp_x = i;
			for (int j = tmp_x; BrightPixel[j].x - BrightPixel[tmp_x - 1].x > 20; ++j)
			{
//				std::cout << "ȥ������" << std::endl;
				BrightPixel[j].y = -1;
			}
		}
	}

	//��ͼƬ�б��������
	for (int i = 0; i < BMP_WIDTH; ++i)
	{
		if (BrightPixel[i].y != -1)
		{
			IMG_DATA[BrightPixel[i].x][BrightPixel[i].y].blue = 255;
			IMG_DATA[BrightPixel[i].x][BrightPixel[i].y].green = 255;
			IMG_DATA[BrightPixel[i].x][BrightPixel[i].y].red = 255;
		}
	}
	//std::cout << count;
	Fit(BrightPixel);
}
