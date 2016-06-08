#include <opencv\highgui.h>
#include <opencv\cv.h>

#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{

	if (argc != 2)
	if(true)
	{
	std::cerr << "\n\n Usage: imProc ImageToLoadAndDisplay\n" << endl;
	return -1;
	}
	

	Mat image;

	std::cout << "\n ----------------------------------------" << endl
			  << " ---------- Welcome to ImProc -----------"   << endl
			  << " ----------------------------------------\n" << endl;

	image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	
	if (!image.data)
	{
		std::cerr << "\n  Could not open or find the image" << std::endl;
		return -1;
	}

	

	namedWindow(argv[1], WINDOW_AUTOSIZE);
	imshow(argv[1], image);				    // open image in separate window
	waitKey(0);								// window stays up until key is pressed

	return 0;
}
