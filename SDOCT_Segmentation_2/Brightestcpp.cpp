#include"Bmp.h"
//------------------------【求每一列最亮点并去噪函数】----------------------------
//功能：求每一列最亮点，并将该点的亮度调到最高,如果最亮点明显不在最亮层，则标记出来并
//		在图片中显示时不将噪声点的亮度调到最高
//时间：2017.1.8  00:16
//说明：遍历图片矩阵，寻找每一列的最亮点，然后将最亮点的灰度值标记为255，保存到图片中，
//		则图片中的白点即每一列的最亮点，观察最亮点的位置是否与预期相符，即分布在最亮层附近
//状态：完成
//修改记录：
//最后修改时间：2017.2.28
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
		BrightPixel[i].x = index_x;               //记录最亮点坐标
		BrightPixel[i].y = index_y;
	}

	//去除噪声
	for (int i = 1; i < BMP_WIDTH; ++i)
	{
		if (BrightPixel[i].x - BrightPixel[i - 1].x > 20)
		{
//			std::cout << "噪声出现" << std::endl;
			int tmp_x = i;
			for (int j = tmp_x; BrightPixel[j].x - BrightPixel[tmp_x - 1].x > 20; ++j)
			{
//				std::cout << "去除噪声" << std::endl;
				BrightPixel[j].y = -1;
			}
		}
	}

	//在图片中标记最亮点
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
