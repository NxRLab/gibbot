#include <iostream>
#include <C:\Users\Brigitte\Documents\jni2.h>
#include <windows.h>
#include "CameraJNI.h"



using namespace std;

#define ARRAY_SIZE 7
double myarr[ARRAY_SIZE] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 };

// double *sendArrayToJava() {
// using JNI framework, write code to send myarr into a Java program
//}

JNIEXPORT jdoubleArray JNICALL Java_CameraJNI_GetArrayFromC
(JNIEnv *, jclass){

	int i;
	cout << "contents or myarr are: " << endl;
	for (i = 0; i < ARRAY_SIZE; i++) {
		cout << "myarr[i] = " << myarr[i] << endl;
	}
	return 0;
}

//gcc -dll
