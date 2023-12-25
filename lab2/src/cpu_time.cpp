#include "../inc/cpu_time.hpp"
#include "../inc/matrix.hpp"
#include <random>
#include <iostream>
#define NUMBER_OPER 1000

double get_time_vinograd(Matrix &first_matrix, Matrix &second_matrix) {
    clock_t start_t, end_t;
    double total_t;

    start_t = clock();
    Matrix *res = first_matrix.MultVinograd(second_matrix);
    end_t = clock();
    total_t = (double) (end_t - start_t);
    delete res;
    return total_t;
}

double get_time_optimized(Matrix &first_matrix, Matrix &second_matrix) {
    clock_t start_t, end_t;
    double total_t;

    start_t = clock();
    Matrix *res = first_matrix.MultOptimized(second_matrix);
    end_t = clock();
    total_t = (double) (end_t - start_t);
    delete res;
    return total_t;
}

double get_time_classic(Matrix &first_matrix, Matrix &second_matrix) {
    clock_t start_t, end_t;
    double total_t;

    start_t = clock();
    Matrix *res = first_matrix.MultClassic(second_matrix);
    end_t = clock();
    total_t = (double) (end_t - start_t);
    delete res;
    return total_t;
}

void random_mtr(Matrix &mtr)
{
    for (size_t i = 0; i < mtr.rows_; i++)
        for (size_t j = 0; j < mtr.columns_; j++)
            mtr.matrix_[i][j] = rand() % 100;
}

void measure_time(size_t start, size_t max_len, size_t step) {


    double st1, st2, st3;
    std::cout.precision(3);

    std::cout << "Размер, Виноград, Оптимизированный Виноград, Классический\n";
    for (size_t i = start; i <= max_len; i += step)
    {
        if (i == 0)
            continue;
        Matrix mtr1(i, i), mtr2(i, i);
        st1 = st2 = st3 = 0;

        random_mtr(mtr1);
        random_mtr(mtr2);

        for(size_t j = 0; j < NUMBER_OPER; j++) {
            st1 += get_time_vinograd(mtr1, mtr2);
            st2 += get_time_optimized(mtr1, mtr2);
            st3 += get_time_classic(mtr1, mtr2);
        }

        if (st1) st1 /= (NUMBER_OPER - 2);
        if (st2) st2 /= (NUMBER_OPER - 2);
        if (st3) st3 /= (NUMBER_OPER - 2);


        std::cout << std::fixed << i << "," << st1 << "," << st2 << "," << st3 << "\n";
    }
    printf("+--------+------------+---------------+---------------+\n");
}
