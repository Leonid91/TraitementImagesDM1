#include <opencv2/opencv.hpp>
#include <opencv2/core/affine.hpp>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;
using namespace cv;

// Pour la question 2
void customVerify()
{
	fstream fragmentFile;
	string fragmentLine;
	std::vector<int> fragListOfPositionsX;
	std::vector<int> fragListOfPositionsY;
	std::vector<int> fragListOfRotations;

	fstream solutionFile;
	string solutionLine;
	std::vector<int> solListOfPositionsX;
	std::vector<int> solListOfPositionsY;
	std::vector<int> solListOfRotations;

	int k = 1; //Compteur principal des listes

	fragmentFile.open("../../fragments.txt", ios::in);

	while (getline(fragmentFile, fragmentLine))
	{
		string arr[4];
		int i = 0;

		//Insère les 4 valeurs de la ligne dans un tableau de string
		stringstream ssin(fragmentLine);
		while (ssin.good() && i < 4)
		{
			ssin >> arr[i];
			++i;
		}

		while (stoi(arr[0]) > k)
		{ //Si l'index de l'image est supérieur au compteur, on rempli les vecteurs par des valeurs par défaut
			fragListOfPositionsX.push_back(-1);
			fragListOfPositionsY.push_back(-1);
			fragListOfRotations.push_back(0);
			k++;
		}

		//Sinon on insère les valeurs qu'on vient de parser
		fragListOfPositionsX.push_back(stoi(arr[1]));
		fragListOfPositionsY.push_back(stoi(arr[2]));
		fragListOfRotations.push_back(stoi(arr[3]));
		k++;
	}

	//Vérification des vecteurs
	//A commenter pour ne pas polluer l'affichage
	// for (int i = 0; i < fragListOfRotations.size(); i++)
	// {
	// 	std::cout << "[" << fragListOfPositionsX[i] << ", " << fragListOfPositionsY[i] << "], " << fragListOfRotations[i] << std::endl;
	// }

	solutionFile.open("../../solutions.txt", ios::in);
	k = 1; // reset

	while (getline(solutionFile, solutionLine))
	{
		string arr[4];
		int i = 0;

		//Insère les 4 valeurs de la ligne dans un tableau de string
		stringstream ssin(solutionLine);
		while (ssin.good() && i < 4)
		{
			ssin >> arr[i];
			++i;
		}

		while (stoi(arr[0]) > k)
		{ //Si l'index de l'image est supérieur au compteur, on rempli les vecteurs par des valeurs par défaut
			solListOfPositionsX.push_back(-1);
			solListOfPositionsY.push_back(-1);
			solListOfRotations.push_back(0);
			k++;
		}

		//Sinon on insère les valeurs qu'on vient de parser
		solListOfPositionsX.push_back(stoi(arr[1]));
		solListOfPositionsY.push_back(stoi(arr[2]));
		solListOfRotations.push_back(stoi(arr[3]));
		k++;
	}

	// // Vérification des vecteurs
	// // A commenter pour ne pas polluer l'affichage
	// std::cout << "QUESTION 2" << std::endl;
	// for (int i = 0; i < solListOfRotations.size(); i++)
	// {
	// 	std::cout << "[" << solListOfPositionsX[i] << ", " << solListOfPositionsY[i] << "], " << solListOfRotations[i] << std::endl;
	// }
	std::cout << std::endl;
	std::cout << "QUESTION 2" << std::endl;

	std::vector<int> coordIsOkX;
	std::vector<int> coordIsOkY;
	// std::vector<int> rotIsOk;

	int dX, dY, dRot;
	dX = 1;
	dY = 1;
	dRot = 1;

	// J'itère sur les coord. du fichier de solution en considerant qu'il pourra être plus petit
	// que le fichier de référence

 exercice2
	// X
	for (size_t i = 0; i < solListOfPositionsX.size(); i++)
	{
		coordIsOkX.push_back(fragListOfPositionsX[i] - solListOfPositionsX[i]);
		if (abs(fragListOfPositionsX[i] - solListOfPositionsX[i]) <= dX)
		{
			std::cout << "Le fragment de position X = " << solListOfPositionsX[i] << " est bien localisé, avec la différence de : " << abs(fragListOfPositionsX[i] - solListOfPositionsX[i]) << " pour dx = " << dX << std::endl;
			coordIsOkX.push_back(fragListOfPositionsX[i] - solListOfPositionsX[i]);
		}
		else
		{
			std::cout << "Le fragment de position X = " << solListOfPositionsX[i] << " est mal localisé, avec la différence de : " << abs(fragListOfPositionsX[i] - solListOfPositionsX[i]) << std::endl;
		}
	}
	std::cout << std::endl;

	// Y 
	for (size_t i = 0; i < solListOfPositionsY.size(); i++)
	{

		if (abs(fragListOfPositionsY[i] - solListOfPositionsY[i]) <= dY)
		{
			std::cout << "Le fragment de position Y = " << solListOfPositionsY[i] << " est bien localisé " << std::endl;
			coordIsOkY.push_back(fragListOfPositionsY[i] - solListOfPositionsY[i]);
		}
		else
		{
			std::cout << "Le fragment de position Y = " << solListOfPositionsY[i] << " est mal localisé " << std::endl;
		}
	}
	std::cout << std::endl;

	// Rot
	for (size_t i = 0; i < solListOfRotations.size(); i++)
	{
		// deltaRot.push_back(fragListOfRotations[i] - solListOfRotations[i]);
		if (abs(fragListOfRotations[i] - solListOfRotations[i]) <= dRot)
		{
			std::cout << "Le fragment de rotation = " << solListOfRotations[i] << " est bien localisé " << std::endl;
		}
		else
		{
			std::cout << "Le fragment de rotation = " << solListOfRotations[i] << " est mal localisé " << std::endl;
		}
	}
	std::cout << std::endl;

	vector<double> sizeAllFrag;
	int nbFrag = 327;
	for (int i = 0; i < nbFrag; i++)
	{
		std::string fragLink = "../../frag_eroded/frag_eroded_" + std::to_string(i) + ".png";
		Mat fragIn = imread(fragLink, IMREAD_GRAYSCALE);

		vector<vector<Point>> contours;
		// findContours(fragIn, contours);

		// for (unsigned int i = 0; i < contours.size(); i++)
		// {
		// 	std::cout << "# of contour points: " << contours[i].size() << std::endl;

		// 	for (unsigned int j = 0; j < contours[i].size(); j++)
		// 	{
		// 		std::cout << "Point(x,y)=" << contours[i][j] << std::endl;
		// 	}

		// 	std::cout << " Area: " << contourArea(contours[i]) << std::endl;
		// }

		// for (int y = 0; y < fragIn.rows; ++y)
		// {
		// 	for (int x = 0; x < fragIn.cols; ++x)
		// 	{
		// 		std::cout << << std::endl;
		// 	}
		// }
	}

	// double surfaceOk = 0;

	// // Surface totale des bien positionnés
	// for (size_t i = 0; i < fragListOfPositionsX.size(); i++)
	// {
	// 	surfaceOk += fragListOfPositionsX[i] * fragListOfPositionsY[i];
	// }

	// k = 1; // reset

	// fstream notOnImageFile;
	// string notOnImageLine;
	// std::vector<int> listOfSurface;

	// notOnImageFile.open("../../fragments_s.txt", ios::in);

	// while (getline(notOnImageFile, notOnImageLine))
	// {
	// 	listOfSurface.push_back(stoi(notOnImageLine));
	// }

	// // Surface des élements bien positionnés pas sur la fresque

	// double surfaceNotOnImage = 0;
	// for (size_t i = 0; i < listOfSurface.size(); i++)
	// {
	// 	surfaceNotOnImage += listOfSurface[i];
	// }

	// double surfaceAllFrag = surfaceNotOnImage; // plus ceux qui sont dans la fresque que j'ajoute dans la boucle
	// for (size_t i = 0; i < fragListOfPositionsX.size(); i++)
	// {
	// 	surfaceAllFrag += fragListOfPositionsX[i]*fragListOfPositionsY[i];
	// }

	// double precision = (surfaceOk - surfaceNotOnImage) / surfaceAllFrag;

	// std::cout << std::endl;
	// std::cout << "La précision de la localisation p = ( " << surfaceOk << " - " << surfaceNotOnImage << ") / " << surfaceAllFrag  << " = " << precision << std::endl;
	// std::cout << std::endl;
}

