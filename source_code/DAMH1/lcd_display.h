#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

// In một trường số 2 chữ số, nhấp nháy khi đang chỉnh (isEditing = true).
void printField(int val, bool isEditing);

// In năm (4 chữ số), nhấp nháy khi đang chỉnh.
void printYear(int val, bool isEditing);

// Màn hình khởi động (đếm ngược 3-2-1).
void showBootScreen();

// Màn hình cảnh báo quá nhiệt (nhấp nháy + buzzer tít ngắn).
void showOverHeatScreen();

// Vẽ màn hình chính: ngày/giờ/nhiệt độ/độ ẩm/báo thức/label mode.
void drawMainScreen();

#endif
