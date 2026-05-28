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

// Đặt lại toàn bộ hệ thống tính điểm về trạng thái ban đầu khi bắt đầu ván mới (New Game)      
void ScoreManager::reset() {
    score_ = 0;
    linesCleared_ = 0;
    level_ = 0;
}

// Tính toán điểm số khi người chơi ăn điểm bằng cách xóa dòng
// Hệ số điểm tăng vọt nếu xóa được nhiều dòng cùng lúc (đặc biệt là 4 dòng - Tetris)
void ScoreManager::addClearedLines(int count) {
    static constexpr int kLineScores[] = {0, 40, 100, 300, 1200};
    if (count < 1 || count > 4) {
        return;
    }
    
    // Điểm thưởng tỉ lệ thuận với cấp độ (level) hiện tại
    score_ += kLineScores[count] * (level_ + 1);
    linesCleared_ += count;
    // Sử dụng kLinesPerLevel thay vì số 10
    // Cứ mỗi kLinesPerLevel (10 dòng) thì tăng 1 cấp độ
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
