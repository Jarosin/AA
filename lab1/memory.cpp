#include "memory.hpp"

int **alloc_matrix(int n, int m) {
    if (n < 1 || m < 1) {
        return nullptr;
    }
    int **matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[m];
    }
    return matrix;
}

int free_matrix(int **matrix, int n) {
    if (n < 1 || matrix == nullptr) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}
