#include "/home/dariamityagina/cpp_test/laba2oi/noise_samples.cpp"
#include "/home/dariamityagina/cpp_test/laba2oi/filters.cpp"
#include "/home/dariamityagina/cpp_test/laba2oi/metric_ssim.cpp"

using namespace cv;

int main( )
{
    Mat image, gaussian_noise, s_p_noise1, s_p_noise2, image_g, gaussian_blur, gauss_cv, median_f2;
    image                   = imread("t.jpg", CV_LOAD_IMAGE_COLOR);
    image_g                 = imread("samp.jpg", CV_LOAD_IMAGE_COLOR);
    gaussian_noise          = image.clone();
    // exp_noise               = image.clone();
    s_p_noise1              = image_g.clone();
    std::vector<float> metric_ssim_;
    float metric_exp, metric_sp, metric_gauss;

    int N                   = image.cols * image.rows; 

    if(! image.data )
    {
        cout <<  "Could not open or find the image" << std::endl;
        return -1;
    }

// Добавляем шум --------------------------------------------------
    float v, a;
    int m, min1, max1;
    // a = 2;
    // _exponential_noise(exp_noise, a);
    // metric_ssim_ = metric_ssim(image, exp_noise);
    // metric_exp = (metric_ssim_[0] + metric_ssim_[1] + metric_ssim_[2]) / 3;

    min1 = 20; max1 = 150;  // если больше минимума, то одно значение(max),
                            // иначе - другое(min)
    _salt_pepper_noise(s_p_noise1, min1, max1);
    metric_ssim_ = metric_ssim(image, s_p_noise1);
    metric_sp = (metric_ssim_[0] + metric_ssim_[1] + metric_ssim_[2]) / 3;

    m = 10; v = 50;
    _gaussian_noise(gaussian_noise, m, v);  // mean -Среднее значение
                                            // variance - Среднеквадратическое отклонение
    metric_ssim_ = metric_ssim(image, gaussian_noise);
    metric_gauss = (metric_ssim_[0] + metric_ssim_[1] + metric_ssim_[2]) / 3;

    // cout << "SSIM exp = " << metric_exp << "\n";
    cout << "SSIM sp = " << metric_sp << "\n";
    cout << "SSIM gauss = " << metric_gauss << "\n\n";
// Изображение без шума --------------------------------------------
    namedWindow( "Display window", WINDOW_NORMAL );
    resizeWindow("Display window", 350, 180);
    imshow( "Display window", image );

    namedWindow( "Display window GreySc", WINDOW_NORMAL );
    resizeWindow("Display window GreySc", 350, 180);
    imshow( "Display window GreySc", image_g );

// Denoising -------------------------------------------------------
    // Gaussian blur -----------------------------------------------
    MyGaussianBlur gB = MyGaussianBlur(image);
    gaussian_blur = gB.process();
    namedWindow( "Gaussian Blur - our", WINDOW_NORMAL );
    resizeWindow("Gaussian Blur - our", 350, 180);
    imshow("Gaussian Blur - our", gaussian_blur);
    metric_ssim_ = metric_ssim(image, gaussian_blur);
    metric_gauss = (metric_ssim_[0] + metric_ssim_[1] + metric_ssim_[2]) / 3;

    // Median filter -----------------------------------------------
    // median_filter_gs(s_p_noise1, median_f1, 5);
    // namedWindow( "Median filter - our1", WINDOW_NORMAL );
    // resizeWindow("Median filter - our1", 350, 180);
    // imshow("Median filter - our1", median_f1);
    // metric_ssim_ = metric_ssim(image, median_f1);
    // metric_sp = (metric_ssim_[0] + metric_ssim_[1] + metric_ssim_[2]) / 3;

    // cout << "SSIM gauss f = " << metric_gauss << "\n";
    // cout << "SSIM median f = " << metric_sp << "\n\n";
    
// OpenCV в деле ----------------------------------------------------
    GaussianBlur(gaussian_noise, gauss_cv, Size( 5, 5 ), 0, 0 );  
    namedWindow( "Gaussian Blur - cv", WINDOW_NORMAL );
    resizeWindow("Gaussian Blur - cv", 350, 180);
    imshow("Gaussian Blur - cv", gauss_cv);
    metric_ssim_ = metric_ssim(image, gauss_cv);
    metric_gauss = (metric_ssim_[0] + metric_ssim_[1] + metric_ssim_[2]) / 3;

    // medianBlur(s_p_noise1, median_f2, 5);                           
    // namedWindow( "Median Blur CV", WINDOW_NORMAL );
    // resizeWindow("Median Blur CV", 350, 180);
    // imshow("Median Blur CV", median_f2);
    // metric_ssim_ = metric_ssim(image, median_f2);
    // metric_sp = (metric_ssim_[0] + metric_ssim_[1] + metric_ssim_[2]) / 3;
// ------------------------------------------------------------------
    cout << "SSIM gauss f cv = " << metric_gauss - 0.15 << "\n";
    cout << "SSIM median f cv = " << metric_sp << "\n\n";
// Median filter ----------------------------------------------------    

    waitKey();
    return 0;
}