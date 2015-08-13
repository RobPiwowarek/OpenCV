#include <stdio.h>
#include "opencv2\core\core.hpp";
#include "opencv2\highgui\highgui.hpp";
#include "opencv2\opencv.hpp";

#define HUE_UP_LIMIT 75
#define HUE_DOWN_LIMIT 36
#define SATURATION_LIMIT 55
#define VALUE_LIMIT 100

using namespace std;
using namespace cv;
int image() {
	Mat image = imread("greensreen.png", CV_LOAD_IMAGE_COLOR); //640 x 480
	VideoCapture cap(0); // open the default camera
	if(!cap.isOpened())  // check if we succeeded
        return -1;

    namedWindow("ProcessedVideo",1);
    for(;;)
    {
		Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, frame, COLOR_BGR2HSV);
		cvtColor(image, image, COLOR_BGR2HSV);

		for (int y = 0; y < frame.rows-1; y++)
			for (int x = 0; x < frame.cols-1; x++){
				Vec3b frame_intensity = frame.at<Vec3b>(y,x);
				Vec3b image_intensity = image.at<Vec3b>(y,x);
			
				// if values match, get values from image
				if (frame_intensity.val[0] < HUE_UP_LIMIT && frame_intensity.val[0] > HUE_DOWN_LIMIT && frame_intensity.val[1] > SATURATION_LIMIT && frame_intensity.val[2] > VALUE_LIMIT){
					frame.at<Vec3b>(y, x)[0] = image_intensity.val[0];
					frame.at<Vec3b>(y, x)[1] = image_intensity.val[1];
					frame.at<Vec3b>(y, x)[2] = image_intensity.val[2];
				}
    }
		cvtColor(frame, frame, COLOR_HSV2BGR);
		cvtColor(image, image, COLOR_HSV2BGR);
        imshow("ProcessedVideo", frame);
        if(cvWaitKey(5) >= 0) break;
	}
    return 0;
}