int main(int argc, char **argv)
{

	Mat imageIn = imread("../../Michelangelo_ThecreationofAdam_1707x775.jpg", IMREAD_GRAYSCALE);

	Mat imageIn = imread( "../../Michelangelo_ThecreationofAdam_1707x775.jpg", IMREAD_UNCHANGED ); //Pour dimensions de l'image finale
	Mat fragIn = imread("../../frag_eroded/frag_eroded_0.png", IMREAD_UNCHANGED); //Pour la profondeur de l'image finale
	//Mat imageOut = Mat::zeros(Size(imageIn.cols, imageIn.rows), fragIn.depth()); //Ne marche pas car en nuances de gris
	Mat imageOut = imageIn.clone(); //Copie de l'image originale
	imageOut = Scalar(255,255,255); //On la remplie de blanc
	//On crée un channel alpha pour l'image de sortie pour gérer la transparence
	Mat newImageOut(imageOut.size(), CV_MAKE_TYPE(imageOut.depth(), 4));
	int from_to[] = { 0,0, 1,1, 2,2, -1,3 };
	mixChannels(&imageOut,1,&newImageOut,1,from_to,4);


	fstream fragmentFile;
	string line;
	std::vector<int> listOfPositionsX;
	std::vector<int> listOfPositionsY;
	std::vector<int> listOfRotations;
	int k = 0; //Compteur principal des listes

	string ext = ".png";

	fragmentFile.open("../../fragments.txt", ios::in);

	while (getline(fragmentFile, line))
	{
		string arr[4];
		int i = 0;

		//Insère les 4 valeurs de la ligne dans un tableau de string
		stringstream ssin(line);
		while (ssin.good() && i < 4)
		{
			ssin >> arr[i];
			++i;
		}

		while (stoi(arr[0]) > k)
		{ //Si l'index de l'image est supérieur au compteur, on rempli les vecteurs par des valeurs par défaut
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

	// for (int i = 0; i < listOfRotations.size(); i++)
	// {
	// 	std::cout << "[" << listOfPositionsX[i] << ", " << listOfPositionsY[i] << "], " << listOfRotations[i] << std::endl;
	// }

	//Création de l'image de sortie
	Mat imageOut = Mat::zeros(Size(imageIn.cols, imageIn.rows), imageIn.depth());

	//Traitement
	int frag_eroded_cpt = 0; //Nombre de frag d'images traités
	// for(int i=0; i<listOfRotations.size();i++){
	for (int i = 0; i < 2; i++)
	{ //On test juste avec quelques fragments
		if (listOfPositionsX[i] != -1)
		{
			string imgToLoad = "../../frag_eroded/frag_eroded_" + std::to_string(frag_eroded_cpt) + ext;
			Mat frag = imread(imgToLoad, IMREAD_COLOR);
			frag_eroded_cpt++;

	//for(int i=0; i<listOfRotations.size();i++){
	//	std::cout << i << " [" << listOfPositionsX[i] << ", " << listOfPositionsY[i] << "], " << listOfRotations[i] << std::endl;
	//}

	//Traitement
	 for(int i=0; i<listOfRotations.size();i++){
	//for(int i=0; i<12;i++){ //On test juste avec quelques fragments
		if(listOfPositionsX[i] != -1){
			Mat frag = imread("../../frag_eroded/frag_eroded_" + std::to_string(i) + ext, IMREAD_UNCHANGED);
			Mat fragGray = imread("../../frag_eroded/frag_eroded_" + std::to_string(i) + ext, IMREAD_GRAYSCALE);
			//imwrite("../../beforeRotation.png", frag);

			Mat thresholded;
			threshold(fragGray, thresholded, 0, 255, THRESH_OTSU);
			imwrite("../../otsu.png", thresholded);
			Rect bbox = boundingRect(thresholded);


			Mat fragRotated;
			Point2f centre((frag.cols - 1) / 2.0, (frag.rows - 1) / 2.0);
			Mat rotationMatrix = getRotationMatrix2D(centre, listOfRotations[i], 1.0); //Matrice de rotation
			//std::cout << "Image " << i << " rotation : " << listOfRotations[i] << std::endl;

			//Pour éviter de rogner pendant la rotation
			//Rect2f bbox = RotatedRect(Point2f(), frag.size(), listOfRotations[i]).boundingRect2f();
			//rotationMatrix.at<double>(0,2) += bbox.width/2.0 - frag.cols/2.0;
			//rotationMatrix.at<double>(1,2) += bbox.height/2.0 - frag.rows/2.0;
			//warpAffine(frag, fragRotated, rotationMatrix, bbox.size());
			//imwrite("../../afterRotationBox.png", fragRotated);

			warpAffine(frag, fragRotated, rotationMatrix, frag.size()); //Application de la matrice de rotation
			//imwrite("../../afterRotation.png", fragRotated);

			//On retire le fond noir après chaque copie
			Mat frag_bgra;
			cvtColor(fragRotated, frag_bgra, COLOR_BGR2BGRA);

			for (int y = 0; y < frag_bgra.rows; ++y)
			{
				for (int x = 0; x < frag_bgra.cols; ++x)
				{
					Vec4b & pixel = frag_bgra.at<cv::Vec4b>(y, x);
					if (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0)
					{
						pixel[3] = 0;
					} else {
						pixel[3] = 255;
					}
				}
			}


			imwrite("../../fragAlpha.png", frag_bgra);

			try{
				frag_bgra.copyTo(newImageOut(Rect(listOfPositionsX[i], listOfPositionsY[i], frag_bgra.cols, frag_bgra.rows)));
			}
			catch (Exception e){

			}


	customVerify();

			//addWeighted(newImageOut(Rect(listOfPositionsX[i], listOfPositionsY[i], fragRotated.cols, fragRotated.rows)), 0.8, fragRotated, 0.2, 0.0, newImageOut);
			//std::cout << "Fragment " << std::to_string(i) << " copié." << std::endl;

			//Comparer les channels des imgs*
			//std::cout<< frag.channels() << std::endl;
			//std::cout<< fragRotated.channels() << std::endl;
			//std::cout << newImageOut.channels() << std::endl;

		} else {
			// std::cout << "Fragment " << std::to_string(i) << " ignoré." << std::endl;
		}
	}

	imwrite("../../out.png", newImageOut);

	fragmentFile.close();


	return 0;
}