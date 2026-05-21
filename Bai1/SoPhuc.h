#ifndef SOPHUC_H
#define SOPHUC_H

#include <iostream>

class SoPhuc {
private:
    double thuc;
    double ao;

public:
    SoPhuc(double r = 0, double i = 0);
    friend SoPhuc operator+(const SoPhuc& sp1, const SoPhuc& sp2);
    friend SoPhuc operator-(const SoPhuc& sp1, const SoPhuc& sp2);
    friend SoPhuc operator*(const SoPhuc& sp1, const SoPhuc& sp2);
    friend SoPhuc operator/(const SoPhuc& sp1, const SoPhuc& sp2);
    friend bool operator==(const SoPhuc& sp1, const SoPhuc& sp2);
    friend bool operator!=(const SoPhuc& sp1, const SoPhuc& sp2);
    friend std::ostream& operator<<(std::ostream& os, const SoPhuc& sp);
    friend std::istream& operator>>(std::istream& is, SoPhuc& sp);
};

#endif