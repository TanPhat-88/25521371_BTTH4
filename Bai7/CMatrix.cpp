#include "CMatrix.h"
#include <stdexcept>

/*
    Hàm khởi tạo mặc định (Constructor không tham số)
    Input: Không có
    Output: Một đối tượng CMatrix rỗng có kích thước 0x0
    Hướng giải thuật:
    - Thiết lập thuộc tính soDong và soCot bằng 0
*/
CMatrix::CMatrix() : soDong(0), soCot(0) {}

/*
    Hàm khởi tạo ma trận với kích thước tùy ý
    Input: Hai số nguyên r (số dòng) và c (số cột)
    Output: Một đối tượng CMatrix kích thước r x c chứa toàn bộ số 0.0
    Hướng giải thuật:
    - Kiểm tra tính hợp lệ của r và c (nếu <= 0 thì đưa về ma trận rỗng)
    - Dùng phương thức resize để cấp phát bộ nhớ mảng động 2 chiều cho thuộc tính data
*/
CMatrix::CMatrix(int r, int c) {
    soDong = (r > 0) ? r : 0;
    soCot = (c > 0) ? c : 0;
    data.resize(soDong, std::vector<double>(soCot, 0.0));
}

/*
    Hàm khởi tạo ma trận từ mảng 2 chiều có sẵn
    Input: Một đối tượng vector 2 chiều chứa các số thực
    Output: Một đối tượng CMatrix lưu trữ dữ liệu tương ứng
    Hướng giải thuật:
    - Gán trực tiếp dữ liệu mảng truyền vào cho thuộc tính data
    - Cập nhật số dòng bằng kích thước mảng ngoài, số cột bằng kích thước hàng đầu tiên
*/
CMatrix::CMatrix(const std::vector<std::vector<double>>& m) : data(m) {
    soDong = m.size();
    soCot = (soDong > 0) ? m[0].size() : 0;
}

/*
    Hàm lấy số dòng của ma trận
    Input: Không có
    Output: Số nguyên là số dòng hiện tại
    Hướng giải thuật: Trả về giá trị của thuộc tính soDong
*/
int CMatrix::GetSoDong() const { return soDong; }

/*
    Hàm lấy số cột của ma trận
    Input: Không có
    Output: Số nguyên là số cột hiện tại
    Hướng giải thuật: Trả về giá trị của thuộc tính soCot
*/
int CMatrix::GetSoCot() const { return soCot; }

/*
    Phép toán cộng hai ma trận
    Input: Hai đối tượng CMatrix m1 và m2
    Output: Một ma trận mới là tổng của m1 và m2
    Hướng giải thuật:
    - Kiểm tra điều kiện: Hai ma trận phải cùng số dòng và cùng số cột
    - Nếu lệch kích thước, ném ra ngoại lệ lỗi cấu trúc toán học (invalid_argument)
    - Tạo ma trận kết quả cùng kích thước và cộng các phần tử tương ứng: kq[i][j] = m1[i][j] + m2[i][j]
*/
CMatrix operator+(const CMatrix& m1, const CMatrix& m2) {
    if (m1.soDong != m2.soDong || m1.soCot != m2.soCot) {
        throw std::invalid_argument("Loi: Hai ma tran khong cung kich thuoc, khong the cong!");
    }
    CMatrix kq(m1.soDong, m1.soCot);
    for (int i = 0; i < m1.soDong; ++i) {
        for (int j = 0; j < m1.soCot; ++j) {
            kq.data[i][j] = m1.data[i][j] + m2.data[i][j];
        }
    }
    return kq;
}

/*
    Phép toán trừ hai ma trận
    Input: Hai đối tượng CMatrix m1 và m2
    Output: Một ma trận mới là hiệu (m1 - m2)
    Hướng giải thuật:
    - Kiểm tra điều kiện tương thích về kích thước của m1 và m2
    - Sử dụng hai vòng lặp lồng nhau để trừ các phần tử tại vị trí tương ứng: kq[i][j] = m1[i][j] - m2[i][j]
*/
CMatrix operator-(const CMatrix& m1, const CMatrix& m2) {
    if (m1.soDong != m2.soDong || m1.soCot != m2.soCot) {
        throw std::invalid_argument("Loi: Hai ma tran khong cung kich thuoc, khong the tru!");
    }
    CMatrix kq(m1.soDong, m1.soCot);
    for (int i = 0; i < m1.soDong; ++i) {
        for (int j = 0; j < m1.soCot; ++j) {
            kq.data[i][j] = m1.data[i][j] - m2.data[i][j];
        }
    }
    return kq;
}

