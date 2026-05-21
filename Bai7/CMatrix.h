#ifndef CMATRIX_H
#define CMATRIX_H

#include <iostream>
#include <vector>
#include "CVector.h"

class CMatrix {
private:
    int soDong;
    int soCot;
    std::vector<std::vector<double>> data;

public:
    CMatrix();                               
    CMatrix(int r, int c);                   
    CMatrix(const std::vector<std::vector<double>>& m);
    int GetSoDong() const;
    int GetSoCot() const;

    friend CMatrix operator+(const CMatrix& m1, const CMatrix& m2);
    friend CMatrix operator-(const CMatrix& m1, const CMatrix& m2);
    friend CMatrix operator*(const CMatrix& m1, const CMatrix& m2);
    friend CVector operator*(const CMatrix& m, const CVector& v);
    friend std::istream& operator>>(std::istream& is, CMatrix& m);
    friend std::ostream& operator<<(std::ostream& os, const CMatrix& m);
};

#endif