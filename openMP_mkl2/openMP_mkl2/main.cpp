#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include "time.h"
#include "omp.h"
#include "mkl.h"

using namespace std;
using namespace std::chrono;

int main() {
    int matrix_layout = LAPACK_COL_MAJOR;
    int n = 2, nrhs = 1, nriter = 70000000;
    int lda = 2, ldb = 2;
    int ipiv[n];
    
    double *a = new double[n*n*nriter];
    double *b = new double[n*nrhs*nriter];

    for (int i = 0; i < n*n*nriter; i++) {
        a[i] = (std::rand() % 100) / (100 + 0.0);
        if (i % n == 0) {
            a[i] += n;
        }
    }
    
    for (int i = 0; i < n*nrhs*nriter; i++){
        b[i] = (std::rand() % 100) / (100 + 0.0);
    }
    
    auto start = high_resolution_clock::now();

#pragma omp parallel
    {
#pragma omp for schedule(dynamic)
        for (int i = 0; i < nriter; i++) {
            LAPACKE_dgesv(matrix_layout, n, nrhs, a+(n*n*i), lda, ipiv, b+(n*nrhs*i), ldb);
        }
    }

    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: " << duration.count() << " microseconds." << endl;
    
    return 0;
}

// the average running time of the code is 6.2 sec.

