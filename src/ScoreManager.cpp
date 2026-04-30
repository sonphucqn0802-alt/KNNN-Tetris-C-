#include "ScoreManager.h"

#include <algorithm>

void ScoreManager::reset() {
    score_ = 0;
    level_ = 0;
    linesCleared_ = 0;
}

void ScoreManager::addSoftDrop() {
    score_ += 1;
}

void ScoreManager::addHardDrop(int rows) {
    score_ += std::max(0, rows) * 2;
}

void ScoreManager::addClearedLines(int lines) {
    static constexpr int kLineScore[] = {0, 40, 100, 300, 1200};
    if (lines <= 0 || lines > 4) {
        return;
    }

    score_ += kLineScore[lines] * (level_ + 1);
    linesCleared_ += lines;
    level_ = linesCleared_ / 10;
}

int ScoreManager::getScore() const {
    return score_;
}

int ScoreManager::getLevel() const {
    return level_;
}

int ScoreManager::getDisplayLevel() const {
    return level_ + 1;
}

int ScoreManager::getLinesCleared() const {
    return linesCleared_;
}

int ScoreManager::getFallDelayMs() const {
    return std::max(90, 800 - level_ * 70);
}
