/*
 * Dinh nghia khoi Tetromino, hinh dang va cac thao tac di chuyen.
 */
#pragma once

#include <vector>

enum class TetrominoType {
    I,
    O,
    T,
    S,
    Z,
    J,
    L
};

struct Cell {
    int x;
    int y;
};

class Tetromino {
public:
    explicit Tetromino(TetrominoType type);

    TetrominoType getType() const;
    int getColorId() const;
    const std::vector<Cell>& cells() const;

    void setPosition(int x, int y);
    void move(int dx, int dy);
    void rotateClockwise();
    void rotateCounterClockwise();

private:
    void updateCells();

    TetrominoType type_;
    int x_;
    int y_;
    int rotation_;
    std::vector<Cell> cells_;
};
