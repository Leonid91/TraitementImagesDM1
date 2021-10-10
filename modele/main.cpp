#include <opencv2/opencv.hpp>
#include <opencv2/core/affine.hpp>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace cv;


int main(int argc, char** argv){

	Mat imageIn = imread( "../../Michelangelo_ThecreationofAdam_1707x775.jpg", IMREAD_GRAYSCALE );

	fstream fragmentFile;
	string line;
	std::vector<int> listOfPositionsX;
	std::vector<int> listOfPositionsY;
	std::vector<int> listOfRotations;
	int k = 1; //Compteur principal des listes

	string ext = ".png";

	fragmentFile.open("../../fragments.txt",ios::in);

	while(getline(fragmentFile, line)){
		string arr[4];
    int i = 0;

		//Insère les 4 valeurs de la ligne dans un tableau de string
    stringstream ssin(line);
    while (ssin.good() && i < 4){
        ssin >> arr[i];
        ++i;
    }

		while(stoi(arr[0]) > k){ //Si l'index de l'image est supérieur au compteur, on rempli les vecteurs par des valeurs par défaut
			listOfPositionsX.push_back(-1);
			listOfPositionsY.push_back(-1);
			listOfRotations.push_back(0);
			k++;
		}

		//Sinon on insère les valeurs qu'on vient de parser
		listOfPositionsX.push_back(stoi(arr[1]));
		listOfPositionsY.push_back(stoi(arr[2]));
		listOfRotations.push_back(stoi(arr[3]));
		k++;
	}

	//Vérification des vecteurs
	//A commenter pour ne pas polluer l'affichage
	for(int i=0; i<listOfRotations.size();i++){
		std::cout << "[" << listOfPositionsX[i] << ", " << listOfPositionsY[i] << "], " << listOfRotations[i] << std::endl;
	}

	//Création de l'image de sortie
	Mat imageOut = Mat::zeros(Size(imageIn.cols, imageIn.rows), imageIn.depth());

	//Traitement
	int frag_eroded_cpt = 0; //Nombre de frag d'images traités
	// for(int i=0; i<listOfRotations.size();i++){
	for(int i=0; i<2;i++){ //On test juste avec quelques fragments
		if(listOfPositionsX[i] != -1){
			string imgToLoad = "../../frag_eroded/frag_eroded_" + std::to_string(frag_eroded_cpt) + ext;
			Mat frag = imread(imgToLoad, IMREAD_COLOR);
			frag_eroded_cpt++;

			Mat fragRotated;
			Point2f centre((frag.cols-1)/2.0, (frag.rows-1)/2.0);
			Mat rotationMatrix = getRotationMatrix2D(centre, listOfRotations[i], 1.0); //Matrice de rotation

			//Pour éviter de rogner pendant la rotation
			//Rect2f bbox = RotatedRect(Point2f(), frag.size(), listOfRotations[i]).boundingRect2f();
			//rotationMatrix.at<double>(0,2) += bbox.width/2.0 - frag.cols/2.0;
    	//rotationMatrix.at<double>(1,2) += bbox.height/2.0 - frag.rows/2.0;
			//warpAffine(frag, fragRotated, rotationMatrix, bbox.size());
			//imwrite("../../afterRotationBox.png", fragRotated);

			warpAffine(frag, fragRotated, rotationMatrix, frag.size());
			imwrite("../../afterRotation.png", fragRotated);

			//Ensuite il faut appliquer la translation à l'image et l'insérer dans la matrice mère
		}
	}

	imwrite("../../out.jpg", imageOut);
	//imshow( "Display window", imageOut);

	fragmentFile.close();

	// Mat imageIn = imread( argv[1], IMREAD_GRAYSCALE );
	//
	//
	// if(! imageIn.data )                              // Check for invalid input
	//   	{
	//       	cout <<  "Could not open or find the image" << std::endl ;
	//       	return -1;
	//  	}

	//imshow( "Display window", imageIn );
	//waitKey(0);


	return 0;
}
