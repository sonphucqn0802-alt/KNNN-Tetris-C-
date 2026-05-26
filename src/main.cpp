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
