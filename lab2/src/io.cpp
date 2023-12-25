#include "../inc/io.hpp"
#include <iostream>

Matrix* read_matrix() {
    int columns, rows;
    std::cout << "Введите кол-во строк в матрице: ";
    std::cin >> rows;
    if (rows <= 0) {
        std::cout << "Ошибка ввода";
        return nullptr;
    }
    std::cout << "Введите кол-во столбцов в матрице: ";
    std::cin >> columns;
    if (columns <= 0) {
        std::cout << "Ошибка ввода";
        return nullptr;
    }
    Matrix *mtr = new Matrix(rows, columns);
    std::cout << "Введите каждый элемент матрицы через пробел\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cin >> (*mtr).matrix_[i][j];
        }
    }
    return mtr;
}
