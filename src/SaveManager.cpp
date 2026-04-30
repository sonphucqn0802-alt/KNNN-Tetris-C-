#include "SaveManager.h"

#include <filesystem>
#include <fstream>

SaveManager::SaveManager(std::string path)
    : path_(std::move(path)) {}

int SaveManager::loadHighScore() const {
    std::ifstream input(path_);
    int score = 0;
    input >> score;
    return score;
}

void SaveManager::saveHighScore(int score) const {
    const std::filesystem::path path(path_);
    if (path.has_parent_path()) {
        std::filesystem::create_directories(path.parent_path());
    }

    std::ofstream output(path_);
    output << score << '\n';
}
