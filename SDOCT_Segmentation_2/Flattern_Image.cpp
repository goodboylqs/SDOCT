//------------------------【拍平图片函数】----------------------------
//功能：根据最亮点进行二次曲线拟合，并根据拟合的曲线拍平图片
//时间：2017.1.8  00:16
//说明：
//状态：完成
//修改记录：
//最后修改时间：
#include"Bmp.h"
int Cal(int x,double xishu[3])
{
	return round(xishu[2] * x * x + xishu[1] * x + xishu[0]);
}
void Flattern(IMAGEDATA **IMG_DATA,Point BrightPixel[BMP_WIDTH])
{
	//曲线拟合
	double *xishu,xishus[3];
	xishu = Fit(BrightPixel);
	xishus[0] = *(xishu + 1);
	xishus[1] = *(xishu + 2);
	xishus[2] = *(xishu + 3);
	std::cout << "xishu:" << xishus[0] << " " << xishus[1] 
	<< " " << xishus[2] << std::endl;

	//测试拟合效果
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

	//进行图片拉平，根据拟合的曲线，以-b/2a为最低点的横坐标进行拉平
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
		
		for (int j = height_distance; j < BMP_HEIGHT; ++j)   //每一列上下平移height_distance个单位
		{	
			IMG_DATA[j - height_distance][i] = IMG_DATA[j][i];
		}
	}
}