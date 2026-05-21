#ifndef CDATE_H
#define CDATE_H

#include <iostream>

class CDate {
private:
    int ngay;
    int thang;
    int nam;
    bool KiemTraNamNhuan(int n) const;
    int SoNgayTrongThang(int t, int n) const;
    long ChuyenNgayThanhSo(int d, int m, int y) const;
    CDate ChuyenSoThanhNgay(long totalDays) const;

public:
    CDate(int d = 1, int m = 1, int y = 2000);
    CDate operator+(int days) const;
    CDate operator-(int days) const;
    CDate& operator++();    // ++CDate
    CDate operator++(int);  // CDate++
    CDate& operator--();    // --CDate
    CDate operator--(int);  // CDate--
    long operator-(const CDate& d) const;
    friend std::istream& operator>>(std::istream& is, CDate& date);
    friend std::ostream& operator<<(std::ostream& os, const CDate& date);
};

#endif