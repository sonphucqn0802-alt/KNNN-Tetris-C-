#pragma once
// Khai báo cấu trúc lớp Board quản lý dữ liệu mảng hai chiều và các thuộc tính trạng thái của bàn cờ

#include "Tetromino.h"

#include <vector>

class Board {
public:
    static constexpr int Width = 10;
    static constexpr int Height = 20;

    Board();

    void reset();
    bool isInside(int x, int y) const;
    bool isCellEmpty(int x, int y) const;
    bool isValidPosition(const Tetromino& piece) const;
    void lockPiece(const Tetromino& piece);
    int clearFullLines();

    int getCell(int x, int y) const;
    void setCell(int x, int y, int value);
    const std::vector<std::vector<int>>& grid() const;

private:
    std::vector<std::vector<int>> grid_;
};
