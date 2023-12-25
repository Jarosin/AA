#include <iostream>
#include "../inc/io.hpp"

int* read_array(int *total_len)
{
    int len;
    std::cout << "Введите длину массива: ";
    std::cin >> len;
    std::cout << "Введите " << len << " элементов массива через пробел: ";
    int *array = new int[len];
    for (int i = 0; i < len; i++)
    {
        std::cin >> array[i];
    }
    *total_len = len;
    return array;
}

int print_array(int *array, int len) {
    for (int i = 0; i < len; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
    return 0;
}
