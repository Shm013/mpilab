/*
 *
 *    matrix.h - Matrix class based on vector.
 *    Copyright (C) 2016 Nikolay Shamanovich. 
 *
 *    This program is distributed under the term of the WTFPL:
 *
 *    0. You just DO WHAT THE FUCK YOU WANT TO.
 *
 */


#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

// Matrix class based on vector.
template <typename T>
class Matrix: public std::vector<T> {
    int col;
    int row;
public:

    class Wrong_size {}; // matrix must be correct size to mutiply;
    
    class Out_of_row {}; // used in get_row;
    class Out_of_col {}; // used in get_col;

    Matrix() : Matrix(0, 0) {}

    Matrix(int columns, int rows, T init=0) :
        std::vector<T>(columns*rows, init) {
            col = columns;
            row = rows;
    }

    int cols() { return col; }
    int rows() { return row; }

    std::vector<T> get_col(int n); // getting column number 'n' as vector;
    std::vector<T> get_row(int n); // getting row number 'n' as vector;
    
    // matrix multipliacation: A = B * C. (A, B, C - Matrix);
    // I could not do friend function, sorry;
    Matrix<T> operator* (const Matrix<T> &);
};


typedef Matrix<double> MatrixD;
typedef Matrix<int>    MatrixI;


template <typename T>
std::vector<T> Matrix<T>::get_row(int n) {
    Matrix<T> mA = *this;

    if (n >= mA.row)
        throw Out_of_row();
    
    std::vector<T> resVec(           // result row
            mA.begin()+n*mA.col,     // from begin row
            mA.begin()+(n+1)*mA.col  // to end row;
            );

    return resVec;
}


template <typename T>
std::vector<T> Matrix<T>::get_col(int n) {
    Matrix<T> mA = *this;

    if (n >= mA.col)
        throw Out_of_col();
    
    std::vector<T> resVec;

    // getting column element;
    for(int i=0; i<row; i++)
        resVec.push_back(mA[mA.col*i+n]); 

    return resVec;
}


template <typename T>
Matrix<T> Matrix<T>::operator* (const Matrix<T> &mB) {

    Matrix<T> mA = *this;

    if (mA.col > mB.col || mA.row < mB.row) {
        throw Wrong_size();
    }
    if (mA.col != mB.row || mA.row != mB.col) {
        throw Wrong_size();
    }

    int rowcol = mB.col;

    Matrix<T> result(rowcol, rowcol);

    for (int row = 0; row < rowcol; row++) {
        for (int col = 0; col < rowcol; col++) {
            for (int inner = 0; inner < mA.col; inner++) {
                result[row*rowcol+col] +=
                    mA[row*mA.col+inner] * mB[inner*rowcol+col];
            }
            //cout << result[row*rowcol+col] << "  ";
        }
        //cout << "\n";
    }
    return result;              // All done!
}


#endif //MATRIX_H
