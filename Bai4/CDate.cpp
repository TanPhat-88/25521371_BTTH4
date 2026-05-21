#include "CDate.h"
#include <cmath>

/*
    Hàm khởi tạo (Constructor) có tham số
    Input: Ba số nguyên d (ngay), m (thang), y (nam) có giá trị mặc định
    Output: Một đối tượng CDate được thiết lập giá trị tương ứng
    Hướng giải thuật:
    - Gán các giá trị tham số vào thuộc tính tương ứng của lớp
*/
CDate::CDate(int d, int m, int y) : ngay(d), thang(m), nam(y) {}

/*
    Hàm kiểm tra năm nhuận
    Input: Số nguyên n (năm cần kiểm tra)
    Output: Trả về true nếu là năm nhuận, ngược lại trả về false
    Hướng giải thuật:
    - Năm nhuận là năm chia hết cho 400 hoặc (chia hết cho 4 và không chia hết cho 100)
*/
bool CDate::KiemTraNamNhuan(int n) const {
    return (n % 400 == 0) || (n % 4 == 0 && n % 100 != 0);
}

/*
    Hàm lấy số ngày trong tháng
    Input: Hai số nguyên t (tháng), n (năm)
    Output: Số ngày tối đa của tháng đó
    Hướng giải thuật:
    - Các tháng 1, 3, 5, 7, 8, 10, 12 có 31 ngày
    - Các tháng 4, 6, 9, 11 có 30 ngày
    - Tháng 2 có 29 ngày nếu là năm nhuận, ngược lại có 28 ngày
*/
int CDate::SoNgayTrongThang(int t, int n) const {
    switch (t) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: 
            return 31;
        case 4: case 6: case 9: case 11: 
            return 30;
        case 2: 
            return KiemTraNamNhuan(n) ? 29 : 28;
        default: 
            return 0;
    }
}

