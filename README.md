# KNNN-Tetris-C-
# 🎮 Tetris C++

> Đồ án môn học **Kỹ Năng Nghề Nghiệp** — Khoa Công Nghệ Thông Tin

---

## Giới Thiệu

Đây là dự án xây dựng trò chơi **Tetris** kinh điển bằng ngôn ngữ lập trình **C++**, được thực hiện như một đồ án nhóm trong môn học Kỹ Năng Nghề Nghiệp.

Dự án không chỉ đơn thuần là tái hiện lại một tựa game huyền thoại, mà còn là cơ hội để nhóm thực hành toàn bộ quy trình phát triển phần mềm theo nhóm: từ phân tích yêu cầu, thiết kế kiến trúc, phân chia công việc, lập trình hướng đối tượng, cho đến kiểm thử và tích hợp sản phẩm cuối.

---

## Mục Tiêu Môn Học

Thông qua đồ án này, nhóm hướng đến việc rèn luyện và thể hiện các kỹ năng:

- **Làm việc nhóm** — phân chia công việc rõ ràng, phối hợp qua Git và Pull Request
- **Lập trình hướng đối tượng** — thiết kế class, encapsulation, tách biệt logic và giao diện
- **Quản lý mã nguồn** — sử dụng Git/GitHub, tuân thủ quy ước đặt tên và commit
- **Tư duy giải quyết vấn đề** — xử lý va chạm, thuật toán xoay khối, quản lý trạng thái game
- **Viết tài liệu kỹ thuật** — README, phân chia nhiệm vụ, chú thích mã nguồn

---

## Về Trò Chơi

Tetris là tựa game xếp hình ra đời năm 1984, được thiết kế bởi lập trình viên người Nga **Alexey Pajitnov**. Người chơi điều khiển các khối hình học (Tetromino) rơi từ trên xuống, sắp xếp sao cho lấp đầy hàng ngang để ghi điểm. Trò chơi kết thúc khi các khối chồng lên đến đỉnh màn hình.

Phiên bản trong đồ án này bao gồm các tính năng:

- 7 loại khối Tetromino chuẩn (I, O, T, S, Z, J, L)
- Hệ thống xoay khối, di chuyển và hard drop
- Ghost piece hiển thị vị trí rơi dự đoán
- Tính điểm theo chuẩn Nintendo (combo xóa nhiều hàng)
- Hệ thống level và tăng tốc độ
- Lưu điểm cao (high score)
- Hiệu ứng âm thanh

---

## Công Nghệ Sử Dụng

| Thành phần | Công nghệ |
|---|---|
| Ngôn ngữ | C++17 |
| Build system | CMake |
| Thư viện đồ họa | SDL2 / SFML / ncurses |
| Quản lý mã nguồn | Git & GitHub |
| Môi trường | Windows / Linux / macOS |

---

## Nhóm Thực Hiện

| Thành viên | MSSV | Phụ trách |
|---|---|---|
| Nguyễn Văn A | xxxxxxxx | Game Board & Grid Logic |
| Nguyễn Văn B | xxxxxxxx | Tetromino & Movement |
| Nguyễn Văn C | xxxxxxxx | Rendering & UI |
| Nguyễn Văn D | xxxxxxxx | Game Loop & Scoring |
| Nguyễn Văn E | xxxxxxxx | Input, Audio & Save |

> **Giảng viên hướng dẫn:** *(Tên giảng viên)*
> **Học kỳ:** *(Học kỳ — Năm học)*

---

## Cấu Trúc Dự Án

```
tetris-cpp/
├── include/        # Header files (interface các module)
├── src/            # Source files (implementation)
├── assets/         # Tài nguyên (âm thanh, font)
├── saves/          # Dữ liệu lưu trữ (high score)
├── tests/          # Unit test từng module
├── CMakeLists.txt
├── README.md
└── TASK_DIVISION.md
```

Xem chi tiết phân chia công việc tại [`TASK_DIVISION.md`](./TASK_DIVISION.md).

---

## Hướng Dẫn Cài Đặt & Chạy

```bash
# Clone repository
git clone https://github.com/<your-org>/tetris-cpp.git
cd tetris-cpp

# Build
mkdir build && cd build
cmake ..
make

# Chạy game
./tetris
```

---

## Điều Hướng Bàn Phím

| Phím | Chức năng |
|---|---|
| ← / → | Di chuyển trái / phải |
| ↓ | Soft drop |
| ↑ / X | Xoay xuôi chiều kim đồng hồ |
| Z | Xoay ngược chiều kim đồng hồ |
| Space | Hard drop |
| P | Tạm dừng |
| Esc | Về menu |

---

*Đồ án được thực hiện với mục đích học tập. Tetris® là thương hiệu thuộc sở hữu của The Tetris Company.*
