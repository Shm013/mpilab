#include <iostream>

#include "matrix.h"

using namespace std;


int main(int argc, char* argv[])
{
    Matrix<double> B(5, 5);
    Matrix<double> A(5, 5);

    int i=1;
    for (Matrix<double>::iterator it = A.begin() ; it != A.end(); ++it)
        *it=i++;
    for (Matrix<double>::iterator it = B.begin() ; it != B.end(); ++it)
        *it=i++;

    Matrix<double> C;
    C=A*B;

    for (Matrix<double>::iterator it = C.begin() ; it != C.end(); ++it)
        cout << ' ' << *it;
    cout << '\n';
}
