# 🕹️ KNNN-Tetris-C- | Classic Tetris in Console

[![C++ Version](https://img.shields.io/badge/C%2B%2B-17-blue.svg?style=flat-glass&logo=c%2B%2B)](https://en.cppreference.com/w/cpp/17)
[![Build System](https://img.shields.io/badge/Build-CMake-green.svg?style=flat-glass&logo=cmake)](https://cmake.org/)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg?style=flat-glass)](https://github.com)

Dự án phát triển trò chơi **Tetris cổ điển** chạy trực tiếp trong môi trường Terminal/Console được viết bằng chuẩn mã nguồn **C++17**. Đây là đồ án thực hành cho môn học **Kỹ Năng Nghề Nghiệp** tại Trường Đại học Công nghệ Thông tin - ĐHQG TP.HCM (UIT).

---

## 🚀 Tính Năng Nổi Bật

*   **Đầy đủ 7 khối gạch chuẩn:** Hỗ trợ đầy đủ các khối Tetromino (I, O, T, S, Z, J, L) với màu sắc ANSI trực quan.
*   **Hệ thống điều khiển mượt mà:** Di chuyển, xoay khối, hạ thấp (Soft Drop) và rơi nhanh (Hard Drop).
*   **Hỗ trợ Ghost Piece:** Hiển thị bóng mờ dự đoán vị trí rơi thực tế để hỗ trợ người chơi căn chỉnh.
*   **Cơ chế tính điểm & Cấp độ:** Tự động tăng tốc độ rơi của khối gạch dựa trên cấp độ và số lượng dòng đã dọn sạch.
*   **Lưu trữ điểm số:** Tích hợp bộ đọc/ghi file nhị phân (`saves/highscore.dat`) giúp lưu trữ và cập nhật điểm kỷ lục bền vững.
*   **Âm thanh tích hợp:** Phát các hiệu ứng âm thanh và nhạc nền thông qua hệ thống Windows `Beep`.

---

## 🛠️ Công Nghệ Sử Dụng

| Thành Phần | Công Nghệ / Giải Pháp | Chi Tiết |
| :--- | :--- | :--- |
| **Ngôn ngữ** | C++17 | Đảm bảo tính hiện đại, tối ưu hiệu năng |
| **Hệ thống Build** | CMake | Quản lý biên dịch dự án đa nền tảng dễ dàng |
| **Giao diện** | ANSI Escape Codes | Kết xuất đồ họa màu sắc trực tiếp trên Console |
| **Âm thanh** | Windows `Beep` API | Phát tiếng bip hệ thống (Bỏ qua trên Linux/macOS) |
| **Dữ liệu** | Binary File Stream | Lưu/đọc điểm kỷ lục dưới dạng nhị phân bảo mật |

---

## 👥 Nhóm Thực Hiện

*   **Giảng viên hướng dẫn:** Thầy Nguyễn Văn Toàn
*   **Học kỳ:** Học kỳ 2 — Năm học 2025 - 2026

| Thành viên | MSSV | Vai trò phụ trách |
| :--- | :--- | :--- |
| **Nguyễn Khánh Hung** | `25520640` | Trưởng nhóm, Quản lý Khối Tetromino & Xử lý Di chuyển |
| **Lê Bửu Chương** | `24520231` | Thiết kế Game Board & Xử lý Logic Ma trận Lưới |
| **Võ Trung Hiếu** | `25520561` | Xử lý Đồ họa, Thiết kế Renderer & Giao diện UI |
| **Phạm Sơn Phúc** | `25521438` | Cấu hình Vòng lặp Game (Game Loop) & Hệ thống Tính điểm |
| **Nguyễn Thanh Phong** | `25521387` | Tích hợp hệ thống Input, Audio & Hệ thống Save/Load |

---

## 📂 Cấu Trúc Dự Án

```text
KNNN-Tetris-C-/
├── .gitignore               # Cấu hình bỏ qua các file tạm, file build khi push Git
├── CMakeLists.txt           # File cấu hình tổng của hệ thống biên dịch CMake
├── Phân công.md             # Tài liệu phân chia công việc trong nhóm
├── README.md                # Tài liệu hướng dẫn và giới thiệu tổng quan dự án
├── tetris.exe               # File thực thi chạy game chính (ở thư mục gốc)
│
├── assets/                  # Thư mục chứa tài nguyên đồ họa và âm thanh của game
│   ├── fonts/               # Chứa các tệp font chữ hiển thị (UI/Score)
│   └── sounds/              # Chứa các tệp hiệu ứng âm thanh, nhạc nền (.mp3, .wav)
│
├── build/                   # Thư mục chứa các file sinh ra trong quá trình biên dịch
│   ├── .cmake/              # Cấu hình hệ thống nội bộ của CMake
│   ├── CMakeFiles/          # Các tệp trung gian phục vụ quá trình dịch code
│   ├── cmake_install.cmake  # Kịch bản cài đặt tự động của CMake
│   ├── CMakeCache.txt       # Bộ nhớ đệm lưu thông tin môi trường build
│   ├── compile_commands.json# Bản đồ định tuyến hỗ trợ gợi ý code cho IntelliSense
│   ├── Makefile             # Kịch bản lệnh biên dịch chi tiết của MinGW
│   └── tetris.exe           # Sản phẩm file chạy game sau khi build thành công
│
├── Deadline/                # Thư mục quản lý tiến độ bài tập theo tuần
│   ├── Tuần 2.md            
│   └── Tuần 3.md            
│
├── include/                 # Thư mục chứa các file Header (.h) định nghĩa lớp
│   ├── AudioManager.h       # Quản lý phát nhạc nền và hiệu ứng âm thanh
│   ├── Board.h              # Quản lý ma trận bàn cờ và xử lý va chạm, dọn dòng
│   ├── GameLoop.h           # Điều phối vòng lặp chính của game (Update, Render, FPS)
│   ├── InputHandler.h       # Bắt sự kiện và ánh xạ phím bấm đa nền tảng
│   ├── Renderer.h           # Chịu trách nhiệm vẽ đồ họa, UI lên màn hình
│   ├── SaveManager.h        # Xử lý luồng đọc/ghi dữ liệu nhị phân để lưu game
│   ├── ScoreManager.h       # Quản lý tính điểm, cập nhật cấp độ và điểm cao
│   └── Tetromino.h          # Định nghĩa cấu trúc, màu sắc và xoay khối gạch
│
├── saves/                   # Thư mục lưu trữ trạng thái game của người chơi
│   └── highscore.dat        # File lưu dữ liệu điểm kỷ lục (Binary Format)
│
└── src/                     # Thư mục chứa các file Implementation (.cpp) xử lý logic
    ├── AudioManager.cpp     
    ├── Board.cpp            
    ├── GameLoop.cpp         
    ├── InputHandler.cpp     
    ├── main.cpp             # Điểm khởi đầu của chương trình (Hàm main)
    ├── Renderer.cpp         
    ├── SaveManager.cpp      
    ├── ScoreManager.cpp     
    └── Tetromino.cpp