/*
    Hàm chuyển ngày tháng năm sang số ngày tuyệt đối
    Input: Ba số nguyên d, m, y
    Output: Số ngày tính từ mốc thời gian cố định (Điểm mốc Công Nguyên)
    Hướng giải thuật:
    - Nếu tháng <= 2 thì giảm năm đi 1, tăng tháng thêm 12
    - Áp dụng công thức Zeller / công thức chuyển đổi lịch để tính ra số ngày tuyệt đối
*/
long CDate::ChuyenNgayThanhSo(int d, int m, int y) const {
    if (m <= 2) {
        y--;
        m += 12;
    }
    return d + (153 * (m - 3) + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400;
}

/*
    Hàm chuyển đổi số ngày tuyệt đối ngược lại thành Ngày Tháng Năm
    Input: Số nguyên long đại diện cho tổng số ngày tuyệt đối
    Output: Một đối tượng CDate lưu ngày, tháng, năm tương ứng
    Hướng giải thuật:
    - Sử dụng các phép toán chia lấy thương và chia lấy dư dựa trên chu kỳ số ngày của lịch Gregory 
      để truy ngược lại giá trị năm, tháng, ngày chính xác.
*/
CDate CDate::ChuyenSoThanhNgay(long totalDays) const {
    long y = (10000 * totalDays + 14780) / 3652425;
    long d = totalDays - (365 * y + y / 4 - y / 100 + y / 400);
    if (d < 0) {
        y--;
        d = totalDays - (365 * y + y / 4 - y / 100 + y / 400);
    }
    long m = (100 * d + 52) / 3060;
    long day = d - (306 * m + 5) / 10 + 1;
    long month = m + 2;
    long year = y + (month - 1) / 12;
    month = (month - 1) % 12 + 1;
    return CDate(static_cast<int>(day), static_cast<int>(month), static_cast<int>(year));
}

/*
    Toán tử cộng một số ngày vào đối tượng CDate
    Input: Số nguyên days (số ngày cần cộng thêm)
    Output: Một đối tượng CDate mới sau khi đã cộng thêm ngày
    Hướng giải thuật:
    - Chuyển đổi ngày hiện tại thành số ngày tuyệt đối
    - Cộng thêm số ngày `days` vào số ngày tuyệt đối đó
    - Chuyển số ngày tổng mới thu được ngược lại thành đối tượng CDate và trả về
*/
CDate CDate::operator+(int days) const {
    long currentDays = ChuyenNgayThanhSo(ngay, thang, nam);
    return ChuyenSoThanhNgay(currentDays + days);
}

/*
    Toán tử trừ một số ngày khỏi đối tượng CDate
    Input: Số nguyên days (số ngày cần trừ đi)
    Output: Một đối tượng CDate mới sau khi đã trừ bớt ngày
    Hướng giải thuật:
    - Chuyển đổi ngày hiện tại thành số ngày tuyệt đối
    - Trừ đi số ngày `days` khỏi số ngày tuyệt đối đó
    - Chuyển kết quả ngược lại thành đối tượng CDate và trả về
*/
CDate CDate::operator-(int days) const {
    long currentDays = ChuyenNgayThanhSo(ngay, thang, nam);
    return ChuyenSoThanhNgay(currentDays - days);
}

/*
    Toán tử tăng 1 ngày - Tiền tố (++CDate)
    Input: Không có
    Output: Trả về tham chiếu đến chính đối tượng CDate sau khi tăng
    Hướng giải thuật:
    - Tăng thuộc tính ngay lên 1
    - Nếu vượt quá số ngày tối đa của tháng hiện tại, reset ngay về 1 và tăng thang lên 1
    - Nếu thang vượt quá 12, reset thang về 1 và tăng nam lên 1
*/
CDate& CDate::operator++() {
    ngay++;
    if (ngay > SoNgayTrongThang(thang, nam)) {
        ngay = 1;
        thang++;
        if (thang > 12) {
            thang = 1;
            nam++;
        }
    }
    return *this;
}

/*
    Toán tử tăng 1 ngày - Hậu tố (CDate++)
    Input: Tham số dummy int để phân biệt với tiền tố
    Output: Trả về một đối tượng CDate mang giá trị cũ trước khi tăng
    Hướng giải thuật:
    - Lưu giá trị hiện tại vào đối tượng tạm `temp`
    - Gọi toán tử tiền tố (++(*this)) để tăng giá trị của đối tượng gốc
    - Trả về đối tượng `temp`
*/
CDate CDate::operator++(int) {
    CDate temp = *this;
    ++(*this);
    return temp;
}

/*
    Toán tử giảm 1 ngày - Tiền tố (--CDate)
    Input: Không có
    Output: Trả về tham chiếu đến chính đối tượng CDate sau khi giảm
    Hướng giải thuật:
    - Giảm thuộc tính ngay đi 1
    - Nếu ngay về bằng 0, giảm thang đi 1 (nếu thang về 0 thì gán thang = 12, giảm nam đi 1)
    - Cập nhật thuộc tính ngay bằng số ngày tối đa của tháng mới vừa được lùi lại
*/
CDate& CDate::operator--() {
    ngay--;
    if (ngay == 0) {
        thang--;
        if (thang == 0) {
            thang = 12;
            nam--;
        }
        ngay = SoNgayTrongThang(thang, nam);
    }
    return *this;
}

/*
    Toán tử giảm 1 ngày - Hậu tố (CDate--)
    Input: Tham số dummy int
    Output: Trả về đối tượng CDate cũ trước khi giảm
    Hướng giải thuật:
    - Lưu giá trị hiện tại vào đối tượng tạm `temp`
    - Gọi toán tử tiền tố (--(*this)) để giảm giá trị đối tượng gốc
    - Trả về đối tượng `temp`
*/
CDate CDate::operator--(int) {
    CDate temp = *this;
    --(*this);
    return temp;
}

/*
    Toán tử trừ hai đối tượng CDate (Tính khoảng cách ngày)
    Input: Đối tượng CDate d cần trừ
    Output: Số ngày chênh lệch kiểu long giữa hai mốc thời gian
    Hướng giải thuật:
    - Chuyển cả hai mốc ngày tháng năm về số ngày tuyệt đối
    - Lấy số ngày tuyệt đối của đối tượng hiện tại trừ đi số ngày tuyệt đối của d
*/
long CDate::operator-(const CDate& d) const {
    return ChuyenNgayThanhSo(ngay, thang, nam) - ChuyenNgayThanhSo(d.ngay, d.thang, d.nam);
}

/*
    Toán tử nhập dữ liệu (>>) cho CDate
    Input: Dòng nhập is và đối tượng date để lưu dữ liệu
    Output: Trả về dòng nhập is
    Hướng giải thuật:
    - Cho người dùng nhập lần lượt ngày, tháng, năm
    - Thực hiện kiểm tra tính hợp lệ sơ bộ (ngày, tháng không âm, ngày không vượt quá giới hạn tháng)
    - Nếu không hợp lệ, yêu cầu nhập lại bằng vòng lặp do-while
*/
std::istream& operator>>(std::istream& is, CDate& date) {
    bool hopLe = false;
    do {
        std::cout << "Nhap ngay, thang, nam (cach nhau bang dau cach): ";
        is >> date.ngay >> date.thang >> date.nam;
        
        if (date.thang >= 1 && date.thang <= 12 && date.nam > 0) {
            if (date.ngay >= 1 && date.ngay <= date.SoNgayTrongThang(date.thang, date.nam)) {
                hopLe = true;
            }
        }
        if (!hopLe) {
            std::cout << "Ngay thang nam khong hop le! Vui long nhap lai.\n";
        }
    } while (!hopLe);
    return is;
}

/*
    Toán tử xuất dữ liệu (<<) cho CDate
    Input: Dòng xuất os và đối tượng date cần xuất
    Output: Trả về dòng xuất os
    Hướng giải thuật:
    - Xuất dữ liệu ra màn hình theo định dạng chuẩn DD/MM/YYYY
*/
std::ostream& operator<<(std::ostream& os, const CDate& date) {
    if (date.ngay < 10) os << "0";
    os << date.ngay << "/";
    if (date.thang < 10) os << "0";
    os << date.thang << "/" << date.nam;
    return os;
}