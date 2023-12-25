#include "../inc/file.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int find_file_line_total(std::ifstream &in) {
    int total = 0;
    if (!in.is_open()) {
        return -1;
    }

    std::string line;
    while (getline(in, line)) {
        total++;
    }
    in.clear();
    in.seekg(0);

    return total;
}
