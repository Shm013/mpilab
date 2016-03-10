/*
 *
 *    mmul - Matrix class demo programm.
 *    Copyright (C) 2016 Nikolay Shamanovich. 
 *
 *    This program is distributed under the term of the WTFPL:
 *
 *    0. You just DO WHAT THE FUCK YOU WANT TO.
 *
 */


#include <iostream>
#include <ctime>

#include "matrix.h"

using namespace std;


int main(int argc, char* argv[])
{
    Matrix<double> B(500, 500);
    Matrix<double> A(500, 500);

    // fill in the matrix sequentially from 1;
    int i=1;
    for (Matrix<double>::iterator it = A.begin() ; it != A.end(); ++it)
        *it=i++;
    for (Matrix<double>::iterator it = B.begin() ; it != B.end(); ++it)
        *it=i++;

    Matrix<double> C; // result matrix;

    time_t begin_t, end_t;
    begin_t = clock();

    C=A*B;

    end_t = clock();

    cout << "Execution time: " << end_t - begin_t << "ms\n";

    // result matrix output;
    /*
    for (Matrix<double>::iterator it = C.begin() ; it != C.end(); ++it)
        cout << ' ' << *it;
    cout << '\n';
    */
}
