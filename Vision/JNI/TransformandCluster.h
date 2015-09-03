#include <vector>
#include <stdio.h>
#include "cameralibrary.h"
#include "Eigen/Dense"
#include <math.h>

using namespace Eigen;
using namespace std;
using namespace CameraLibrary;

float BOARD_SIZE[2] = {2394.0, 1231.9};


float * getBoardCorners(){   //this function is called if the user calls it without arguments
							 //it returns the size of the full board

	//corners are (0,0) (0,y) (x,y) and (x,0)
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

float * getBoardCorners(bool isLeft){	//this function is called if the user wants just half the board
										//the user puts in a bool saying whether they want the left or the right half coordinates
										//and the funciton returns either the left or the right half coordinates
	
	float * boardArray = new float[8];
		
		// right side of board coordinates are (x/2,0) (x/2,y) (x,y) (x,0)
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

		//left side of board coordinates are (0,0) (0,y) (x/2,y) (x/2,0)
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

	//this assumes camera is straight up and down (attached on bottom)
	int X = camera->Width();
	int Y = camera->Height();

	//camera frame coordinates are (0,0) (0,y) (x,y) (x,0)
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

	//initialize an 8 by 8 matrix 'A'
	MatrixXf A(8,8);

	//initialize a vector of length 8 'B'
	VectorXf B(8,1);
	
	//put data in matrix
	A << a0[0], a0[1], 1,     0,     0, 0, -a0[0]*b0[0], -a0[1]*b0[0],
             0,     0, 0, a0[0], a0[1], 1, -a0[0]*b0[1], -a0[1]*b0[1],
         a1[0], a1[1], 1,     0,     0, 0, -a1[0]*b1[0], -a1[1]*b1[0],
             0,     0, 0, a1[0], a1[1], 1, -a1[0]*b1[1], -a1[1]*b1[1],
         a2[0], a2[1], 1,     0,     0, 0, -a2[0]*b2[0], -a2[1]*b2[0],
             0,     0, 0, a2[0], a2[1], 1, -a2[0]*b2[1], -a2[1]*b2[1],
         a3[0], a3[1], 1,     0,     0, 0, -a3[0]*b3[0], -a3[1]*b3[0],
             0,     0, 0, a3[0], a3[1], 1, -a3[0]*b3[1], -a3[1]*b3[1];
	
	//put data in vector
	B << b0[0], b0[1], b1[0], b1[1], b2[0], b2[1], b3[0], b3[1];
	
	return A.jacobiSvd(ComputeThinU|ComputeThinV).solve(B); // solve A\B and return answer
}

//use a transform matrix to move the coordinates of points from one plane to another
float * transformBlob(cObject * blob, MatrixXf transform){
	float y = blob->Y(); 
	float x = blob->X(); 
	float * newCoords = new float[2];
	newCoords[0] = (transform(0,0)*x + transform(1,0)*y + transform(2,0))/(transform(6,0)*x + transform(7,0)*y + 1); //X
	newCoords[1] = (transform(3,0)*x + transform(4,0)*y + transform(5,0))/(transform(6,0)*x + transform(7,0)*y + 1); //Y

	return newCoords;
}

//same function as above but modified so that it can be called with a float* instead of a cObject
float * transformBlob(float * coordinates, MatrixXf transform){
	float x = coordinates[0]; 
	float y = coordinates[1]; 
	float * newCoords = new float[2];
	newCoords[0] = (transform(0,0)*x + transform(1,0)*y + transform(2,0))/(transform(6,0)*x + transform(7,0)*y + 1); //X
	newCoords[1] = (transform(3,0)*x + transform(4,0)*y + transform(5,0))/(transform(6,0)*x + transform(7,0)*y + 1); //Y

	return newCoords;
}

// get the 4 marker LED coordinates that each camera sees (the corners and middle of the board)
//Note: commented out code here is due to a changing from getting coordinates from cObject to float*. Either should work though
float ** getCornerBlobs(cObject ** blobArray, int numBlobs, Camera * camera, bool isLeft){

	//make a new cObjects to put the best LED selection for in
	cObject * bestNblob = new cObject;
	cObject * bestSblob = new cObject;
	//cObject * bestNangle = new cObject;
	//cObject * bestSangle = new cObject;
	float * bestNangle = new float[2];
	float * bestSangle = new float[2];

	//initialize ideal locations depending upon whether camera is right or left
	int camX = 0;
	int camY = 0;
	if (!isLeft){
		int camY = camera->Height();
		int camX = camera->Width();
	}

	//initialize other variables
	int Nskip, Sskip;
	float bestNDistSq = 10000000;
	float bestSDistSq = 10000000;
	float nAngleVal = 10;
	float sAngleVal = 10;

	//go through all possible points and compare based on distance to camera corners
	//here we are finding board corner LEDs (as opposed to board middle LEDs)
	for (int i = 0; i < numBlobs; i++) {
		float y = blobArray[i]->Y();
		float x = blobArray[i]->X();
		if (pow(x, 2) + pow(y, 2) < bestNDistSq){
			bestNDistSq = pow(x, 2) + pow(y, 2);
			bestNblob = blobArray[i];
			Nskip = i; //save the location of the best upper point so we can filter it out later
		}
		if (pow(x - camX, 2) + pow(y - camY, 2) < bestSDistSq){
			bestSDistSq = pow(x - camX, 2) + pow(y - camY, 2);
			bestSblob = blobArray[i];
			Sskip = i; //save the location of the best lower point so we can filter it out later
		}
	}



	//now convert bestNblob and bestSblob into float arrays
	//this is because of the change from cObjects to float*. If you change back you can ignore.
	float * NewBestNblob = new float[2];
	float * NewBestSblob = new float[2];
	NewBestNblob[0] = bestNblob->X();
	NewBestNblob[1] = bestNblob->Y();
	NewBestSblob[0] = bestSblob->X();
	NewBestSblob[1] = bestSblob->Y();

	//this is me testing to see where the JNI code throws the error
	cout << "1 ";

	//make a new array for the points excluding the 2 corners we already found
		//cObject ** newblobArray = new cObject * [numBlobs-2];
	float ** newblobArray = new float *[numBlobs - 2];					//***THIS IS THE PROBLEM LINE***//

	//again testing to find error
	cout << "2 ";

	//put the points in an array skipping the points we have already determined to be corners
	int k = 0;
	for (int j = 0; j < numBlobs; j++){
		if (j == Nskip || j == Sskip) continue;
		//newblobArray[k] = blobArray[j];
		newblobArray[k][0] = blobArray[j]->X();
		newblobArray[k][1] = blobArray[j]->Y();
		k++;
	}

	//find the other two corners by comparing the angles from the corners we have to the other points.
	//whichever angles are closest to 0 or 180 (depending on right/left) are the angles we want
	for (int ii = 0; ii < k; ii++){
		float nY = bestNblob->Y();
		float nX = bestNblob->X();
		float sY = bestSblob->Y();
		float sX = bestSblob->X();
		float testX = newblobArray[ii][0];
		float testY = newblobArray[ii][1];
		if (abs((sY - testY) / (sX - testX)) < sAngleVal){	//since the smallest y/x results in the smallest tan(y/x) we only need to check y/x
			//bestSangle = newblobArray[ii];
			bestSangle[0] = newblobArray[ii][0];
			bestSangle[1] = newblobArray[ii][1];
			sAngleVal = abs((sY - testY) / (sX - testX));
		}
		if (abs((nY - testY) / (nX - testX)) < nAngleVal){
			//bestNangle = newblobArray[ii];
			bestNangle[0] = newblobArray[ii][0];
			bestNangle[1] = newblobArray[ii][1];
			nAngleVal = abs((nY - testY) / (nX - testX));
		}
	}


	//cObject ** returnArray = new cObject * [4];
	//returnArray[0] = bestNblob;
	//returnArray[1] = bestSblob;
	//returnArray[2] = bestSangle;
	//returnArray[3] = bestNangle;

	float ** returnArray = new float  *[4];
	returnArray[0][0] = NewBestNblob[0];
	returnArray[0][1] = NewBestNblob[1];
	returnArray[1][0]= NewBestSblob[0];
	returnArray[1][1] = NewBestSblob[1];
	returnArray[2][0] = bestSangle[0];
	returnArray[2][1] = bestSangle[1];
	returnArray[3][0] = bestNangle[0];
	returnArray[3][1] = bestNangle[1];

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

//remove float*s from an array of float*
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


//find and return clusters of size nClust
//also returns which camera it was found in
//returns null if none found
pair<float **,int> getClusterN(float***allPoints,int numCams, int nClust){

	//initialize variables
		//float * coordArray = new float [2];
	float ** holdClusters = new float * [nClust];
	int MAX_DIST = 30;
	int whichCam = 0;

	//look through both cameras
	for (int i = 0; i < numCams; i++){
		int maxArrayNum = 0;
		float dist = 0;
		whichCam = i;

		//find how many points there are in the camera we are using
		for (int m = 0; allPoints[i][m][0] != NULL; m++){
			maxArrayNum = m;
		}

		//search through the points in the camera
		for (int j = 0; j < maxArrayNum; j++){
			
			//set the first point in the cluster array to try
			holdClusters[0][0] = allPoints[i][j][0];
			holdClusters[0][1] = allPoints[i][j][1];

			//there is one point in the cluster array so tag is 1
			int tag = 1;

			//compare the other points in the array to the first one
			for (int k = j+1; k < maxArrayNum; k++){
				dist = sqrt(pow(allPoints[i][j][0]-allPoints[i][k][0],2)+pow(allPoints[i][j][1]-allPoints[i][k][1],2));
				
				//if the distance is good then we add it to the next spot in the array and add one to tag
				if (dist < MAX_DIST){
					holdClusters[tag][0] = allPoints[i][k][0];
					holdClusters[tag][1] = allPoints[i][k][1];
					tag++;
				}

				//if tag (the number of points in the array) is equal to the cluster count we want then return the array and the camera we found it in
				//this means that we have to call this function on the biggest cluster groups first
				//also if there is more than 1 point when we call it for a cluster of size 1 it doesn't check to find the right point
				if (tag == nClust){
					pair<float **, int> make_pair(holdClusters, whichCam);
					return pair<float **, int>(holdClusters,whichCam);
				}
			}
		}
	}

	//if nothing is found return a null pointer
	float ** nullPoint;
	pair<float **, int> make_pair(nullPoint,whichCam);
	return pair<float**,int>(nullPoint,whichCam);
}


//find the center of the cluster by taking an average
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

//this is the main function getting called
//it puts all of the other functions together
//call it with a the number of cameras in a list and the list of cameras
vector<double> TransformandCluster(int nCams, Camera ** camera){
	
	//initialize variables
	bool isLeftCam = false;
	int MAX_OFFSET_DIST = 50;
	float * boardArray = getBoardCorners();
	float *** cameraBlobs = new float** [nCams]; //an array of arrays containing gibbot LED coordinates
	vector<double> copy;

	//go through both cameras
	for (int i = 0; i < nCams; i++){
		
		//determine whether camera is right or left -- we will assume ID 199314 is left and 199313 is right
		if (camera[i]->CameraID() == 199314)
		{
			isLeftCam = true;
		}


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
		float **cornerArray = getCornerBlobs(objArray,objcount,camera[i], isLeftCam);


		//use corner blobs to get new transform
		float * transformCorners = new float[8];
		for (int l = 0; l < 4; l++){
			transformCorners[2*l] = cornerArray[l][0];
			transformCorners[2*l+1] = cornerArray[l][0];
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

	//now let's make an array that returns the position of cluster 3, the angle between the arms, and the angle with respect to the board
	float x1, x2, x3, y1, y2, y3, theta1, theta2, theta3;
	x1 = cluster1center[0];
	y1 = cluster1center[1];
	x2 = cluster2center[0];
	y2 = cluster2center[1];
	x3 = cluster3center[0];
	y3 = cluster3center[1];
	float * GibbotPosition = new float[4];
	
	// cluster 3; x in first spot of array, y in second spot
	GibbotPosition[0] = x3;
	GibbotPosition[1] = y3;

	//find angle between arms (theta1) and put in third spot
	float dist1, dist2, dist3;
	dist1 = sqrt(pow(x1-x3,2)+pow(y1-y3,2));
	dist2 = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
	dist3 = sqrt(pow(x2-x3,2)+pow(y2-y3,2));
	theta1 = acos((dist1*dist1+dist2*dist2-dist3*dist3)/(2*dist1*dist2))*180/3.14159265; // theta1 in degrees

	//find absolute angle from center gibbot to arm "3"
	theta2 = atan((y3-y1)/(x3-x1))*180/3.14159265;

	if (x1 > x3)
	{
		theta2 += 180; //if x1 is larger than x3 then angle in opposite quadrant
	}

	//find absolute angle from center to arm "2"
	theta3 = atan((y2 - y1) / (x2 - x1)) * 180 / 3.1415265;

	if (x1 > x2)
	{
		theta3 += 180;
	}

	//add absolute angles to get relative angle between the two arms ***theta 1 is degrees arm 2 is in clockwise direction
	theta1 = theta3 - theta2;

	
	//finally return the vector here:
	vector<double> rvec;

	rvec[0] = x3;
	rvec[1] = y3;
	rvec[2] = theta1;
	rvec[3] = theta2;

	return rvec;
}
