/*
 * Cai dat cach tinh diem, len cap va dieu chinh toc do roi theo tien do.
 */
#include "ScoreManager.h"
#include <algorithm>
ScoreManager::ScoreManager() : score_(0), linesCleared_(0), level_(0), comboCount_(-1), isLastClearTetris_(false){}
void ScoreManager::reset(){
    score_ = 0;
    linesCleared_ = 0;
    level_ = 0;
    comboCount_ = -1;
    isLastClearTetris_ = false;
}
void ScoreManager::addClearedLines(int count){
    static constexpr int kLineScores[] = {0, 40, 100, 300, 1200};
    if (count < 1 || count > 4){
        comboCount_ = -1;
        return;
    }
    comboCount_++;
    int baseScore = kLineScores[count];
    if (count == 4){
        if (isLastClearTetris_){
            baseScore = static_cast<int>(baseScore * 1.5);
        }
        isLastClearTetris_ = true;
    } else {
        isLastClearTetris_ = false;
    }
    score_ += baseScore * (level_ + 1);
    if (comboCount_ > 0){
        score_ += comboCount_ * kComboBonusBase * (level_ + 1);
    }
    linesCleared_ += count;
    level_ = linesCleared_ / kLinesPerLevel; 
}
void ScoreManager::addSoftDrop(){
    score_ += kSoftDropScore; 
}
void ScoreManager::addHardDrop(int rows){
    score_ += rows * kHardDropMultiplier; 
}
int ScoreManager::getScore() const { return score_; }
int ScoreManager::getLinesCleared() const { return linesCleared_; }
int ScoreManager::getLevel() const { return level_; }
int ScoreManager::getDisplayLevel() const { return level_ + 1; }
int ScoreManager::getComboCount() const { return std::max(0, comboCount_); }
int ScoreManager::getFallDelayMs() const {
    int calculatedDelay = kBaseFallDelayMs;
    for (int i = 0; i < level_; ++i){
        calculatedDelay = static_cast<int>(calculatedDelay * 0.85);
    }
    return std::max(kMinFallDelayMs, calculatedDelay);
}
