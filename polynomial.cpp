#include <iostream>
#include <vector>
#include <math.h>
#include <stdexcept>

#pragma once

class Polynomial {
    std::vector<double> coefficients;
    size_t deg;
public:
    Polynomial() : deg(0) {}
    Polynomial(std::vector<double> &c) : deg(0), coefficients(c) {
        for (int i = size() - 1; i >= 0; --i) {
            if (coefficients[i]) {
                deg = i;
                break;
            }
        }
    }

    double operator[](unsigned int i) const {
        if (i >= size()) {
            return 0;
        }

        return coefficients[i];
    }

    bool operator==(const Polynomial &p) const {
        for (int i = 0; i < std::max(size(), p.size()); ++i) {
            if ((*this)[i] != p[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Polynomial &p) {
        return !(*this == p);
    }

    Polynomial operator+() const {
        return *this;
    }

    Polynomial operator+(const Polynomial &p) {
        std::vector<double> res;

        for (int i = 0; i < std::max(p.size(), size()); ++i) {
            res.push_back((*this)[i] + p[i]);
        }

        return Polynomial(res);
    }

    Polynomial operator-() const {
        std::vector<double> res;

        for (int i = 0; i < size(); ++i) {
            res.push_back(-(*this)[i]);
        }

        return Polynomial(res);
    }

    Polynomial operator-(const Polynomial &p) {
        return (*this) + (-p);
    }

    void operator+=(const Polynomial &p) {
        *this = (*this) + p;
    }

    void operator-=(const Polynomial &p) {
        *this = (*this) - p;
    }

    Polynomial operator*(double num) {
        std::vector<double> res;

        for (int i = 0; i < size(); ++i) {
            res.push_back((*this)[i] * num);
        }

        return Polynomial(res);
    }

    Polynomial operator/(double num) {
        std::vector<double> res;

        for (int i = 0; i < size(); ++i) {
            res.push_back((*this)[i] / num);
        }

        return Polynomial(res);
    }

    void operator*=(double num) {
        *this = (*this) * num;
    }

    void operator/=(double num) {
        *this = (*this) / num;
    }

    int size() const {
        return coefficients.size();
    }

    int degree() const {
        return deg;
    }

    void add(double num) {
        coefficients.push_back(num);
    }

    void clear() {
        coefficients.clear();
    }
};

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {   
    os << p.degree() << " : ";
    for (int i = p.size() - 1; i >= 0; --i) {
        if (!p[i]) {
            continue;
        }

        if (p[i] > 0) {
            os << " + ";
        } else {
            os << " - ";
        }
        
        os << std::abs(p[i]) << "*x^" << i;
    }

    os << '\n';

    return os;
}

std::istream& operator>>(std::istream& is, Polynomial &p) {   
    unsigned int n;  // degree of polynomial
    is >> n;
    p.clear();
    double num;

    for (int i = 0; i <= n; ++i) {
        is >> num;
        p.add(num);
    }

    return is;
}