#include <stdio.h>
#include "Eigen/Dense"
#include "cameralibrary.h"

using namespace Eigen;
using namespace std;
using namespace CameraLibrary;

//variables
float BOARD_SIZE[2] = {2394.0, 1231.9};

//CameraList list;
//int camCount = list.Count();
//board corners NW, SW, SE, NE where 0,2,4 and 6 array positions correspond to X coordinates and odd positions to Y coordinates
//float boardCorners[8] = {0, 0, 0, BOARD_SIZE[1], BOARD_SIZE[0]/2, BOARD_SIZE[1], BOARD_SIZE[0]/2, 0};



float * getBoardCorners(){
	float * boardArray = new float[8];
	boardArray[0] = 0;
	boardArray[1] = 0;
	boardArray[2] = 0;
	boardArray[3] = BOARD_SIZE[1];
	boardArray[4] = BOARD_SIZE[0]/2;
	boardArray[5] = BOARD_SIZE[1];
	boardArray[6] = BOARD_SIZE[0]/2;
	boardArray[7] = 0;

	return boardArray;
}

// get camera corners
float * getCamCorners(Camera * camera){
	float * camCorners = new float [8];
	int X = camera->Width();
	int Y = camera->Height();

	//notice X and Y are switched. This effectively rotates the camera 90 degrees
	camCorners[0] = 0;
	camCorners[1] = 0;
	camCorners[2] = 0;
	camCorners[3] = X; //should be 'y' coordinate
	camCorners[4] = Y; //should be 'x' coordinate
	camCorners[5] = X; // 'y'
	camCorners[6] = Y; // 'x'
	camCorners[7] = 0;

	return camCorners;
}




//VectorXd pts8(8); //declared as array to assert that we only need 8 points
//VectorXd b0,b1,b2,b3,a0,a1,a2,a3;

    /* Code */
MatrixXf getTransformData(float * aArray, float * bArray){   //Camera array in aArray and board array in bArray
	//b0,b1,b2,b3,a0,a1,a2,a3 = pts8;
	
	//put camera corner coordinates in a0, a1, a2, a3 and board corner coordinates in b0, b1, b2, b3
	float a0[2]; a0[0] = aArray[0]; a0[1] = aArray[1];
	float a1[2]; a1[0] = aArray[2]; a1[1] = aArray[3];
	float a2[2]; a2[0] = aArray[4]; a2[1] = aArray[5];
	float a3[2]; a3[0] = aArray[6]; a3[1] = aArray[7];
	float b0[2]; b0[0] = bArray[0]; b0[1] = bArray[1];
	float b1[2]; b1[0] = bArray[2]; b1[1] = bArray[3];
	float b2[2]; b2[0] = bArray[4]; b2[1] = bArray[5];
	float b3[2]; b3[0] = bArray[6]; b3[1] = bArray[7];

	// new code
	MatrixXf A(8,8);
	VectorXf B(8,1);
	
	//make Matrix
	A << a0[0], a0[1], 1,     0,     0, 0, -a0[0]*b0[0], -a0[1]*b0[0],
             0,     0, 0, a0[0], a0[1], 1, -a0[0]*b0[1], -a0[1]*b0[1],
         a1[0], a1[1], 1,     0,     0, 0, -a1[0]*b1[0], -a1[1]*b1[0],
             0,     0, 0, a1[0], a1[1], 1, -a1[0]*b1[1], -a1[1]*b1[1],
         a2[0], a2[1], 1,     0,     0, 0, -a2[0]*b2[0], -a2[1]*b2[0],
             0,     0, 0, a2[0], a2[1], 1, -a2[0]*b2[1], -a2[1]*b2[1],
         a3[0], a3[1], 1,     0,     0, 0, -a3[0]*b3[0], -a3[1]*b3[0],
             0,     0, 0, a3[0], a3[1], 1, -a3[0]*b3[1], -a3[1]*b3[1];
	
	//make vector
	B << b0[0], b0[1], b1[0], b1[1], b2[0], b2[1], b3[0], b3[1];
	
	return A.jacobiSvd(ComputeThinU|ComputeThinV).solve(B); // solve A\B and return answer
}

