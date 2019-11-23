#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cmath>
#include <math.h>
#include <chrono>
#include <random>
#include <vector>

#define PI 3.1415926

using namespace cv;
using namespace std;

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
const float Mask1[5][5] = {
            {0.003, 0.013, 0.022, 0.013, 0.003},
            {0.013, 0.059, 0.097, 0.059, 0.013},
            {0.022, 0.097, 0.159, 0.097, 0.022},
            {0.013, 0.059, 0.097, 0.059, 0.013},
            {0.003, 0.13, 0.022, 0.013, 0.003}
    };
// const float Mask2[3][3] = {
//             {0.0625, 0.125, 0.0625},
//             {0.125, 0.25, 0.125},
//             {0.0625, 0.125, 0.0625},
//     };

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
        for (int j = 0; j < 5; ++j) {                        // Смотрим окрестность ядра
            for (int k = 0; k < 5; ++k) {
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

// --------------------------------------------------------------------------------------------------------------------- //
// ------------------------------------------------- Another filter ---------------------------------------------------- //
// --------------------------------------------------------------------------------------------------------------------- //
// Просто сортировка
// int insertionSort(int med[])
// {
//     int temp, i, j;
//     for (i = 0; i < 9; i++) {
//         temp = med[i];
//         for (j = i - 1; j >= 0 && temp < med[j]; j--) {
//             med[j + 1] = med[j];
//         }
//         med[j + 1] = temp;
//     }
//     return med[4];
// }

/*Mat _median_filter(Mat source) {
    Mat median;
    for (int x = 1; x < source.rows - 1; x++) {
        for (int y = 1; y < source.cols - 1; y++) {
            int kernelMedian[9], k = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    kernelMedian[k] = source.at<uchar>(x + i, y + j);
                    k++;
                }
            }
            median.at<uchar>(x, y) = insertionSort(kernelMedian);
        }
    }
    return median;
}*/
// Проверка на выход за границы, используется в 140 строчке
// bool inBounds(int r, int c, int rows, int cols) {
//     return (r >= 0 && r < rows) && (c >= 0 && c < cols);
// }

// Идея : выбирает из группы входных значений среднее и выдает на выход.
// void median_filter_gs(Mat& input, Mat& output, int kernelSize)
// {
//     output = input.clone();
//     vector<int> newPixelValue;

//     for (int i = 0; i < input.rows; i++)
//         for (int j = 0; j < input.cols; j++)
//         {
//             newPixelValue.clear();
//             for (int x = -kernelSize / 2 ; x <= kernelSize / 2; x++)
//                 for (int y = -kernelSize / 2; y <= kernelSize / 2; y++)
//                 {
//                     if (!inBounds(x + i, y + j, input.rows, input.cols)) { 
//                         newPixelValue.push_back(0);
//                     }
//                     else {
//                     newPixelValue.push_back(input.at<uchar>(i + x, j + y));
//                     }
//                 }
//             sort(begin(newPixelValue), end(newPixelValue)); // Сортируем вектор
//             output.at<uchar>(i, j) = newPixelValue[newPixelValue.size()/2]; 
//             // Берем среднее значение (~ size / 2 - так как 
//             // вектор отсортирован) -> среднее значение располагается в серединке
//         }
// }
/*
// Просто сортировка
void insertionSort(uchar* values, int size) {
    for (int i = 1; i < size; i++) {
        int j = i;
        while (j != 0 && values[j - 1] > values[j]) {
            uchar temp = values[j];
            values[j] = values[j - 1];
            values[j - 1] = temp;
            j--;
        }
    }
}

int median(uchar* values, int size) {
    insertionSort(values, size);
    return values[size / 2];
    //return values[size];
}

// Идея : выбирает из группы входных значений среднее и выдает на выхход.
void medianFilter(cv::Mat& src, cv::Mat& dst, int kernelSize) {
    uchar* values = new uchar[kernelSize * kernelSize];
    for (int r = 0; r < src.rows; r++) {
        for (int c = 0; c < src.cols; c++) {
            int halfKernelSize = kernelSize / 2;
            for (int i = -halfKernelSize, index = 0; i <= halfKernelSize; i++) {
                for (int j = -halfKernelSize; j <= halfKernelSize; j++, index++) {
                    if (!inBounds(r + i, c + j, src.rows, src.cols)) { 
                        values[index] = 0;
                    }
                    else {
                        values[index] = src.at<uchar>(r + i, c + j);
                    }
                }
            }
            dst.at<uchar>(r, c) = median(values, kernelSize * kernelSize);
        }
    }
    delete[] values;
}
*/
