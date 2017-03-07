//------------------------��������Ϻ�����----------------------------
//���ܣ�������õ�ȥ��������������꣬��ö��ζ���ʽ��ʹ�ö���ʽ����״��������ֲ�������
//ʱ�䣺2017.1.8  00:16
//˵����
//״̬�����
//�޸ļ�¼��
//����޸�ʱ�䣺2017.3.6   06��00

#include <iostream>  
#include <vector>  
#include <cmath>  
#include"Bmp.h"
using namespace std;

//��С���������غ�������  
double sum(vector<double> Vnum, int n);
double MutilSum(vector<double> Vx, vector<double> Vy, int n);
double RelatePow(vector<double> Vx, int n, int ex);
double RelateMutiXY(vector<double> Vx, vector<double> Vy, int n, int ex);
void EMatrix(vector<double> Vx, vector<double> Vy, int n, int ex, double coefficient[]);
void CalEquation(int exp, double coefficient[]);
double F(double c[], int l, int m);
double Em[6][4];

//�����������ｫ������ϳɶ�������  
double* Fit(Point BrightPixel[BMP_WIDTH])
{
	int count_all = 0;
//	double arry1[5] = { 0,0.25,0,5,0.75 };
//	double arry2[5] = { 1,1.283,1.649,2.212,2.178 };

	//����������ȥ�������������
	for (int i = 0; i < BMP_WIDTH; ++i)
	{
		if (BrightPixel[i].y != -1)
			count_all++;
	}

	//��ʼ������
	double *arry1 = (double*)malloc(sizeof(double) * count_all);
	double *arry2 = (double*)malloc(sizeof(double) * count_all);
	memset(arry1, 0, count_all);
	memset(arry2, 0, count_all);

	//�������
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
	printf("��Ϸ���Ϊ��y = %lf + %lfx + %lfx^2 \n", coefficient[1], coefficient[2], coefficient[3]);
	return coefficient;
}
//�ۼ�  
double sum(vector<double> Vnum, int n)
{
	double dsum = 0;
	for (int i = 0; i<n; i++)
	{
		dsum += Vnum[i];
	}
	return dsum;
}
//�˻���  
double MutilSum(vector<double> Vx, vector<double> Vy, int n)
{
	double dMultiSum = 0;
	for (int i = 0; i<n; i++)
	{
		dMultiSum += Vx[i] * Vy[i];
	}
	return dMultiSum;
}
//ex�η���  
double RelatePow(vector<double> Vx, int n, int ex)
{
	double ReSum = 0;
	for (int i = 0; i<n; i++)
	{
		ReSum += pow(Vx[i], ex);
	}
	return ReSum;
}
//x��ex�η���y�ĳ˻����ۼ�  
double RelateMutiXY(vector<double> Vx, vector<double> Vy, int n, int ex)
{
	double dReMultiSum = 0;
	for (int i = 0; i<n; i++)
	{
		dReMultiSum += pow(Vx[i], ex)*Vy[i];
	}
	return dReMultiSum;
}
//���㷽������������  
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
//��ⷽ��  
void CalEquation(int exp, double coefficient[])
{
	for (int k = 1; k<exp; k++) //��Ԫ����  
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
	for (int l = exp - 1; l >= 1; l--)   //�ش����  
		coefficient[l] = (Em[l][exp + 1] - F(coefficient, l + 1, exp)) / Em[l][l];
}
//��CalEquation��������  
double F(double c[], int l, int m)
{
	double sum = 0;
	for (int i = l; i <= m; i++)
		sum += Em[l - 1][i] * c[i];
	return sum;
}