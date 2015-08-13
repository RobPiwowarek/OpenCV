#include <stdio.h>
#include <iostream>
#include "opencv2\core\core.hpp";
#include "opencv2\highgui\highgui.hpp";
#include "opencv2\opencv.hpp";

using namespace std;
using namespace cv;

void calculateDistance(){
	Mat img = imread("cam.jpg", CV_LOAD_IMAGE_COLOR);
	Mat dist;
	cvtColor(img, img, COLOR_BGR2HSV);

	const Mat cameraMatrix = (Mat_<float>(3,3) << 1.7917289417427517e+03, 0, 3.2059784509788682e+02,
											0, 1.7536521507193281e+03, 2.4935529542211555e+02, 
											0, 0, 1.0);

	const Mat distMatrix = (Mat_<float>(1,4) << -2.4083180166341303e-01, 1.7227746733297394e+01, -4.9043790553566370e-02, 1.7392455468230417e-02);
	undistort(img, dist, cameraMatrix, distMatrix);

	namedWindow("org", WINDOW_AUTOSIZE);
	namedWindow("undist", WINDOW_AUTOSIZE);
	
	for (int y = 0; y < dist.rows-1; y++)
		for (int x = 0; x < dist.cols-1; x++) {
			Vec3b intensity = dist.at<Vec3b>(y, x);
			uchar hue = intensity.val[0];
			uchar saturation = intensity.val[1];
			uchar value = intensity.val[2];

			if ((int)hue < 13 && (int)saturation > 180 && (int)value > 99) {
						dist.at<Vec3b>(y,x)[0] = 0;
						dist.at<Vec3b>(y,x)[1] = 0;
						dist.at<Vec3b>(y,x)[2] = 0;
			}
			else { 
				dist.at<Vec3b>(y,x)[0] = 255;
				dist.at<Vec3b>(y,x)[1] = 255;
				dist.at<Vec3b>(y,x)[2] = 255;				
			}

		}
		erode(dist, dist, Mat(), Point(-1,-1), 10);
		dilate(dist, dist, Mat(), Point(-1, -1),12);
		erode(dist, dist, Mat(), Point(-1, -1), 2);

		int x_max =-1, x_min=-1, y_max=-1, y_min=-1;

		// find max and min coords. of left-most and right-most black pixels.
		for (int x = 0; x < dist.cols-1; x++) 
		for (int y = 0; y < dist.rows-1; y++){
			Vec3b intensity = dist.at<Vec3b>(y, x);
			uchar saturation = intensity.val[1];

			if (saturation == 0){
				if (x_min == -1 && y_min == -1) {
					x_min = x;
					y_min = y;
				}
				else if (x_min != -1 && y_min != -1) {
						x_max = x;
						y_max = y;
					}
			}
			 else continue;
		}
		
		Mat p = (Mat_<float>(3,1) << x_min, y_min, 1.0f); // point in 3d
		Mat p2 = (Mat_<float>(3,1) << x_max, y_max, 1.0f); // point in 3d
		Mat v1 = cameraMatrix.inv()*p, v2 = cameraMatrix.inv()*p2; // 3d vector

		float v1_length = sqrt((float)(pow(v1.at<float>(0, 0),2)+pow(v1.at<float>(1, 0),2)+pow(v1.at<float>(2, 0),2)));
		float v2_length = sqrt((float)(pow(v2.at<float>(0, 0),2)+pow(v2.at<float>(1, 0),2)+pow(v2.at<float>(2, 0),2)));

		double angle = acos(v1.dot(v2)/(v1_length*v2_length));
		const double radius = 13.9/2;

		double distance = radius/tan(angle/2);
		cout << "Distance from camera: " << distance << endl;
	    imshow("undist", dist);
		imshow("org", img);
	waitKey(0);
}