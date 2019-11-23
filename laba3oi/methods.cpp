#include "methods.h"
#include "k_means.cpp"
#include <vector>
#include <math.h>

using namespace std;
using namespace cv;

// Otsu's
//-------------------------------------------------------------------------------------------------------

// Алгоритм предполагает , что изображение содержит два класса пикселей следующих би-модальных гистограмм 
// (передний план пикселей и фоновые пикселов), он затем вычисляет оптимальный порог , разделяющий два класса

float helper_in_Otsus_method(int hist[], int level, float v, int pixels_n)
// просто считаем коэффициенты ддля взвешенной суммы, по формулам из отчета
{
	long int total = pixels_n * v, m = 0, rem;
	float w0, w1, u0, u1;
	int n = 0, rem_pixels;

	for (int i = 0; i < level; i++)
	{
		m += i * hist[i];
		n += hist[i];
	}

	rem = total - m;
	rem_pixels = pixels_n - n;

	w0 = (1.0 * n) / (1.0 * pixels_n);
	w1 = (1.0 * rem) / (1.0 * pixels_n);
	u0 = (1.0 * m) / (1.0 * n);
	u1 = (1.0 * rem) / (1.0 * rem_pixels);

	// Метод Оцу ищет порог, уменьшающий дисперсию внутри класса, которая определяется 
	// как взвешенная сумма дисперсий двух классов:
	return (w0 * w1 * (u0 - u1) * (u0 - u1));
}

void Otsus_method(Mat &input, Mat &output) 
{
	long int u = 0;
	int hist[256], size = input.rows * input.cols, n, pixels_n = size, treshold = 0;
	float v, max = 0, x;
	for (int i; i< 256; i++)
		hist[i] = 0;
	cvtColor(input, input, CV_RGB2GRAY);

	output = input.clone();

	for (int i = 0; i < output.rows; i++)
	{
		for (int j = 0; j < output.cols; j++)
		{
			n = output.at<uchar>(i, j);  // значение пикселя
			u += n;
			hist[n]++;  // Вычисляем гистограмму
		}
	}

	v = (1.0 * u) / float(pixels_n);  // среднее значение 

	for (int i = 1; i < 255; i++)
	{
		x = helper_in_Otsus_method(hist, i, v, pixels_n);
		if (x > max)  // если полученная взвешенная сумма больше, чем имеющееся, то запоминаем ее 
					  // и значение порога treshold
		{
			max = x;
			treshold = i;
		}
	}

	for (int i = 0; i < output.rows; i++)
	{
		for (int j = 0; j < output.cols; j++)
		{
			if (output.at<uchar>(i, j) > treshold)
				output.at<uchar>(i, j) = 255;
			else output.at<uchar>(i, j) = 0;
		}
	}

	imwrite("otsu.jpg", output);
}
//-------------------------------------------------------------------------------------------------------

void k_means_method(Mat &input, Mat &output) 
{
	// in file "k_means.cpp"
}

// Canny
//-------------------------------------------------------------------------------------------------------
void Canny_method(Mat &input, Mat &output, double low_treshold, double upper_treshold) 
{
	if (input.type() != CV_8UC1)
		cvtColor(input, input, CV_RGB2GRAY);
	output = input.clone();
}

//-------------------------------------------------------------------------------------------------------
void regional_expansion_algorythm(Mat &input, Mat &output)
{
	if (input.type() != CV_8UC1)
		cvtColor(input, input, CV_RGB2GRAY);
	output = input.clone();
}

void Hough_transform(Mat &input, Mat &output) 
{
	if (input.type() != CV_8UC1)
		cvtColor(input, input, CV_RGB2GRAY);
	output = input.clone();
}