// transform LED coordinates from camera frame to board frame --- takes blob input and transform matrix computed above
float * transformBlob(cObject * blob, MatrixXf transform){
	float x = blob->Y(); //rotate 90 degrees
	float y = blob->X(); // rotate 90 degrees
	float * newCoords = new (nothrow) float[2];
	newCoords[0] = (transform(0,0)*x + transform(1,0)*y + transform(2,0))/(transform(6,0)*x + transform(7,0)*y + 1); //X
	newCoords[1] = (transform(3,0)*x + transform(4,0)*y + transform(5,0))/(transform(6,0)*x + transform(7,0)*y + 1); //Y

	return newCoords;
}

// get the 4 marker LED coordinates that each camera sees
cObject ** getCornerBlobs(cObject ** blobArray, int numBlobs, Camera * camera){
	cObject * bestNblob;
	cObject * bestSblob;
	cObject * bestNangle;
	cObject * bestSangle;
	int camX = camera->Height();
	int camY = camera->Width();
	int Nskip, Sskip;
	float bestNDistSq = 10000000;
	float bestSDistSq = 10000000;
	float nAngleVal = 10;
	float sAngleVal = 10;
	for (int i = 0; i < numBlobs; i++) {
		float x = blobArray[i]->Y(); //rotate 90 degrees
		float y = blobArray[i]->X(); // rotate 90 degrees
		if (pow(x,2)+pow(y,2) < bestNDistSq){
			bestNDistSq = pow(x,2) + pow(y,2);
			bestNblob = blobArray[i];
			Nskip = i;
		}
		if (pow(x-camX,2)+pow(y-camY,2) < bestSDistSq){
			bestSDistSq = pow(x-camX,2)+pow(y-camY,2);
			bestSblob = blobArray[i];
			Sskip = i;
		}
	}
	cObject ** newblobArray = new (nothrow) cObject * [numBlobs-2];
	int k = 0;
	for (int j = 0; j < numBlobs; j++){
		if (j == Nskip || j == Sskip) continue;
		newblobArray[k] = blobArray[j];
		k++;
	}
	for (int ii = 0; ii < k; ii++){
		float nX = bestNblob->Y();
		float nY = bestNblob->X();
		float sX = bestSblob->Y();
		float sY = bestSblob->X();
		float testX = newblobArray[ii]->Y();
		float testY = newblobArray[ii]->X();
		if (abs((sY-testY)/(sX-testX)) < sAngleVal){
			bestSangle = newblobArray[ii];
			sAngleVal = abs((sY-testY)/(sX-testX));
		}
		if (abs((nY-testY)/(nX-testX)) < nAngleVal){
			bestNangle = newblobArray[ii];
			nAngleVal = abs((nY-testY)/(nX-testX));
		}
	}

	cObject ** returnArray = new (nothrow) cObject * [4];
	returnArray[0] = bestNblob;
	returnArray[1] = bestSblob;
	returnArray[2] = bestNangle;
	returnArray[3] = bestSangle;

	return returnArray;
}

// remove cObjects from an array of cObjects
float ** filterBlobs(float ** fullArray, float ** removeArray, int fullArraySize, int removeArraySize){
	float ** newArray = new (nothrow) float * [fullArraySize - 4];
	for (int l = 0; l < fullArraySize -  4; l++){
		newArray[l] = new (nothrow) float[2];
	}
	int k = 0;
	for (int i = 0; i < fullArraySize/*fullArray[i] != NULL*/; i++){
		int tag = 0;
		for (int j = 0; j < removeArraySize/*removeArray[j] != NULL*/; j++){
			if (fullArray[i][0] == removeArray[j][0] && fullArray[i][1] == removeArray[j][1]) {tag = 1; continue;}
		}
		if (tag == 1) {continue;}
		newArray[k][0] = fullArray[i][0];
		newArray[k][1] = fullArray[i][1];
		k++;
	}
	return newArray;
}