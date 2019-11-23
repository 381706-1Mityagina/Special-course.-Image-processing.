#include "methods.cpp"

int main()
{
	Mat image, otsu, k_means;
    image = imread("ball.jpg", CV_LOAD_IMAGE_COLOR);

    namedWindow( "Normal", WINDOW_NORMAL );
    resizeWindow("Normal", 350, 180);
    imshow( "Normal", image );

// Otsu's
// ------------------------------------------------------------------
    Otsus_method(image, otsu);

    namedWindow( "Otsu", WINDOW_NORMAL );
    resizeWindow("Otsu", 350, 180);
    imshow( "Otsu", otsu);
// ------------------------------------------------------------------
    int segments_num = 5;
    kMeans(segments_num, image, k_means, 10);

    namedWindow( "K-means", WINDOW_NORMAL );
    resizeWindow("K-means", 350, 180);
    imshow( "K-means", k_means);

    waitKey();

	return 0;
}