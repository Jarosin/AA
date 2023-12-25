#include <ctime>
#include "time.hpp"
#include "levenshtein.hpp"

// returns time in ns
float avg_elapsed_lev(int repition_amount, int letter_amount, lev_func func) {
    std::wstring a = L"", b = L"";

    for (int i = 0; i < letter_amount; i++) {
        a = a + L"a";
        b = b + L"b";
    }
    const std::clock_t c_start = std::clock();

    for (int i = 0; i < repition_amount; i++) {
        func(a, b);
    }

    const std::clock_t c_end = std::clock();

    return (1e+3 * (c_end - c_start)) / (CLOCKS_PER_SEC * repition_amount);
}
