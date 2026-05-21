#ifndef TIME_H
#define TIME_H

#include <iostream>
using namespace std;

class CTime
{
private:
    int gio, phut, giay;
    void ChuanHoa();
public: 
    CTime(int,int,int);
    CTime();
    void LayGioHeThong();
    CTime operator+(int s);
    CTime operator-(int s);
    CTime& operator++();
    CTime operator++(int);
    CTime& operator--();
    CTime operator--(int);
    friend istream& operator>>(istream& is, CTime& t);
    friend ostream& operator<<(ostream& os, const CTime& t);

};

#endif