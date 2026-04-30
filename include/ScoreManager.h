#pragma once

class ScoreManager {
public:
    void reset();
    void addSoftDrop();
    void addHardDrop(int rows);
    void addClearedLines(int lines);

    int getScore() const;
    int getLevel() const;
    int getDisplayLevel() const;
    int getLinesCleared() const;
    int getFallDelayMs() const;

private:
    int score_ = 0;
    int level_ = 0;
    int linesCleared_ = 0;
};
