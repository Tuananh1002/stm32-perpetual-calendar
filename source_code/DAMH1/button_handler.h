#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

// Hành động khi bấm nút MODE / UP / DOWN (đổi giá trị theo mode hiện tại).
void doModeAction();
void doUpAction();
void doDownAction();

// Đọc & xử lý 3 nút MODE/UP/DOWN, bao gồm nhấn-giữ để tăng nhanh.
void handleButtons(unsigned long now);

// Đọc & xử lý nút ON/OFF (bật/tắt toàn hệ thống).
void handleOnOffButton(unsigned long now);

#endif
