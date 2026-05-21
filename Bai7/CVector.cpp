#include "CVector.h"

/*
    Hàm khởi tạo mặc định
    Input: Không có
    Output: Vector 1 chiều có giá trị bằng 0
    Hướng giải thuật: Gán số chiều bằng 1 và thêm một số 0 vào mảng
*/
CVector::CVector() : soChieu(1) {
    toaDo.push_back(0.0);
}

/*
    Hàm khởi tạo vector với số chiều cho trước
    Input: Số nguyên n (số chiều)
    Output: Vector n chiều chứa toàn số 0
    Hướng giải thuật: Thay đổi kích thước vector hệ thống về n phần tử 0
*/
CVector::CVector(int n) {
    soChieu = (n > 0) ? n : 1;
    toaDo.resize(soChieu, 0.0);
}

/*
    Hàm khởi tạo từ mảng vector có sẵn
    Input: Mảng std::vector<double> chứa các tọa độ
    Output: Đối tượng CVector tương ứng
    Hướng giải thuật: Sao chép toàn bộ mảng dữ liệu đầu vào và cập nhật lại số chiều
*/
CVector::CVector(const std::vector<double>& v) : toaDo(v) {
    soChieu = v.size();
}

/*
    Hàm lấy số chiều của vector
    Input: Không có
    Output: Số chiều kiểu nguyên
    Hướng giải thuật: Trả về giá trị thuộc tính soChieu
*/
int CVector::GetSoChieu() const {
    return soChieu;
}

/*
    Hàm lấy giá trị tọa độ tại vị trí i
    Input: Chỉ số nguyên i (tính từ 0)
    Output: Giá trị tọa độ kiểu double tại vị trí tương ứng
    Hướng giải thuật: Trả về phần tử toaDo[i] (Hàm này giúp CMatrix lấy dữ liệu dễ dàng)
*/
double CVector::GetToaDo(int i) const {
    return toaDo[i];
}

/*
    Toán tử nhập dữ liệu (>>) cho Vector
    Input: Luồng nhập is và đối tượng vector v
    Output: Trả về luồng nhập is
    Hướng giải thuật: Nhập số chiều, cấp phát lại mảng và duyệt lặp để nhập từng tọa độ
*/
std::istream& operator>>(std::istream& is, CVector& v) {
    int n;
    do {
        std::cout << "Nhap so chieu cho vector (n > 0): ";
        is >> n;
    } while (n <= 0);

    v.soChieu = n;
    v.toaDo.resize(n);
    std::cout << "Nhap cac toa do cho vector (" << n << " chieu):\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "-> Toa do thu " << i + 1 << ": ";
        is >> v.toaDo[i];
    }
    return is;
}

/*
    Toán tử xuất dữ liệu (<<) cho Vector
    Input: Luồng xuất os và đối tượng vector v
    Output: Trả về luồng xuất os
    Hướng giải thuật: Xuất mảng theo định dạng toán học chuẩn (x1, x2, ..., xn)
*/
std::ostream& operator<<(std::ostream& os, const CVector& v) {
    os << "(";
    for (int i = 0; i < v.soChieu; ++i) {
        os << v.toaDo[i];
        if (i < v.soChieu - 1) {
            os << ", ";
        }
    }
    os << ")";
    return os;
}