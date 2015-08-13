#include <stdio.h>
#include "opencv2\core\core.hpp";
#include "opencv2\highgui\highgui.hpp";
#include "opencv2\opencv.hpp";

using namespace std;
using namespace cv;
int detect() {
	Mat m = imread("marker.jpg", CV_LOAD_IMAGE_COLOR);
	const Mat org = imread("marker.jpg", CV_LOAD_IMAGE_COLOR);
	cvtColor(m, m, COLOR_BGR2HSV);
	imwrite("marker2.jpg", m);
	namedWindow("window", WINDOW_AUTOSIZE);
	namedWindow("org", WINDOW_AUTOSIZE);
	
	for (int y = 0; y < m.rows-1; y++)
		for (int x = 0; x < m.cols-1; x++) {
			Vec3b intensity = m.at<Vec3b>(y, x);
			uchar hue = intensity.val[0];
			uchar saturation = intensity.val[1];
			uchar value = intensity.val[2];

			if ((int)hue < 5 && (int)saturation > 185 && (int)value > 110) {
						m.at<Vec3b>(y,x)[0] = 0;
						m.at<Vec3b>(y,x)[1] = 0;
						m.at<Vec3b>(y,x)[2] = 0;
			}
			else { 
				m.at<Vec3b>(y,x)[0] = 255;
				m.at<Vec3b>(y,x)[1] = 255;
				m.at<Vec3b>(y,x)[2] = 255;				
			}

		}

		erode(m, m, Mat(), Point(-1,-1), 6);
		dilate(m, m, Mat(), Point(-1, -1), 8);
		erode(m, m, Mat(), Point(-1, -1), 2);
		
	imshow("org", org);
	imshow("window", m);
	waitKey(0);
return 0;
}
