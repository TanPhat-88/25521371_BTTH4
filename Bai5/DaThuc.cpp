#include "DaThuc.h"
#include <cmath>
#include <algorithm>

/*
    Hàm khởi tạo mặc định (Constructor không tham số)
    Input: Không có
    Output: Một đối tượng DaThuc tương ứng với đa thức P(x) = 0
    Hướng giải thuật:
    - Thêm một phần tử giá trị 0 vào vector hệ số (tương ứng bậc 0)
*/
DaThuc::DaThuc() {
    heSo.push_back(0.0);
}

/*
    Hàm khởi tạo đa thức với bậc cho trước
    Input: Số nguyên bac đại diện cho bậc lớn nhất dự kiến của đa thức
    Output: Một đối tượng DaThuc có kích thước mảng chứa đủ (bac + 1) phần tử
    Hướng giải thuật:
    - Dùng phương thức resize của vector để cấp phát bộ nhớ, mặc định gán các hệ số bằng 0
*/
DaThuc::DaThuc(int bac) {
    if (bac < 0) bac = 0;
    heSo.resize(bac + 1, 0.0);
}

/*
    Hàm khởi tạo đa thức từ một danh sách hệ số có sẵn
    Input: Một vector các số thực hs
    Output: Đối tượng DaThuc sao chép các hệ số tương ứng
    Hướng giải thuật:
    - Gán trực tiếp vector hs cho thuộc tính heSo của lớp
    - Gọi hàm ChuanHoa() để phòng trường hợp mảng truyền vào chứa các số 0 thừa ở cuối
*/
DaThuc::DaThuc(const std::vector<double>& hs) : heSo(hs) {
    ChuanHoa();
}

/*
    Hàm lấy bậc của đa thức
    Input: Không có
    Output: Số nguyên là bậc hiện tại của đa thức
    Hướng giải thuật:
    - Bậc của đa thức bằng số lượng phần tử của vector hệ số trừ đi 1 (vì tính cả bậc 0)
*/
int DaThuc::GetBac() const {
    return heSo.size() - 1;
}

/*
    Hàm chuẩn hóa đa thức
    Input: Không có
    Output: Thuộc tính heSo được rút gọn, loại bỏ các phần tử thừa bằng 0 ở vị trí bậc cao
    Hướng giải thuật:
    - Duyệt từ cuối vector về đầu, nếu gặp phần tử bằng 0 (hoặc xấp xỉ 0 do sai số) thì xóa (pop_back)
    - Dừng lại khi gặp phần tử khác 0 đầu tiên hoặc khi vector chỉ còn đúng 1 phần tử (đa thức không)
*/
void DaThuc::ChuanHoa() {
    while (heSo.size() > 1 && std::abs(heSo.back()) < 1e-9) {
        heSo.pop_back();
    }
}

/*
    Phép toán cộng hai đa thức
    Input: Hai đối tượng DaThuc dt1 và dt2
    Output: Một đối tượng DaThuc mới là tổng của hai đa thức truyền vào
    Hướng giải thuật:
    - Bậc của đa thức tổng tối đa sẽ bằng giá trị lớn nhất giữa bậc của dt1 và dt2
    - Khởi tạo đa thức kết quả với bậc tối đa đó
    - Chạy vòng lặp để cộng dồn hệ số của dt1 và dt2 vào kết quả tại các vị trí tương ứng
    - Gọi hàm ChuanHoa() cho kết quả trước khi trả về (đề phòng trường hợp các hệ số bậc cao tự triệt tiêu nhau)
*/
DaThuc operator+(const DaThuc& dt1, const DaThuc& dt2) {
    int bacMax = std::max(dt1.GetBac(), dt2.GetBac());
    DaThuc kq(bacMax);

    for (int i = 0; i <= bacMax; ++i) {
        double h1 = (i <= dt1.GetBac()) ? dt1.heSo[i] : 0.0;
        double h2 = (i <= dt2.GetBac()) ? dt2.heSo[i] : 0.0;
        kq.heSo[i] = h1 + h2;
    }
    kq.ChuanHoa();
    return kq;
}

/*
    Phép toán trừ hai đa thức
    Input: Hai đối tượng DaThuc dt1 và dt2
    Output: Một đối tượng DaThuc mới là hiệu (dt1 - dt2)
    Hướng giải thuật:
    - Tìm bậc lớn nhất giữa hai đa thức để khởi tạo cấu trúc đa thức kết quả
    - Duyệt qua từng bậc, lấy hệ số của dt1 trừ đi hệ số của dt2
    - Chuẩn hóa kết quả thu được trước khi trả về để dọn dẹp các hệ số bậc cao bị triệt tiêu về 0
*/
DaThuc operator-(const DaThuc& dt1, const DaThuc& dt2) {
    int bacMax = std::max(dt1.GetBac(), dt2.GetBac());
    DaThuc kq(bacMax);

    for (int i = 0; i <= bacMax; ++i) {
        double h1 = (i <= dt1.GetBac()) ? dt1.heSo[i] : 0.0;
        double h2 = (i <= dt2.GetBac()) ? dt2.heSo[i] : 0.0;
        kq.heSo[i] = h1 - h2;
    }
    kq.ChuanHoa();
    return kq;
}

