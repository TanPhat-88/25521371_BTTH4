#include <iostream>
#include "DaThuc.h"

int main() {
    DaThuc dt1, dt2;

    std::cout << "=== NHAP DA THUC THU NHAT ===\n";
    std::cin >> dt1;
    std::cout << "Da thuc 1 vua nhap: P(x) = " << dt1 << "\n\n";

    std::cout << "=== NHAP DA THUC THU HAI ===\n";
    std::cin >> dt2;
    std::cout << "Da thuc 2 vua nhap: Q(x) = " << dt2 << "\n\n";

    std::cout << "=== KET QUA CAC PHEP TOAN ===\n";
    std::cout << "P(x) + Q(x) = " << (dt1 + dt2) << "\n";
    std::cout << "P(x) - Q(x) = " << (dt1 - dt2) << "\n";
    std::cout << "P(x) * Q(x) = " << (dt1 * dt2) << "\n\n";

    std::cout << "=== TINH GIA TRI DA THUC ===\n";
    double x0;
    std::cout << "Nhap gia tri x0 de tinh P(x0): ";
    std::cin >> x0;
    std::cout << "Gia tri P(" << x0 << ") = " << dt1.TinhGiaTri(x0) << "\n";

    return 0;
}