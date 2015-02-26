//Cluster Header file

#include <stdio.h>
#include "cameralibrary.h"


using namespace std;
using namespace CameraLibrary;

//=== If equals 6 ===

float * findCenters(float ** bArray){

	float * ansArray = new (nothrow) float [6];
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




//=== If greater than 6 ===

//Separate by camera.

//Perform above function for each camera.

//Compare groups for each camera. Average closest groups

//After compare size of groups. Assign group based on which camera had the higher group size (with an overlap, one camera will always have full set)


//=== If less than 6 ===

//At least one LED is not being detected by the camera. Report error.

