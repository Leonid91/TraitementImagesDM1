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

	fstream fragmentFile;
	string line;
	std::vector<int> listOfPositionsX;
	std::vector<int> listOfPositionsY;
	std::vector<int> listOfRotations;
	int k = 1; //Compteur principal des listes

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
	for(int i=0; i<listOfRotations.size();i++){
		//A commenter pour ne pas polluer l'affichage
		//std::cout << "[" << listOfPositionsX[i] << ", " << listOfPositionsY[i] << "], " << listOfRotations[i] << std::endl;
	}

	string ext = ".png";

	//Traitement
	int frag_eroded_cpt = 0; //Nombre de frag d'images traités
	// for(int i=0; i<listOfRotations.size();i++){
	for(int i=0; i<3;i++){ //On test juste avec quelques fragments
		if(listOfPositionsX[i] != -1){
			Mat frag = imread("../../frag_eroded/frag_eroded_" + frag_eroded_cpt + ext, IMREAD_COLOR);
			frag_eroded_cpt++;

			Point2f centre(listOfPositionsX[i], listOfPositionsY[i]);
			Mat fragRotated = getRotationMatrix2D(centre, listOfRotations[i], 1.0);			
		}
	}

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
