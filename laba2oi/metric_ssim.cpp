#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <vector>

using namespace cv;
using namespace std;

// Индекс структурного сходства.
// Метод полного сопоставления.

// 1 ~ полное сходство образцов

vector<float> metric_ssim(Mat &a, Mat &b)
{
	int N = a.rows * a.cols;
	double ma[3], mb[3];
	double sigma_a[3], sigma_b[3], cov[3];
	float l[3], s[3], c[3], constant;
	std::vector<float> out;

	constant = 0.02;

// Sum
	for (int i = 0; i < a.rows; i++) 
	{
		for (int j = 0; j < a.cols; j++) 
		{
			for (int ch= 0; ch < 3; ch++)
			{
				ma[ch] += a.at<Vec3b>(i, j)[ch];
				mb[ch] += b.at<Vec3b>(i, j)[ch];
			}
		}
	}

// Intensity
	for (int ch = 0; ch < 3; ch++)
	{
		ma[ch] /= N;
		mb[ch] /= N;
	}

// Sigmas
	for (int i = 0; i < a.rows; i++) 
	{
		for (int j = 0; j < a.cols; j++) 
		{
			for (int ch = 0; ch < 3; ch++)
			{
				sigma_a[ch] += powf(a.at<Vec3b>(i, j)[ch] - ma[ch], 2);
				sigma_b[ch] += powf(b.at<Vec3b>(i, j)[ch] - mb[ch], 2);
				cov[ch] += (a.at<Vec3b>(i, j)[ch] - ma[ch]) * (b.at<Vec3b>(i, j)[ch] - mb[ch]);
			}
		}
	}
// Contrast + main part
	for (int ch  = 0; ch < 3; ch++)
	{
		sigma_a[ch] /= (N - 1);
		sigma_b[ch] /= (N - 1);
		cov[ch] /= N;

		l[ch] = (2 * ma[ch] * mb[ch] + constant) / (powf(ma[ch], 2) + powf(ma[ch], 2) + constant);
		c[ch] = (2 * sqrt(sigma_a[ch] * sigma_b[ch]) + constant) / (sigma_a[ch] + sigma_b[ch] + constant);
		s[ch] = (cov[ch] + constant) / (sqrt(sigma_a[ch] * sigma_b[ch]) + constant);

		out.push_back(l[ch] * c[ch] * s[ch]);
	}
	return out;
}