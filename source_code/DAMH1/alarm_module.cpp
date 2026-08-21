#include "alarm_module.h"
#include "globals.h"

void stopAlarm() {
  alarmRinging = false;
  alarmBeepOn  = false;
  digitalWrite(BUZZER,    LOW);
  digitalWrite(LED_ALARM, LOW);
}

void updateAlarm(unsigned long now) {
  // --- Kích hoạt báo thức khi tới giờ hẹn ---
  if (alarmEnabled && h == alarmH && m == alarmM && s == 0
      && !alarmRinging && !alarmTriggeredThisMinute) {
    alarmRinging = true;
    alarmTriggeredThisMinute = true;
    alarmRingStart = now;
    lastAlarmBeep  = now;
    alarmBeepOn    = false;
  }
  // Reset cờ khi qua giây khác (cho phép lần hẹn sau)
  if (s != 0) alarmTriggeredThisMinute = false;

  // --- Xử lý chuông báo thức đang kêu (bíp ngắt quãng) ---
  if (alarmRinging) {
    // tự tắt sau ALARM_DURATION
    if (now - alarmRingStart >= ALARM_DURATION) {
      stopAlarm();
    } else if (now - lastAlarmBeep >= 250) {  // nhịp bíp 250ms
      lastAlarmBeep = now;
      alarmBeepOn = !alarmBeepOn;
      digitalWrite(BUZZER,    alarmBeepOn ? HIGH : LOW);
      digitalWrite(LED_ALARM, alarmBeepOn ? HIGH : LOW);
    }
  }
}
