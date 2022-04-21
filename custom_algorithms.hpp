#include <iostream>

#pragma once

// https://stackoverflow.com/questions/10632251/undefined-reference-to-template-function

template <typename InputIterator, typename Predicate>
std::pair<size_t, size_t> count(InputIterator begin, InputIterator end, Predicate pred) {
    size_t c = 0, n = 0;
    
    while (begin != end) {
        if (pred(*begin)) {
            ++c;
        }

        ++n;
        ++begin;
    }

    return {c, n};
}

template <typename InputIterator, typename Predicate>
bool all_of(InputIterator begin, InputIterator end, Predicate pred) {
    std::pair<size_t, size_t> res = count(begin, end, pred);

    if (res.first == res.second) {
        return true;
    } else {
        return false;
    }
}

template <typename InputIterator, typename Predicate>
bool any_of(InputIterator begin, InputIterator end, Predicate pred) {
    std::pair<size_t, size_t> res = count(begin, end, pred);

    if (res.first) {
        return true;
    } else {
        return false;
    }
}

template <typename InputIterator, typename Predicate>
bool none_of(InputIterator begin, InputIterator end, Predicate pred) {
    std::pair<size_t, size_t> res = count(begin, end, pred);

    if (!res.first) {
        return true;
    } else {
        return false;
    }
}

template <typename InputIterator, typename Predicate>
bool one_of(InputIterator begin, InputIterator end, Predicate pred) {
    std::pair<size_t, size_t> res = count(begin, end, pred);

    if (res.first == 1) {
        return true;
    } else {
        return false;
    }
}

template <typename InputIterator, typename Predicate>
bool is_sorted(InputIterator begin, InputIterator end, Predicate pred) {
    if (begin == end) {
        return true;
    }

    InputIterator next = begin;
    ++next;

    while (next != end) {
        if (!pred(*begin, *next)) {
            return false;
        }

        ++begin;
        ++next;
    }

    return true;
}

template <typename InputIterator, typename Predicate>
bool is_partitioned(InputIterator begin, InputIterator end, Predicate pred) {
    if (begin == end) {
        return true;
    }

    size_t partitions = 0;
    bool prev = pred(*begin), cur;
    InputIterator next = begin;
    ++next;

    while (next != end) {
        cur = pred(*next);

        if (prev != cur) {
            ++partitions;
        }

        prev = cur;
        ++begin;
        ++next;
    }

    return partitions <= 1;
}

template <typename InputIterator, typename Predicate>
InputIterator find_not(InputIterator begin, InputIterator end, Predicate pred, InputIterator value) {
    while (begin != end) {
        if (!pred(*begin, *value)) {
            break;
        }

        ++begin;
    }

    return begin;
}

template <typename InputIterator, typename Predicate>
InputIterator find_backward(InputIterator begin, InputIterator end, Predicate pred, InputIterator value) {
    InputIterator res = end;
    
    while (begin != end) {
        if (pred(*begin, *value)) {
            res = begin;
        }

        ++begin;
    }

    return res;
}

template <typename InputIterator, typename BidirectionalIterator, typename Predicate>
bool is_palindrome(InputIterator begin, BidirectionalIterator end, Predicate pred) {
    if (begin == end) {
        return true;
    }

    --end;
    
    while (begin != end) {
        if (!pred(*begin, *end)) {
            return false;
        }

        ++begin;

        if (begin == end) {
            break;
        }
        
        --end;
    }

    return true;
}
