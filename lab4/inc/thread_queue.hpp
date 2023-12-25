#ifndef THREADQUEUE_H
#define THREADQUEUE_H

#pragma once
#include <string>
#include <mutex>
#include <vector>
#include <queue>
#include <algorithm>

template <typename T>
class ThreadQueue
{
public:
    void push(T str) {
        block_.lock();
        queue_.push(str);
        block_.unlock();
    }
    T pop() {
        block_.lock();
        if (queue_.size() == 0) {
            block_.unlock();
            throw std::exception();
        }
        T res = queue_.front();
        queue_.pop();
        block_.unlock();
        return res;
    }
    bool empty() {
        block_.lock();
        bool res = queue_.empty();
        block_.unlock();
        return res;
    }
private:
    std::mutex block_;
    std::queue<T> queue_;
};

#endif
