#include "../inc/cpu_time.hpp"
#include <random>
#include <iostream>
#include <fstream>
#include "../inc/threads.hpp"

#define NUMBER_OPER 50

double get_time_seq(std::string &in_file, std::string &out_file, std::string &substr)
{
    clock_t start_t, end_t;
    double total_t;

    start_t = clock();
    seq_substring_replace(in_file, out_file, substr);
    end_t = clock();
    total_t = (double)(end_t - start_t) / (CLOCKS_PER_SEC) * 1e3;
    return total_t;
}

double get_time_threads(std::string &in_file, std::string &out_file, std::string &substr, size_t total_connections)
{
    clock_t start_t, end_t;
    double total_t;

    start_t = clock();
    thread_substring_replace(in_file, out_file, substr, total_connections);
    end_t = clock();
    total_t = (double)(end_t - start_t) / (CLOCKS_PER_SEC) * 1e3;
    return total_t;
}


void measure_time(size_t start, size_t max, size_t step, std::string &substring)
{
    double time;
    std::string in_file = "in.txt";
    std::string out_file = "out.txt";
    std::ifstream in(in_file, std::ios::in);
    if (!in.is_open()) {
        return;
    }
    std::string temp;
    while (getline(in, temp)) {}
    in.close();

    std::cout.precision(3);
    std::cout << "Все время указано в наносекундах\n";
    std::cout << "Кол-во процессов, Время выполнения\n";
    time = 0;
    for (size_t i = 0; i < NUMBER_OPER; i++) {
        time += get_time_seq(in_file, out_file, substring);
    }
    if (time)
        time /= (NUMBER_OPER - 2);

    std::cout << std::fixed << "0" << "," << time << std::endl;
    for (size_t i = start; i <= max; i += step)
    {
        if (i == 0)
            continue;
        time = 0;

        for (size_t j = 0; j < NUMBER_OPER; j++)
        {
            time += get_time_threads(in_file, out_file, substring, i);
        }

        if (time)
            time /= (NUMBER_OPER - 2);

        std::cout << std::fixed << i << "," << time << "\n";
    }
}
