#include "globals.h"
#include "rtc_module.h"
#include "lcd_display.h"
#include "alarm_module.h"
#include "button_handler.h"

void setup() {
  Wire.setSDA(PB7);
  Wire.setSCL(PB6);
  Wire.begin();
  lcd.init();
  lcd.backlight();

  pinMode(BTN_MODE,  INPUT_PULLUP);
  pinMode(BTN_UP,    INPUT_PULLUP);
  pinMode(BTN_DOWN,  INPUT_PULLUP);
  pinMode(BTN_ONOFF, INPUT_PULLUP);
  pinMode(LED_HOT,   OUTPUT);
  pinMode(LED_ALARM, OUTPUT);
  pinMode(BUZZER,    OUTPUT);
  digitalWrite(LED_HOT,   LOW);
  digitalWrite(LED_ALARM, LOW);
  digitalWrite(BUZZER,    LOW);

  rtc.begin();

  delay(2000);

  showBootScreen();

  // Đọc giờ từ DS1307 một lần duy nhất, nạp vào biến đếm bằng millis()
  loadFromRTC();

  lastTick = millis();
  lastDHT  = millis();
}

void loop() {
  unsigned long now = millis();

  // --- ON/OFF ---
  handleOnOffButton(now);
  if (!systemOn) { delay(100); return; }

  // --- Đọc DHT11 ---
  if (now - lastDHT >= 10000) {
    lastDHT = now;
    byte t = 0, f = 0;
    if (dht11.read(&t, &f, NULL) == SimpleDHTErrSuccess) {
      temp = (float)t;
      humi = (float)f;
    }
  }

  // --- Kiểm tra quá nhiệt (45°C) ---
  overHeat = (temp > 45.0);
  if (overHeat) {
    showOverHeatScreen();
    if (mode == 0 && now - lastTick >= 1000) {
      lastTick += 1000;
      if (++s >= 60) { s = 0; if (++m >= 60) { m = 0; if (++h >= 24) h = 0; } }
    }
    delay(100);
    return;
  }

  // --- Tắt LED_HOT khi hết quá nhiệt ---
  digitalWrite(LED_HOT, LOW);

  // --- Đếm giờ (bằng millis, KHÔNG đọc DS1307) ---
  if (mode == 0 && now - lastTick >= 1000) {
    lastTick += 1000;
    if (++s >= 60) { s = 0; if (++m >= 60) { m = 0; if (++h >= 24) h = 0; } }
  }

  // --- Blink ---
  if (now - lastBlink >= 400) { lastBlink = now; blinkOn = !blinkOn; }

  // --- Buttons: MODE / UP / DOWN ---
  handleButtons(now);

  // --- Alarm ---
  updateAlarm(now);

  // --- LCD chính ---
  drawMainScreen();

  delay(50);
}
