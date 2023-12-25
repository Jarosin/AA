#include <iostream>
#include "inc/algs.hpp"
#include "inc/io.hpp"
#include "inc/cpu_time.hpp"
int main()
{
    setlocale(LC_CTYPE, "");
    std::cout.precision(3);
    std::string prompt = "Выберите команду: \n"
    "1 - Отсортировать массив с помощью сортировки вставками\n"
    "2 - Отсортировать массив с помощью пирамидальной сортировки\n"
    "3 - Отсортировать массив с помощью битонной сортировки\n"
    "4 - Сравнить время выполнения\n"
    "5 - Остановить выполнение\n";

    std::string command = "";
    int min = 0, max = 0;
    int step = 0;
    int option = 0;
    int *array, len = 0;
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
                array = read_array(&len);
                insert_sort(array, len);
                std::cout << "Отсортированный массив: ";
                print_array(array, len);
                delete[] array;
                break;
            case 2:
                array = read_array(&len);
                heap_sort(array, len);
                std::cout << "Отсортированный массив: ";
                print_array(array, len);
                delete[] array;
                break;
            case 3:
                array = read_array(&len);
                bitonic_sort(array, len, 1);
                std::cout << "Отсортированный массив: ";
                print_array(array, len);
                delete[] array;
                break;
            case 4:
                std::cout << "Введите начальный длину массива: ";
                std::cin >> min;
                std::cout << "Введите конечный длину массива: ";
                std::cin >> max;
                std::cout << "Введите шаг изменения длины: ";
                std::cin >> step;
                measure_time_two(min, max, step);
                break;
            case 5:
            default:
                return 0;
        }
    }
}
