#include <iostream>
#include "CVector.h"
#include <stdexcept>

int main() {
    CVector v1, v2;

    std::cout << "=== NHAP VECTOR THU NHAT ===\n";
    std::cin >> v1;
    std::cout << "Vector 1 vua nhap: V1 = " << v1 << "\n\n";

    std::cout << "=== NHAP VECTOR THU HAI ===\n";
    std::cin >> v2;
    std::cout << "Vector 2 vua nhap: V2 = " << v2 << "\n\n";

    std::cout << "=== THUCC HIEN CAC PHEP TOAN ===\n";
    
    // Đặt trong khối try-catch để phòng ngừa lỗi tính toán lệch số chiều
    try {
        std::cout << "V1 + V2 = " << (v1 + v2) << "\n";
        std::cout << "V1 - V2 = " << (v1 - v2) << "\n";
        std::cout << "Tich vo huong (V1 * V2) = " << (v1 * v2) << "\n";
    } 
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << "\n";
    }

    std::cout << "\n=== PHEP NHAN VO HUONG VOI HANG SO ===\n";
    double k = 2.5;
    std::cout << "V1 * " << k << " = " << (v1 * k) << "\n";
    std::cout << k << " * V2 = " << (k * v2) << "\n";

    return 0;
}