#include <string>
#include "../inc/levenshtein.hpp"

int **alloc_matrix(int n, int m) {
    if (n < 1 || m < 1) {
        return nullptr;
    }
    int **matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[m];
    }
    return matrix;
}

int free_matrix(int **matrix, int n) {
    if (n < 1 || matrix == nullptr) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}


int damerau_levenshtein_matrix(std::string &first_word,
                               std::string &second_word)
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
