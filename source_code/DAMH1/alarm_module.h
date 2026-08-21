#ifndef ALARM_MODULE_H
#define ALARM_MODULE_H

// Tắt chuông báo thức (buzzer + LED alarm).
void stopAlarm();

// Kiểm tra thời điểm kích hoạt báo thức và xử lý nhịp kêu (bíp ngắt quãng).
// Gọi trong loop() mỗi vòng lặp, truyền vào millis() hiện tại.
void updateAlarm(unsigned long now);

#endif
