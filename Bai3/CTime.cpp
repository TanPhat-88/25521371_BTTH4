#include <windows.h>
#include "CTime.h"
using namespace std;

/*
    Hàm chuẩn hóa thời gian
    Input: Không có tham số truyền vào (sử dụng thuộc tính gio, phut, giay của đối tượng hiện tại)
    Output: Các thuộc tính gio, phut, giay được đưa về khoảng hợp lệ (0-23 cho giờ, 0-59 cho phút và giây)
    Hướng giải thuật:
    - Nếu giây >= 60, cộng thương của (giây / 60) vào phút, giữ lại phần dư cho giây
    - Nếu giây < 0, dùng vòng lặp cộng thêm 60 vào giây và giảm phút xuống cho đến khi giây không âm
    - Áp dụng logic tương tự để chuẩn hóa số phút sang số giờ
    - Xử lý số giờ bằng công thức đồng hồ vòng tròn: (gio % 24 + 24) % 24 để đảm bảo giờ luôn nằm trong khoảng [0, 23]
*/
void CTime::ChuanHoa() {
    if (giay >= 60) {
        phut += giay / 60;
        giay %= 60;
    }
    while (giay < 0) {
        giay += 60;
        phut--;
    }
    if (phut >= 60) {
        gio += phut / 60;
        phut %= 60;
    }
    while (phut < 0) {
        phut += 60;
        gio--;
    }
    gio = (gio % 24 + 24) % 24; 
}

/*
    Hàm khởi tạo có tham số (Constructor)
    Input: Ba số nguyên h (giờ), p (phút), s (giây) có giá trị mặc định bằng 0
    Output: Một đối tượng CTime được thiết lập giá trị thời gian ban đầu
    Hướng giải thuật:
    - Sử dụng danh sách khởi tạo (Initializer list) để gán trực tiếp h cho gio, p cho phut, s cho giay
*/
CTime::CTime(int h = 0, int p = 0, int s = 0) : gio(h), phut(p), giay(s) {};

/*
    Hàm khởi tạo mặc định (Constructor không tham số)
    Input: Không có
    Output: Một đối tượng CTime có giá trị mặc định là 00:00:00
    Hướng giải thuật:
    - Gán trực tiếp ba thuộc tính gio, phut, giay bằng 0
*/
CTime::CTime() : gio(0), phut(0), giay(0) {};

/*
    Hàm lấy giờ hệ thống máy tính
    Input: Không có
    Output: Cập nhật thời gian thực tại của hệ thống vào thuộc tính gio, phut, giay
    Hướng giải thuật:
    - Khai báo cấu trúc SYSTEMTIME của thư viện Windows.h
    - Gọi hàm GetLocalTime(&st) để đọc thời gian hiện tại từ hệ thống máy tính
    - Trích xuất dữ liệu giờ, phút, giây từ cấu trúc st và gán vào thuộc tính tương ứng của lớp
*/
void CTime::LayGioHeThong()
{
    SYSTEMTIME st;
    GetLocalTime(&st);
    gio = st.wHour;
    phut = st.wMinute;
    giay = st.wSecond;
}

/*
    Toán tử cộng thêm một số giây vào thời gian
    Input: Một số nguyên s đại diện cho số giây cần cộng thêm
    Output: Một đối tượng CTime mới lưu mốc thời gian sau khi cộng
    Hướng giải thuật:
    - Sao chép đối tượng hiện tại sang đối tượng tạm `kq`
    - Cộng trực tiếp số giây `s` vào thuộc tính giay của `kq`
    - Gọi hàm ChuanHoa() cho `kq` để xử lý tràn giây, phút, giờ và trả về `kq`
*/
CTime CTime::operator+(int s)
{
    CTime kq = *this;
    kq.giay += s;
    kq.ChuanHoa();
    return kq;
}

/*
    Toán tử trừ đi một số giây từ thời gian
    Input: Một số nguyên s đại diện cho số giây cần trừ đi
    Output: Một đối tượng CTime mới lưu mốc thời gian sau khi trừ
    Hướng giải thuật:
    - Sao chép đối tượng hiện tại sang đối tượng tạm `kq`
    - Trừ trực tiếp số giây `s` khỏi thuộc tính giay của `kq`
    - Gọi hàm ChuanHoa() cho `kq` để hiệu chỉnh lại thời gian hợp lệ và trả về `kq`
*/
CTime CTime::operator-(int s)
{
    CTime kq = *this;
    kq.giay -= s;
    kq.ChuanHoa();
    return kq;
}

