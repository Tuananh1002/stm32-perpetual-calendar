#include "button_handler.h"
#include "globals.h"
#include "rtc_module.h"
#include "alarm_module.h"

void doModeAction() {
  if (++mode > 9) { mode = 0; lastTick = millis(); }   // 0..9
  blinkOn = true; lastBlink = millis();
}

void doUpAction() {
  if      (mode == 1) { if (++h  >= 24) h  = 0; }
  else if (mode == 2) { if (++m  >= 60) m  = 0; }
  else if (mode == 3) { if (++s  >= 60) s  = 0; }
  else if (mode == 4) { if (++dd > 31)  dd = 1; }
  else if (mode == 5) { if (++mo > 12)  mo = 1; }
  else if (mode == 6) { yyyy++; }
  else if (mode == 7) { alarmEnabled = true; }
  else if (mode == 8) { if (++alarmH >= 24) alarmH = 0; }  // giờ hẹn
  else if (mode == 9) { if (++alarmM >= 60) alarmM = 0; }  // phút hẹn

  // Chỉnh giờ/ngày (mode 1..6) -> ghi lại vào DS1307
  if (mode >= 1 && mode <= 6) saveToRTC();
}

void doDownAction() {
  if      (mode == 1) { if (--h  < 0)  h  = 23; }
  else if (mode == 2) { if (--m  < 0)  m  = 59; }
  else if (mode == 3) { if (--s  < 0)  s  = 59; }
  else if (mode == 4) { if (--dd < 1)  dd = 31; }
  else if (mode == 5) { if (--mo < 1)  mo = 12; }
  else if (mode == 6) { yyyy--; }
  else if (mode == 7) { alarmEnabled = false; }
  else if (mode == 8) { if (--alarmH < 0)  alarmH = 23; }  // giờ hẹn
  else if (mode == 9) { if (--alarmM < 0)  alarmM = 59; }  // phút hẹn

  // Chỉnh giờ/ngày (mode 1..6) -> ghi lại vào DS1307
  if (mode >= 1 && mode <= 6) saveToRTC();
}

void handleOnOffButton(unsigned long now) {
  bool btnOnOffState = digitalRead(BTN_ONOFF);
  if (btnOnOffState == LOW && lastBtnOnOffState == HIGH && (now - lastBtnOnOff) > 500) {
    lastBtnOnOff = now;
    systemOn = !systemOn;
    if (!systemOn) {
      lcd.noBacklight(); lcd.clear();
      digitalWrite(LED_ALARM, LOW);
      digitalWrite(LED_HOT,   LOW);
      digitalWrite(BUZZER,    LOW);
      buzzerOn = false;
      stopAlarm();
    } else {
      lcd.backlight();
    }
  }
  lastBtnOnOffState = btnOnOffState;
}

void handleButtons(unsigned long now) {
  // --- MODE ---
  bool btnModeState = digitalRead(BTN_MODE);
  if (btnModeState == LOW) {
    if (lastBtnModeState == HIGH) {
      if (alarmRinging) stopAlarm();   // đang kêu -> bấm nút tắt luôn
      holdStartMode = now; lastRepeatMode = now;
      doModeAction();
    } else if (now - holdStartMode > HOLD_DELAY && now - lastRepeatMode > REPEAT_RATE) {
      lastRepeatMode = now; doModeAction();
    }
  }
  lastBtnModeState = btnModeState;

  // --- UP ---
  bool btnUpState = digitalRead(BTN_UP);
  if (btnUpState == LOW) {
    if (lastBtnUpState == HIGH) {
      if (alarmRinging) stopAlarm();
      holdStartUp = now; lastRepeatUp = now;
      doUpAction();
    } else if (now - holdStartUp > HOLD_DELAY && now - lastRepeatUp > REPEAT_RATE) {
      lastRepeatUp = now; doUpAction();
    }
  }
  lastBtnUpState = btnUpState;

  // --- DOWN ---
  bool btnDownState = digitalRead(BTN_DOWN);
  if (btnDownState == LOW) {
    if (lastBtnDownState == HIGH) {
      if (alarmRinging) stopAlarm();
      holdStartDown = now; lastRepeatDown = now;
      doDownAction();
    } else if (now - holdStartDown > HOLD_DELAY && now - lastRepeatDown > REPEAT_RATE) {
      lastRepeatDown = now; doDownAction();
    }
  }
  lastBtnDownState = btnDownState;
}
