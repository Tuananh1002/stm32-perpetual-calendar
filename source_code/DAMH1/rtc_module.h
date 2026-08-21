#ifndef RTC_MODULE_H
#define RTC_MODULE_H

// Ghi giờ hiện tại (biến toàn cục) vào DS1307.
// Năm được lưu thêm vào NVRAM để né lỗi thanh ghi năm.
void saveToRTC();

// Đọc giờ từ DS1307 vào biến toàn cục lúc khởi động.
// Nếu RTC mất pin / chưa từng chạy -> ghi giờ mặc định vào IC.
void loadFromRTC();

#endif
