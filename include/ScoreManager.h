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

private:
    int score_;
    int linesCleared_;
    int level_;
};
