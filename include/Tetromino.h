#pragma once

#include <array>
#include <vector>

struct Point {
    int x{};
    int y{};
};

enum class TetrominoType {
    I,
    O,
    T,
    S,
    Z,
    J,
    L
};

class Tetromino {
public:
    explicit Tetromino(TetrominoType type = TetrominoType::I);

    TetrominoType getType() const;
    int getX() const;
    int getY() const;
    int getRotation() const;
    int getColorId() const;

    void setPosition(int x, int y);
    void move(int dx, int dy);
    void rotateClockwise();
    void rotateCounterClockwise();

    std::vector<Point> cells() const;

private:
    TetrominoType type_;
    int x_;
    int y_;
    int rotation_;
};
