#include <string>
#include <mutex>

int thread_substring_replace(std::string &in_file, std::string &out_file, std::string &substr, size_t thread_total);
int seq_substring_replace(std::string &in_file, std::string &out_file, std::string &substr);
int substr_search_pos(std::ifstream &in, std::ofstream &out, std::string &substr, int first_line, int last_line);
