
// Hệ thống thư viện chuẩn: iostream (nhập xuất), windows.h (can thiệp màn hình console)
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <exception>

#include "GameLoop.h"

void gotoxy(int cx, int cy) {
    COORD c = { (SHORT)(cx * 2), (SHORT)cy };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main() {
    // Khởi chạy luồng game chính, quản lý thời gian thực (FPS) và điều khiển vòng lặp tương tác người chơi
    try {
        GameLoop game;
        game.run();
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Fatal error: " << error.what() << '\n';
        return 1;
    }
}

