#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include "omp.h"
#include "mkl.h"
#include "time.h"

using namespace std;
using namespace std::chrono;

int main() {
    CBLAS_LAYOUT Layout = CblasRowMajor;    // MATLAB: column major
    CBLAS_TRANSPOSE transa = CblasNoTrans;
    CBLAS_TRANSPOSE transb = CblasNoTrans;
    int n = 2, m = 2, k = 2;
    int nriter = 50000000;
    int lda = 2, ldb = 2, ldc = 2;
    double alpha = 4, beta = 2;
    
    
    double *A = new double[n*n*nriter];
    double *B = new double[n*n*nriter];
    double *C = new double[n*n*nriter];
//    double *A = (double *)malloc(sizeof(double) *n*n*nriter);
//    double *B = (double *)malloc(sizeof(double) *n*n*nriter);
//    double *C = (double *)malloc(sizeof(double) *n*n*nriter);
    
    for (int i = 0; i < n*n*nriter; i++) {
        A[i] = (rand() % 100) / (100 + 0.0);
        B[i] = (rand() % 100) / (100 + 0.0);
        C[i] = (rand() % 100) / (100 + 0.0);
    }
    
    auto start = high_resolution_clock::now();
    
#pragma omp parallel 
    {
#pragma omp for schedule(dynamic)
        for (int i = 0; i<nriter; i++) {
            cblas_dgemm(Layout, transa, transb, m, n, k, alpha, A+(n*n*i), lda, B+(n*n*i), ldb, beta, C+(n*n*i), ldc);
        }
    } // end of omp
    
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "Time taken by function: " << duration.count() << " seconds." << endl;
    
//    for (int i = 0; i < n*n*nriter; i++) {
//           std::cout << i << " " << C[i] << std::endl;
//
//    }
    return 0;
}

// dgemm with openMP, the average time taken by function is 8.5 sec.

