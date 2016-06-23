#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <iostream>

//#include "operators.h"
//#include "operators.cpp"

using namespace cv;
using namespace std;


// Gaussian Blur 
Mat gblur(Mat src, int kernLength)
{
	Mat dst;
	for (int i = 1; i < kernLength; i = i + 2)
	{
		GaussianBlur(src, dst, Size(i, i), 0, 0);
	}
	return dst;
}

// Edge detection using Canny operator
Mat edgeDetect(Mat src)
{
	Mat draw, grey, edge;

	cvtColor(src, grey, CV_BGR2GRAY);

	Canny(grey, edge, 100, 150, 3);

	edge.convertTo(draw, CV_8U);
	return draw;
}

static void help() {
	std::cout << "\n     COMMANDS:" << endl
		<< " help ...................... Opens help menu " << endl
		<< " open ...................... Opens loaded image " << endl
		<< " new ....................... Load a new image " << endl
		<< " sobel ..................... Find edges with sobel operator " << endl
		<< " gblur ..................... Gaussian blur " << endl
		<< " bye ....................... Exit imProc" << endl
		<< "\n imProc is created by Corey Brooks, UBC computer engineering." << endl

		<< "\n\n";
}

// ------------------------------------------------------------------------------------------------------- //

int main(int argc, char** argv)
{
	Mat image;
	String command;
	const char* keys = "{help h about ?||}";
	cv::CommandLineParser parser(argc, argv, keys);



	if (argc != 2)
		if (true)
		{
			std::cerr << "\n\n Error: no argument specified" << endl;
			return -1;
		}

	image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

	if (!image.data)
	{
		std::cerr << "\n  Could not open or find the image" << std::endl;
		return -1;
	}
	else std::cout << " Succesfully loaded " << argv[1] << endl;

	std::cout << "\n ----------------------------------------" << endl
			  <<   " ---------- Welcome to ImProc -----------" << endl
			  << " ----------------------------------------" << endl;


	std::cout << " For help, type 'help' \n" << endl;



	while (std::cin >> command)
	{

		if (!command.compare("open"))
		{
			namedWindow(argv[1], WINDOW_AUTOSIZE);
			imshow(argv[1], image);				    // open image in separate window
			waitKey(0);								// window stays up until key is pressed
		}
	else if (!command.compare("help"))
		help(); // Display help messages

		else if (!command.compare("new"))
			std::cout << " Function not yet implemented" << endl;

		else if (!command.compare("gblur")) // Gaussian blur
		{
			int kern_lth = 16;
//			std::cout << " Enter a kernel length (default - 16):  ";
//			std::cin  >> kern_lth;

			Mat gaussIm = gblur(image, kern_lth);
 
			namedWindow("Original", WINDOW_AUTOSIZE);
			imshow("Original", image);

			namedWindow("Blurred", WINDOW_AUTOSIZE);
			imshow("Blurred", gaussIm);				    // open image in separate window


			waitKey(0);
		}

		else if (!command.compare("edge")) // Canny edge detection
		{
			Mat edgeIm = edgeDetect(gblur(image, 8));

			namedWindow("Original", CV_WINDOW_AUTOSIZE);
			imshow("Original", image);

			namedWindow("Edge", CV_WINDOW_AUTOSIZE);
			imshow("Edge", edgeIm);

			waitKey(0);
		}
		else if (!command.compare("bye"))
			return 0;

		else
			std::cout << " Not a valid command.\n For help, type help." << endl;
	}
	return 0;
}