/*
    Toán tử tăng 1 giây - Tiền tố (++CTime)
    Input: Không có
    Output: Trả về tham chiếu đến chính đối tượng CTime hiện tại sau khi đã tăng giá trị
    Hướng giải thuật:
    - Tăng thuộc tính giay của đối tượng hiện tại lên 1 đơn vị
    - Gọi hàm ChuanHoa() để xử lý tràn thời gian nếu có
    - Trả về con trỏ dereference (*this)
*/
CTime& CTime::operator++()
{
    giay++;
    ChuanHoa();
    return *this;
}

/*
    Toán tử tăng 1 giây - Hậu tố (CTime++)
    Input: Một tham số nguyên dummy (int) không dùng tới để phân biệt với tiền tố
    Output: Trả về một đối tượng CTime chứa giá trị thời gian cũ trước khi tăng
    Hướng giải thuật:
    - Tạo đối tượng tạm `temp` sao chép lại giá trị hiện tại của đối tượng
    - Tăng thuộc tính giay của đối tượng gốc lên 1 đơn vị và thực hiện ChuanHoa()
    - Trả về đối tượng `temp` (giá trị cũ)
*/
CTime CTime::operator++(int)
{
    CTime temp = *this;
    giay++;
    ChuanHoa();
    return temp;
}

/*
    Toán tử giảm 1 giây - Tiền tố (--CTime)
    Input: Không có
    Output: Trả về tham chiếu đến chính đối tượng CTime hiện tại sau khi đã giảm giá trị
    Hướng giải thuật:
    - Giảm thuộc tính giay của đối tượng hiện tại đi 1 đơn vị
    - Gọi hàm ChuanHoa() để hiệu chỉnh lại các mốc thời gian âm nếu có
    - Trả về con trỏ dereference (*this)
*/
CTime& CTime::operator--()
{
    giay--;
    ChuanHoa();
    return *this;
}

/*
    Toán tử giảm 1 giây - Hậu tố (CTime--)
    Input: Một tham số nguyên dummy (int) để phân biệt với tiền tố
    Output: Trả về một đối tượng CTime chứa giá trị thời gian cũ trước khi giảm
    Hướng giải thuật:
    - Tạo đối tượng tạm `temp` sao chép lại giá trị hiện tại của đối tượng
    - Giảm thuộc tính giay của đối tượng gốc đi 1 đơn vị và thực hiện ChuanHoa()
    - Trả về đối tượng `temp` (giá trị cũ)
*/
CTime CTime::operator--(int)
{
    CTime temp = *this;
    giay--;
    ChuanHoa();
    return temp;
}

/*
    Toán tử nhập dữ liệu (>>) cho đối tượng CTime
    Input: Đối tượng dòng nhập is và đối tượng t của lớp CTime cần lưu dữ liệu
    Output: Trả về dòng nhập is để cho phép nhập liên tiếp nhiều đối tượng
    Hướng giải thuật:
    - Nhập lần lượt các giá trị giờ, phút, giây từ bàn phím thông qua luồng nhập is
    - Gọi hàm ChuanHoa() để đảm bảo thời gian vừa nhập vào là hợp lý
*/
istream& operator>>(istream& is, CTime& t)
{
    cout << "Nhap gio: "; is >> t.gio;
    cout << "Nhap phut: "; is >> t.phut;
    cout << "Nhap giay: "; is >> t.giay;
    t.ChuanHoa();
    return is;
}

/*
    Toán tử xuất dữ liệu (<<) cho đối tượng CTime
    Input: Đối tượng dòng xuất os và đối tượng t của lớp CTime cần in dữ liệu
    Output: Trả về dòng xuất os để cho phép xuất liên tiếp nhiều đối tượng
    Hướng giải thuật:
    - Định dạng xuất thời gian ra màn hình theo cấu trúc "gio:phut:giay" thông qua luồng os
*/
ostream& operator<<(ostream& os, const CTime& t)
{
    os << t.gio << ":" << t.phut << ":" << t.giay;
    return os;
}