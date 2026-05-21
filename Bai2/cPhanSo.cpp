#include <iostream>
#include <algorithm>
#include "cPhanSo.h"
using namespace std;

/*
    Hàm khởi tạo mặc định (Constructor không tham số)
    Input: Không có
    Output: Một đối tượng cPhanSo có giá trị mặc định là 0/1
    Hướng giải thuật:
    - Gán trực tiếp tử số bằng 0 và mẫu số bằng 1
*/
cPhanSo::cPhanSo() : tu(0) , mau(1) {};

/*
    Hàm khởi tạo có tham số (Hỗ trợ chuyển đổi số nguyên sang phân số)
    Input: Hai số nguyên t (tử số, mặc định = 0) và m (mẫu số, mặc định = 1)
    Output: Một đối tượng cPhanSo hoàn chỉnh đã được tối giản
    Hướng giải thuật:
    - Gán tử số bằng t, mẫu số bằng m
    - Gọi hàm RutGon() để tối giản phân số ngay khi khởi tạo
*/
cPhanSo::cPhanSo(int t = 0, int m = 1) : tu(t) , mau(m) {RutGon();};

/*
    Hàm rút gọn phân số
    Input: Không có tham số truyền vào (sử dụng thuộc tính tu và mau của đối tượng hiện tại)
    Output: Phân số được tối giản và đưa dấu trừ lên tử số nếu có
    Hướng giải thuật:
    - Tìm ước chung lớn nhất (UCLN) của tử và mẫu bằng hàm __gcd
    - Chia cả tử và mẫu cho UCLN đó
    - Nếu mẫu số âm, đổi dấu cả tử và mẫu để đảm bảo mẫu luôn dương
*/
void cPhanSo::RutGon()
{
    int ucln = __gcd(tu,mau);
    tu /= ucln;
    mau /= ucln;
    if (mau < 0)
    {
        tu = -tu;
        mau = -mau;
    }
}

/*
    Toán tử nhập dữ liệu (>>) cho phân số
    Input: Đối tượng dòng nhập is và phân số ps để lưu dữ liệu
    Output: Trả về dòng nhập is để cho phép nhập liên tiếp
    Hướng giải thuật:
    - Sử dụng vòng lặp do-while để yêu cầu nhập tử số và mẫu số từ bàn phím
    - Nếu người dùng nhập mẫu số bằng 0, thông báo lỗi và bắt buộc nhập lại
    - Sau khi nhập hợp lệ, gọi hàm RutGon() để tối giản phân số trước khi trả về
*/
istream& operator>>(istream& is, cPhanSo& ps)
{
    do
    {
        cout << "Nhap tu: "; is >> ps.tu;
        cout << "Nhap mau: "; is >> ps.mau;
        if (ps.mau == 0) cout << "Phan so khong hop le! Vui long nhap lai!\n";
    } 
    while(ps.mau == 0);
    ps.RutGon();
    return is;
}

/*
    Toán tử xuất dữ liệu (<<) cho phân số
    Input: Đối tượng dòng xuất os và phân số ps cần xuất
    Output: Trả về dòng xuất os để cho phép xuất liên tiếp
    Hướng giải thuật:
    - Kiểm tra các trường hợp đặc biệt để hiển thị đẹp mắt:
      + Nếu mẫu số bằng 1: Chỉ xuất tử số (hiển thị như số nguyên)
      + Nếu tử số bằng 0: Chỉ xuất số 0
      + Các trường hợp còn lại: Xuất theo định dạng "tu/mau"
*/
ostream& operator<<(ostream& os, const cPhanSo& ps)
{
    if (ps.mau == 1) os << ps.tu;
    else if (ps.tu == 0) os << 0;
    else os << ps.tu << "/" << ps.mau;
    return os;
}

/*
    Phép toán cộng hai phân số
    Input: Hai phân số a và b
    Output: Một phân số mới là tổng của a và b
    Hướng giải thuật:
    - Quy đồng mẫu số và cộng các tử: tử mới = a.tu * b.mau + a.mau * b.tu
    - Mẫu số mới = a.mau * b.mau
    - Trả về đối tượng cPhanSo mới (hàm khởi tạo của class sẽ tự động rút gọn)
*/
cPhanSo operator+(const cPhanSo& a, const cPhanSo& b)
{
    return cPhanSo(a.tu * b.mau + a.mau * b.tu, a.mau*b.mau);
}

