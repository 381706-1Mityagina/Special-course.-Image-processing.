#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std; 

void _gaussian_noise(Mat& image, int mean, float variance);
void _exponential_noise(Mat& image, float a);
void _salt_pepper_noise(Mat& image, int minimum, int maximum);