/*
 * Dinh nghia giao dien luu, tai diem cao va cac thiet lap cua nguoi choi.
 */
#pragma once

#include <string>

class SaveManager {
public:
    explicit SaveManager(std::string savePath = "saves/highscore.dat");

    int loadHighScore() const;
    void saveHighScore(int score) const;

private:
    std::string savePath_;
};