/*
    Phép toán nhân hai đa thức
    Input: Hai đối tượng DaThuc dt1 và dt2
    Output: Một đối tượng DaThuc mới là tích của hai đa thức
    Hướng giải thuật:
    - Bậc của đa thức tích bằng tổng bậc của hai đa thức thành phần: bậc = dt1.GetBac() + dt2.GetBac()
    - Khởi tạo đa thức kết quả `kq` với bậc vừa tính
    - Sử dụng 2 vòng lặp lồng nhau: Nhân từng hệ số `dt1.heSo[i]` với `dt2.heSo[j]` rồi cộng dồn vào `kq.heSo[i + j]`
    - Chuẩn hóa đa thức kết quả và trả về
*/
DaThuc operator*(const DaThuc& dt1, const DaThuc& dt2) {
    int bacKq = dt1.GetBac() + dt2.GetBac();
    DaThuc kq(bacKq);

    for (int i = 0; i <= dt1.GetBac(); ++i) {
        for (int j = 0; j <= dt2.GetBac(); ++j) {
            kq.heSo[i + j] += dt1.heSo[i] * dt2.heSo[j];
        }
    }
    kq.ChuanHoa();
    return kq;
}

/*
    Hàm tính giá trị của đa thức tại một điểm x0 cụ thể
    Input: Số thực x0
    Output: Giá trị của đa thức kiểu double
    Hướng giải thuật:
    - Áp dụng lược đồ Horner (Horner's Method) để tính toán tối ưu, tránh dùng hàm pow gây lãng phí hiệu năng
    - Bắt đầu từ hệ số bậc cao nhất, liên tục nhân với x0 rồi cộng với hệ số đứng trước nó lùi dần về bậc 0
*/
double DaThuc::TinhGiaTri(double x0) const {
    double ketQua = heSo.back();
    for (int i = GetBac() - 1; i >= 0; --i) {
        ketQua = ketQua * x0 + heSo[i];
    }
    return ketQua;
}

/*
    Toán tử nhập dữ liệu (>>) cho đa thức
    Input: Dòng nhập is và đối tượng đa thức dt cần lưu dữ liệu
    Output: Trả về dòng nhập is để nhập liên tiếp
    Hướng giải thuật:
    - Yêu cầu người dùng nhập vào bậc của đa thức (phải là số không âm)
    - Cấp phát lại bộ nhớ cho vector hệ số dựa trên bậc vừa nhập
    - Sử dụng vòng lặp duyệt từ bậc cao về bậc thấp (hoặc ngược lại) để người dùng nhập từng hệ số tương ứng
    - Cuối cùng gọi ChuanHoa() để làm sạch đa thức
*/
std::istream& operator>>(std::istream& is, DaThuc& dt) {
    int bac;
    do {
        std::cout << "Nhap bac cua da thuc (>= 0): ";
        is >> bac;
    } while (bac < 0);

    dt.heSo.resize(bac + 1);
    for (int i = bac; i >= 0; --i) {
        std::cout << "Nhap he so cua x^" << i << ": ";
        is >> dt.heSo[i];
    }
    dt.ChuanHoa();
    return is;
}

/*
    Toán tử xuất dữ liệu (<<) cho đa thức
    Input: Dòng xuất os và đối tượng đa thức dt cần in
    Output: Trả về dòng xuất os để xuất liên tiếp
    Hướng giải thuật:
    - Duyệt qua từng hệ số từ bậc cao nhất về bậc 0
    - Kiểm tra loại trừ các trường hợp hệ số bằng 0 (không in) để đa thức hiển thị đẹp mắt
    - Định dạng dấu '+' hoặc '-' thích hợp, định dạng cách viết x^i rút gọn (ví dụ: x^1 ghi là x, x^0 không ghi x)
*/
std::ostream& operator<<(std::ostream& os, const DaThuc& dt) {
    bool holdsValue = false; // Biến đánh dấu xem đa thức đã in phần tử nào chưa
    int bac = dt.GetBac();

    for (int i = bac; i >= 0; --i) {
        double val = dt.heSo[i];
        if (val == 0) continue; // Bỏ qua hệ số bằng 0

        holdsValue = true;
        // Xử lý in dấu
        if (val > 0 && i != bac) os << " + ";
        else if (val < 0) {
            if (i == bac) os << "-";
            else os << " - ";
        }

        // Xử lý in giá trị số của hệ số
        double absVal = std::abs(val);
        if (absVal != 1 || i == 0) {
            os << absVal;
        }

        // Xử lý in biến x kèm số mũ
        if (i > 1) os << "x^" << i;
        else if (i == 1) os << "x";
    }

    if (!holdsValue) os << "0"; // Nếu tất cả hệ số đều bằng 0 thì in ra số 0
    return os;
}