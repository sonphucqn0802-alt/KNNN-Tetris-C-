/*
 * Cai dat doc ghi diem cao va du lieu luu tru cua game.
 */
#include "SaveManager.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <utility>
namespace {
std::filesystem::path ResolveSavePath(const std::string &SavePath){
    const std::filesystem::path Direct(SavePath);
    if (std::filesystem::exists(Direct) || std::filesystem::exists(Direct.parent_path())){
        return Direct;
    }
    const std::filesystem::path FromBuild = std::filesystem::path("..") / Direct;
    if (std::filesystem::exists(FromBuild.parent_path())){
        return FromBuild;
    }
    return Direct;
}
}
SaveManager::SaveManager(std::string SavePath) : SavePath_(std::move(SavePath)){}
int SaveManager::LoadHighScore() const {
    std::ifstream Input(ResolveSavePath(SavePath_), std::ios::binary);
    int Score = 0;
    if (!Input.read(reinterpret_cast<char*>(&Score), sizeof(Score))){
        return 0;
    }
    return std::max(0, Score);
}
void SaveManager::SaveHighScore(int Score) const {
    const std::filesystem::path Path = ResolveSavePath(SavePath_);
    const auto Parent = Path.parent_path();
    if (!Parent.empty()){
        std::filesystem::create_directories(Parent);
    }
    std::ofstream Output(Path, std::ios::trunc | std::ios::binary);
    if (Output){
        int ValidScore = std::max(0, Score);
        Output.write(reinterpret_cast<const char*>(&ValidScore), sizeof(ValidScore));
    }
}   
int SaveManager::LoadHighScore() const {
    std::ifstream Input(ResolveSavePath(SavePath_), std::ios::binary);
    int Score = 0;

    // Kiểm tra xem file có mở thành công và có dữ liệu không
    if (!Input.is_open() || !Input.read(reinterpret_cast<char*>(&Score), sizeof(Score))){
        return 0; // Trả về 0 nếu file chưa tồn tại hoặc lỗi đọc
    }
    return std::max(0, Score);
}