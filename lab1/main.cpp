#include <iostream>
#include "levenshtein.hpp"
#include <locale>
#include "time.hpp"


void reverseStr(std::wstring& str)
{
    int n = str.length();

    for (int i = 0; i < n / 2; i++)
        std::swap(str[i], str[n - i - 1]);
}

int main() {
    setlocale(LC_CTYPE, "");
    std::wcout.precision(3);
    std::wstring prompt = L"Выберете команду: 1 - Найти расстояние с помощью алгоритма Левенштейна с матрицами\n"
    L"2 - Найти расстояние с помощью алгоритма Дамерау-Левенштейна с матрицами\n"
    L"3 - Найти расстояние с помощью алгоритма Дамерау-Левенштейна с рекурсией\n"
    L"4 - Найти расстояние с помощью алгоритма Дамерау-Левенштейна с рекурсией и кэшем\n"
    L"5 - Найти среднее время на выполнение\n"
    L"6 - Остановить выполнение\n"
    L"7 - Найти путь\n";

    std::wstring command = L"";
    std::wstring first_word, second_word;
    int min = 0, max = 0;
    int repition_amount = 0;
    int option = 0;
    int res;
    while (true) {
        std::wcout << prompt;
        std::wcin >> command;
        try {
            option = std::stoi(command);
        } catch(...) {
            std::wcout << L"Такой команды не предусмотрено\n";
            continue;
        }
        switch(option) {
            case 1:
                std::wcout << L"Введите первое слово: ";
                std::wcin >> first_word;
                std::wcout << L"Введите второе слово: ";
                std::wcin >> second_word;
                res = levenshtein_matrix(first_word, second_word);
                std::wcout << L"Результат: " << res << L"\n\n";
                break;
            case 2:
                std::wcout << L"Введите первое слово: ";
                std::wcin >> first_word;
                std::wcout << L"Введите второе слово: ";
                std::wcin >> second_word;
                res = damerau_levenshtein_matrix(first_word, second_word);
                std::wcout << L"Результат: " << res << L"\n\n";
                break;
            case 3:
                std::wcout << L"Введите первое слово: ";
                std::wcin >> first_word;
                std::wcout << L"Введите второе слово: ";
                std::wcin >> second_word;
                res = damerau_lev_recursion(first_word, second_word);
                std::wcout << L"Результат: " << res << L"\n\n";
                break;
            case 4:
                std::wcout << L"Введите первое слово: ";
                std::wcin >> first_word;
                std::wcout << L"Введите второе слово: ";
                std::wcin >> second_word;
                res = damerau_lev_recursion_hash(first_word, second_word);
                std::wcout << L"Результат: " << res << L"\n\n";
                break;
            case 5:
                std::wcout << L"Введите начальное количество букв: ";
                std::wcin >> min;
                std::wcout << L"Введите конечное количество букв: ";
                std::wcin >> max;
                std::wcout << L"Введите количество повторений: ";
                std::wcin >> repition_amount;
                std::wcout << L"Всё время в наносекундах\n";
                std::wcout << L"Длина слов, Лев. матрица, Дам. матрица, рекурсия, хэш\n";
                for (int i = min; i <= max; i++) {
                    std::wcout << i << L", ";
                    std::wcout << std::fixed << avg_elapsed_lev(repition_amount, i, &levenshtein_matrix) << L", ";
                    std::wcout << std::fixed << avg_elapsed_lev(repition_amount, i, &damerau_levenshtein_matrix) << L", ";
                    if (i < 10) {
                        std::wcout << std::fixed << avg_elapsed_lev(repition_amount, i, &damerau_lev_recursion) << L", ";
                    } else {
                        std::wcout << L"-, ";
                    }
                    std::wcout << std::fixed << avg_elapsed_lev(repition_amount, i, &damerau_lev_recursion_hash) << L"\n";
                }
                break;
            case 6:
                return 0;
            case 7:
                std::wcout << L"Введите первое слово: ";
                std::wcin >> first_word;
                std::wcout << L"Введите второе слово: ";
                std::wcin >> second_word;
                std::wstring path = levenshtein_matrix_path(first_word, second_word);
                reverseStr(path);
                std::wcout << L"Результат: " << path << L"\n";
                break;
        }
    }
}
