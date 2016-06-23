/*
#include "operators.h"
#include <opencv\cv.h>

using namespace cv;
using namespace std;

// Edge detection using the Sobel operator in the 'x' direction

Mat operators::edgeDetect(Mat src) {
	cvtColor(src, grey, CV_BGR2GRAY);

	Sobel(grey, sobelIm, CV_32F, 1, 0);

	double minVal, maxVal;
	minMaxLoc(sobelIm, &minVal, &maxVal); //find minimum and maximum intensities
	cout << "minVal : " << minVal << endl << "maxVal : " << maxVal << endl;

	Mat draw;
	sobelIm.convertTo(draw, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
	return draw;
}


// Gaussian Blur 
Mat operators::gblur(Mat src, int kernLength)
{
	Mat dst;
	for (int i = 1; i < kernLength; i = i + 2)
	{
		GaussianBlur(src, dst, Size(i, i), 0, 0);
	}
	return dst;
}
*/