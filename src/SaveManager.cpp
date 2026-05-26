/*
 * Cai dat doc ghi diem cao va du lieu luu tru cua game.
 */
#include "SaveManager.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <utility>

namespace {
std::filesystem::path resolveSavePath(const std::string& savePath) {
    const std::filesystem::path direct(savePath);
    if (std::filesystem::exists(direct) || std::filesystem::exists(direct.parent_path())) {
        return direct;
    }

    const std::filesystem::path fromBuild = std::filesystem::path("..") / direct;
    if (std::filesystem::exists(fromBuild.parent_path())) {
        return fromBuild;
    }

    return direct;
}
}

SaveManager::SaveManager(std::string savePath)
    : savePath_(std::move(savePath)) {}

int SaveManager::loadHighScore() const {
    std::ifstream input(resolveSavePath(savePath_));
    int score = 0;

    if (!(input >> score)) {
        return 0;
    }

    return std::max(0, score);
}

void SaveManager::saveHighScore(int score) const {
    const std::filesystem::path path = resolveSavePath(savePath_);
    const auto parent = path.parent_path();

    if (!parent.empty()) {
        std::filesystem::create_directories(parent);
    }

    std::ofstream output(path, std::ios::trunc);
    if (output) {
        output << std::max(0, score) << '\n';
    }
}
