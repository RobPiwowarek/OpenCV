#include <stdio.h>
#include <opencv2\core\core.hpp>;
#include <opencv2\highgui\highgui.hpp>;
#include <opencv2\opencv.hpp>;

using namespace std;
using namespace cv;
void filter()
{
	Mat m = imread("eevee.png", CV_LOAD_IMAGE_COLOR);
	Mat org = imread("eevee.png", CV_LOAD_IMAGE_COLOR);
	imwrite("eevee2.png", m);
	namedWindow("filtered", WINDOW_AUTOSIZE);
	namedWindow("org", WINDOW_AUTOSIZE);

	Mat mask = (Mat_<uchar>(3,3)<<(uchar)1, (uchar)1, (uchar)1, (uchar)1, (uchar)1, (uchar)1, (uchar)1, (uchar)1, (uchar)1); 
	
	for (int y = 1; y < m.rows-2; y++)
		for (int x = 1; x < m.cols-2; x++) {
			uchar new_red_value = 0;
			uchar new_green_value = 0;
			uchar new_blue_value = 0;

			for (int y_temp = y-1; y_temp < y+mask.rows-1; y_temp++) {
				for (int x_temp = x-1; x_temp < x+mask.cols-1; x_temp++) {
					Vec3b rgb = m.at<Vec3b>(y_temp, x_temp);
					uchar red_temp = rgb[0];
					uchar green_temp = rgb[1];
					uchar blue_temp = rgb[2];
					new_red_value += (mask.at<uchar>(y_temp - (y-1), x_temp - (x-1))*red_temp)/(uchar)(mask.rows*mask.cols);
					new_green_value += (mask.at<uchar>(y_temp - (y-1), x_temp - (x-1))*green_temp)/(uchar)(mask.rows*mask.cols);
					new_blue_value += (mask.at<uchar>(y_temp - (y-1), x_temp - (x-1))*blue_temp)/(uchar)(mask.rows*mask.cols);
				}
			}
			m.at<Vec3b>(y,x)[0] = new_red_value;
			m.at<Vec3b>(y,x)[1] = new_green_value;
			m.at<Vec3b>(y,x)[2] = new_blue_value;
		}

	imwrite("eevee2.png", m);
	imshow("org", org);
	imshow("filtered", m);
	waitKey(0);
}