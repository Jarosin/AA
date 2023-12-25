#include "../inc/matrix.hpp"
#include <vector>
#include <iostream>

Matrix::Matrix(size_t rows, size_t columns)
{
    matrix_ = new int*[rows];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix_[i] = new int[columns];
        }
    }
    rows_ = rows;
    columns_ = columns;
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows_; i++) {
        delete[] matrix_[i];
    }
    delete[] matrix_;
}

Matrix* Matrix::MultVinograd(Matrix &other)
{
    Matrix *res = new Matrix(rows_, other.columns_);
    std::vector<int> row_sum, col_sum;
    row_sum.resize(rows_, 0);
    col_sum.resize(other.rows_, 0);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.rows_ / 2; j++) {
            row_sum[i] = row_sum[i] + matrix_[i][2 * j] * matrix_[i][2 * j + 1];
        }
    }
    for (size_t i = 0; i < other.columns_; i++)
        for (size_t j = 0; j < other.rows_ / 2; j++)
            col_sum[i] = col_sum[i] + other.matrix_[2 * j][i] *
             other.matrix_[2 * j + 1][i];
    for (size_t i = 0; i < rows_; i++)
        for (size_t j = 0; j < other.columns_; j++) {
            res->matrix_[i][j] = -row_sum[i] - col_sum[j];
            for (size_t k = 0; k < other.rows_ / 2; k++)
                res->matrix_[i][j] = res->matrix_[i][j]
                + (matrix_[i][2 * k + 1] + other.matrix_[2 * k][j]) *
                (matrix_[i][2 * k] + other.matrix_[2 * k + 1][j]);
        }
    if (other.rows_ % 2 == 1)
        for(size_t i = 0; i < rows_; i++)
            for(size_t j = 0; j < other.columns_; j++)
                res->matrix_[i][j] = res->matrix_[i][j] + matrix_[i][other.rows_ - 1] * other.matrix_[other.rows_ - 1][j];
    return res;
}

Matrix* Matrix::MultOptimized(Matrix &other)
{
    Matrix *res = new Matrix(rows_, other.columns_);
    int half_rows = other.rows_ / 2;
    std::vector<int> row_sum, col_sum;
    row_sum.resize(rows_, 0);
    col_sum.resize(other.rows_, 0);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < half_rows; j++) {
            row_sum[i] += matrix_[i][j << 1] * matrix_[i][(j << 1) + 1];
        }
    }
    for (size_t i = 0; i < other.columns_; i++)
        for (size_t j = 0; j < half_rows; j++)
            col_sum[i] += other.matrix_[j << 1][i] *
             other.matrix_[(j << 1) + 1][i];
    for (size_t i = 0; i < rows_; i++)
        for (size_t j = 0; j < other.columns_; j++) {
            res->matrix_[i][j] = -row_sum[i] - col_sum[j];
            for (size_t k = 0; k < half_rows; k++) {
                int column = k << 1;
                res->matrix_[i][j] += (matrix_[i][column + 1] + other.matrix_[column][j]) *
                (matrix_[i][column] + other.matrix_[column + 1][j]);
            }
        }
    if (other.rows_ % 2 == 1) {
        int rows = other.rows_ - 1;
        for(size_t i = 0; i < rows_; i++)
            for(size_t j = 0; j < other.columns_; j++)
                res->matrix_[i][j] += matrix_[i][rows] * other.matrix_[rows][j];
    }
    return res;
}

Matrix* Matrix::MultClassic(Matrix &other)
{
    if (columns_ != other.rows_)
        return nullptr;

    Matrix *res = new Matrix(rows_, other.columns_);
    size_t n = rows_;
    size_t m = other.rows_;
    size_t t = other.columns_;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < t; j++)
            for (int k = 0; k < m; k++)
                res->matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];

    return res;
}

int Matrix::PrintMatrix() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
            std::cout << matrix_[i][j] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}

bool Matrix::isEqual(Matrix &other)
{
    if (rows_ != other.rows_ || columns_ != other.columns_) {
        return false;
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < rows_; j++) {
            if (matrix_[i][j] != other.matrix_[i][j])
                return false;
        }
    }
    return true;
}
