/**
 * @class Board
 * @brief Quan ly ma tran ban co va logic va cham cua Tetris.
 */
#pragma once
#include <vector>
class Tetromino; // Forward declaration de tranh loi include vong lap

 // Khai báo lớp Board: Quản lý ma trận lưới (grid) và cung cấp các phương thức kiểm tra va chạm, dọn dòng
class Board {
    public:
    static constexpr int Width = 10; // Chot lai kich thuoc chuan quoc te la 10x20 nhen
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
