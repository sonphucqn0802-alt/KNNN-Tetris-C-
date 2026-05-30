/**
 * @class ScoreManager
 * @brief Đảm nhận toàn bộ logic liên quan đến tiến trình ván đấu Tetris.
 */
#pragma once
class ScoreManager {
    public:
    ScoreManager();
    void reset();
    void addClearedLines(int count);
    void addSoftDrop();
    void addHardDrop(int rows);
    int getScore() const;
    int getLinesCleared() const;
    int getLevel() const;
    int getDisplayLevel() const;
    int getFallDelayMs() const;
    int getComboCount() const;
    private:
    static constexpr int kLinesPerLevel = 10;
    static constexpr int kHardDropMultiplier = 2;
    static constexpr int kSoftDropScore = 1;
    static constexpr int kBaseFallDelayMs = 800;
    static constexpr int kMinFallDelayMs = 80;
    static constexpr int kDelayDecreasePerLevel = 60;
    static constexpr int kComboBonusBase = 50;
    int score_;
    int linesCleared_;
    int level_;
    int comboCount_;
    bool isLastClearTetris_;
};
