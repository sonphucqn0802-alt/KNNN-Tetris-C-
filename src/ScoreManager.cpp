#include "ScoreManager.h"

#include <algorithm>

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
    level_ = linesCleared_ / 10;
}

void ScoreManager::addSoftDrop() {
    score_ += 1;
}

void ScoreManager::addHardDrop(int rows) {
    score_ += rows * 2;
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
    return std::max(80, 800 - level_ * 60);
}
