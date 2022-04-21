#include "custom_algorithms.hpp"
#include "circular_buffer.hpp"
#include "polynomial.cpp"

template<class T>
struct is_odd {
    bool operator() (const T& value) const {
        return value % 2;
    }
};

template<class T>
struct is_even {
    bool operator() (const T& value) const {
        return (value % 2 == 0);
    }
};

template<class T>
struct sorted {
    bool operator() (const T& v1, const T& v2) const {
        return (v1 <= v2);
    }
};

template<class T>
struct equal {
    bool operator() (const T& v1, const T& v2) const {
        return (v1 == v2);
    }
};

template<class T>
struct has_const_term {
    bool operator() (const T& p) const {
        return p[0];
    }
};

template<class T>
struct sorted_desc_poly {
    bool operator() (const T& p1, const T& p2) const {
        return p1.degree() >= p2.degree();
    }
};

int main() {
//     // INBUILT INT TYPE
    CircularBuffer<int> cb;
    cb.push_back(8);
    cb.push_front(6);
    cb.push_back(6);
    cb.push_front(1);
    cb.push_back(1);
    cb.print_data();

    std::cout << "all even: " << all_of(cb.begin(), cb.end(), is_even<int>()) << "\n";
    std::cout << "any even: " << any_of(cb.begin(), cb.end(), is_even<int>()) << "\n";
    std::cout << "none even: " << none_of(cb.begin(), cb.end(), is_even<int>()) << "\n";
    std::cout << "one even: " << one_of(cb.begin(), cb.end(), is_even<int>()) << "\n";
    std::cout << "sorted: " << is_sorted(cb.begin(), cb.end(), sorted<int>()) << "\n";
    std::cout << "partitioned: " << is_partitioned(cb.begin(), cb.end(), is_even<int>()) << "\n";
    std::cout << "find not 1: " << (*find_not(cb.begin(), cb.end(), equal<int>(), cb.begin())) << "\n";
    std::cout << "find backward 1: " << (*find_backward(cb.begin(), cb.end(), equal<int>(), cb.begin())) << "\n";
    std::cout << "palindrome: " << is_palindrome(cb.begin(), cb.end(), equal<int>()) << "\n\n";

    // CUSTOM POLYNOMIAL IMPLEMENTATION
    CircularBuffer<Polynomial> cb_poly;
    std::vector<double> v1 = {0, 2, 3};
    cb_poly.push_back(Polynomial(v1));
    std::vector<double> v2 = {0, 100, 25, 4};
    cb_poly.push_front(Polynomial(v2));
    std::vector<double> v3 = {10};
    cb_poly.push_back(Polynomial(v3));
    cb_poly.print_data();

    CircularBuffer<Polynomial>::iterator second = cb_poly.begin();
    ++second;
    
    std::cout << "all have constant terms: " << all_of(cb_poly.begin(), cb_poly.end(), has_const_term<Polynomial>()) << "\n";
    std::cout << "any have constant terms: " << any_of(cb_poly.begin(), cb_poly.end(), has_const_term<Polynomial>()) << "\n";
    std::cout << "none have constant terms: " << none_of(cb_poly.begin(), cb_poly.end(), has_const_term<Polynomial>()) << "\n";
    std::cout << "one has constant term: " << one_of(cb_poly.begin(), cb_poly.end(), has_const_term<Polynomial>()) << "\n";
    std::cout << "sorted in descending degree: " << is_sorted(cb_poly.begin(), cb_poly.end(), sorted_desc_poly<Polynomial>()) << "\n";
    std::cout << "partitioned: " << is_partitioned(cb_poly.begin(), cb_poly.end(), has_const_term<Polynomial>()) << "\n";
    std::cout << "find not {0, 2, 3} poly: " << (*find_not(cb_poly.begin(), cb_poly.end(), equal<Polynomial>(), second)) << "\n";
    std::cout << "find backward {0, 2, 3} poly: " << (*find_backward(cb_poly.begin(), cb_poly.end(), equal<Polynomial>(), second)) << "\n";
    std::cout << "palindrome: " << is_palindrome(cb_poly.begin(), cb_poly.end(), equal<Polynomial>()) << "\n";;

    return 0;
}