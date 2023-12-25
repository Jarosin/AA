#include <iostream>
#include "inc/matrix.hpp"
#include "inc/io.hpp"
#include "inc/cpu_time.hpp"

int main() {
    setlocale(LC_CTYPE, "");
    std::cout.precision(3);
    std::string prompt = "Выберите команду: 1 - Найти произведение матриц с помощью алгоритма Винограда\n"
    "2 - Найти произведение матриц с помощью оптимизированного алгоритма Винограда\n"
    "3 - Найти произведение матриц с помощью классического алгоритма умножения\n"
    "4 - Найти среднее время на выполнение каждого алгоритма\n"
    "5 - Остановить выполнение\n";

    std::string command = "";
    Matrix *first_matrix, *second_matrix, *res;
    int min = 0, max = 0;
    int step = 0;
    int option = 0;
    while (true) {
        std::cout << prompt;
        std::cin >> command;
        try {
            option = std::stoi(command);
        } catch(...) {
            std::cout << "Такой команды не предусмотрено\n";
            continue;
        }
        switch(option) {
            case 1:
                std::cout << "Ввод первой матрицы\n";
                first_matrix = read_matrix();
                std::cout << "Ввод второй матрицы\n";
                second_matrix = read_matrix();
                res = first_matrix->MultVinograd(*second_matrix);
                std::cout << "Результат: \n";
                res->PrintMatrix();
                break;
            case 2:
                std::cout << "Ввод первой матрицы\n";
                first_matrix = read_matrix();
                std::cout << "Ввод второй матрицы\n";
                second_matrix = read_matrix();
                res = first_matrix->MultOptimized(*second_matrix);
                std::cout << "Результат: \n";
                res->PrintMatrix();
                break;
            case 3:
                std::cout << "Ввод первой матрицы\n";
                first_matrix = read_matrix();
                std::cout << "Ввод второй матрицы\n";
                second_matrix = read_matrix();
                res = first_matrix->MultClassic(*second_matrix);
                std::cout << "Результат: \n";
                res->PrintMatrix();
                break;
            case 4:
                std::cout << "Введите начальный размер матрицы: ";
                std::cin >> min;
                std::cout << "Введите конечный размер матрицы: ";
                std::cin >> max;
                std::cout << "Введите шаг изменения размера: ";
                std::cin >> step;
                measure_time(min, max, step);
                break;
            case 5:
                return 0;
        }
    }
}
