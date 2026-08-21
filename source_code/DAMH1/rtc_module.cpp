#include "rtc_module.h"
#include "globals.h"

void saveToRTC() {
  rtc.adjust(DateTime(yyyy, mo, dd, h, m, s));
  rtc.writenvram(NVRAM_YEAR_ADDR, (uint8_t)(yyyy - 2000));  // vd 2026 -> 26
}

void loadFromRTC() {
  if (rtc.isrunning()) {
    DateTime t = rtc.now();
    yyyy = t.year();   // thanh ghi năm có thể lỗi -> ghi đè bằng NVRAM bên dưới
    mo   = t.month();
    dd   = t.day();
    h    = t.hour();
    m    = t.minute();
    s    = t.second();

    // Lấy năm từ NVRAM thay cho thanh ghi năm bị lỗi
    uint8_t ny = rtc.readnvram(NVRAM_YEAR_ADDR);
    if (ny >= 20 && ny <= 99) yyyy = 2000 + ny;   // hợp lệ (2020..2099) thì dùng
    // nếu NVRAM rác (chưa từng lưu) thì giữ nguyên yyyy mặc định
  } else {
    // DS1307 mất pin / lần đầu chạy -> dùng giờ mặc định rồi ghi vào IC + NVRAM
    saveToRTC();
  }
}
