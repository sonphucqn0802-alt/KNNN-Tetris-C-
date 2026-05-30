====================================================================
BÁO CÁO KIỂM THỬ SẢN PHẨM (TEST REPORT)
Dự án: Hệ thống Game Tetris C++ (Console-Based)
====================================================================

1. Thông Tin Môi Trường Kiểm Thử (Test Environment)
--------------------------------------------------
- Hệ điều hành: Microsoft Windows 11 (Môi trường Local)
- Thư mục làm việc (Workspace): d:\Hoc_tap\Ki_nang_nghe_nghiep\KNNN-Tetris-C-
- Công cụ biên dịch (Build Tools): Hệ thống CMake + MinGW (ucrt64)
- Sản phẩm kiểm thử (Artifact): Tệp thực thi mục tiêu build\tetris.exe
- Ràng buộc quy trình: Không thực hiện git add / commit trong suốt giai đoạn kiểm thử.

---

2. Mục Tiêu Kiểm Thử (Test Objectives)
--------------------------------------
- Xác minh khả năng đóng gói: Đảm bảo mã nguồn biên dịch thành công qua CMake chuẩn.
- Kiểm thử giao diện & Khởi tạo: Xác nhận game chạy được, vẽ đúng khung lưới và thông số ban đầu.
- Đánh giá logic điều khiển: Rà soát mô-đun xử lý sự kiện bàn phím trong mã nguồn.
- Ghi nhận lỗi & Khuyến nghị: Phát hiện điểm nghẽn hệ thống và đề xuất tối ưu.

---

3. Kết Quả Kiểm Thử Chi Tiết
----------------------------

Kịch bản 1: Đóng gói và Biên dịch hệ thống (Build System)
+ Thao tác thực hiện: Chạy lệnh "cmake --build ." bên trong thư mục build.
+ Kết quả: Hệ thống tạo thành công file thực thi tetris.exe.
+ Vấn đề phát hiện: Nếu tiến trình cũ chưa tắt hẳn, trình liên kết sẽ báo lỗi "Permission denied" do file bị khóa. Sau khi tắt tiến trình cũ, build lại bình thường.

Kịch bản 2: Khởi động trò chơi và Kết xuất giao diện (UI Render)
+ Thao tác thực hiện: Kích hoạt tệp build\tetris.exe.
+ Kết quả hiển thị: Khung Console khởi tạo thành công giao diện với cấu trúc:

  TETRIS C++

  +--------------------+
  |                    |
  |                    |  Score: 0
  |                    |  High:  221852983
  |                    |  Level: 1
  |                    |  Lines: 0
  |                    |
  |                    |  Next: I
  |                    |
  |                    |  Arrows: move
  |                    |  W/Up/X: rotate
  |                    |  Z: rotate back
  |                    |  S/Down: soft drop
  |                    |  Space: hard drop
  |                    |  P: pause  R: restart
  |                    |  Q/Esc: quit
  |                    |
  |                    |
  |                    |
  |                    |
  |                    |
  +--------------------+

  Game over. Press R to restart or Q to quit.

+ Trạng thái hệ thống: Chương trình báo Game over và thoát với mã EXIT:-1 khi chạy trong terminal tự động hóa không tương tác.

Kịch bản 3: Rà soát logic ánh xạ phím bấm (Input Mapping Review)
Do môi trường giả lập không gửi được tín hiệu phần cứng trực tiếp, tương tác phím chưa thể xác minh hộp đen. Tuy nhiên, rà soát hộp trắng file src/InputHandler.cpp cho thấy các phím đã định tuyến chuẩn:
- A / D hoặc Mũi tên Trái / Phải: Di chuyển khối sang Trái / Phải.
- S hoặc Mũi tên Xuống: Soft Drop (Hạ khối từ từ).
- W / X hoặc Mũi tên Lên: Xoay khối thuận chiều kim đồng hồ.
- Z: Xoay khối ngược chiều kim đồng hồ.
- Space: Hard Drop (Thả khối rơi lập tức).
- P: Tạm dừng game (Pause).
- R: Chơi lại lượt mới (Restart).
- Q hoặc Esc: Thoát chương trình lập tức (Quit).

---

4. Nhận Xét Và Khuyến Nghị Chuyên Môn
-------------------------------------

[1] Khắc phục lỗi Crash/Thoát Game ngay khi khởi động
- Bản chất vấn đề: Trò chơi tự động báo Game over ngay vòng lặp đầu tiên. Đồng thời, hàm SaveManager::loadHighScore() đang đọc ra giá trị rác khổng lồ (221852983) từ file highscore.dat gây lỗi logic điểm số.
- Giải pháp: Bổ sung hàm khởi tạo giá trị mặc định cho highscore bằng 0 nếu không tìm thấy file hoặc file hỏng. Đặt Breakpoint tại GameLoop::initialize() để kiểm tra điều kiện kích hoạt isGameOver.

[2] Tối ưu hóa trải nghiệm Build (CMake Automation)
- Bản chất vấn đề: Lỗi khóa file "Permission denied" làm gián đoạn việc build lại mã nguồn.
- Giải pháp: Thêm đoạn script Pre-build vào file CMakeLists.txt để tự động tìm và tắt tiến trình tetris.exe đang chạy trước khi biên dịch phiên bản mới:

  if(WIN32)
      add_custom_target(kill_old_process PRE_BUILD
          COMMAND taskkill /f /im tetris.exe 2>NUL || exit 0
          COMMENT "Dang kiem tra va giai phong file thuc thi cu..."
      )
      add_dependencies(${PROJECT_NAME} kill_old_process)
  endif()

[3] Đề xuất mở rộng Kịch bản kiểm thử
- Kiểm thử độ phân giải Console: Kiểm tra hiển thị trên Windows Terminal, CMD, Git Bash vì một số console cũ không tự dịch được màu ANSI, gây lỗi ký tự rác.
- Tách biệt luồng xử lý Input: Khuyến nghị nâng cấp InputHandler sang cơ chế bất đồng bộ (sử dụng luồng std::thread riêng) để phím bấm nhạy hơn, không làm đóng băng chu kỳ cập nhật đồ họa của GameLoop.