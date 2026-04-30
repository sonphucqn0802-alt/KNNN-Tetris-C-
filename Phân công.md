# Phân Chia Công Việc - Dự Án Tetris C++

## Cấu Trúc Thư Mục

```
tetris-cpp/
├── CMakeLists.txt
├── README.md
├── TASK_DIVISION.md
│
├── include/                    # Header files (dùng chung)
│   ├── Board.h                 # TV1
│   ├── Tetromino.h             # TV2
│   ├── Renderer.h              # TV3
│   ├── GameLoop.h              # TV4
│   ├── ScoreManager.h          # TV4
│   ├── InputHandler.h          # TV5
│   ├── AudioManager.h          # TV5
│   └── SaveManager.h           # TV5
│
├── src/                        # Source files
│   ├── Board.cpp               # TV1
│   ├── Tetromino.cpp           # TV2
│   ├── Renderer.cpp            # TV3
│   ├── GameLoop.cpp            # TV4
│   ├── ScoreManager.cpp        # TV4
│   ├── InputHandler.cpp        # TV5
│   ├── AudioManager.cpp        # TV5
│   ├── SaveManager.cpp         # TV5
│   └── main.cpp                # TV4 (tích hợp chung)
│
├── assets/
│   ├── sounds/                 # TV5
│   └── fonts/                  # TV3
│
├── saves/                      # TV5 (runtime, gitignore)
│   └── highscore.dat
│
└── tests/                      # Mỗi TV tự viết test cho module mình
    ├── test_board.cpp           # TV1
    ├── test_tetromino.cpp       # TV2
    ├── test_score.cpp           # TV4
    └── test_input.cpp           # TV5
```

---

## Thành Viên 1 — Game Board & Grid Logic

**Files phụ trách:** `include/Board.h` · `src/Board.cpp` · `tests/test_board.cpp`

**Mô tả:** Xây dựng nền tảng lưới trò chơi 10×20, là module trung tâm mà tất cả các thành viên khác phụ thuộc vào. Cần hoàn thành **sớm nhất** để các thành viên khác có thể tích hợp.

### Nhiệm vụ cụ thể

- Khởi tạo và quản lý ma trận `grid[20][10]` (0 = ô trống, 1-7 = màu khối)
- Hàm kiểm tra ô có hợp lệ không: `isValidPosition(x, y, shape)`
- Hàm đặt khối cố định vào board: `lockPiece(tetromino)`
- Hàm kiểm tra và xóa hàng đầy: `clearLines()` → trả về số hàng đã xóa
- Hàm dồn hàng xuống sau khi xóa: `collapseRows(clearedRow)`
- Hàm kiểm tra thua (khối tràn lên đỉnh): `isGameOver()`
- Hàm reset board: `reset()`

### Interface cần định nghĩa sớm (cho TV khác dùng)

```cpp
class Board {
public:
    static const int WIDTH  = 10;
    static const int HEIGHT = 20;

    Board();
    bool isValidPosition(int x, int y, const std::vector<std::vector<int>>& shape) const;
    void lockPiece(const Tetromino& piece);
    int  clearLines();
    bool isGameOver() const;
    void reset();
    int  getCell(int row, int col) const;
};
```

### Thứ tự ưu tiên

1. Định nghĩa `Board.h` (interface) — **Tuần 1, ưu tiên cao nhất**
2. Implement `isValidPosition()` và `lockPiece()`
3. Implement `clearLines()` và `collapseRows()`
4. Viết test cases
5. Implement `isGameOver()` và `reset()`

---

## Thành Viên 2 — Tetromino & Movement

**Files phụ trách:** `include/Tetromino.h` · `src/Tetromino.cpp` · `tests/test_tetromino.cpp`

**Mô tả:** Xây dựng các loại khối Tetromino và logic di chuyển/xoay. Phụ thuộc vào `Board.h` để kiểm tra va chạm.

### Nhiệm vụ cụ thể

