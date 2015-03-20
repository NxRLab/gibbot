//Cluster Header file

#include <stdio.h>
#include "cameralibrary.h"
#include <vector>

#define MAX_D 25

 
///=== NEED TO CALCULATE NEW TRANSFORM MATRIX BASED ON CORNER BLOBS ===

using namespace std;
using namespace CameraLibrary;

//=== If equals 6 ===

float * findCenters(float ** bArray){

	float * ansArray = new float [6];
	int j = 0, tag = 0;
	float dist;
	int numHold1 = -1;
	int numHold2 = -1;
	int numHold3 = -1;
	int hold2 = -1;
	float * group1;
	float * group2[2];
	float * group3[3];

//sort objects in to their cluster a.k.a. group#
	for (j = 0; j < 6; j++){
		int k;
		tag = 0;
		if (j == hold2 || j == numHold2 || j == numHold3) {continue;} //if number already belongs to a group, skip it
		for (k = j+1; k < 6; k++){
			dist = sqrt(pow(bArray[j][0]-bArray[k][0],2)+pow(bArray[j][1]-bArray[k][1],2)); //[0] gets x, [1] gets y
			if (dist < 50){                //max distance to be in cluster is 50 millimeters
				tag++;
				if (tag == 2){           
					numHold2 = numHold1;    //save numbers in group so we can skip them later
					numHold3 = k;           // " "
				}
				numHold1 = k;               // " "
			}
		}
		if (tag == 1){hold2 = numHold1;}    // " "
		switch (tag){
		case 0:
			group1 = bArray[j];

		case 1:
			group2[0] = bArray[j];
			group2[1] = bArray[hold2];
		case 2:
			group3[0] = bArray[j];
			group3[1] = bArray[numHold2];
			group3[2] = bArray[numHold3];
		}
	}

//Pick point and compare lengths to other points. If 2 other points closer that **20** millimeters assign to group 3. If 1 point group 2. Else group 1.

//***If assigned to group 1 and group 1 is not empty then make another group.

//Average positions for each group and return location
	ansArray[0] = group1[0];
	ansArray[1] = group1[1];
	ansArray[2] = (group2[0][0] + group2[1][0])/2;
	ansArray[3] = (group2[0][1] + group2[1][1])/2;
	ansArray[4] = (group3[0][0] + group3[1][0] + group3[2][0])/3;
	ansArray[5] = (group3[0][1] + group3[1][1] + group3[2][1])/3;

	//note: coordinates should already be rotated at this point

	return ansArray; // ansArray = {group1.X, group1.Y, group2.X, group2.Y, group3.X, group3.Y}

}

float * getClusters(float ** blobArray, int numPoints){
/* Get all points (assume points are already transformed)*/
//int numPoints = 0;
float * clusterCenters = new (nothrow) float [6];
//cObject  * blobs;
//int i = 0;
//for (i = 0; blobArray[i] != NULL; i++) {numPoints = numPoints+1;}

//Get rid of reference points
// === Here either compare points to known reference points or only pass function non reference points ===

//If total points now is 6 then continue

if (numPoints == 6){
	clusterCenters = findCenters(blobArray);
}

//If total points > 6 perform overlap calculations

//If total points < 6 report error


return clusterCenters;
}


/* === Different Approach ===
float * VecAvg(vector<float *> vec){
	float * sum = new float [2];
	for (int i = 0; i < vec.size(); i++){
		sum[0] += vec.at(i)[0];
		sum[1] += vec.at(i)[1];
	}
	sum[0] = sum[0]/vec.size();
	sum[1] = sum[1]/vec.size();
	return sum;
}
*/

/* 
float * dealWithAllBlobs(float **bArray){
	vector<float *> bVec;
	vector<float *> vec1;
	vector<float *> vec2;
	vector<float *> vec3;
	vector<float *> shitVec;
	float x, y, x1, y1, x2, y2, x3, y3;

	for (int m = 0; bArray[m] != NULL; m++){
		bVec.push_back(bArray[m]);
	}
	for (int q = 0; q < bVec.size(); q++){
		x = bVec.at(q)[0];
		y = bVec.at(q)[1];
		
		if (q==0){
			vec1.push_back(bVec.at(q));
			x1 = vec1.front()[0];
			y1 = vec1.front()[1];
		}
		else if (sqrt(pow(x - x1,2)+pow(y-y1,2)) < MAX_D){
			vec1.push_back(bVec.at(q));
		}
		else if (vec2.size() == 0){
			vec2.push_back(bVec.at(q));
			x2 = vec2.front()[0];
			y2 = vec2.front()[1];
		}
		else if (sqrt(pow(x - x2,2)+pow(y-y2,2)) < MAX_D){
			vec2.push_back(bVec.at(q));
		}
		else if (vec3.size() == 0){
			vec3.push_back(bVec.at(q));
			x3 = vec3.front()[0];
			y3 = vec3.front()[1];
		}
		else if (sqrt(pow(x - x3,2)+pow(y-y3,2)) < MAX_D){
			vec3.push_back(bVec.at(q));
		}
		else {
			shitVec.push_back(bVec.at(q));
		}
	}
	vector<float *> topSpot;
	//start at top y
	if (VecAvg(vec1)[1] > VecAvg(vec2)[1]){
		if (VecAvg(vec1)[1] > VecAvg(vec3)[1])
			topSpot = vec1;
		else 
			topSpot = vec3;
	}
	else if (VecAvg(vec2)[1] > VecAvg(vec3)[1]) topSpot = vec2;		
	else topSpot = vec3;
			
	

}

*/
//=== If greater than 6 ===

//Separate by camera.

//Perform above function for each camera.

//Compare groups for each camera. Average closest groups

//After compare size of groups. Assign group based on which camera had the higher group size (with an overlap, one camera will always have full set)


//=== If less than 6 ===

//At least one LED is not being detected by the camera. Report error.

