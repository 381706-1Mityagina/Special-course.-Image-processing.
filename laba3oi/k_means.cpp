#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// Особенности :
// В качестве метрики используется Евклидово расстояние
// Число кластеров заранее не известно и выбирается исследователем заранее 


// Структура с именем Cluster_params характеризуется:
// media ~ cреднее значение синего, зеленого и красного в кластере
// label ~ идентификатор кластера

struct Cluster_params{
	Vec3b media;
	int label;
};

// int get_area(int k, vector<Cluster_params> clusters, Mat res) {
// 	int **pixels = new int *[res.rows]; // ids
// 	for(int i = 0; i < res.rows; i++)
// 		pixels[i] = new int[res.cols];
// 	for(int i = 0; i < res.rows; i++)
// 		for(int j = 0; j < res.cols; j++)
// 				pixels[i][j] = -1;

// 	int S = 0;
// 	for(int i=0;i<res.rows;i++)
// 	{
// 		for(int j=0;j<res.cols;j++)
// 		{
// 			if (res.at<Vec3b>(i,j) == clusters[k].media)
// 				S += 1;
// 		}
// 	}
// 	std::cout << "S = " << S << "\n";
// }	

// Метод, который инициализирует кластеры
// k -> количество кластеров
// in -> входное изображение

// Создаем k кластеров, выбрав для каждого случайный пиксель, и инициализируем среднее значение этого k-го
// кластерa со значением BGR этого пикселя и связываем целое значение в качестве метки для кластера.

vector<Cluster_params>initClusters(int k, Mat in)
{
	vector<Cluster_params> clusters;
	srand(time(NULL));
	int label=-1; 

	for(int i = 0; i < k; i++) {
		Cluster_params clust;
		clust.media = in.at<Vec3b>(rand() % in.rows, rand() % in.cols); //инициализировать media ~ BGR выбранного пикселя
		label++;  
		clust.label = label; 
		clusters.push_back(clust); 
	}

	return clusters;
}

// Метод, который вычисляет евклидово расстояние
// Ввод: значение пикселя1 и значение пикселя2

int distEuclidea(Vec3b p1, Vec3b p2)
{
	return(int)sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2) + pow(p2[2] - p1[2], 2));
}

// Метод, который вычисляет новое среднее.
// Ввод:
// Входное изображение, двумерный массив, содержащий для каждого пикселя идентификатор, 
// кластер, к которому он принадлежит, и метка обрабатываемого кластера.
//
// Метод прокручивает исходное изображение и для каждого пикселя проверяет:
// принадлежит ли он обрабатываемому кластеру, да = проверяется,
// совпадает ли (i, j) с меткой обрабатываемого кластера.
// В положительном случае значение среднее сохраняется в векторе.
// Относим наблюдения к тем кластерам, чье среднее к ним ближе всего. 

Vec3b mediaCluster(Mat in, int **pixels, int label)
{
	vector<Vec3b> p; 
	for(int i = 0; i < in.rows; i++)
		for(int j = 0; j < in.cols; j++)
			if(pixels[i][j] == label)   // если метка совпадает, добавляем в грууппу пикселей
				p.push_back(in.at<Vec3b>(i,j)); 

	Scalar media, stdDev;
	// Вычисляет среднее и стандартное отклонение элементов массива.
	meanStdDev(p, media, stdDev);  // вычисляем значение среднего значения пикселей группы

	Vec3b bgr;

	bgr[0]= media[0];
	bgr[1] = media[1];
	bgr[2] = media[2];

	return bgr;
}


void kMeans(int k, Mat &in, Mat &out, int iter)
{
	vector<Cluster_params> clusters = initClusters(k,in);  

	int **pixels = new int *[in.rows]; // ids
	for(int i = 0; i < in.rows; i++)
		pixels[i] = new int[in.cols];
	for(int i = 0; i < in.rows; i++)
		for(int j = 0; j < in.cols; j++)
				pixels[i][j] = -1;

	int it = 0; 
	vector<Cluster_params> olds;
	while(it < iter)
	{ // пока не будет достигнуто максимальное количество итераций
		olds = clusters;  
		for(int i = 0; i < in.rows; i++){
			for(int j = 0; j < in.cols; j++){
				// Евклидово расстояние между (i, j) 0-го кластера
				int min = distEuclidea(in.at<Vec3b>(i,j), clusters[0].media); 
				int dis = 0; 
				// Label
				int c = 0; 
				for(int k = 1; k < clusters.size(); k++)
				{ // Теперь управляем расстоянием между пикселями и центроидами оставшихся кластеров
					dis = distEuclidea(in.at<Vec3b>(i,j), clusters[k].media);
					if(dis < min)
					{ 
						min = dis; 
						c = k;				
					}
				}
				pixels[i][j] = clusters[c].label; // Устанавливаем (i, j) пиксель как принадлежащий кластеру [c]
			}
		}
		
		for(int i = 0; i < clusters.size(); i++)
			clusters[i].media = mediaCluster(in, pixels, clusters[i].label);
		int stop = 0;
		for(int i = 0; i < clusters.size(); i++)
		{
			if(olds[i].media != clusters[i].media)  // алгоритм останавливается, когда значения media не меняются
				stop++;
		}
		if(stop == 0) 
			break;

		it++;
	}

	for(int i=0;i<in.rows;i++)
	{
		for(int j=0;j<in.cols;j++)
		{
			in.at<Vec3b>(i,j) = clusters[pixels[i][j]].media;
		}
	}

	imwrite("kmeans.jpg",in); 

	out = in.clone();

	// int S[5] = {0};

	// for (int i = 0; i < k; i++)
	// {
    //    S[i] = get_area(i, clusters, in);
	// }
}
