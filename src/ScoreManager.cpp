/*
 * Cai dat cach tinh diem, len cap va dieu chinh toc do roi theo tien do.
 */
#include "ScoreManager.h"

#include <algorithm>

// Khởi tạo ScoreManager: Đặt điểm số, số dòng đã xóa và cấp độ ban đầu về 0
ScoreManager::ScoreManager()
    : score_(0),
      linesCleared_(0),
      level_(0) {}

void ScoreManager::reset() {
    score_ = 0;
    linesCleared_ = 0;
    level_ = 0;
}

void ScoreManager::addClearedLines(int count) {
    static constexpr int kLineScores[] = {0, 40, 100, 300, 1200};
    if (count < 1 || count > 4) {
        return;
    }

    score_ += kLineScores[count] * (level_ + 1);
    linesCleared_ += count;
    // Sử dụng kLinesPerLevel thay vì số 10
    level_ = linesCleared_ / kLinesPerLevel; 
}

void ScoreManager::addSoftDrop() {
    // Sử dụng kSoftDropScore thay vì số 1
    score_ += kSoftDropScore; 
}

void ScoreManager::addHardDrop(int rows) {
    // Sử dụng kHardDropMultiplier thay vì số 2
    score_ += rows * kHardDropMultiplier; 
}

int ScoreManager::getScore() const {
    return score_;
}

int ScoreManager::getLinesCleared() const {
    return linesCleared_;
}

int ScoreManager::getLevel() const {
    return level_;
}

int ScoreManager::getDisplayLevel() const {
    return level_ + 1;
}

int ScoreManager::getFallDelayMs() const {
    // Thay thế 80, 800 và 60 bằng các hằng số tương ứng
    return std::max(kMinFallDelayMs, kBaseFallDelayMs - level_ * kDelayDecreasePerLevel);
}
