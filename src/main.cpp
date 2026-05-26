
// Hệ thống thư viện chuẩn: iostream (nhập xuất), windows.h (can thiệp màn hình console)git add .
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;
void gotoxy(int cx, int cy) {
    COORD c = { (SHORT)(cx * 2), (SHORT)cy };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

/*
 * Diem vao chuong trinh, khoi tao game va xu ly loi ngoai le.
 */
#include "GameLoop.h"

#include <exception>
#include <iostream>

int main() {
    try {
        GameLoop game;
        game.run();
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Fatal error: " << error.what() << '\n';
        return 1;
    }
}