/*
    Phép toán nhân hai ma trận
    Input: Hai đối tượng CMatrix m1 (kích thước m x n) và m2 (kích thước n x p)
    Output: Một ma trận mới kích thước m x p là tích (m1 * m2)
    Hướng giải thuật:
    - Kiểm tra điều kiện: Số cột của ma trận trước phải bằng số dòng của ma trận sau (m1.soCot == m2.soDong)
    - Khởi tạo ma trận kết quả có kích thước là (m1.soDong x m2.soCot)
    - Sử dụng 3 vòng lặp lồng nhau (i, j, k) để tính tổng tích lũy cho từng phần tử của ma trận tích
*/
CMatrix operator*(const CMatrix& m1, const CMatrix& m2) {
    if (m1.soCot != m2.soDong) {
        throw std::invalid_argument("Loi: So cot ma tran truoc phai bang so dong ma tran sau!");
    }
    CMatrix kq(m1.soDong, m2.soCot);
    for (int i = 0; i < m1.soDong; ++i) {
        for (int j = 0; j < m2.soCot; ++j) {
            for (int k = 0; k < m1.soCot; ++k) {
                kq.data[i][j] += m1.data[i][k] * m2.data[k][j];
            }
        }
    }
    return kq;
}

/*
    Phép toán nhân một ma trận với một vector
    Input: Một ma trận m (kích thước m x n) và một vector v (số chiều n)
    Output: Một đối tượng CVector mới có số chiều bằng m (số dòng của ma trận)
    Hướng giải thuật:
    - Kiểm tra điều kiện: Số cột của ma trận phải bằng số chiều của vector đầu vào
    - Tạo một mảng tạm kiểu std::vector<double> kích thước bằng m.soDong để chứa kết quả
    - Phần tử thứ i của mảng kết quả bằng tổng tích lũy của hàng i trong ma trận nhân với các tọa độ tương ứng của vector v (lấy qua hàm v.GetToaDo(k))
    - Trả về một đối tượng CVector được dựng trực tiếp từ mảng tạm này
*/
CVector operator*(const CMatrix& m, const CVector& v) {
    if (m.soCot != v.GetSoChieu()) {
        throw std::invalid_argument("Loi: So cot cua ma tran phai bang so chieu cua vector!");
    }
    
    std::vector<double> mangKq(m.soDong, 0.0);
    for (int i = 0; i < m.soDong; ++i) {
        for (int k = 0; k < m.soCot; ++k) {
            mangKq[i] += m.data[i][k] * v.GetToaDo(k);
        }
    }
    return CVector(mangKq);
}

/*
    Toán tử nhập dữ liệu (>>) cho ma trận
    Input: Luồng nhập is và đối tượng ma trận m cần gán dữ liệu
    Output: Trả về luồng nhập is để cho phép nhập liên tiếp
    Hướng giải thuật:
    - Yêu cầu người dùng nhập vào số dòng và số cột hợp lệ (> 0)
    - Cấp phát lại kích thước cho mảng 2 chiều data dựa theo thông số mới
    - Dùng 2 vòng lặp lồng nhau duyệt qua từng hàng và từng cột để nhập giá trị
*/
std::istream& operator>>(std::istream& is, CMatrix& m) {
    int r, c;
    do {
        std::cout << "Nhap so dong ( > 0): "; is >> r;
        std::cout << "Nhap so cot ( > 0): ";  is >> c;
    } while (r <= 0 || c <= 0);

    m.soDong = r;
    m.soCot = c;
    m.data.resize(r, std::vector<double>(c));

    std::cout << "Nhap cac phan tu cho ma tran (" << r << "x" << c << "):\n";
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            std::cout << "-> Phan tu [" << i << "][" << j << "]: ";
            is >> m.data[i][j];
        }
    }
    return is;
}

/*
    Toán tử xuất dữ liệu (<<) cho ma trận
    Input: Luồng xuất os và đối tượng ma trận m cần hiển thị
    Output: Trả về luồng xuất os để xuất liên tiếp
    Hướng giải thuật:
    - Sử dụng 2 vòng lặp duyệt qua ma trận
    - In các phần tử trên cùng một hàng cách nhau một dấu tab `\t` để căn thẳng hàng
    - In ký tự xuống dòng `\n` khi kết thúc một hàng để tạo hình khối ma trận hoàn chỉnh
*/
std::ostream& operator<<(std::ostream& os, const CMatrix& m) {
    for (int i = 0; i < m.soDong; ++i) {
        for (int j = 0; j < m.soCot; ++j) {
            os << m.data[i][j] << "\t";
        }
        os << "\n";
    }
    return os;
}