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

std::shared_mutex reader_done_mutex;
bool reader_done;

std::mutex parsers_done_mutex;
bool parsers_done;

void thread_substr(std::string &substr, ThreadQueue<std::string> &out_queue, ThreadQueue<std::pair<std::string, int>> &in_queue)
{
    size_t pos;
    std::pair<std::string, int> top;

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

        pos = top.first.find(substr);
        while (pos != std::string::npos)
        {
            std::ostringstream stream;
            stream << top.second + 1 << " " << pos << "\n";
            out_queue.push(stream.str());

            pos = top.first.find(substr, pos + 1);
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

    int total = find_file_line_total(in);
    if (substr_search_pos(in, out, substr, 0, total))
    {
        in.close();
        out.close();
        return 1;
    }

    in.close();
    out.close();
    return 0;
}

int substr_search_pos(std::ifstream &in, std::ofstream &out, std::string &substr, int first_line, int last_line)
{
    if (!in.is_open() || !out.is_open())
        return 1;

    std::string line;
    in.seekg(0);
    for (int i = 0; i < first_line; i++)
    {
        if (!getline(in, line))
            return 1;
    }

    size_t pos;
    for (int i = first_line; i < last_line; i++)
    {
        if (!getline(in, line))
            return 1;
        pos = line.find(substr);
        while (pos != std::string::npos)
        {
            out << i + 1 << " " << pos << "\n";
            pos = line.find(substr, pos + 1);
        }
    }

    return 0;
}
