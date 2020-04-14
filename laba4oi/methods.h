#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cmath>
#include <math.h>
#include <chrono>
#include <random>
#include <vector>

using namespace cv;
using namespace std; 

#define PI 3.1415926

//-----------------------------------------------------------------------------------
class MyGaussianBlur
{
private:
    Mat source;
    Mat result;

    Vec3b processPixel(int i, int j);   // Vec3b - аббревиатура для «вектора с 3-байтовыми записями»
                                        // Vec3b это один пиксель RGB (или лучше BGR). Итак, Vec3bVar [0]
                                        // может быть частью синего цвета, [1] зеленого и [2] красного.
public:
    MyGaussianBlur(Mat input);

    Mat process();
};

// Обычно матрица заполняется по нормальному (гауссовому закону).
// Ниже приведена матрица размытия 5x5 заполненная по закону Гауссовского распределения.
//const float Mask1[5][5] = {
//            {0.003, 0.013, 0.022, 0.013, 0.003},
//            {0.013, 0.059, 0.097, 0.059, 0.013},
//            {0.022, 0.097, 0.159, 0.097, 0.022},
//            {0.013, 0.059, 0.097, 0.059, 0.013},
//            {0.003, 0.13, 0.022, 0.013, 0.003}
//};
 const float Mask1[3][3] = {
             {0.0625, 0.125, 0.0625},
             {0.125, 0.25, 0.125},
             {0.0625, 0.125, 0.0625},
     };

MyGaussianBlur::MyGaussianBlur(Mat input)
{
    source = input;
    result = Mat(source.rows, source.cols, CV_8UC3, 0.0);   // CV_8UC3 представляет собой 8-разрядную целую
                                                            // матрицу/изображение без знака с тремя каналами.
}

Vec3b MyGaussianBlur::processPixel(int x, int y) {
    Point p = Point(x,y);
    Vec3b pixel = source.at<Vec3b>(p);

    for (int i = 0; i < 3; ++i) {  // по числу каналов
        int sum = 0;
        for (int j = 0; j < 3; ++j) {                        // Смотрим окрестность ядра
            for (int k = 0; k < 3; ++k) {
                int x_idx = x + j - 2;
                int y_idx = y + k - 2;

                if (x_idx < 0 || x_idx > result.cols - 1)    // Проверка на выход за границы изображения
                    x_idx = x;                               // Стоит упомянуть о граничных условиях.
                                                             // (эта проблема актуальна для всех матричных фильтров).
                                                             // У верхнего левого пикселя не существует «соседа» с
                                                             // права от него, следовательно, нам не на что умножать коэффициент матрицы.

                if (y_idx < 0 || y_idx > result.rows - 1)
                    y_idx = y;

                sum += source.at<Vec3b>(Point(x_idx, y_idx)).val[i] * Mask1[j][k];
            }
        }
        int newValue = sum;
        pixel.val[i] = newValue;
    }
    return pixel;
}

Mat MyGaussianBlur::process() {
    for (int i = 0; i < result.cols; ++i) {
        for (int j = 0; j < result.rows; ++j) {
            Point p = Point(i,j);
            Vec3b pixel = processPixel(i, j);
            result.at<Vec3b>(p) = pixel;
        }
    }
    return result;
}

//-----------------------------------------------------------------------------------
// Алгоритм вычисления порога бинаризации для полутонового изображения.
// Позволяет разделить пиксели двух классов ("полезные" и "фоновые"),
// рассчитывая порог.
float helper_in_Otsus_method(int hist[], int level, float v, int pixels_n);
Mat Otsus_method(Mat &input, Mat &output);

//-----------------------------------------------------------------------------------
Mat Sobel(Mat input);

//-----------------------------------------------------------------------------------
Mat Gauss(Mat input);

//-----------------------------------------------------------------------------------
Mat Gray_sc(Mat input);
//-----------------------------------------------------------------------------------
Mat Linear_contrast(Mat input);
