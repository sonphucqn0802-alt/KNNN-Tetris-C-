/*
 * Dinh nghia giao dien luu, tai diem cao va cac thiet lap cua nguoi choi.
 */
#pragma once
#include <string>

class SaveManager {
public:
    explicit SaveManager(std::string SavePath = "saves/highscore.dat");

    int LoadHighScore() const;
    void SaveHighScore(int Score) const;

private:
    std::string SavePath_;
};
