/*
 *
 *    mmul-mpi - parallem matrix multiplication demo based on mpi.
 *    Copyright (C) 2016 Nikolay Shamanovich. 
 *
 *    This program is distributed under the term of the WTFPL:
 *
 *    0. You just DO WHAT THE FUCK YOU WANT TO.
 *
 */


#include <iostream>
#include <ctime>
#include <mpi.h>

#include "matrix.h"

using namespace std;

//void MatrixMultiplicationMPI(double *&A, double *&B, double *&C, int &Size) {
template <typename T>
Matrix<T> mmulmpi(const Matrix<T> &A, const Matrix<T> &B) { 
	
	//int dim = Size;
	//int i, j, k, p, ind;
	//double temp;
    /*
	MPI_Status Status;
	int ProcPartSize = dim/ProcNum; 
	int ProcPartElem = ProcPartSize*dim; 
    */

	double bufA[10]; 
    /*
	double* bufB = new double[ProcPartElem];
	double* bufC = new double[ProcPartElem];
    */

	//int ProcPart = dim/ProcNum, part = ProcPart*dim;
	//if (ProcRank == 0) {
		//Flip(B, Size);
	//}
	
    // ?
    MPI::COMM_WORLD.Scatter(
            &A[0], 5, MPI::DOUBLE,      // send 5 item from A
            &bufA, 5, MPI::DOUBLE, 0    // to bufA (sending from 0 proc).
            );
	//MPI_Scatter(A, part, MPI_DOUBLE, bufA, part, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	//MPI_Scatter(B, part, MPI_DOUBLE, bufB, part, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
    for(int i=0; i< 5; i++)
        cout << bufA[i];
    cout << endl;

    /*
	temp = 0.0;
	for (i=0; i < ProcPartSize; i++) {
		for (j=0; j < ProcPartSize; j++) {
			for (k=0; k < dim; k++) 
				temp += bufA[i*dim+k]*bufB[j*dim+k];
			bufC[i*dim+j+ProcPartSize*ProcRank] = temp;
			temp = 0.0;
		}
	}

	int NextProc; int PrevProc;
	for (p=1; p < ProcNum; p++) {
		NextProc = ProcRank+1;
		if (ProcRank == ProcNum-1) 
			NextProc = 0;
		PrevProc = ProcRank-1;
		if (ProcRank == 0) 
			PrevProc = ProcNum-1;
		MPI_Sendrecv_replace(bufB, part, MPI_DOUBLE, NextProc, 0, PrevProc, 0, MPI_COMM_WORLD, &Status);
		temp = 0.0;
		for (i=0; i < ProcPartSize; i++) {
			for (j=0; j < ProcPartSize; j++) {
				for (k=0; k < dim; k++) {
					temp += bufA[i*dim+k]*bufB[j*dim+k];
				}
				if (ProcRank-p >= 0 ) 
					ind = ProcRank-p;
				else ind = (ProcNum-p+ProcRank);
				bufC[i*dim+j+ind*ProcPartSize] = temp;
				temp = 0.0;
			}
		}
	}
	
	MPI_Gather(bufC, ProcPartElem, MPI_DOUBLE, C, ProcPartElem, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	delete []bufA;
	delete []bufB;
	delete []bufC;
    */
    return Matrix<T>(2,2);
}


int main(int argc, char** argv)
{
    MPI::Init(argc, argv);

    const int mpi_rank = MPI::COMM_WORLD.Get_rank();
    const int mpi_size = MPI::COMM_WORLD.Get_size();

    if (mpi_rank==0) {

        cout << "Proc #" << mpi_rank << ": I'm MASTER!\n";

        // matrix only on 0 proc;
        MatrixD *A = new MatrixD(3,4);
        MatrixD *B = new MatrixD(4,3);

        // fill in the matrix sequentially from 1;
        int i=1;
        for (Matrix<double>::iterator it = A->begin() ; it != A->end(); ++it)
            *it=i++;
        for (Matrix<double>::iterator it = B->begin() ; it != B->end(); ++it)
            *it=i++;

        // testing
        for (Matrix<double>::iterator it = B->begin() ; it != B->end(); ++it)
            cout << ' ' << *it;
        cout << endl;

        MatrixD *C = new MatrixD(B->cols(), A->rows());

        // buffer size for each proc;
        const int proc_buf_size = C->size()/mpi_size; 

    } else {
    
        cout << "Proc #" << mpi_rank << ": noting to do!\n";
    }

    /*
    vector<double> tmp = A.get_col(2);
    for (vector<double>::iterator it = tmp.begin() ; it != tmp.end(); ++it)
        cout << ' ' << *it;
    cout << '\n';
    */
    

    // result matrix output;
    
    /*
    if (mpi_rank==0)
        for (Matrix<double>::iterator it = C.begin() ; it != C.end(); ++it)
            cout << ' ' << *it;
        cout << '\n';
        */

    MPI::Finalize();
    return 0;
}
