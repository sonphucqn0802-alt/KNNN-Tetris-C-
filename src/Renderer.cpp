/*
 * Thanh Phong Cap nhat ham ve board, khoi hien tai, diem so va huong dan tren console.
 */
#include "Renderer.h"

#include <iostream>
#include <sstream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace {
std::string tileForValue(int value) {
    static constexpr const char* kColors[] = {
        "",
        "\x1B[106m",
        "\x1B[103m",
        "\x1B[105m",
        "\x1B[102m",
        "\x1B[101m",
        "\x1B[104m",
        "\x1B[43m"
    };

    if (value > 0 && value < static_cast<int>(sizeof(kColors) / sizeof(kColors[0]))) {
        return std::string(kColors[value]) + "  " + "\x1B[0m";
    }

    return "[]";
}

std::string ghostTile() {
    return "\x1B[90m::\x1B[0m";
}

bool containsCell(const Tetromino& piece, int x, int y) {
    for (const auto& cell : piece.cells()) {
        if (cell.x == x && cell.y == y) {
            return true;
        }
    }
    return false;
}

std::string typeName(TetrominoType type) {
    switch (type) {
    case TetrominoType::I:
        return "I";
    case TetrominoType::O:
        return "O";
    case TetrominoType::T:
        return "T";
    case TetrominoType::S:
        return "S";
    case TetrominoType::Z:
        return "Z";
    case TetrominoType::J:
        return "J";
    case TetrominoType::L:
        return "L";
    }
    return "?";
}
}

Renderer::Renderer()
    : firstDraw_(true) {
#ifdef _WIN32
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    if (output != INVALID_HANDLE_VALUE) {
        DWORD mode = 0;
        if (GetConsoleMode(output, &mode)) {
            SetConsoleMode(output, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }

        CONSOLE_CURSOR_INFO cursorInfo{};
        if (GetConsoleCursorInfo(output, &cursorInfo)) {
            cursorInfo.bVisible = FALSE;
            SetConsoleCursorInfo(output, &cursorInfo);
        }
    }
#endif
    std::cout << "\x1B[?25l";
}

Renderer::~Renderer() {
#ifdef _WIN32
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    if (output != INVALID_HANDLE_VALUE) {
        CONSOLE_CURSOR_INFO cursorInfo{};
        if (GetConsoleCursorInfo(output, &cursorInfo)) {
            cursorInfo.bVisible = TRUE;
            SetConsoleCursorInfo(output, &cursorInfo);
        }
    }
#endif
    std::cout << "\x1B[?25h" << std::flush;
}

void Renderer::draw(const Board& board,
                    const Tetromino& current,
                    const Tetromino& ghost,
                    const Tetromino& next,
                    const ScoreManager& score,
                    int highScore,
                    bool paused,
                    bool gameOver) const {
    clearScreen();

    std::cout << "TETRIS C++\x1B[K\n\x1B[K\n";
    std::cout << '+' << std::string(Board::Width * 2, '-') << "+\x1B[K\n";
    for (int y = 0; y < Board::Height; ++y) {
        std::cout << '|';
        for (int x = 0; x < Board::Width; ++x) {
            std::string display = "  ";
            const int cell = board.getCell(x, y);
            if (cell != 0) {
                display = tileForValue(cell);
            } else if (containsCell(current, x, y)) {
                display = tileForValue(current.getColorId());
            } else if (containsCell(ghost, x, y)) {
                display = ghostTile();
            }

            std::cout << display;
        }
        std::cout << '|';

        if (y == 1) {
            std::cout << "  Score: " << score.getScore();
        } else if (y == 2) {
            std::cout << "  High:  " << highScore;
        } else if (y == 3) {
            std::cout << "  Level: " << score.getDisplayLevel();
        } else if (y == 4) {
            std::cout << "  Lines: " << score.getLinesCleared();
        } else if (y == 6) {
            std::cout << "  Next: " << typeName(next.getType());
        } else if (y == 8) {
            std::cout << "  A/D or Arrows: move";
        } else if (y == 9) {
            std::cout << "  W/Up/X: rotate";
        } else if (y == 10) {
            std::cout << "  Z: rotate back";
        } else if (y == 11) {
            std::cout << "  S/Down: soft drop";
        } else if (y == 12) {
            std::cout << "  Space: hard drop";
        } else if (y == 13) {
            std::cout << "  P: pause  R: restart";
        } else if (y == 14) {
            std::cout << "  Q/Esc: quit";
        }

        std::cout << "\x1B[K\n";
    }
    std::cout << '+' << std::string(Board::Width * 2, '-') << "+\x1B[K\n";

    std::cout << "\x1B[K\n";
    std::cout << (paused ? "Paused" : "") << "\x1B[K\n";
    std::cout << (gameOver ? "Game over. Press R to restart or Q to quit." : "") << "\x1B[K\n";

    std::cout.flush();
    firstDraw_ = false;
}

void Renderer::clearScreen() const {
    if (firstDraw_) {
        std::cout << "\x1B[2J\x1B[H";
    } else {
        std::cout << "\x1B[H";
    }
}
