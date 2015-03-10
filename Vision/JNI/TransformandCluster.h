#include <vector>
#include <stdio.h>
#include "cameralibrary.h"
#include "Eigen/Dense"

using namespace Eigen;
using namespace std;
using namespace CameraLibrary;

float BOARD_SIZE[2] = {2394.0, 1231.9};


float * getBoardCorners(){
	float * boardArray = new float[8];
	boardArray[0] = 0;
	boardArray[1] = 0;
	boardArray[2] = 0;
	boardArray[3] = BOARD_SIZE[1];
	boardArray[4] = BOARD_SIZE[0];
	boardArray[5] = BOARD_SIZE[1];
	boardArray[6] = BOARD_SIZE[0];
	boardArray[7] = 0;

	return boardArray;
}

float * getBoardCorners(bool isLeft){
	
	float * boardArray = new float[8];
	
	if (!isLeft){
		boardArray[0] = BOARD_SIZE[0]/2;
		boardArray[1] = 0;
		boardArray[2] = BOARD_SIZE[0]/2;
		boardArray[3] = BOARD_SIZE[1];
		boardArray[4] = BOARD_SIZE[0];
		boardArray[5] = BOARD_SIZE[1];
		boardArray[6] = BOARD_SIZE[0];
		boardArray[7] = 0;
	}
	else {
		boardArray[0] = 0;
		boardArray[1] = 0;
		boardArray[2] = 0;
		boardArray[3] = BOARD_SIZE[1];
		boardArray[4] = BOARD_SIZE[0]/2;
		boardArray[5] = BOARD_SIZE[1];
		boardArray[6] = BOARD_SIZE[0]/2;
		boardArray[7] = 0;
	}

	return boardArray;
}

// get camera corners
float * getCamCorners(Camera * camera){
	float * camCorners = new float [8];
	int X = camera->Width();
	int Y = camera->Height();

	
	camCorners[0] = 0;
	camCorners[1] = 0;
	camCorners[2] = 0;
	camCorners[3] = Y; 
	camCorners[4] = X; 
	camCorners[5] = Y; 
	camCorners[6] = X; 
	camCorners[7] = 0;

	return camCorners;
}




//VectorXd pts8(8); //declared as array to assert that we only need 8 points
//VectorXd b0,b1,b2,b3,a0,a1,a2,a3;

    /* Code */
