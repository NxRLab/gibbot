#include <iostream>
using namespace std;

#define ARRAY_SIZE 7
double myarr[ARRAY_SIZE] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};

// double *sendArrayToJava() {
// using JNI framework, write code to send myarr into a Java program
//}


// uncomment to compile and test with output
 
int main(void) {
int i;

cout << "contents or myarr are: " << endl;
for(i = 0; i < ARRAY_SIZE; i++) {
cout << "myarr[i] = " << myarr[i] << endl;
}

return 0;
}

