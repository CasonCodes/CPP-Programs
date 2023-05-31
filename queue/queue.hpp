#pragma once
#include <vector>

namespace data {

    class FixedQueue {
        std::vector<int> data;
        size_t front, back;

    public:
        FixedQueue(size_t capacity);
        size_t capacity();
        size_t size();
        bool enqueue(int element);
        bool dequeue(int& element);
    };

}