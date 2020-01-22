#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include "mkl.h"
#include "time.h"
#include "mkl_dgemm.hpp"

using namespace std;
using namespace std::chrono;

int mkl_dgemm() {
    CBLAS_LAYOUT Layout = CblasRowMajor;
    CBLAS_TRANSPOSE transa = CblasNoTrans;
    CBLAS_TRANSPOSE transb = CblasNoTrans;
    int n = 2, m = 2, k = 2;
    int nriter = 50000000;
    int lda = 2, ldb = 2, ldc = 2;
    double alpha = 4, beta = 2;
    
    
    double *A = new double[n*n*nriter];
    double *B = new double[n*n*nriter];
    double *C = new double[n*n*nriter];
    
    for (int i = 0; i < n*n*nriter; i++) {
        A[i] = (rand() % 100) / (100 + 0.0);
        B[i] = (rand() % 100) / (100 + 0.0);
        C[i] = (rand() % 100) / (100 + 0.0);
    }
    
    auto start = high_resolution_clock::now();
    
    
    for (int i = 0; i<nriter; i++) {
        cblas_dgemm(Layout, transa, transb, m, n, k, alpha, A+(n*n*i), lda, B+(n*n*i), ldb, beta, C+(n*n*i), ldc);
    }
    
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    
    
    cout << "Time taken by function: " << duration.count() << " seconds." << endl;
    
    return 0;
}


// dgemm code w/o using openMP, the time taken by function is 19 sec.

