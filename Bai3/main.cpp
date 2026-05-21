#include <iostream>
#include <windows.h>
#include "CTime.h"
using namespace std;

int main()
{
    CTime time;
    cin >> time;
    
    cout << "Thoi gian sau khi cong 5s: " << time + 5 << "\n";
    cout << "Thoi gian sau khi tru 5s: " <<time - 5 << "\n";
    cout << "Thoi gian sau khi ++time: " <<++time << "\n";
    cout << "Thoi gian sau khi time++: " <<time++ << "\n";
    cout << "Thoi gian sau khi --time: " <<--time << "\n";
    cout << "Thoi gian sau khi time--: " <<time-- << "\n";

    CTime dongho;
    dongho.LayGioHeThong();
    int choice;
    cout << "Chon so 1 de in dong ho he thong: ";
    cin >> choice;
    if (choice == 1)
    {
        while (true)
        {
            system("cls");
            cout << "[" << dongho << "]";
            dongho++;
            Sleep(1000);
        };
    }
    else
        cout << "Lua chon khac so 1, chuong trinh tu dong hoan thanh!\n";
}