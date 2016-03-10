//#include <iostream>
//#include <conio.h>
#include <mpi.h>
#include <stdio.h>

using namespace std;

#define NMAX 200 // у нас будут массивы 10х10 - значит 100 элементов
int ProcNum=0;
int ProcRank=0;

void MatrixMultiplicationMPI(double *&A, double *&B, double *&C, int &Size) {
	
	int dim = Size;
	int i, j, k, p, ind;
	double temp;
	MPI_Status Status;
	int ProcPartSize = dim/ProcNum; 
	int ProcPartElem = ProcPartSize*dim; 
	double* bufA = new double[ProcPartElem];
	double* bufB = new double[ProcPartElem];
	double* bufC = new double[ProcPartElem];
	int ProcPart = dim/ProcNum, part = ProcPart*dim;
	//if (ProcRank == 0) {
		//Flip(B, Size);
	//}
	
	MPI_Scatter(A, part, MPI_DOUBLE, bufA, part, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Scatter(B, part, MPI_DOUBLE, bufB, part, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
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
}

int main() {	

	 MPI_Init(NULL, NULL);

    // Get the number of processes
    int size, Size=128;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	ProcNum=size;

    // Get the rank of the process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	ProcRank=rank;

	double *A=new double[Size*Size];
	double *B=new double[Size*Size];
	double *C=new double[Size*Size];

	/*for(int i=0;i<100;i++){
		A[i]=1;
		B[i]=1;
		C[i]=0;
	}*/
	
	double val=2; 
	//memset (A,(double)val,sizeof(double)*Size*Size);
	fill_n(A,Size*Size,val);
	fill_n(B,Size*Size,val);
	fill_n(C,Size*Size,val);

	double startwtime=0.0, endwtime; 
	if(rank==0) { startwtime = MPI_Wtime(); }

	MatrixMultiplicationMPI(A,B,C,Size);

	if(rank==0){
		endwtime = MPI_Wtime();
		printf("wall clock time = %f\n", endwtime-startwtime); 

		cout<<"Parallelnoe umnozhenie matrix"<<endl;
		for(int i=0;i<Size*Size;i++){
			//cout<<C[i]<<" ";
		}
		cout<<endl;

	}
	MPI_Finalize();
    return 0;
}
