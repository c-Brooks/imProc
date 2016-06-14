#include <opencv\highgui.h>
#include <opencv\cv.h>


#include <iostream>

using namespace cv;
using namespace std;

Mat edgeDetect(Mat im);
Mat gblur(Mat im);

int main(int argc, char** argv)
{

	if (argc != 2)
		if (true)
		{
			std::cerr << "\n\n Error: no argument specified" << endl;
			return -1;
		}


	Mat image;
	String command;

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
	else if (!command.compare("help")) // display help messages TODO: dont take whitespace
	{
  std::cout << "\n     COMMANDS:" << endl
			<< " help ...................... Opens help menu " << endl
			<< " open ...................... Opens loaded image " << endl
			<< " new ....................... Load a new image " << endl
	  	    << " gblur ..................... Gaussian blur " << endl
		    << " bye ....................... Exit imProc" << endl
			<< "\n imProc is created by Corey Brooks, UBC computer engineering." << endl

			<< "\n\n";
	}
		else if (!command.compare("new"))
			std::cout << " Function not yet implemented" << endl;

		else if (!command.compare("gblur")) // Gaussian blur
		{
			int kern_lth = 16;
			std::cout << " Enter a kernel length (default - 16):  ";
			std::cin  >> kern_lth;

//			Mat gaussIm = gblur(image, kern_lth);
			Mat gaussIm;
			for (int i = 1; i < kern_lth; i = i + 2)
			{
				GaussianBlur(image, gaussIm, Size(i, i), 0, 0);
			}

			namedWindow(argv[1], WINDOW_AUTOSIZE);
			imshow(argv[1], gaussIm);				    // open image in separate window
			waitKey(0);
		}

		else if (!command.compare("sobel")) // Sobel edge detection
		{
			Mat sobelIm;
			int ddepth;
			std::cout << " Enter an image depth:  ";
			std::cin >> ddepth;
			Mat edgeIm = edgeDetect(image);

			namedWindow("image", CV_WINDOW_AUTOSIZE);
			imshow("image", edgeIm);

			waitKey(0);
		}
		else if (!command.compare("bye"))
			return 0;

		else
			std::cout << " Not a valid command.\n For help, type help." << endl;
	}
	return 0;
}

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

Mat edgeDetect(Mat src)
{
	Mat grey;
	cvtColor(src, grey, CV_BGR2GRAY);

	Mat sobelIm;
	Sobel(grey, sobelIm, CV_32F, 1, 0);

	double minVal, maxVal;
	minMaxLoc(sobelIm, &minVal, &maxVal); //find minimum and maximum intensities
	cout << "minVal : " << minVal << endl << "maxVal : " << maxVal << endl;

	Mat draw;
	sobelIm.convertTo(draw, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
	return draw;
}
