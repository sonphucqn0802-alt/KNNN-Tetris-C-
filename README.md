# KNNN-Tetris-C-
# Tetris C++

Do an mon hoc Ky Nang Nghe Nghiep: game Tetris viet bang C++17, chay truc tiep trong terminal/console.

Game hien co:

- 7 khoi Tetromino: I, O, T, S, Z, J, L
- Di chuyen, xoay khoi, soft drop va hard drop
- Ghost piece hien vi tri roi du doan
- Tinh diem, level va tang toc do roi theo so dong da xoa
- Luu diem cao vao file `saves/highscore.dat`
- Giao dien console co mau ANSI
- Am thanh don gian tren Windows bang `Beep`

---

## Cong Nghe Su Dung

| Thanh phan | Cong nghe |
|---|---|
| Ngon ngu | C++17 |
| Build system | CMake |
| Giao dien | Console/terminal ANSI |
| Am thanh | Windows `Beep`, he dieu hanh khac se bo qua am thanh |
| Luu du lieu | File `saves/highscore.dat` |

---

## Nhom Thuc Hien

| Thanh vien | MSSV | Phu trach |
|---|---|---|
| Nguyen Khanh Hung - Nhom truong | 25520640 | Tetromino & Movement |
| Le Buu Chuong | 24520231 | Game Board & Grid Logic |
| Vo Trung Hieu | 25520561 | Rendering & UI |
| Pham Son Phuc | 25521438 | Game Loop & Scoring |
| Nguyen Van E | xxxxxxxx | Input, Audio & Save |

> Giang vien huong dan: Nguyen Van Toan
> Hoc ky: Hoc ky 2 - Nam hoc 2025-2026

---

## Cau Truc Du An

```text
KNNN-Tetris-C-/
|-- CMakeLists.txt
|-- README.md
|-- Phân công.md
|-- Deadline/
|   |-- Tuần 2.md
|   `-- Tuần 3.md
|-- assets/
|   |-- fonts/
|   `-- sounds/
|-- include/
|   |-- AudioManager.h
|   |-- Board.h
|   |-- GameLoop.h
|   |-- InputHandler.h
|   |-- Renderer.h
|   |-- SaveManager.h
|   |-- ScoreManager.h
|   `-- Tetromino.h
|-- saves/
|   `-- highscore.dat
`-- src/
    |-- AudioManager.cpp
    |-- Board.cpp
    |-- GameLoop.cpp
    |-- InputHandler.cpp
    |-- main.cpp
    |-- Renderer.cpp
    |-- SaveManager.cpp
    |-- ScoreManager.cpp
    `-- Tetromino.cpp
```

Ghi chu: hien tai du an khong co thu muc `tests/`. File phan cong cua nhom la `Phân công.md`.

---

## Cach Tai Xuong

Dung Git:

```bash
git clone https://github.com/ChuongLe279/KNNN-Tetris-C-.git
cd KNNN-Tetris-C-
```

Hoac vao GitHub, bam `Code` -> `Download ZIP`, roi giai nen.

---

## Cach Build Va Chay

### Cach 1: Dung CMake

Can cai san CMake va compiler C++.

```bash
cmake -S . -B build
cmake --build build
```

Chay tren Windows:

```powershell
.\build\tetris.exe
```

Chay tren Linux/macOS:

```bash
./build/tetris
```

### Cach 2: Build nhanh bang g++

Neu may co `g++`, co the build truc tiep:

```bash
g++ -std=c++17 -Iinclude src/AudioManager.cpp src/Board.cpp src/GameLoop.cpp src/InputHandler.cpp src/main.cpp src/Renderer.cpp src/SaveManager.cpp src/ScoreManager.cpp src/Tetromino.cpp -o tetris
```

Tren Windows, neu dung PowerShell:

```powershell
g++ -std=c++17 -Iinclude src\AudioManager.cpp src\Board.cpp src\GameLoop.cpp src\InputHandler.cpp src\main.cpp src\Renderer.cpp src\SaveManager.cpp src\ScoreManager.cpp src\Tetromino.cpp -o tetris.exe
.\tetris.exe
```

---

## Dieu Khien

| Phim | Chuc nang |
|---|---|
| `A` hoac mui ten trai | Di chuyen sang trai |
| `D` hoac mui ten phai | Di chuyen sang phai |
| `S` hoac mui ten xuong | Soft drop |
| `W`, `X` hoac mui ten len | Xoay xuoi chieu kim dong ho |
| `Z` | Xoay nguoc chieu kim dong ho |
| `Space` | Hard drop |
| `P` | Tam dung / tiep tuc |
| `R` | Choi lai |
| `Q` hoac `Esc` | Thoat game |

---

## Cac File Chinh

| File | Vai tro |
|---|---|
| `src/main.cpp` | Diem bat dau chuong trinh |
| `GameLoop.*` | Dieu phoi vong lap game, spawn khoi, xu ly trang thai |
| `Board.*` | Quan ly luoi choi, va cham, khoa khoi, xoa dong |
| `Tetromino.*` | Dinh nghia hinh dang, vi tri va xoay khoi |
| `Renderer.*` | Ve giao dien console |
| `InputHandler.*` | Doc phim va doi sang hanh dong |
| `ScoreManager.*` | Tinh diem, level va toc do roi |
| `SaveManager.*` | Doc/ghi high score |
| `AudioManager.*` | Phat am thanh don gian |

---

Link Overleaf: https://www.overleaf.com/project/69b669a6c9c8842b2d77068d
