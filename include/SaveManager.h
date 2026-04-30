#pragma once

#include <string>

class SaveManager {
public:
    explicit SaveManager(std::string path = "saves/highscore.dat");

    int loadHighScore() const;
    void saveHighScore(int score) const;

private:
    std::string path_;
};
