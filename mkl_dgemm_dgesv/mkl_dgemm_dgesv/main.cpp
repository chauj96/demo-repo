#include <iostream>
#include "mkl.h"
#include "mkl_dgemm.hpp"
#include "mkl_dgesv.hpp"


int mkl_dgemm();
int mkl_dgesv();

int main() {
    int runFunc;
    
    runFunc = mkl_dgesv();
    return 0;
}
