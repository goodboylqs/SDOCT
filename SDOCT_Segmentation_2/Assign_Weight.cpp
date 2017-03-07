//------------------------【给边赋予权重】----------------------------
//功能：根据亮度差来给边赋予权重
//时间：2017.1.8  00:16
//说明：wab  = 2 − (g a  + gb )+ wmin , where	(1)

//		wab	is the weight assigned to the edge connecting nodes a and b,

//		ga	is the vertical gradient of the image at node a,

//		gb	is the vertical gradient of the image at node b,

//		wmin	is  the  minimum  weight  in  the  graph, a  small  positive  number  added  for
//		system stabilization.
//状态：
//修改记录：
//最后修改时间：
#include"Bmp.h"
//---------------------------【Assign_Weight函数】-----------------------------------
//功能：根据亮度差异，给边赋值权重，并找出权重和最小的边，在图中以蓝色标记
//起始时间：2017.3.6   13：39
//说明：目前为未完成版，由于自动初始化断点还没有实现，因此暂时自定断点和区间
//状态：未完成
//修改记录：
//最后修改时间：2017.3.6   13：40
void Assign_Weight(IMAGEDATA **IMG_DATA)
{
	float ga = 0.0, gb = 0.0, wmin, wab = 0.0;
	wmin = 0.00005;

	int Pixel_a, Pixel_b, max;
	int i = 600, j = 0;
	int max_x, max_y;
	float sum_weight = 0.0;
	int count = 0;
	while (i >=500 && i < 700 && j >= 0 && j < BMP_WIDTH)
	{
		std::cout << "i:" << i << ",j:" << j << std::endl;
		count++;
		Pixel_a = IMG_DATA[i][j].blue;
		//在图片中对点a进行标记
		IMG_DATA[i][j].blue = 255;
		IMG_DATA[i][j].red = 0;
		IMG_DATA[i][j].green = 0;

		//寻找亮度差异最大的邻接点
		//注意：由于方向从左到右，因此可以忽略寻找除右边三个点之外的其它点
		int max = -1000;
		if (j + 1 < BMP_WIDTH)
		{
			if (i - 1 >= 0)
			{
				Pixel_b = IMG_DATA[i - 1][j + 1].blue;
				max = abs(Pixel_b - Pixel_a);
				max_x = i - 1;
				max_y = j + 1;
			}
			if (max < abs(IMG_DATA[i][j + 1].blue - Pixel_a))
			{
				Pixel_b = IMG_DATA[i][j + 1].blue;
				max = abs(Pixel_b - Pixel_a);
				max_x = i;
				max_y = j + 1;
			}
			if (i + 1 < BMP_HEIGHT && max < abs(IMG_DATA[i + 1][j + 1].blue))
			{
				Pixel_b = IMG_DATA[i + 1][j + 1].blue;
				max = abs(Pixel_b - Pixel_a);
				max_x = i + 1;
				max_y = j + 1;
			}
		}
		else
		{
			i += 10;
			j = 0;
		}
		//在图片中对点b进行标记
		IMG_DATA[max_x][max_y].blue = 255;
		IMG_DATA[max_x][max_y].green = 0;
		IMG_DATA[max_x][max_y].red = 0;

		//计算权重
		ga = (float)max / Pixel_a;
		gb = (float)max / Pixel_b;
		wab = 2 - (ga + gb) / 2 + wmin;

		sum_weight += wab;

		i = max_x;     //坐标迭代，这一次寻找到的点作为下一次的基准点
		j = max_y;
	}
	std::cout << "最小权重和：" << sum_weight << std::endl;
	std::cout << "count" << count << std::endl;
	
}