//Desitnation array followed by Source array
MatrixXf getTransformData(float * aArray, float * bArray){   //Camera array in aArray and board array in bArray
		
	//put camera corner coordinates in a0, a1, a2, a3 and board corner coordinates in b0, b1, b2, b3
	float a0[2]; a0[0] = aArray[0]; a0[1] = aArray[1];
	float a1[2]; a1[0] = aArray[2]; a1[1] = aArray[3];
	float a2[2]; a2[0] = aArray[4]; a2[1] = aArray[5];
	float a3[2]; a3[0] = aArray[6]; a3[1] = aArray[7];
	float b0[2]; b0[0] = bArray[0]; b0[1] = bArray[1];
	float b1[2]; b1[0] = bArray[2]; b1[1] = bArray[3];
	float b2[2]; b2[0] = bArray[4]; b2[1] = bArray[5];
	float b3[2]; b3[0] = bArray[6]; b3[1] = bArray[7];

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


float * transformBlob(cObject * blob, MatrixXf transform){
	float y = blob->Y(); 
	float x = blob->X(); 
	float * newCoords = new float[2];
	newCoords[0] = (transform(0,0)*x + transform(1,0)*y + transform(2,0))/(transform(6,0)*x + transform(7,0)*y + 1); //X
	newCoords[1] = (transform(3,0)*x + transform(4,0)*y + transform(5,0))/(transform(6,0)*x + transform(7,0)*y + 1); //Y

	return newCoords;
}

float * transformBlob(float * coordinates, MatrixXf transform){
	float x = coordinates[0]; 
	float y = coordinates[1]; 
	float * newCoords = new float[2];
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
	int camY = camera->Height();
	int camX = camera->Width();
	int Nskip, Sskip;
	float bestNDistSq = 10000000;
	float bestSDistSq = 10000000;
	float nAngleVal = 10;
	float sAngleVal = 10;
	for (int i = 0; i < numBlobs; i++) {
		float y = blobArray[i]->Y(); //rotate 90 degrees
		float x = blobArray[i]->X(); // rotate 90 degrees
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
	cObject ** newblobArray = new cObject * [numBlobs-2];
	int k = 0;
	for (int j = 0; j < numBlobs; j++){
		if (j == Nskip || j == Sskip) continue;
		newblobArray[k] = blobArray[j];
		k++;
	}
	for (int ii = 0; ii < k; ii++){
		float nY = bestNblob->Y();
		float nX = bestNblob->X();
		float sY = bestSblob->Y();
		float sX = bestSblob->X();
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

	cObject ** returnArray = new cObject * [4];
	returnArray[0] = bestNblob;
	returnArray[1] = bestSblob;
	returnArray[2] = bestSangle;
	returnArray[3] = bestNangle;

	return returnArray;
}

// remove cObjects from an array of cObjects
float ** filterBlobs(float ** fullArray, float ** removeArray, int fullArraySize, int removeArraySize){
	float ** newArray = new float * [fullArraySize - 4];
	for (int l = 0; l < fullArraySize -  4; l++){
		newArray[l] = new float[2];
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

float ** filterBlobs(float ** fullArray, float ** removeArray){
	int fullArraySize = 0, removeArraySize = 0;
	for (int m = 0; fullArray[m][0] != NULL; m++){fullArraySize = m;}
	for (int n = 0; removeArray[n][0] != NULL; n++){removeArraySize = n;}
	float ** newArray = new float * [fullArraySize - removeArraySize];
	for (int l = 0; l < fullArraySize -  removeArraySize; l++){
		newArray[l] = new float[2];
	}
	int k = 0;
	for (int i = 0; i < fullArraySize; i++){
		int tag = 0;
		for (int j = 0; j < removeArraySize; j++){
			if (fullArray[i][0] == removeArray[j][0] && fullArray[i][1] == removeArray[j][1]) {tag = 1; continue;}
		}
		if (tag == 1) {continue;}
		newArray[k][0] = fullArray[i][0];
		newArray[k][1] = fullArray[i][1];
		k++;
	}
	return newArray;
}



pair<float **,int> getClusterN(float***allPoints,int numCams, int nClust){

	//float * coordArray = new float [2];
	float ** holdClusters = new float * [nClust];
	int MAX_DIST = 30;
	int countSecondArray = 0;
	int whichCam = 0;

	for (int i = 0; i < numCams; i++){
		int maxArrayNum = 0;
		float dist = 0;
		whichCam = i;
		for (int m = 0; allPoints[m][0][0] != NULL; m++){
			maxArrayNum = m;
		}
		countSecondArray = i;
		for (int j = 0; j < maxArrayNum; j++){
			int tag = 1;
			holdClusters[0][0] = allPoints[i][j][0];
			holdClusters[0][1] = allPoints[i][j][1];

			for (int k = j+1; k < 6; k++){
				dist = sqrt(pow(allPoints[i][j][0]-allPoints[i][k][0],2)+pow(allPoints[i][j][1]-allPoints[i][k][1],2));
				if (dist < MAX_DIST){
					holdClusters[tag][0] = allPoints[i][k][0];
					holdClusters[tag][1] = allPoints[i][k][1];
					tag++;
				}
				if (tag == nClust){
					pair<float **, int> make_pair(holdClusters, whichCam);
					return pair<float **, int>(holdClusters,whichCam);
				}
			}
		}
	}
	float ** nullPoint;
	pair<float **, int> make_pair(nullPoint,whichCam);
	return pair<float**,int>(nullPoint,whichCam);
}

float * getClusterCenter(float ** cluster, int nClust){
	float * clusterSum = new float [2];
	float * coordArray = new float [2];

	for (int ii = 0; ii < nClust; ii++){
		clusterSum[0] += cluster[ii][0];
		clusterSum[1] += cluster[ii][1];
	}
	coordArray[0] = clusterSum[0]/nClust;
	coordArray[1] = clusterSum[1]/nClust;
	return coordArray;
}


int NelsonCode(int nCams, Camera ** camera, bool isLeftCam){

	int MAX_OFFSET_DIST = 50;
	float * boardArray = getBoardCorners();
	float *** cameraBlobs = new float** [nCams]; //an array of arrays containing gibbot LED coordinates
	vector<double> copy;

	for (int i = 0; i < nCams; i++){
		
		//get objects a.k.a. LED positions
		Frame *frame = camera[i]->GetLatestFrame();
		int objcount = frame->ObjectCount();

		cObject **objArray = new cObject* [objcount];
		for (int ii = 0; ii < objcount; ii++){
			objArray[ii] = frame->Object(ii);
		}

		//get array of corners in camera frame
		float * cameraArray = getCamCorners(camera[i]);

		//Get transform matrix for board to frame
		MatrixXf TSolve = getTransformData(cameraArray,boardArray);

		float ** newBlobCoords = new float*[objcount];
		for (int jj = 0; jj < objcount; jj++){
			newBlobCoords[jj] = transformBlob(objArray[jj],TSolve);
		}

		//find corner blobs and change them to float arrays
		cObject **cornerArray = getCornerBlobs(objArray,objcount,camera[i]);
		
		//use corner blobs to get new transform
		float * transformCorners = new float[8];
		for (int l = 0; l < 4; l++){
			transformCorners[2*l] = cornerArray[l]->X();
			transformCorners[2*l+1] = cornerArray[l]->Y();
		}
		float * halfBoardArray = getBoardCorners(isLeftCam);
		MatrixXf newTransform = getTransformData(halfBoardArray,transformCorners);

		//Filter out corners
		float ** fourCorners = new float * [4];
		for (int kk = 0; kk < 4; kk++){
			fourCorners[kk] = transformBlob(cornerArray[kk],TSolve);
		}
		float ** filteredArray = filterBlobs(newBlobCoords, fourCorners, objcount, 4);

		//transform remaining blobs in to correct board locations
		for (int K = 0; K < objcount - 4; K++){
			filteredArray[K] = transformBlob(filteredArray[K],newTransform);
		}

		//store remaining blobs in the camera position in cameraBlobs (1st cam in 0 spot etc.)
		cameraBlobs[i] = filteredArray;

	}

	pair<float**,int> ans;

	//search all cameras for cluster of 3
	int cluster3cam = 0;
	float ** cluster3 = new float * [3];
	ans = getClusterN(cameraBlobs,nCams,3);
	cluster3 = ans.first;
	cluster3cam = ans.second;

	//find center
	float * cluster3center = new float [2];
	cluster3center = getClusterCenter(cluster3,3);

	//filter out points from the camera where we found the clusters (cluster3cam)
	cameraBlobs[cluster3cam] = filterBlobs(cameraBlobs[cluster3cam],cluster3);
	
	//find all close points in other cameras and average them with current center. Then filter them out.
	int nClustAvgd = 3;
	float ** removeArr = new float * [1];
	for (int I = 0; I < nCams; I++){
		for (int J = 0; cameraBlobs[I][J][0] != NULL; J++){
			if ((pow(cameraBlobs[I][J][0]-cluster3center[0],2)+pow(cameraBlobs[I][J][1]-cluster3center[1],2)) < MAX_OFFSET_DIST*MAX_OFFSET_DIST){
				cluster3center[0] = (cluster3center[0]*nClustAvgd + cameraBlobs[I][J][0])/(nClustAvgd+1);
				cluster3center[1] = (cluster3center[1]*nClustAvgd + cameraBlobs[I][J][1])/(nClustAvgd+1);
				nClustAvgd++;
				removeArr[0] = cameraBlobs[I][J];
				cameraBlobs[I] = filterBlobs(cameraBlobs[I], removeArr);
				J--; //The new cameraBlobs will be 1 coordinate array shorter so we must decrement J
			}
		}
	}

	//repeat with cluster2

	//search all cameras for cluster of 2
	int cluster2cam = 0;
	float ** cluster2 = new float * [2];
	ans = getClusterN(cameraBlobs,nCams,2);
	cluster2 = ans.first;
	cluster2cam = ans.second;

	//find center
	float * cluster2center = new float [2];
	cluster2center = getClusterCenter(cluster2,2);

	//filter out points from the camera where we found the clusters (cluster2cam)
	cameraBlobs[cluster2cam] = filterBlobs(cameraBlobs[cluster2cam],cluster2);
	
	//find all close points in other cameras and average them with current center. Then filter them out.
	nClustAvgd = 2;
	removeArr = new float * [1];
	for (int I = 0; I < nCams; I++){
		for (int J = 0; cameraBlobs[I][J][0] != NULL; J++){
			if ((pow(cameraBlobs[I][J][0]-cluster2center[0],2)+pow(cameraBlobs[I][J][1]-cluster2center[1],2)) < MAX_OFFSET_DIST*MAX_OFFSET_DIST){
				cluster2center[0] = (cluster2center[0]*nClustAvgd + cameraBlobs[I][J][0])/(nClustAvgd+1);
				cluster2center[1] = (cluster2center[1]*nClustAvgd + cameraBlobs[I][J][1])/(nClustAvgd+1);
				nClustAvgd++;
				removeArr[0] = cameraBlobs[I][J];
				cameraBlobs[I] = filterBlobs(cameraBlobs[I], removeArr);
				J--; //The new cameraBlobs will be 1 coordinate array shorter so we must decrement J
			}
		}
	}

	//...and for cluster 1

	//search all cameras for cluster of 1
	int cluster1cam = 0;
	float ** cluster1 = new float * [1];
	ans = getClusterN(cameraBlobs,nCams,1);
	cluster1 = ans.first;
	cluster1cam = ans.second;

	//find center
	float * cluster1center = new float [2];
	cluster1center = getClusterCenter(cluster1,1);

	//since there might be other points getting registered, lets filter out points anyways
	cameraBlobs[cluster1cam] = filterBlobs(cameraBlobs[cluster1cam],cluster1);
	
	//find all close points in other cameras and average them with current center. Then filter them out.
	nClustAvgd = 1;
	removeArr = new float * [1];
	for (int I = 0; I < nCams; I++){
		for (int J = 0; cameraBlobs[I][J][0] != NULL; J++){
			if ((pow(cameraBlobs[I][J][0]-cluster1center[0],2)+pow(cameraBlobs[I][J][1]-cluster1center[1],2)) < MAX_OFFSET_DIST*MAX_OFFSET_DIST){
				cluster1center[0] = (cluster1center[0]*nClustAvgd + cameraBlobs[I][J][0])/(nClustAvgd+1);
				cluster1center[1] = (cluster1center[1]*nClustAvgd + cameraBlobs[I][J][1])/(nClustAvgd+1);
				nClustAvgd++;
				removeArr[0] = cameraBlobs[I][J];
				cameraBlobs[I] = filterBlobs(cameraBlobs[I], removeArr);
				J--; //The new cameraBlobs will be 1 coordinate array shorter so we must decrement J
			}
		}
	}
	

	return 0;
}
