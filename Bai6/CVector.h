#ifndef CVECTOR_H
#define CVECTOR_H

#include <iostream>
#include <vector>

class CVector {
private:
    int soChieu;              
    std::vector<double> toaDo;

public:
    CVector();                 
    CVector(int n);
    CVector(const std::vector<double>& v);
    int GetSoChieu() const;

    friend CVector operator+(const CVector& v1, const CVector& v2); 
    friend CVector operator-(const CVector& v1, const CVector& v2); 
    friend double operator*(const CVector& v1, const CVector& v2);  
    friend CVector operator*(double k, const CVector& v);           
    friend CVector operator*(const CVector& v, double k);   
    friend std::istream& operator>>(std::istream& is, CVector& v);
    friend std::ostream& operator<<(std::ostream& os, const CVector& v);
};

#endif