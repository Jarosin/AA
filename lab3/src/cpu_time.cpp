#include "../inc/cpu_time.hpp"
#include <random>
#include <iostream>
#include "../inc/algs.hpp"
#define NUMBER_OPER 1000

int *fill_array(int len)
{
    int *array = new int[len];
    for (int i = 0; i < len; i++)
    {
        array[i] = std::rand() % (3 * len) + 1;
        // array[i] = i;
        // array[i] = len - i;
    }
    return array;
}

double get_time_insert(int *array, int len)
{
    clock_t start_t, end_t;
    double total_t;

    start_t = clock();
    insert_sort(array, len);
    end_t = clock();
    total_t = (double)(end_t - start_t) / (CLOCKS_PER_SEC);
    return total_t;
}

double get_time_heap(int *array, int len)
{
    clock_t start_t, end_t;
    double total_t;

    array = fill_array(len);
    start_t = clock();
    heap_sort(array, len);
    end_t = clock();
    total_t = (double)(end_t - start_t) / (CLOCKS_PER_SEC);
    return total_t;
}

double get_time_bitonic(int *array, int len)
{
    clock_t start_t, end_t;
    double total_t;

    array = fill_array(len);
    start_t = clock();
    bitonic_sort(array, len, 1);
    end_t = clock();
    total_t = (double)(end_t - start_t) / (CLOCKS_PER_SEC);
    return total_t;
}


void measure_time(size_t start, size_t max_len, size_t step)
{

    double st1, st2, st3;
    std::cout.precision(3);
    std::cout << "Все время указано в милисекундах\n";
    std::cout << "Длина массива, Вставки, Пирамидальная, Битонная\n";
    for (size_t i = start; i <= max_len; i += step)
    {
        if (i == 0)
            continue;
        st1 = st2 = st3 = 0;

        for (size_t j = 0; j < NUMBER_OPER; j++)
        {
            int *array = fill_array(i);
            int *matrix[3];
            for (int r = 0; r < 3; r++)
            {
                matrix[r] = new int[i];
                for (int k = 0; k < i; k++)
                {
                    matrix[r][k] = array[k];
                }
            }
            st1 += get_time_insert(matrix[0], i);
            st2 += get_time_heap(matrix[1], i);
            st3 += get_time_bitonic(matrix[2], i);

            delete[] array;
            for (int k = 0; k < 3; k++) {
                delete[] matrix[k];
            }
        }

        if (st1)
            st1 /= (NUMBER_OPER - 2);
        if (st2)
            st2 /= (NUMBER_OPER - 2);
        if (st3)
            st2 /= (NUMBER_OPER - 2);

        std::cout << std::fixed << i << "," << st1 << "," << st2 << "," << st3 << "\n";
    }
}

void measure_time_two(size_t start, size_t max_len, size_t step)
{

    double st1, st2, st3;
    std::cout.precision(3);
    std::cout << "Все время указано в милисекундах\n";
    std::cout << "Длина массива, Вставки, Пирамидальная, Битонная\n";
    for (size_t i = start; i <= max_len; i *= 2)
    {
        if (i == 0)
            continue;
        st1 = st2 = st3 = 0;

        for (size_t j = 0; j < NUMBER_OPER; j++)
        {
            int *array = fill_array(i);
            int *matrix[3];
            for (int r = 0; r < 3; r++)
            {
                matrix[r] = new int[i];
                for (int k = 0; k < i; k++)
                {
                    matrix[r][k] = array[k];
                }
            }
            st1 += get_time_insert(matrix[0], i);
            st2 += get_time_heap(matrix[1], i);
            st3 += get_time_bitonic(matrix[2], i);

            delete[] array;
            for (int k = 0; k < 3; k++) {
                delete[] matrix[k];
            }
        }

        if (st1)
            st1 /= (NUMBER_OPER - 2);
        if (st2)
            st2 /= (NUMBER_OPER - 2);
        if (st3)
            st2 /= (NUMBER_OPER - 2);

        std::cout << std::fixed << i << "," << st1 << "," << st2 << "," << st3 << "\n";
    }
}
