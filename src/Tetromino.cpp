
#include "Tetromino.h"

#include <array>

namespace {
using Shape = std::array<Cell, 4>;

Shape baseShape(TetrominoType type) {
    switch (type) {
    case TetrominoType::I:
        return {{{-1, 0}, {0, 0}, {1, 0}, {2, 0}}};
    case TetrominoType::O:
        return {{{0, 0}, {1, 0}, {0, 1}, {1, 1}}};
    case TetrominoType::T:
        return {{{-1, 0}, {0, 0}, {1, 0}, {0, 1}}};
    case TetrominoType::S:
        return {{{0, 0}, {1, 0}, {-1, 1}, {0, 1}}};
    case TetrominoType::Z:
        return {{{-1, 0}, {0, 0}, {0, 1}, {1, 1}}};
    case TetrominoType::J:
        return {{{-1, 0}, {0, 0}, {1, 0}, {-1, 1}}};
    case TetrominoType::L:
        return {{{-1, 0}, {0, 0}, {1, 0}, {1, 1}}};
    }
    return {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}};
}

Cell rotateCell(Cell cell, int rotation) {
    for (int i = 0; i < rotation; ++i) {
        cell = Cell{-cell.y, cell.x};
    }
    return cell;
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
    for (Cell cell : baseShape(type_)) {
        Cell rotated = rotateCell(cell, rotation_);
        cells_.push_back(Cell{x_ + rotated.x, y_ + rotated.y});
    }
}
