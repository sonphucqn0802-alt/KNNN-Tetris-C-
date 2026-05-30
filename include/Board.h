/*
 * Dinh nghia giao dien cho bang choi, luoi o va cac thao tac tren board.
 */
#pragma once

#include "Tetromino.h"

#include <vector>

class Board {
public:
    static constexpr int Width = 15;
    static constexpr int Height = ;

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

