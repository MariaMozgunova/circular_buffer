#include <iostream>
#include <stdexcept>

#pragma once

// https://codereview.stackexchange.com/questions/113957/random-access-iterator-for-custom-data-type-in-c
// https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
// https://www.youtube.com/watch?v=R-37W4pGJ_M
// https://caiorss.github.io/C-Cpp-Notes/STL%20Iterators%20and%20Algorithms.html#orgbd12a27

template<class T>
class CircularBuffer {
    T* data;
    size_t filled;
    size_t capacity;
    size_t head;
public:
    template<typename U>
    class CircularBufferIter : public std::iterator<std::random_access_iterator_tag, U, int> {
    friend class CircularBuffer;

    private:
        U* cb;
        size_t i;
        size_t cap;

        // CircularBufferIter(U* cb) : 
        //     cb(cb), i(0)
        //     {}

        CircularBufferIter(U* cb, size_t i, size_t cap) : 
            cb(cb), i(i), cap(cap)
            {}
    public:
        typedef typename std::iterator<std::random_access_iterator_tag, U, int>::pointer pointer;
        typedef typename std::iterator<std::random_access_iterator_tag, U, int>::reference reference;
        typedef typename std::iterator<std::random_access_iterator_tag, U, int>::difference_type difference_type;

        reference operator*() const {
            return cb[i];
        }

        pointer operator->() const {
            return &(cb[i]);
        }

        CircularBufferIter& operator++() {
            i = (i + 1) % cap;
            return *this;
        }

        CircularBufferIter& operator--() {
            if (i) {
                --i;
            } else {
                i = cap - 1;
            }
            return *this;
        }

        CircularBufferIter operator++(int) {
            return CircularBufferIter(cb, i++, cap);
        }

        CircularBufferIter operator--(int) {
            return CircularBufferIter(cb, i--, cap);
        }

        CircularBufferIter operator+(const difference_type& n) const {
            return CircularBufferIter(cb, (i + n) % cap, cap);
        }

        CircularBufferIter& operator+=(const difference_type& n)  {
            i = (i + n) % cap;
            return *this;
        }

        CircularBufferIter operator-(const difference_type& n) const {
            return CircularBufferIter(cb, (cap + i - n) % cap, cap);
        }

        CircularBufferIter& operator-=(const difference_type& n)  {
            i = (cap + i - n) % cap;
            return *this;
        }

        reference operator[](const difference_type& n) const {
            return cb[(i + n) % cap];
        }

        bool operator==(const CircularBufferIter& other) const {
            return i == other.i;
        }

        bool operator!=(const CircularBufferIter& other) const {
            return i != other.i;
        }

        bool operator<(const CircularBufferIter&other) const {
            return i < other.i;
        }

        bool operator>(const CircularBufferIter&other) const {
            return i > other.i;
        }

        bool operator<=(const CircularBufferIter&other) const {
            return i <= other.i;
        }

        bool operator>=(const CircularBufferIter&other) const {
            return i >= other.i;
        }

        difference_type operator+(const CircularBufferIter& other) const {
            return (i + other.i) % cap;
        }

        difference_type operator-(const CircularBufferIter& other) const {
            return (cap + i - other.i) % cap;
        }
    };

    typedef CircularBufferIter<T> iterator;
    typedef CircularBufferIter<const T> const_iterator;

    CircularBuffer() : 
        data(0), filled(0), capacity(1), head(0)
        {}

    CircularBuffer(const CircularBuffer<T>& other) 
        : filled(other.filled), capacity(other.capacity), head(0)
    {
        data = new T[capacity];

        for (size_t i = 0; i < filled; ++i) {
            data[i] = other[i];
        }
    }

    ~CircularBuffer() {
        if (data) {
            delete[] data;
        }
    }

    iterator begin() {
        return iterator(data, head, capacity);
    }

    const_iterator begin() const {
        return const_iterator(data, head, capacity);
    }

    const_iterator cbegin() const {
        return const_iterator(data, head, capacity);
    } 
    
    iterator end() {
        return iterator(data, (head + filled) % capacity, capacity);
    }
    
    const_iterator end() const {
        return const_iterator(data, (head + filled) % capacity, capacity);
    }
    
    const_iterator cend() const {
        return const_iterator(data, (head + filled) % capacity, capacity);
    }

    T& operator[](size_t i) const {
        if (i >= filled) {
            throw std::invalid_argument("index out of range");
        }

        return data[(head + i) % capacity];
    }

    void operator=(const CircularBuffer<T>& other) {
        if (this == &other) {
            return;
        }

        if (data) {
            delete[] data;
        }

        filled = other.filled;
        capacity = other.capacity;
        head = 0;
        data = new T[capacity];

        for (size_t i = 0; i < filled; ++i) {
            data[i] = other[i];
        }
    }

    bool empty() {
        return !filled;
    }
    
    bool full() {
        return filled + 1 == capacity;
    }

    void resize(size_t cap) {
        if (cap + 1 == capacity) {
            return;
        }

        T* new_data = new T[cap + 1];

        for (size_t i = 0; i < std::min(filled, cap); ++i) {
            new_data[i] = (*this)[i];
        }

        if (data != 0) {
            delete[] data;
        }

        data = new_data;
        filled = std::min(filled, cap);
        capacity = cap + 1;
        head = 0;
    }
    
    T& front() {
        return (*this)[0];
    }
    
    T& back() {
        return (*this)[filled - 1];
    }

    void push_front(T el) {
        if (full()) {
            resize((capacity + 1) * 2);
        }

        if (head == 0) {
            head = capacity - 1;
        } else {
            --head;
        }

        data[head] = el;
        ++filled;
    }

    void push_back(T el) {
        if (full()) {
            resize((capacity + 1) * 2);
        }

        data[(head + filled) % capacity] = el;
        ++filled;
    }

    void pop_front() {
        if (empty()) {
            return;
        }

        head = (head + 1) % capacity;
        --filled;
    }

    void pop_back() {
        if (empty()) {
            return;
        }

        --filled;
    }

    void print_properties() {
        std::cout << "filled : " << filled << '\n';
        std::cout << "capacity : " << capacity << '\n';
        std::cout << "head : " << head << "\n\n";
    }

    void print_data() {
        std::cout << "****YOUR CIRCULAR BUFFER****\n";
        for (int i = 0; i < filled; ++i) {
            std::cout << (*this)[i] << ' ';
        }

        std::cout << '\n';
        print_properties();
    }
};