/*
 * Cai dat hinh dang, mau, vi tri va phep xoay cua cac khoi Tetromino.
 */
#include "Tetromino.h"

namespace {
constexpr int BlockSize = 4;

char blocks[][BlockSize][BlockSize] = {
    {{' ', 'I', ' ', ' '},
     {' ', 'I', ' ', ' '},
     {' ', 'I', ' ', ' '},
     {' ', 'I', ' ', ' '}},

    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},

    {{' ', ' ', ' ', ' '},
     {' ', 'T', ' ', ' '},
     {'T', 'T', 'T', ' '},
     {' ', ' ', ' ', ' '}},

    {{' ', ' ', ' ', ' '},
     {' ', 'S', 'S', ' '},
     {'S', 'S', ' ', ' '},
     {' ', ' ', ' ', ' '}},

    {{' ', ' ', ' ', ' '},
     {'Z', 'Z', ' ', ' '},
     {' ', 'Z', 'Z', ' '},
     {' ', ' ', ' ', ' '}},

    {{' ', ' ', ' ', ' '},
     {'J', ' ', ' ', ' '},
     {'J', 'J', 'J', ' '},
     {' ', ' ', ' ', ' '}},

    {{' ', ' ', ' ', ' '},
     {' ', ' ', 'L', ' '},
     {'L', 'L', 'L', ' '},
     {' ', ' ', ' ', ' '}}
};

Cell rotateCellInBlock(int x, int y, int rotation) {
    for (int i = 0; i < rotation; ++i) {
        const int oldX = x;
        x = BlockSize - 1 - y;
        y = oldX;
    }

    return Cell{x, y};
}
}

Tetromino::Tetromino(TetrominoType type)
    : type_(type),
      x_(0),
      y_(0),
      rotation_(0) {
    updateCells();
}

TetrominoType Tetromino::getType() const {
    return type_;
}

int Tetromino::getColorId() const {
    return static_cast<int>(type_) + 1;
}

const std::vector<Cell>& Tetromino::cells() const {
    return cells_;
}

void Tetromino::setPosition(int x, int y) {
    x_ = x;
    y_ = y;
    updateCells();
}

void Tetromino::move(int dx, int dy) {
    x_ += dx;
    y_ += dy;
    updateCells();
}

void Tetromino::rotateClockwise() {
    if (type_ == TetrominoType::O) {
        return;
    }
    rotation_ = (rotation_ + 1) % 4;
    updateCells();
}

void Tetromino::rotateCounterClockwise() {
    if (type_ == TetrominoType::O) {
        return;
    }
    rotation_ = (rotation_ + 3) % 4;
    updateCells();
}

void Tetromino::updateCells() {
    cells_.clear();
    const int blockIndex = static_cast<int>(type_);

    for (int row = 0; row < BlockSize; ++row) {
        for (int column = 0; column < BlockSize; ++column) {
            if (blocks[blockIndex][row][column] == ' ') {
                continue;
            }

            Cell rotated = rotateCellInBlock(column, row, rotation_);
            cells_.push_back(Cell{x_ + rotated.x, y_ + rotated.y});
        }
    }
}
