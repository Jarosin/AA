#include <iostream>
#include <string>
#include "inc/file.hpp"
#include "inc/threads.hpp"
#include "inc/cpu_time.hpp"

int main()
{
    std::string input_file = "in.txt";
    std::string output_file = "out.txt";
    std::string thread_output_file = "out_threads.txt";
    std::string substr;

    setlocale(LC_CTYPE, "");
    std::cout.precision(3);
    std::string prompt = "Выберите команду:\n1 - Найти все подстроки с помощью последовательного поиска\n"
    "2 - Найти все подстроки с помощью параллельного поиска\n"
    "3 - Найти среднее время на выполнение последовательной реализации и параллельной реализации с разным количеством потоков\n"
    "4 - Остановить выполнение\n";

    std::string command = "";
    int min = 0, max = 0;
    int step = 0;
    int option = 0;
    int thread_total;
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
                std::cout << "Введите название исходного файла: ";
                std::cin >> input_file;
                std::cout << "Введите название результирующего файла: ";
                std::cin >> output_file;
                std::cout << "Введите искомую подстроку: ";
                std::cin >> substr;
                if (seq_substring_replace(input_file, output_file, substr))
                {
                    std::cout << "Произошла ошибка во время выполнения\n";
                    continue;
                }
                std::cout << "Выполнение завершилось успешно\n";
                break;
            case 2:
                std::cout << "Введите название исходного файла: ";
                std::cin >> input_file;
                std::cout << "Введите название результирующего файла: ";
                std::cin >> output_file;
                std::cout << "Введите количество потоков: ";
                std::cin >> thread_total;
                std::cout << "Введите искомую подстроку: ";
                std::cin >> substr;
                if (thread_substring_replace(input_file, output_file, substr, thread_total))
                {
                    std::cout << "Произошла ошибка во время выполнения\n";
                    continue;
                }
                std::cout << "Выполнение завершилось успешно\n";
                break;
            case 3:
                std::cout << "Введите искомую подстроку: ";
                std::cin >> substr;
                std::cout << "Введите начальное количество потоков: ";
                std::cin >> min;
                std::cout << "Введите конечное количество потоков: ";
                std::cin >> max;
                std::cout << "Введите шаг изменения количества потоков: ";
                std::cin >> step;
                measure_time(min, max, step, substr);
                break;
            case 4:
                return 0;
        }
    }

    return 0;
}
