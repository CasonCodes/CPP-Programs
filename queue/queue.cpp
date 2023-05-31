#include "queue.hpp"
#include <utility>

namespace data {

    FixedQueue::FixedQueue(size_t capacity) {
        data.resize(capacity + 1);
        front = 0;
        back = 0;
    }

    size_t FixedQueue::capacity() {
        return data.size() - 1;
    }

    size_t FixedQueue::size() {
        return (back - front + data.size()) % data.size();
    }

    bool FixedQueue::enqueue(int element) {
        size_t next = (back + 1) % data.size();
        if (next != front) {
            data[back] = element;
            back = next;
            return true;
        }
        else {
            return false;
        }
    }

    bool FixedQueue::dequeue(int& element) {
        if (front != back) {
            element = data[front];
            front = (front + 1) % data.size();
            return true;
        }
        else {
            return false;
        }
    }

}