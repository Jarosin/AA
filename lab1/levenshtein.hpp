#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#pragma once

#include <string>
#include <algorithm>
#include "memory.hpp"

int levenshtein_matrix(std::wstring &first_word, std::wstring &second_word);
int damerau_levenshtein_matrix(std::wstring &first_word, std::wstring &second_word);
int damerau_lev_recursion(std::wstring &first_word, std::wstring &second_word);
int damerau_lev_recursion_hash(std::wstring &first_word, std::wstring &second_word);
std::wstring levenshtein_matrix_path(std::wstring &first_word, std::wstring &second_word);
std::wstring get_path(int cur_column, int cur_row, int **matrix, std::wstring cur_path);

#endif
