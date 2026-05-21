#include <iostream>
#include "CMatrix.h"
#include "CVector.h"
#include <stdexcept>

int main() {
    CMatrix A, B;
    CVector V;

    std::cout << "=== NHAP MA TRAN A ===\n";
    std::cin >> A;
    std::cout << "\nMa tran A vua nhap:\n" << A << "\n";

    std::cout << "=== NHAP MA TRAN B ===\n";
    std::cin >> B;
    std::cout << "\nMa tran B vua nhap:\n" << B << "\n";

    std::cout << "=== NHAP VECTOR V ===\n";
    std::cin >> V;
    std::cout << "\nVector V vua nhap: " << V << "\n\n";

    std::cout << "================ KET QUA TINH TOAN ================\n\n";

    // 1. Tính tích của hai ma trận (A * B)
    try {
        CMatrix C = A * B;
        std::cout << "Tich hai ma tran (A * B) la:\n" << C << "\n";
    } 
    catch (const std::invalid_argument& e) {
        std::cout << "Khong the nhan hai ma tran: " << e.what() << "\n\n";
    }

    // 2. Tính tích của một ma trận và một vector (A * V)
    try {
        CVector resVector = A * V;
        std::cout << "Tich ma tran va vector (A * V) la: " << resVector << "\n";
    } 
    catch (const std::invalid_argument& e) {
        std::cout << "Khong the nhan ma tran voi vector: " << e.what() << "\n";
    }

    return 0;
}