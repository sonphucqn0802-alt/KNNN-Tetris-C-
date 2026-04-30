#include "Tetromino.h"

#include <array>

namespace {
using Shape = std::array<std::array<Point, 4>, 4>;

constexpr std::array<Shape, 7> kShapes{{
    // I
    Shape{{
        {{{0, 1}, {1, 1}, {2, 1}, {3, 1}}},
        {{{2, 0}, {2, 1}, {2, 2}, {2, 3}}},
        {{{0, 2}, {1, 2}, {2, 2}, {3, 2}}},
        {{{1, 0}, {1, 1}, {1, 2}, {1, 3}}},
    }},
    // O
    Shape{{
        {{{1, 0}, {2, 0}, {1, 1}, {2, 1}}},
        {{{1, 0}, {2, 0}, {1, 1}, {2, 1}}},
        {{{1, 0}, {2, 0}, {1, 1}, {2, 1}}},
        {{{1, 0}, {2, 0}, {1, 1}, {2, 1}}},
    }},
    // T
    Shape{{
        {{{1, 0}, {0, 1}, {1, 1}, {2, 1}}},
        {{{1, 0}, {1, 1}, {2, 1}, {1, 2}}},
        {{{0, 1}, {1, 1}, {2, 1}, {1, 2}}},
        {{{1, 0}, {0, 1}, {1, 1}, {1, 2}}},
    }},
    // S
    Shape{{
        {{{1, 0}, {2, 0}, {0, 1}, {1, 1}}},
        {{{1, 0}, {1, 1}, {2, 1}, {2, 2}}},
        {{{1, 1}, {2, 1}, {0, 2}, {1, 2}}},
        {{{0, 0}, {0, 1}, {1, 1}, {1, 2}}},
    }},
    // Z
    Shape{{
        {{{0, 0}, {1, 0}, {1, 1}, {2, 1}}},
        {{{2, 0}, {1, 1}, {2, 1}, {1, 2}}},
        {{{0, 1}, {1, 1}, {1, 2}, {2, 2}}},
        {{{1, 0}, {0, 1}, {1, 1}, {0, 2}}},
    }},
    // J
    Shape{{
        {{{0, 0}, {0, 1}, {1, 1}, {2, 1}}},
        {{{1, 0}, {2, 0}, {1, 1}, {1, 2}}},
        {{{0, 1}, {1, 1}, {2, 1}, {2, 2}}},
        {{{1, 0}, {1, 1}, {0, 2}, {1, 2}}},
    }},
    // L
    Shape{{
        {{{2, 0}, {0, 1}, {1, 1}, {2, 1}}},
        {{{1, 0}, {1, 1}, {1, 2}, {2, 2}}},
        {{{0, 1}, {1, 1}, {2, 1}, {0, 2}}},
        {{{0, 0}, {1, 0}, {1, 1}, {1, 2}}},
    }},
}};

int typeIndex(TetrominoType type) {
    return static_cast<int>(type);
}
}

Tetromino::Tetromino(TetrominoType type)
    : type_(type), x_(3), y_(0), rotation_(0) {}

TetrominoType Tetromino::getType() const {
    return type_;
}

int Tetromino::getX() const {
    return x_;
}

int Tetromino::getY() const {
    return y_;
}

int Tetromino::getRotation() const {
    return rotation_;
}

int Tetromino::getColorId() const {
    return typeIndex(type_) + 1;
}

void Tetromino::setPosition(int x, int y) {
    x_ = x;
    y_ = y;
}

void Tetromino::move(int dx, int dy) {
    x_ += dx;
    y_ += dy;
}

void Tetromino::rotateClockwise() {
    rotation_ = (rotation_ + 1) % 4;
}

void Tetromino::rotateCounterClockwise() {
    rotation_ = (rotation_ + 3) % 4;
}

std::vector<Point> Tetromino::cells() const {
    std::vector<Point> result;
    result.reserve(4);

    const auto& shape = kShapes[typeIndex(type_)][rotation_];
    for (const auto& block : shape) {
        result.push_back({x_ + block.x, y_ + block.y});
    }

    return result;
}