- Định nghĩa 7 loại khối (I, O, T, S, Z, J, L) bằng ma trận 2D
- Mỗi khối có màu tương ứng (dùng enum `TetrominoType`)
- Hàm di chuyển: `moveLeft()`, `moveRight()`, `moveDown()`
- Hàm xoay: `rotateClockwise()`, `rotateCounterClockwise()` (thuật toán SRS - Super Rotation System)
- Hard drop (rơi thẳng xuống vị trí thấp nhất): `hardDrop(const Board&)`
- Ghost piece (tính vị trí bóng): `getGhostPosition(const Board&)`
- Sinh khối ngẫu nhiên: `spawnRandom()`

### Interface cần định nghĩa sớm

```cpp
enum class TetrominoType { I, O, T, S, Z, J, L };

class Tetromino {
public:
    Tetromino(TetrominoType type);

    void moveLeft(const Board& board);
    void moveRight(const Board& board);
    bool moveDown(const Board& board);   // false = không di chuyển được
    void rotateClockwise(const Board& board);
    void hardDrop(const Board& board);

    int getGhostY(const Board& board) const;
    std::vector<std::vector<int>> getShape() const;
    int getX() const;
    int getY() const;
    TetrominoType getType() const;

    static Tetromino spawnRandom();
};
```

### Thứ tự ưu tiên

1. Định nghĩa `Tetromino.h` — **Tuần 1**
2. Định nghĩa 7 loại khối và màu sắc
3. Implement di chuyển và kiểm tra va chạm với Board
4. Implement xoay (bắt đầu với xoay đơn giản, sau nâng cấp SRS)
5. Implement ghost piece và hard drop
6. Viết test cases

---

## Thành Viên 3 — Rendering & UI

**Files phụ trách:** `include/Renderer.h` · `src/Renderer.cpp` · `assets/fonts/`

**Mô tả:** Xây dựng toàn bộ phần hiển thị. Phụ thuộc vào `Board` và `Tetromino`. Có thể dùng **ncurses** (terminal) hoặc **SDL2/SFML** (đồ họa — cần thống nhất nhóm).

### Nhiệm vụ cụ thể

- Khởi tạo và dọn dẹp hệ thống render: `init()`, `cleanup()`
- Vẽ board (ô trống và ô đã lấp): `drawBoard(const Board&)`
- Vẽ khối đang rơi: `drawActivePiece(const Tetromino&)`
- Vẽ ghost piece (khối bóng mờ): `drawGhostPiece(const Tetromino&, int ghostY)`
- Vẽ khối tiếp theo (preview): `drawNextPiece(const Tetromino&)`
- Vẽ HUD (điểm, level, số hàng): `drawHUD(int score, int level, int lines)`
- Màn hình menu chính: `drawMenu()`
- Màn hình game over: `drawGameOver(int finalScore)`
- Màn hình tạm dừng: `drawPaused()`
- Hàm clear màn hình và render: `clear()`, `render()`

### Bảng màu cho các khối

| Loại | Màu       |
|------|-----------|
| I    | Cyan      |
| O    | Yellow    |
| T    | Purple    |
| S    | Green     |
| Z    | Red       |
| J    | Blue      |
| L    | Orange    |

### Thứ tự ưu tiên

1. Chọn thư viện render và cài đặt CMake — **Tuần 1**
2. Implement `init()`, `clear()`, `render()`
3. Implement `drawBoard()` và `drawActivePiece()`
4. Implement `drawHUD()` và `drawNextPiece()`
5. Implement ghost piece, menu, game over, pause screens

---

## Thành Viên 4 — Game Loop, Scoring & Tích Hợp

**Files phụ trách:** `include/GameLoop.h` · `src/GameLoop.cpp` · `include/ScoreManager.h` · `src/ScoreManager.cpp` · `src/main.cpp` · `tests/test_score.cpp`

**Mô tả:** Điều phối vòng lặp game chính, tính điểm và tích hợp tất cả các module lại với nhau. Là người viết `main.cpp` và chịu trách nhiệm build toàn bộ project.

### Nhiệm vụ cụ thể

**Game Loop:**
- Vòng lặp chính với fixed timestep (60 FPS): `run()`
- Quản lý trạng thái: `GameState` (MENU, PLAYING, PAUSED, GAME_OVER)
- Điều khiển tốc độ rơi tự động theo level: `getDropInterval(int level)`
- Spawn khối mới khi khối cũ đã lock: `spawnNext()`
- Xử lý sự kiện từ InputHandler

