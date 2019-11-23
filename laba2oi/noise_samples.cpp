#include "/home/dariamityagina/cpp_test/laba2oi/noise_samples.h"

void _gaussian_noise(Mat& image, int mean, float variance) {
  Mat noise(image.size(), image.type());
  
  randn(noise, mean, variance); // Заполняет массив нормально распределенными случайными числами.
  add(noise, image, image); // добавляем шум

  imwrite("GaussianNoise.jpg", image);
  namedWindow( "Gaussian noise", WINDOW_NORMAL );
  resizeWindow("Gaussian noise", 350, 180);
  imshow("Gaussian noise", image);
}

// void _exponential_noise(Mat& image, float a) {
//   Mat noise(image.size(), image.type());
//   RNG rng;
//   double res, r;

//   for (int i = 0; i < noise.rows; ++i)
//     for (int j = 0; j < noise.cols; ++j)
//       if (rng.uniform(0, 100) >= 50)
//         for (int ch = 0; ch < 3; ++ch) {
//           r = rng.uniform((double)0, (double)1);  // возвращает равномерно распределенное целое случайное число из диапазона [a, b)
//           //res = log(1. / r * ) * a;   // через логарифм
//           res = exp(-a * r) * a;
//           noise.at<Vec3b>(i, j)[ch] = res;
//         }
//       else
//         noise.at<Vec3b>(i, j) = Vec3b(0, 0, 0);

//   image += noise;

//   imwrite("ExponentialNoise.jpg", image);
//   namedWindow( "Exponential noise", WINDOW_NORMAL );
//   resizeWindow("Exponential noise", 350, 180);
//   imshow("Exponential noise", image);
// }

void _salt_pepper_noise(Mat& image, int minimum, int maximum) {
  Mat noise(image.size(), image.type());
  for (int i = 0; i < image.rows; i++)
    for (int j = 0; j < image.cols; j++) 
      noise.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
  RNG rng;
  int r;

  for (int i = 0; i < image.rows; i++)
    for (int j = 0; j < image.cols; j++)
      if (rng.uniform(0, 100) >= 50)        
        for (int ch = 0; ch < 3; ++ch) {
          r = rng.uniform(0, 256);
          if (r < minimum) noise.at<Vec3b>(i, j)[ch] = minimum;
          if (r > maximum) noise.at<Vec3b>(i, j)[ch] = maximum;
        }

  image += noise;

  imwrite("SaltPepperNoise.jpg", image);
  namedWindow( "Salt&Pepper noise", WINDOW_NORMAL );
  resizeWindow("Salt&Pepper noise", 350, 180);
  imshow("Salt&Pepper noise", image);
}
