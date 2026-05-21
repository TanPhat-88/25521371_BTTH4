#include "CVector.h"
#include <stdexcept>

/*
    Hàm khởi tạo mặc định (Constructor không tham số)
    Input: Không có
    Output: Một đối tượng CVector thuộc không gian 1 chiều, tọa độ gốc (0)
    Hướng giải thuật:
    - Gán số chiều mặc định bằng 1
    - Thêm một phần tử có giá trị 0.0 vào mảng tọa độ
*/
CVector::CVector() : soChieu(1) {
    toaDo.push_back(0.0);
}

/*
    Hàm khởi tạo vector n chiều
    Input: Số nguyên n đại diện cho số chiều không gian
    Output: Một đối tượng CVector n chiều với toàn bộ tọa độ ban đầu bằng 0
    Hướng giải thuật:
    - Kiểm tra nếu n hợp lệ (n > 0), nếu không mặc định đưa về 1 chiều
    - Cập nhật biến soChieu và resize vector toaDo chứa n phần tử 0.0
*/
CVector::CVector(int n) {
    soChieu = (n > 0) ? n : 1;
    toaDo.resize(soChieu, 0.0);
}

/*
    Hàm khởi tạo vector từ danh sách tọa độ có sẵn
    Input: Một vector kiểu double chứa các giá trị tọa độ
    Output: Một đối tượng CVector hoàn chỉnh
    Hướng giải thuật:
    - Lấy kích thước của vector truyền vào gán cho thuộc tính soChieu
    - Sao chép toàn bộ mảng dữ liệu vào thuộc tính toaDo của lớp
*/
CVector::CVector(const std::vector<double>& v) : toaDo(v) {
    soChieu = v.size();
}

/*
    Hàm lấy số chiều của vector
    Input: Không có
    Output: Số nguyên là số chiều hiện tại của không gian vector
    Hướng giải thuật:
    - Trả về giá trị của thuộc tính soChieu
*/
int CVector::GetSoChieu() const {
    return soChieu;
}

/*
    Phép toán cộng hai vector
    Input: Hai đối tượng CVector v1 và v2
    Output: Một đối tượng CVector mới là tổng của v1 và v2
    Hướng giải thuật:
    - Kiểm tra điều kiện: Hai vector bắt buộc phải cùng số chiều. 
      Nếu lệch số chiều, ném (throw) lỗi ngoại lệ invalid_argument.
    - Tạo vector kết quả cùng số chiều.
    - Chạy vòng lặp từ 0 đến soChieu - 1, tính: kq[i] = v1[i] + v2[i]
*/
CVector operator+(const CVector& v1, const CVector& v2) {
    if (v1.soChieu != v2.soChieu) {
        throw std::invalid_argument("Loi: Hai vector khong cung so chieu, khong the cong!");
    }
    CVector kq(v1.soChieu);
    for (int i = 0; i < v1.soChieu; ++i) {
        kq.toaDo[i] = v1.toaDo[i] + v2.toaDo[i];
    }
    return kq;
}

/*
    Phép toán trừ hai vector
    Input: Hai đối tượng CVector v1 và v2
    Output: Một đối tượng CVector mới là hiệu của v1 và v2
    Hướng giải thuật:
    - Kiểm tra tính tương thích về số chiều của hai vector.
    - Tạo vector kết quả và dùng vòng lặp trừ các tọa độ tương ứng: kq[i] = v1[i] - v2[i]
*/
CVector operator-(const CVector& v1, const CVector& v2) {
    if (v1.soChieu != v2.soChieu) {
        throw std::invalid_argument("Loi: Hai vector khong cung so chieu, khong the tru!");
    }
    CVector kq(v1.soChieu);
    for (int i = 0; i < v1.soChieu; ++i) {
        kq.toaDo[i] = v1.toaDo[i] - v2.toaDo[i];
    }
    return kq;
}

/*
    Phép toán tích vô hướng của hai vector (Dot Product)
    Input: Hai đối tượng CVector v1 và v2
    Output: Một số thực kiểu double là giá trị tích vô hướng
    Hướng giải thuật:
    - Kiểm tra tính tương thích về số chiều.
    - Khởi tạo biến tổng tích lũy (tong = 0).
    - Duyệt qua từng chiều không gian, nhân hai tọa độ tương ứng lại rồi cộng dồn vào tổng.
*/
double operator*(const CVector& v1, const CVector& v2) {
    if (v1.soChieu != v2.soChieu) {
        throw std::invalid_argument("Loi: Hai vector khong cung so chieu, khong the tinh tich vo huong!");
    }
    double tong = 0;
    for (int i = 0; i < v1.soChieu; ++i) {
        tong += v1.toaDo[i] * v2.toaDo[i];
    }
    return tong;
}

/*
    Phép toán nhân hằng số với vector (Dạng: k * v)
    Input: Một số thực k và một đối tượng CVector v
    Output: Một đối tượng CVector mới đã được tỷ lệ hóa (scale) theo k
    Hướng giải thuật:
    - Khởi tạo vector kết quả sao chép cấu trúc từ vector v.
    - Nhân mọi tọa độ của v với hệ số k: kq[i] = k * v[i]
*/
CVector operator*(double k, const CVector& v) {
    CVector kq(v.soChieu);
    for (int i = 0; i < v.soChieu; ++i) {
        kq.toaDo[i] = k * v.toaDo[i];
    }
    return kq;
}

/*
    Phép toán nhân vector với hằng số (Dạng: v * k)
    Input: Một đối tượng CVector v và một số thực k
    Output: Một đối tượng CVector mới nhân với k
    Hướng giải thuật:
    - Áp dụng tính chất giao hoán, gọi lại toán tử nhân hằng số với vector (k * v) đã định nghĩa ở trên.
*/
CVector operator*(const CVector& v, double k) {
    return k * v;
}

/*
    Toán tử nhập dữ liệu (>>) cho CVector
    Input: Luồng nhập is và đối tượng vector v cần gán dữ liệu
    Output: Trả về luồng nhập is để nhập liên tiếp
    Hướng giải thuật:
    - Yêu cầu người dùng nhập số chiều mong muốn (n > 0).
    - Thay đổi kích thước mảng toaDo tương ứng với số chiều mới.
    - Chạy vòng lặp để lần lượt nhập giá trị tọa độ cho từng chiều (từ chiều thứ 1 đến chiều thứ n).
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
    Toán tử xuất dữ liệu (<<) cho CVector
    Input: Luồng xuất os và đối tượng vector v cần hiển thị
    Output: Trả về luồng xuất os để xuất liên tiếp
    Hướng giải thuật:
    - Hiển thị vector dưới định dạng chuẩn toán học: (x1, x2, ..., xn)
    - Duyệt mảng, in dấu phẩy ngăn cách giữa các phần tử nhưng không in dấu phẩy sau phần tử cuối cùng.
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