**Score Manager:**
- Tính điểm theo hàng xóa (hệ thống Nintendo):
  - 1 hàng = 100 × level
  - 2 hàng = 300 × level
  - 3 hàng = 500 × level
  - 4 hàng (Tetris!) = 800 × level
- Tính level: tăng mỗi 10 hàng xóa
- Lưu và load high score (phối hợp TV5)

### Interface

```cpp
enum class GameState { MENU, PLAYING, PAUSED, GAME_OVER };

class GameLoop {
public:
    GameLoop(Board&, Renderer&, InputHandler&, AudioManager&, ScoreManager&);
    void run();
    GameState getState() const;

private:
    void update(float deltaTime);
    void handleInput();
    void spawnNext();
};
```

### Thứ tự ưu tiên

1. Viết `main.cpp` skeleton và `CMakeLists.txt` — **Tuần 1**
2. Implement `ScoreManager` (điểm, level)
3. Implement vòng lặp chính với drop tự động
4. Implement quản lý trạng thái game
5. Tích hợp tất cả module, kiểm tra end-to-end

---

## Thành Viên 5 — Input, Audio & Save

**Files phụ trách:** `include/InputHandler.h` · `src/InputHandler.cpp` · `include/AudioManager.h` · `src/AudioManager.cpp` · `include/SaveManager.h` · `src/SaveManager.cpp` · `assets/sounds/` · `tests/test_input.cpp`

**Mô tả:** Xử lý đầu vào bàn phím, âm thanh và hệ thống lưu trữ dữ liệu.

### Nhiệm vụ cụ thể

**Input Handler:**
- Đọc phím và map sang hành động game: `pollEvents()`
- Hỗ trợ DAS (Delayed Auto Shift) — giữ phím để di chuyển liên tục
- Các phím cần xử lý:

| Phím          | Hành động              |
|---------------|------------------------|
| ← / →         | Di chuyển trái/phải    |
| ↓             | Soft drop (rơi nhanh)  |
| ↑ / X         | Xoay xuôi              |
| Z             | Xoay ngược             |
| Space         | Hard drop              |
| P / Esc       | Pause / Menu           |
| C             | Hold piece (nâng cao)  |

**Audio Manager:**
- Phát nhạc nền: `playBGM()`, `stopBGM()`
- Phát hiệu ứng âm thanh: `playSFX(SoundEffect)`
- Điều chỉnh âm lượng, tắt tiếng
- Các SFX cần có: di chuyển, xoay, lock, xóa hàng, Tetris, game over

**Save Manager:**
- Lưu high score ra file `saves/highscore.dat`
- Load high score khi khởi động
- Lưu cài đặt (âm lượng, keybinding)

### Thứ tự ưu tiên

1. Implement `InputHandler` cơ bản (không có DAS) — **Tuần 1**
2. Implement `SaveManager` (đọc/ghi file)
3. Thêm DAS vào InputHandler
4. Implement `AudioManager` (nếu dùng SDL2_mixer hoặc SFML Audio)
5. Thêm hold piece

---

## Lịch Trình Chung

| Tuần | Mục tiêu |
|------|-----------|
| 1 | TV1 + TV2 hoàn thành interface (`.h`), TV4 dựng CMake + main.cpp skeleton |
| 2 | TV1 + TV2 implement core logic, TV3 chọn thư viện và dựng render cơ bản |
| 3 | TV4 tích hợp TV1+TV2, TV5 hoàn thành Input + Save |
| 4 | TV3 hoàn thiện UI, TV5 thêm Audio, toàn nhóm test tích hợp |
| 5 | Bug fix, polish, hoàn thiện README |

---

## Quy Tắc Chung

- Mỗi thành viên tạo branch riêng: `feature/board`, `feature/tetromino`, v.v.
- Merge vào `main` qua Pull Request, cần ít nhất 2 người review
- **Không** hardcode hằng số — dùng `Board::WIDTH`, `Board::HEIGHT`
- Header files phải có include guard hoặc `#pragma once`
