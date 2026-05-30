/*
 * Cai dat cac thao tac tren board nhu kiem tra vi tri, khoa khoi va xoa dong.
 */

#include "Board.h"
#include "Tetromino.h"

#include <algorithm>

Board::Board()
    : grid_(Height, std::vector<int>(Width, 0)) {}
// Cài đặt thuật toán khởi tạo/khôi phục ma trận bàn chơi và kiểm tra điều kiện va chạm biên của khối gạch
void Board::reset() {
    for (auto& row : grid_) {
        std::fill(row.begin(), row.end(), 0);
    }
}

bool Board::isInside(int x, int y) const {
    return x >= 0 && x < Width && y >= 0 && y < Height;
}

bool Board::isCellEmpty(int x, int y) const {
    return isInside(x, y) && grid_[y][x] == 0;
}

bool Board::isValidPosition(const Tetromino& piece) const {
    for (const auto& cell : piece.cells()) {
        if (!isInside(cell.x, cell.y) || grid_[cell.y][cell.x] != 0) {
            return false;
        }
    }
    return true;
}

void Board::lockPiece(const Tetromino& piece) {
    for (const auto& cell : piece.cells()) {
        if (isInside(cell.x, cell.y)) {
            grid_[cell.y][cell.x] = piece.getColorId();
        }
    }
}

int Board::clearFullLines() {
    int cleared = 0;

    for (int y = Height - 1; y >= 0; --y) {
        const bool full = std::all_of(grid_[y].begin(), grid_[y].end(), [](int cell) {
            return cell != 0;
        });

        if (!full) {
            continue;
        }

        grid_.erase(grid_.begin() + y);
        grid_.insert(grid_.begin(), std::vector<int>(Width, 0));
        ++cleared;
        ++y;
    }

    return cleared;
}
<<<<<<< HEAD
// Hàm Getter: Trả về trạng thái ID của ô tại vị trí (x, y). Trả về -1 nếu tọa độ bị sai.
=======
/*
 * Hàm truy xuất dữ liệu (Getter) của ma trận:
 * - Nhận vào tọa độ (x, y) và trả về giá trị ID màu sắc của ô (cell) tương ứng trên bàn chơi.
 * - Sử dụng hàm isInside() để kiểm tra an toàn. Nếu tọa độ truy xuất nằm ngoài ranh giới ma trận, hàm sẽ trả về -1 để báo lỗi, tránh crash chương trình.
 */
>>>>>>> pr-phan-he-7
int Board::getCell(int x, int y) const {
    if (!isInside(x, y)) {
        return -1;
    }
    return grid_[y][x];
}

void Board::setCell(int x, int y, int value) {
    if (isInside(x, y)) {
        grid_[y][x] = value;
    }
}

const std::vector<std::vector<int>>& Board::grid() const {
    return grid_;
}

