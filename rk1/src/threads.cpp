#include <thread>
#include <fstream>
#include <iostream>
#include "../inc/threads.hpp"
#include "../inc/file.hpp"
#include <mutex>
#include <shared_mutex>
#include <vector>
#include "../inc/thread_queue.hpp"
#include <sstream>
#include <utility>
#include <unistd.h>
#include "../inc/levenshtein.hpp"
#include <math.h>

std::shared_mutex reader_done_mutex;
bool reader_done;

std::mutex parsers_done_mutex;
bool parsers_done;

bool is_substr_prefix(std::string &src, std::string &substr, int max_typo_count, size_t pos)
{
    std::string src_substr = src.substr(pos, std::min(src.length() - pos, substr.length()));
    int typo_count = damerau_levenshtein_matrix(src_substr, substr);
    if (typo_count > max_typo_count)
    {
        return false;
    }

    return true;
}

int calculate_k(int substr_len)
{
    return std::floor(log2(substr_len));
}

void thread_substr(std::string &substr, ThreadQueue<std::string> &out_queue, ThreadQueue<std::pair<std::string, int>> &in_queue)
{
    std::pair<std::string, int> top;
    int max_typo_total = calculate_k(substr.length());

    while (true)
    {
        try
        {
            top = in_queue.pop();
        }
        catch (...)
        {
            std::shared_lock<std::shared_mutex> r(reader_done_mutex);
            if (reader_done)
            {
                return;
            }
            continue;
        }

        for (int i = 0; i < top.first.length(); i++)
        {
            if (is_substr_prefix(top.first, substr, max_typo_total, i))
            {
                std::ostringstream stream;
                stream << top.second + 1 << " " << i << "\n";
                out_queue.push(stream.str());
            }
        }
    }
}

void read_thread(std::ifstream &in, ThreadQueue<std::pair<std::string, int>> &out_queue)
{
    if (!in.is_open())
    {
        return;
    }

    std::string line;
    int cur = 0;
    while (getline(in, line))
    {
        out_queue.push(std::pair<std::string, int>(line, cur));
        cur++;
    }
    std::unique_lock<std::shared_mutex> r(reader_done_mutex);
    reader_done = true;
    return;
}

void write_thread(std::ofstream &out, ThreadQueue<std::string> &in_queue)
{
    if (!out.is_open())
    {
        return;
    }

    std::string line;
    while (true)
    {
        if (in_queue.empty())
        {
            std::lock_guard<std::mutex> _(parsers_done_mutex);
            if (parsers_done)
                return;
            continue;
        }
        line = in_queue.pop();
        out << line;
    }
    return;
}

int thread_substring_replace(std::string &in_file, std::string &out_file, std::string &substr, size_t thread_total)
{
    reader_done = false;
    parsers_done = false;
    std::ifstream in(in_file, std::ios::in);
    if (!in.is_open())
    {
        return 1;
    }
    std::ofstream out(out_file);
    if (!out.is_open())
    {
        return 1;
    }
    std::string line;
    ThreadQueue<std::string> out_queue;
    ThreadQueue<std::pair<std::string, int>> in_queue;
    std::vector<std::thread> threads;
    std::thread thread_read(read_thread, std::ref(in), std::ref(in_queue));
    threads.push_back(std::move(thread_read));
    for (int i = 0; i < thread_total; i++)
    {
        std::thread thread_obj(thread_substr, std::ref(substr), std::ref(out_queue), std::ref(in_queue));
        threads.push_back(std::move(thread_obj));
    }
    std::thread thread_write(write_thread, std::ref(out), std::ref(out_queue));
    for (int i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }
    {
        std::lock_guard<std::mutex> _(parsers_done_mutex);
        parsers_done = true;
    }
    thread_write.join();
    in.close();
    out.close();
    return 0;
}

int seq_substring_replace(std::string &in_file, std::string &out_file, std::string &substr)
{
    std::ifstream in(in_file, std::ios::in);
    if (!in.is_open())
    {
        return 1;
    }
    std::ofstream out(out_file);
    if (!out.is_open())
    {
        return 1;
    }

    if (substr_search_pos(in, out, substr))
    {
        in.close();
        out.close();
        return 1;
    }

    in.close();
    out.close();
    return 0;
}

int substr_search_pos(std::ifstream &in, std::ofstream &out, std::string &substr)
{
    if (!in.is_open() || !out.is_open())
        return 1;

    int max_typo_total = calculate_k(substr.length());
    std::string line;
    in.seekg(0);

    size_t pos;
    int i = 0;
    while (getline(in, line))
    {
        for (int j = 0; j < line.length(); j++)
        {
            if (is_substr_prefix(line, substr, max_typo_total, j))
            {
                out << i + 1 << " " << j << "\n";
            }
        }
        i++;
    }

    return 0;
}
