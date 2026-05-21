#ifndef PHANSO_H
#define PHANSO_H

#include <iostream>
using namespace std;

class cPhanSo {
private:
    int tu, mau;
public:
    cPhanSo();
    cPhanSo(int,int);
    friend istream& operator>>(istream& is, cPhanSo& ps);
    friend ostream& operator<<(ostream& os, const cPhanSo& ps);
    void RutGon();
    friend cPhanSo operator+(const cPhanSo& a, const cPhanSo& b);
    friend cPhanSo operator-(const cPhanSo& a, const cPhanSo& b);
    friend cPhanSo operator*(const cPhanSo& a, const cPhanSo& b);
    friend cPhanSo operator/(const cPhanSo& a, const cPhanSo& b);
    friend bool operator==(const cPhanSo& a, const cPhanSo& b);
    friend bool operator>(const cPhanSo& a, const cPhanSo& b);
    friend bool operator<(const cPhanSo& a, const cPhanSo& b);
};
#endif