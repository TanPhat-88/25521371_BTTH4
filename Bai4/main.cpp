#include <iostream>
#include <iomanip>
#include "CDate.h"

int main() {
    std::cout << "=== CHUONG TRINH UNG DUNG CDATE TINH LAI SUAT NGAN HANG ===\n\n";

    CDate ngayGui, ngayRut;
    double tienGoc = 0;
    double laiSuatNam = 0; // Ví dụ: 6.5 nghĩa là 6.5%/năm

    std::cout << "1. Nhap thong tin thoi gian:\n";
    std::cout << "-> Nhap ngay GUI tien:\n";
    std::cin >> ngayGui;

    // Vòng lặp đảm bảo ngày rút phải sau hoặc bằng ngày gửi
    do {
        std::cout << "-> Nhap ngay RUT tien:\n";
        std::cin >> ngayRut;
        if (ngayRut - ngayGui < 0) {
            std::cout << "Loi: Ngay rut khong the truoc ngay gui! Vui long nhap lai.\n";
        }
    } while (ngayRut - ngayGui < 0);

    std::cout << "\n2. Nhap thong tin tai chinh:\n";
    std::cout << "Nhap so tien goc gui ban dau (VND): ";
    std::cin >> tienGoc;
    std::cout << "Nhap lai suat gui (%/nam): ";
    std::cin >> laiSuatNam;

    // Áp dụng toán tử trừ (-) của lớp CDate để tính khoảng cách ngày
    long soNgayGui = ngayRut - ngayGui;

    // Tính toán lãi suất (Giả định ngân hàng tính lãi theo ngày thực tế dựa trên kỳ hạn năm 365 ngày)
    double laiSuatNgay = (laiSuatNam / 100) / 365;
    double tienLai = tienGoc * laiSuatNgay * soNgayGui;
    double tongNhan = tienGoc + tienLai;

    // Xuất kết quả báo cáo
    std::cout << "\n================= KET QUA KINH DOANH =================\n";
    std::cout << "Ngay gui tien      : " << ngayGui << "\n";
    std::cout << "Ngay rut tien      : " << ngayRut << "\n";
    std::cout << "Tong so ngay gui   : " << soNgayGui << " ngay\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "So tien goc        : " << tienGoc << " VND\n";
    std::cout << "Tien lai nhan duoc : " << tienLai << " VND\n";
    std::cout << "Tong so tien rut   : " << tongNhan << " VND\n";
    std::cout << "======================================================\n";
    return 0;
}