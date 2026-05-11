## Tóm tắt phần đóng góp của từng SV

| SV | Nhiệm vụ | Chi tiết |
|---|---|---|
| SV1 | Base code | initBoard, block2Board, boardDelBlock, canMove, gotoxy, vòng lặp main |
| SV2 | removeLine() | Duyệt từ dưới lên, kiểm tra dòng đầy, dịch toàn bộ dòng trên xuống, tăng linesCleared |
| SV3 | Giao diện vuông | printCell() in mỗi ô 2 ký tự ([] , () , ##, ...); gotoxy nhân *2; ẩn con trỏ; panel thông tin bên phải |
| SV4 | Xoay khối | tryRotate() dùng công thức ma trận rotated[j][3-i] = current[i][j], kiểm tra va chạm trước khi áp dụng; nhấn W để xoay |
| SV5 | Tăng tốc độ | Biến speed khởi đầu 300ms; sau mỗi 5 dòng xóa giảm 30ms, tối thiểu 60ms; hiển thị level lên và thông báo "LEVEL UP!" |