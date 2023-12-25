#include <string>
typedef int (*lev_func)(std::wstring &, std::wstring &);
float avg_elapsed_lev(int repition_amount, int letter_amount, lev_func func);
