// based on: 
// http://eigen.tuxfamily.org/dox-devel/group__TutorialLinearAlgebra.html

#include  <iostream>
#include "Eigen/Dense"

using namespace std;
using namespace Eigen;

int main()
{
    MatrixXf A = MatrixXf::Random(3,2);
    cout << "Here is the matrix A:\n" << A << endl;

    VectorXf b = VectorXf::Random(3);
    cout << "Here is the right hand side b:\n" << b << endl;

    cout << "The least-squares solutions is:\n";
    cout << A.jacobiSvd(ComputeThinU|ComputeThinV).solve(b) << endl;
}
