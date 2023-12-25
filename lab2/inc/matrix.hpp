#ifndef MATRIX_H
#define MATRIX_H

#pragma once

#include <ctime>

class Matrix
{
public:
    Matrix(size_t rows, size_t columns);
    ~Matrix();
    Matrix *MultVinograd(Matrix &other);
    Matrix *MultOptimized(Matrix &other);
    Matrix* MultClassic(Matrix &other);
    int PrintMatrix();
    bool isEqual(Matrix &other);
public:
    size_t rows_;
    size_t columns_;
    int **matrix_;
};

#endif
