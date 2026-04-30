#include "Renderer.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

namespace {
constexpr int kFrameWidth = 64;

char blockForValue(int value) {
    static constexpr char kBlocks[] = " IOTSZJL";
    if (value >= 0 && value < static_cast<int>(sizeof(kBlocks) - 1)) {
        return kBlocks[value];
    }
    return '#';
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

void appendLine(std::ostringstream& frame, std::string line) {
    if (line.size() < kFrameWidth) {
        line.resize(kFrameWidth, ' ');
    }
    frame << line << '\n';
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
    std::ostringstream frame;

    appendLine(frame, "TETRIS C++");
    appendLine(frame, "");

    for (int y = 0; y < Board::Height; ++y) {
        std::ostringstream line;
        line << '|';
        for (int x = 0; x < Board::Width; ++x) {
            char display = ' ';
            const int cell = board.getCell(x, y);
            if (cell != 0) {
                display = blockForValue(cell);
            } else if (containsCell(current, x, y)) {
                display = blockForValue(current.getColorId());
            } else if (containsCell(ghost, x, y)) {
                display = '.';
            }

            line << display << display;
        }
        line << '|';

        if (y == 1) {
            line << "  Score: " << score.getScore();
        } else if (y == 2) {
            line << "  High:  " << highScore;
        } else if (y == 3) {
            line << "  Level: " << score.getDisplayLevel();
        } else if (y == 4) {
            line << "  Lines: " << score.getLinesCleared();
        } else if (y == 6) {
            line << "  Next: " << typeName(next.getType());
        } else if (y == 8) {
            line << "  A/D or Arrows: move";
        } else if (y == 9) {
            line << "  W/Up/X: rotate";
        } else if (y == 10) {
            line << "  Z: rotate back";
        } else if (y == 11) {
            line << "  S/Down: soft drop";
        } else if (y == 12) {
            line << "  Space: hard drop";
        } else if (y == 13) {
            line << "  P: pause  R: restart";
        } else if (y == 14) {
            line << "  Q/Esc: quit";
        }

        appendLine(frame, line.str());
    }
    appendLine(frame, "+" + std::string(Board::Width * 2, '-') + "+");
    appendLine(frame, "");
    appendLine(frame, paused ? "Paused" : "");
    appendLine(frame, gameOver ? "Game over. Press R to restart or Q to quit." : "");

    if (firstDraw_) {
        clearScreen();
        firstDraw_ = false;
    } else {
        std::cout << "\x1B[H";
    }

    std::cout << frame.str() << "\x1B[J" << std::flush;
}

void Renderer::clearScreen() const {
    std::cout << "\x1B[2J\x1B[H";
}
