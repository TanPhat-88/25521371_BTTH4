#include "SoPhuc.h"
#include <cmath>

/*
    Hàm khởi tạo (Constructor) số phức
    Input: Hai số thực r (phần thực), i (phần ảo) có giá trị mặc định bằng 0
    Output: Một đối tượng SoPhuc được thiết lập giá trị tương ứng
    Hướng giải thuật:
    - Gán tham số r cho thuộc tính thuc
    - Gán tham số i cho thuộc tính ao
    - Nếu chỉ truyền 1 tham số x, i tự động bằng 0 (quan điểm số thực là số phức đặc biệt)
*/
SoPhuc::SoPhuc(double r, double i) : thuc(r), ao(i) {}

/*
    Phép toán cộng hai số phức
    Input: Hai đối tượng SoPhuc sp1 và sp2
    Output: Một đối tượng SoPhuc là tổng của hai số phức
    Hướng giải thuật:
    - Tạo một số phức mới có phần thực = thuc(sp1) + thuc(sp2)
    - Phần ảo = ao(sp1) + ao(sp2)
*/
SoPhuc operator+(const SoPhuc& sp1, const SoPhuc& sp2) {
    return SoPhuc(sp1.thuc + sp2.thuc, sp1.ao + sp2.ao);
}

/*
    Phép toán trừ hai số phức
    Input: Hai đối tượng SoPhuc sp1 và sp2
    Output: Một đối tượng SoPhuc là hiệu của hai số phức
    Hướng giải thuật:
    - Tạo một số phức mới có phần thực = thuc(sp1) - thuc(sp2)
    - Phần ảo = ao(sp1) - ao(sp2)
*/
SoPhuc operator-(const SoPhuc& sp1, const SoPhuc& sp2) {
    return SoPhuc(sp1.thuc - sp2.thuc, sp1.ao - sp2.ao);
}

/*
    Phép toán nhân hai số phức
    Input: Hai đối tượng SoPhuc sp1 và sp2
    Output: Một đối tượng SoPhuc là tích của hai số phức
    Hướng giải thuật:
    - Áp dụng công thức nhân hai số phức: (a + bi)(c + di) = (ac - bd) + (ad + bc)i
    - Phần thực mới = sp1.thuc * sp2.thuc - sp1.ao * sp2.ao
    - Phần ảo mới = sp1.thuc * sp2.ao + sp1.ao * sp2.thuc
*/
SoPhuc operator*(const SoPhuc& sp1, const SoPhuc& sp2) {
    return SoPhuc(sp1.thuc * sp2.thuc - sp1.ao * sp2.ao, sp1.thuc * sp2.ao + sp1.ao * sp2.thuc);
}

/*
    Phép toán chia hai số phức
    Input: Hai đối tượng SoPhuc sp1 (tử số) và sp2 (mẫu số)
    Output: Một đối tượng SoPhuc là thương của hai số phức
    Hướng giải thuật:
    - Nhân cả tử và mẫu với số phức liên hợp của mẫu: (c - di)
    - Mẫu số mới (mẫu số chung) = c^2 + d^2
    - Phần thực mới = (a*c + b*d) / mẫu số chung
    - Phần ảo mới = (b*c - a*d) / mẫu số chung
*/
SoPhuc operator/(const SoPhuc& sp1, const SoPhuc& sp2) {
    double mauSoChung = sp2.thuc * sp2.thuc + sp2.ao * sp2.ao;
    if (mauSoChung == 0) {
        return SoPhuc(0, 0); 
    }
    double thucMoi = (sp1.thuc * sp2.thuc + sp1.ao * sp2.ao) / mauSoChung;
    double aoMoi = (sp1.ao * sp2.thuc - sp1.thuc * sp2.ao) / mauSoChung;
    return SoPhuc(thucMoi, aoMoi);
}

/*
    Phép so sánh bằng giữa hai số phức
    Input: Hai đối tượng SoPhuc sp1 và sp2
    Output: Giá trị kiểu bool (true nếu bằng nhau, false nếu khác nhau)
    Hướng giải thuật:
    - Kiểm tra xem phần thực của sp1 có bằng phần thực của sp2 hay không
    - Kiểm tra xem phần ảo của sp1 có bằng phần ảo của sp2 hay không
    - Trả về true nếu cả hai điều kiện trên đều đúng
*/
bool operator==(const SoPhuc& sp1, const SoPhuc& sp2) {
    return (sp1.thuc == sp2.thuc && sp1.ao == sp2.ao);
}

/*
    Phép so sánh khác giữa hai số phức
    Input: Hai đối tượng SoPhuc sp1 và sp2
    Output: Giá trị kiểu bool (true nếu khác nhau, false nếu bằng nhau)
    Hướng giải thuật:
    - Sử dụng phủ định của toán tử so sánh bằng (==) đã định nghĩa ở trên
*/
bool operator!=(const SoPhuc& sp1, const SoPhuc& sp2) {
    return !(sp1 == sp2);
}

/*
    Toán tử xuất dữ liệu (<<) cho số phức
    Input: Đối tượng dòng xuất os và số phức sp cần xuất
    Output: Trả về chính dòng xuất os để cho phép xuất liên tiếp (chaining)
    Hướng giải thuật:
    - Định dạng hiển thị đẹp mắt theo các trường hợp:
      + Nếu phần ảo >= 0: Xuất dạng "thuc + aoi"
      + Nếu phần ảo < 0: Xuất dạng "thuc - |ao|i"
*/
std::ostream& operator<<(std::ostream& os, const SoPhuc& sp) {
    if (sp.ao >= 0) {
        os << sp.thuc << " + " << sp.ao << "i";
    } else {
        os << sp.thuc << " - " << std::abs(sp.ao) << "i";
    }
    return os;
}

/*
    Toán tử nhập dữ liệu (>>) cho số phức
    Input: Đối tượng dòng nhập is và số phức sp để lưu dữ liệu nhập vào
    Output: Trả về chính dòng nhập is để cho phép nhập liên tiếp
    Hướng giải thuật:
    - Hướng dẫn người dùng nhập lần lượt phần thực và phần ảo qua bàn phím
    - Gán trực tiếp vào các thuộc tính thuc và ao của đối tượng sp
*/
std::istream& operator>>(std::istream& is, SoPhuc& sp) {
    std::cout << "Nhap phan thuc: ";
    is >> sp.thuc;
    std::cout << "Nhap phan ao: ";
    is >> sp.ao;
    return is;
}