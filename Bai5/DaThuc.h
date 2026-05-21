#ifndef DATHUC_H
#define DATHUC_H

#include <iostream>
#include <vector>

class DaThuc {
private:
    std::vector<double> heSo; 

public:
    DaThuc();
    DaThuc(int bac);
    DaThuc(const std::vector<double>& hs);
    int GetBac() const;
    void ChuanHoa();
    friend DaThuc operator+(const DaThuc& dt1, const DaThuc& dt2);
    friend DaThuc operator-(const DaThuc& dt1, const DaThuc& dt2);
    friend DaThuc operator*(const DaThuc& dt1, const DaThuc& dt2);
    double TinhGiaTri(double x0) const;
    friend std::istream& operator>>(std::istream& is, DaThuc& dt);
    friend std::ostream& operator<<(std::ostream& os, const DaThuc& dt);
};

#endif