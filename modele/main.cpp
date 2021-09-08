#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace cv;


int main(int argc, char** argv){

	// fstream fragmentFile;
	// string tp;
	// std::vector<int> listOfPositions;
	// std::vector<int> listOfRotations;
  // fragmentFile.open("../fragments.txt",ios::in);
	//
  //     while(getline(newfile, tp)){
	// 			std::string delimiter = " ";
	// 			std::string token = tp.substr(0, tp.find(delimiter));
  //     }
  //     newfile.close();

	Mat imageIn = imread( argv[1], IMREAD_GRAYSCALE );


	if(! imageIn.data )                              // Check for invalid input
    	{
        	cout <<  "Could not open or find the image" << std::endl ;
        	return -1;
   	}




	//imshow( "Display window", imageIn );
	//waitKey(0);


	return 0;
}
