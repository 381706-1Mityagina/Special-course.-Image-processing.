#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

int main( )
{

    Mat image, r, g, b, gray, min, max, average; 
    vector<Mat> channels(3); // вектор для каналов
    float MSE1, MSE2, MSE3, MSE4, N, sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0; // переменные для вычисления метрики

    image = imread("sample.jpg", CV_LOAD_IMAGE_COLOR); // загружаем картинку

    if(! image.data )
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    N = image.cols * image.rows; 

    split(image, channels); // разделяем картинку на каналы

    r = channels[0]; 
    g = channels[1];
    b = channels[2];

    // последний способ перевода в оттенки серого
    for (int i = 0; i < image.cols; i++) 
    {
        for (int j = 0; j < image.rows; j++) 
        {
            r.at<uchar>(Point(i,j)) *= 0.2952;  
            g.at<uchar>(Point(i,j)) *= 0.5547; 
            b.at<uchar>(Point(i,j)) *= 0.148 ;
        }
    }

    // Конвертироем RGB изображение в оттенки серого с помощью функции из openCV
    cvtColor(image, gray, CV_BGR2GRAY);

    // вычисляем сумму из формулы MSE
    for (int i = 0; i < N; i++)
    {
        sum1 += pow((gray.at<uchar>(i) - r.at<uchar>(i)), 2);
        sum2 += pow((gray.at<uchar>(i) - g.at<uchar>(i)), 2);
        sum3 += pow((gray.at<uchar>(i) - b.at<uchar>(i)), 2);
        sum4 += pow((gray.at<uchar>(i) - (b.at<uchar>(i) + g.at<uchar>(i) + r.at<uchar>(i))), 2);
    }

    MSE1 = sum1 / N;
    MSE2 = sum2 / N;
    MSE3 = sum3 / N;
    MSE3 = sum4 / N;

    std::cout << "MSE1 = " << MSE1 << "\n";
    std::cout << "MSE2 = " << MSE2 << "\n";
    std::cout << "MSE3 = " << MSE3 << "\n";
    std::cout << "MSE4 = " << MSE4 << "\n";

    //gray = merge(r, b, g, 0);

    namedWindow( "Original", CV_WINDOW_AUTOSIZE );
    imshow( "Original", image );

    namedWindow( "cv_function", CV_WINDOW_AUTOSIZE );
    imshow( "cv_function", gray );

    /*namedWindow( "R", CV_WINDOW_AUTOSIZE );
    imshow( "R", r );

    namedWindow( "G", CV_WINDOW_AUTOSIZE );
    imshow( "G", g );

    namedWindow( "B", CV_WINDOW_AUTOSIZE );
    imshow( "B", b );*/

    namedWindow( "sum", CV_WINDOW_AUTOSIZE );
    imshow( "sum", b + g + r );

    //namedWindow( "Result window", CV_WINDOW_AUTOSIZE );
    //imshow( "Result window", gray );*/

    waitKey(0);
    return 0;
}
