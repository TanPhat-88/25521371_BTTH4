#include <iostream>
#include "SoPhuc.h"

int main() {
    SoPhuc sp1, sp2;

    std::cout << "--- Nhap so phuc thu nhat ---\n";
    std::cin >> sp1;

    std::cout << "\n--- Nhap so phuc thu hai ---\n";
    std::cin >> sp2;

    std::cout << "\n--- Ket qua cac phep toan ---\n";
    std::cout << "sp1 = " << sp1 << "\n";
    std::cout << "sp2 = " << sp2 << "\n";
    std::cout << "sp1 + sp2 = " << (sp1 + sp2) << "\n";
    std::cout << "sp1 - sp2 = " << (sp1 - sp2) << "\n";
    std::cout << "sp1 * sp2 = " << (sp1 * sp2) << "\n";
    std::cout << "sp1 / sp2 = " << (sp1 / sp2) << "\n";

    std::cout << "\n--- Kiem tra so sanh ---\n";
    if (sp1 == sp2) {
        std::cout << "sp1 bang sp2\n";
    } else {
        std::cout << "sp1 khac sp2\n";
    }

    std::cout << "\n--- Kiem tra quan diem so thuc la so phuc dac biet ---\n";
    // Số thực 5.5 tự động được ép kiểu ngầm định thành SoPhuc(5.5, 0) nhờ constructor mặc định
    SoPhuc spThuc = 5.5; 
    std::cout << "So thuc 5.5 duoc hieu la so phuc: " << spThuc << "\n";
    
    // Thực hiện phép toán giữa số phức và số thực một cách tự nhiên
    std::cout << "sp1 + 10 = " << (sp1 + 10) << "\n"; 
    std::cout << "20 * sp2 = " << (20 * sp2) << "\n";

    return 0;
}