/**
 * @class ScoreManager
 * @brief Đảm nhận toàn bộ logic liên quan đến tiến trình ván đấu Tetris.
 * 
 * Class này lưu trữ và xử lý việc tính điểm (score), đếm số dòng đã xóa (lines cleared),
 * theo dõi cấp độ (level) và điều chỉnh tốc độ rơi của khối gạch theo độ khó tăng dần.
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

private:
    // --- Các hằng số cấu hình game (Thay thế Magic Numbers) ---
    static constexpr int kLinesPerLevel = 10;
    static constexpr int kHardDropMultiplier = 2;
    static constexpr int kSoftDropScore = 1;
    static constexpr int kBaseFallDelayMs = 800;
    static constexpr int kMinFallDelayMs = 80;
    static constexpr int kDelayDecreasePerLevel = 60;

    int score_;
    int linesCleared_;
    int level_;
};
