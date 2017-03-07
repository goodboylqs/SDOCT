//------------------------【曲线拟合函数】----------------------------
//功能：根据求得的去噪后的最亮点的坐标，求得二次多项式，使得多项式的形状与最亮点分布最相似
//时间：2017.1.8  00:16
//说明：
//状态：完成
//修改记录：
//最后修改时间：2017.3.6   06：00

#include <iostream>  
#include <vector>  
#include <cmath>  
#include"Bmp.h"
using namespace std;

//最小二乘拟合相关函数定义  
double sum(vector<double> Vnum, int n);
double MutilSum(vector<double> Vx, vector<double> Vy, int n);
double RelatePow(vector<double> Vx, int n, int ex);
double RelateMutiXY(vector<double> Vx, vector<double> Vy, int n, int ex);
void EMatrix(vector<double> Vx, vector<double> Vy, int n, int ex, double coefficient[]);
void CalEquation(int exp, double coefficient[]);
double F(double c[], int l, int m);
double Em[6][4];

//主函数，这里将数据拟合成二次曲线  
double* Fit(Point BrightPixel[BMP_WIDTH])
{
	int count_all = 0;
//	double arry1[5] = { 0,0.25,0,5,0.75 };
//	double arry2[5] = { 1,1.283,1.649,2.212,2.178 };

	//计算最亮点去除噪声后的数量
	for (int i = 0; i < BMP_WIDTH; ++i)
	{
		if (BrightPixel[i].y != -1)
			count_all++;
	}

	//初始化数组
	double *arry1 = (double*)malloc(sizeof(double) * count_all);
	double *arry2 = (double*)malloc(sizeof(double) * count_all);
	memset(arry1, 0, count_all);
	memset(arry2, 0, count_all);

	//填充数组
	count_all = 0;
	for (int i = 0; i < BMP_WIDTH; ++i)
	{
		if (BrightPixel[i].y != -1)
		{
			arry1[count_all] = BrightPixel[i].y;
			arry2[count_all++] = BrightPixel[i].x;
		}
	}

//	double coefficient[5];
	double * coefficient = (double *)malloc(sizeof(double) * count_all);
	memset(coefficient, 0, sizeof(double) * count_all);
	vector<double> vx, vy;
	for (int i = 0; i<count_all; i++)
	{
		vx.push_back(arry1[i]);
		vy.push_back(arry2[i]);
	}
	EMatrix(vx, vy, count_all, 3, coefficient);
	printf("拟合方程为：y = %lf + %lfx + %lfx^2 \n", coefficient[1], coefficient[2], coefficient[3]);
	return coefficient;
}
//累加  
double sum(vector<double> Vnum, int n)
{
	double dsum = 0;
	for (int i = 0; i<n; i++)
	{
		dsum += Vnum[i];
	}
	return dsum;
}
//乘积和  
double MutilSum(vector<double> Vx, vector<double> Vy, int n)
{
	double dMultiSum = 0;
	for (int i = 0; i<n; i++)
	{
		dMultiSum += Vx[i] * Vy[i];
	}
	return dMultiSum;
}
//ex次方和  
double RelatePow(vector<double> Vx, int n, int ex)
{
	double ReSum = 0;
	for (int i = 0; i<n; i++)
	{
		ReSum += pow(Vx[i], ex);
	}
	return ReSum;
}
//x的ex次方与y的乘积的累加  
double RelateMutiXY(vector<double> Vx, vector<double> Vy, int n, int ex)
{
	double dReMultiSum = 0;
	for (int i = 0; i<n; i++)
	{
		dReMultiSum += pow(Vx[i], ex)*Vy[i];
	}
	return dReMultiSum;
}
//计算方程组的增广矩阵  
void EMatrix(vector<double> Vx, vector<double> Vy, int n, int ex, double coefficient[])
{
	for (int i = 1; i <= ex; i++)
	{
		for (int j = 1; j <= ex; j++)
		{
			Em[i][j] = RelatePow(Vx, n, i + j - 2);
		}
		Em[i][ex + 1] = RelateMutiXY(Vx, Vy, n, i - 1);
	}
	Em[1][1] = n;
	CalEquation(ex, coefficient);
}
//求解方程  
void CalEquation(int exp, double coefficient[])
{
	for (int k = 1; k<exp; k++) //消元过程  
	{
		for (int i = k + 1; i<exp + 1; i++)
		{
			double p1 = 0;

			if (Em[k][k] != 0)
				p1 = Em[i][k] / Em[k][k];

			for (int j = k; j<exp + 2; j++)
				Em[i][j] = Em[i][j] - Em[k][j] * p1;
		}
	}
	coefficient[exp] = Em[exp][exp + 1] / Em[exp][exp];
	for (int l = exp - 1; l >= 1; l--)   //回代求解  
		coefficient[l] = (Em[l][exp + 1] - F(coefficient, l + 1, exp)) / Em[l][l];
}
//供CalEquation函数调用  
double F(double c[], int l, int m)
{
	double sum = 0;
	for (int i = l; i <= m; i++)
		sum += Em[l - 1][i] * c[i];
	return sum;
}