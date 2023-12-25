#include "levenshtein.hpp"
#include <iostream>
#include <cmath>

int levenshtein_matrix(std::wstring &first_word, std::wstring &second_word)
{
    int first_length = first_word.length();
    int second_length = second_word.length();

    int **matrix = alloc_matrix(first_length + 1, second_length + 1);

    for (int i = 0; i < first_length + 1; i++)
    {
        for (int j = 0; j < second_length + 1; j++)
        {
            if (i == 0 || j == 0)
            {
                matrix[i][j] = abs(i - j);
            }
            else
            {
                int equal = 1;
                if (first_word[i - 1] == second_word[j - 1])
                    equal = 0;
                matrix[i][j] = std::min({matrix[i - 1][j] + 1,
                                         matrix[i][j - 1] + 1,
                                         matrix[i - 1][j - 1] + equal});
            }
        }
    }
    int res = matrix[first_length][second_length];
    free_matrix(matrix, first_length + 1);

    return res;
}

int damerau_levenshtein_matrix(std::wstring &first_word,
                               std::wstring &second_word)
{
    int first_length = first_word.length();
    int second_length = second_word.length();

    int **matrix = alloc_matrix(first_length + 1, second_length + 1);

    for (int i = 0; i < first_length + 1; i++)
    {
        for (int j = 0; j < second_length + 1; j++)
        {
            if (i == 0 || j == 0)
            {
                matrix[i][j] = abs(i - j);
            }
            else
            {
                int equal = 1;
                if (first_word[i - 1] == second_word[j - 1])
                    equal = 0;
                matrix[i][j] = std::min({matrix[i - 1][j] + 1,
                                         matrix[i][j - 1] + 1,
                                         matrix[i - 1][j - 1] + equal});
                if (i > 1 && j > 1 && first_word[i - 2] == second_word[j - 1] &&
                    first_word[i - 1] == second_word[j - 2])
                {
                    matrix[i][j] = std::min(matrix[i][j],
                                            matrix[i - 2][j - 2] + 1);
                }
            }
        }
    }
    int res = matrix[first_length][second_length];
    free_matrix(matrix, first_length + 1);

    return res;
}

int damerau_lev_rec(std::wstring &first_word, std::wstring &second_word,
                    int n, int m)
{
    if (n == 0 || m == 0)
        return abs(n - m);

    int equal = 1;
    if (first_word[n - 1] == second_word[m - 1])
        equal = 0;

    int res = std::min({damerau_lev_rec(first_word, second_word, n, m - 1) + 1,
                       damerau_lev_rec(first_word, second_word, n - 1, m) + 1,
                       damerau_lev_rec(first_word, second_word,
                                       n - 1, m - 1) + equal});

    if (n > 1 && m > 1 && first_word[n - 1] == second_word[m - 2] &&
        first_word[n - 2] == second_word[m - 1])
    {
        res = std::min(res, damerau_lev_rec(first_word, second_word,
                                            n - 2, m - 2) + 1);
    }

    return res;
}

int damerau_lev_recursion(std::wstring &first_word, std::wstring &second_word)
{
    return damerau_lev_rec(first_word, second_word,
                           first_word.length(), second_word.length());
}

int damerau_lev_rec_hash(std::wstring &first_word, std::wstring &second_word,
                    int **matrix, int n, int m)
{
    if (matrix[n][m] != -1) {
        return matrix[n][m];
    }

    if (n == 0 || m == 0) {
        matrix[n][m] = std::max(m, n);
        return matrix[n][m];
    }

    int equal = 1;
    if (first_word[n - 1] == second_word[m - 1])
        equal = 0;

    matrix[n][m] = std::min({damerau_lev_rec_hash(first_word, second_word, matrix, n, m - 1) + 1,
                       damerau_lev_rec_hash(first_word, second_word, matrix, n - 1, m) + 1,
                       damerau_lev_rec_hash(first_word, second_word, matrix,
                                       n - 1, m - 1) + equal});

    if (n > 1 && m > 1 && first_word[n - 1] == second_word[m - 2] &&
        first_word[n - 2] == second_word[m - 1])
    {
        matrix[n][m] = std::min(matrix[n][m], damerau_lev_rec_hash(first_word, second_word, matrix,
                                            n - 2, m - 2) + 1);
    }

    return matrix[n][m];
}

int damerau_lev_recursion_hash(std::wstring &first_word, std::wstring &second_word)
{
    int first_length = first_word.length();
    int second_length = second_word.length();

    int **matrix = alloc_matrix(first_length + 1, second_length + 1);
    for (int i = 0; i < first_length + 1; i++) {
        for (int j = 0; j < second_length + 1; j++) {
            matrix[i][j] = -1;
        }
    }

    int res = damerau_lev_rec_hash(first_word, second_word, matrix,
                           first_word.length(), second_word.length());

    free_matrix(matrix, first_length + 1);
    return res;
}

std::wstring levenshtein_matrix_path(std::wstring &first_word, std::wstring &second_word)
{
    int first_length = first_word.length();
    int second_length = second_word.length();

    int **matrix = alloc_matrix(first_length + 1, second_length + 1);

    for (int i = 0; i < first_length + 1; i++)
    {
        for (int j = 0; j < second_length + 1; j++)
        {
            if (i == 0 || j == 0)
            {
                matrix[i][j] = abs(i - j);
            }
            else
            {
                int equal = 1;
                if (first_word[i - 1] == second_word[j - 1])
                    equal = 0;
                matrix[i][j] = std::min({matrix[i - 1][j] + 1,
                                         matrix[i][j - 1] + 1,
                                         matrix[i - 1][j - 1] + equal});
            }
        }
    }

    std::wstring start = L"";

    std::wstring res = get_path(second_length, first_length, matrix, start);

    free_matrix(matrix, first_length + 1);

    return res;
}

std::wstring get_path(int cur_column, int cur_row, int **matrix, std::wstring cur_path) {
    if (cur_column == 0 && cur_row == 0) {
        return cur_path;
    }
    if (cur_column == 0) {
        cur_path += L"i";
        return get_path(cur_column, cur_row - 1, matrix, cur_path);
    }
    if (cur_row == 0) {
        cur_path += L"d";
        return get_path(cur_column - 1, cur_row, matrix, cur_path);
    }
    if (matrix[cur_row - 1][cur_column - 1] == matrix[cur_row][cur_column]) {
        cur_path += L"m";
        return get_path(cur_column - 1, cur_row - 1, matrix, cur_path);
    }
    if (matrix[cur_row - 1][cur_column - 1] == matrix[cur_row][cur_column] - 1) {
        cur_path += L"r";
        return get_path(cur_column - 1, cur_row - 1, matrix, cur_path);
    }
    if (matrix[cur_row - 1][cur_column] == matrix[cur_row][cur_column]) {
        cur_path += L"i";
        return get_path(cur_column, cur_row - 1, matrix, cur_path);
    }
    cur_path += L"d";
    return get_path(cur_column - 1, cur_row, matrix, cur_path);
}
