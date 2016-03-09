#include <iostream>
#include <ctime>

#include "matrix.h"

using namespace std;


int main(int argc, char* argv[])
{
    Matrix<double> B(500, 500);
    Matrix<double> A(500, 500);

    int i=1;
    for (Matrix<double>::iterator it = A.begin() ; it != A.end(); ++it)
        *it=i++;
    for (Matrix<double>::iterator it = B.begin() ; it != B.end(); ++it)
        *it=i++;

    Matrix<double> C;

    time_t begin_t, end_t;
    begin_t = clock();

    C=A*B;

    end_t = clock();

    cout << "Execution time: " << end_t - begin_t << "ms\n";

    /*
    for (Matrix<double>::iterator it = C.begin() ; it != C.end(); ++it)
        cout << ' ' << *it;
    cout << '\n';
    */
}
