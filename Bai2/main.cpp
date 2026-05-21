#include <iostream>
#include "cPhanSo.h"
using namespace std;

int main()
{
    cPhanSo ps1, ps2;
    cout << "Nhap phan so 1: "; cin >> ps1;
    cout << "Nhap phan so 2: "; cin >> ps2;
    cout << "Phan so 1 vua nhap: " << ps1 << "\n";
    cout << "Phan so 2 vua nhap: " << ps2 << "\n";

    cout << ps1 << " + " << ps2 << " = " << ps1 + ps2 << "\n";
    cout << ps1 << " - " << ps2 << " = " << ps1 - ps2 << "\n";
    cout << ps1 << " * " << ps2 << " = " << ps1 * ps2 << "\n";
    cout << ps1 << " / " << ps2 << " = " << ps1 / ps2 << "\n";
    
    if (ps1 > ps2)
        cout << ps1 << " > " << ps2 << "\n";
    else if (ps1 < ps2)
        cout << ps1 << " < " << ps2 << "\n";
    else   
        cout << ps1 << " = " << ps2 << "\n";
}