/*
    Phép toán trừ hai phân số
    Input: Hai phân số a và b
    Output: Một phân số mới là hiệu của a và b
    Hướng giải thuật:
    - Quy đồng mẫu số và trừ các tử: tử mới = a.tu * b.mau - b.tu * a.mau
    - Mẫu số mới = a.mau * b.mau
    - Trả về đối tượng cPhanSo mới
*/
cPhanSo operator-(const cPhanSo& a, const cPhanSo& b)
{
    return cPhanSo(a.tu * b.mau - b.tu * a.mau, a.mau * b.mau);
}

/*
    Phép toán nhân hai phân số
    Input: Hai phân số a và b
    Output: Một phân số mới là tích của a và b
    Hướng giải thuật:
    - Nhân tử với tử: tử mới = a.tu * b.tu
    - Nhân mẫu với mẫu: mẫu mới = a.mau * b.mau
    - Trả về đối tượng cPhanSo mới
*/
cPhanSo operator*(const cPhanSo& a, const cPhanSo& b)
{
    return cPhanSo(a.tu * b.tu, a.mau * b.mau);
}

/*
    Phép toán chia hai phân số
    Input: Hai phân số a (số bị chia) và b (số chia)
    Output: Một phân số mới là thương của a và b
    Hướng giải thuật:
    - Kiểm tra nếu tử số của phân số b bằng 0 (chia cho 0), thông báo lỗi và trả về phân số 0/1
    - Nếu hợp lệ, nhân phân số a với phân số đảo ngược của b:
      + Tử mới = a.tu * b.mau
      + Mẫu mới = a.mau * b.tu
    - Trả về đối tượng cPhanSo mới
*/
cPhanSo operator/(const cPhanSo& a, const cPhanSo& b)
{
    if (b.tu == 0)
    {
        cout << "Loi: Khong the chia cho 0!\n";
        return cPhanSo(0,1);
    }
    return cPhanSo(a.tu * b.mau, a.mau * b.tu);
}

/*
    Toán tử so sánh bằng giữa hai phân số
    Input: Hai phân số a và b
    Output: Giá trị kiểu bool (true nếu bằng nhau, false nếu khác nhau)
    Hướng giải thuật:
    - Vì phân số luôn được tự động rút gọn khi khởi tạo, chỉ cần kiểm tra:
      Nếu (a.tu == b.tu) và (a.mau == b.mau) thì hai phân số bằng nhau, trả về true
    - Ngược lại trả về false
*/
bool operator==(const cPhanSo& a, const cPhanSo& b)
{
    if (a.tu == b.tu && a.mau == b.mau) return true;
    return false;
}

/*
    Toán tử so sánh lớn hơn giữa hai phân số
    Input: Hai phân số a và b
    Output: Giá trị kiểu bool (true nếu a > b, ngược lại là false)
    Hướng giải thuật:
    - Thực hiện nhân chéo để so sánh (tránh việc chia ra số thực bị sai số):
      Nếu (a.tu * b.mau) > (b.tu * a.mau) thì phân số a lớn hơn b, trả về true
    - Ngược lại trả về false
*/
bool operator>(const cPhanSo& a, const cPhanSo& b)
{
    if (a.tu * b.mau > b.tu * a.mau) return true;
    return false;
}

/*
    Toán tử so sánh nhỏ hơn giữa hai phân số
    Input: Hai phân số a và b
    Output: Giá trị kiểu bool (true nếu a < b, ngược lại là false)
    Hướng giải thuật:
    - Thực hiện nhân chéo tương tự phép toán lớn hơn:
      Nếu (a.tu * b.mau) < (b.tu * a.mau) thì phân số a nhỏ hơn b, trả về true
    - Ngược lại trả về false
*/
bool operator<(const cPhanSo& a, const cPhanSo& b)
{
    if (a.tu * b.mau < b.tu * a.mau) return true;
    return false;
}