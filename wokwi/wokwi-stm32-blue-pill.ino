#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define DHTPIN    PA15

#define BTN_ONOFF PA0
#define BTN_MODE  PA1
#define BTN_UP    PA3
#define BTN_DOWN  PA2

#define LED_HOT   PA12
#define LED_ALARM PA5
#define BUZZER    PA8

DHT dht(DHTPIN, DHT22);

int dd = 16, mo = 4, yyyy = 2026;
int h = 10, m = 30, s = 0;

int mode = 0;

unsigned long lastTick     = 0;
unsigned long lastDHT      = 0;
unsigned long lastBtnMode  = 0;
unsigned long lastBtnUp    = 0;
unsigned long lastBtnDown  = 0;
unsigned long lastBlink    = 0;
unsigned long lastBtnOnOff = 0;
bool blinkOn = true;

float temp = 0, humi = 0;
bool lastBtnModeState  = HIGH;
bool lastBtnUpState    = HIGH;
bool lastBtnDownState  = HIGH;
bool lastBtnOnOffState = HIGH;
bool systemOn = true;

void setup() {
  Wire.setSDA(PB7);
  Wire.setSCL(PB6);
  Wire.begin();

  lcd.init();
  lcd.backlight();
  lcd.clear();

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

  dht.begin();

  lastTick = millis();
  lastDHT  = millis();
}

void printField(int val, bool isEditing) {
  if (isEditing && !blinkOn) {
    lcd.print("  ");
  } else {
    if (val < 10) lcd.print("0");
    lcd.print(val);
  }
}

void printYear(int val, bool isEditing) {
  if (isEditing && !blinkOn) {
    lcd.print("    ");
  } else {
    lcd.print(val);
  }
}

void loop() {
  unsigned long now = millis();

  // Nút ON/OFF toggle
  bool btnOnOffState = digitalRead(BTN_ONOFF);
  if (btnOnOffState == LOW && lastBtnOnOffState == HIGH && (now - lastBtnOnOff) > 500) {
    lastBtnOnOff = now;
    systemOn = !systemOn;
    if (!systemOn) {
      lcd.noBacklight();
      lcd.clear();
      digitalWrite(LED_ALARM, LOW);
      digitalWrite(BUZZER,    LOW);
    } else {
      lcd.backlight();
    }
  }
  lastBtnOnOffState = btnOnOffState;

  if (!systemOn) {
    delay(100);
    return;
  }

  // Đếm giây khi không ở mode chỉnh
  if (mode == 0 && now - lastTick >= 1000) {
    lastTick += 1000;
    s++;
    if (s >= 60) { s = 0; m++; }
    if (m >= 60) { m = 0; h++; }
    if (h >= 24) h = 0;
  }

  // Blink mỗi 400ms
  if (now - lastBlink >= 400) {
    lastBlink = now;
    blinkOn = !blinkOn;
  }

  // Nút MODE
  bool btnModeState = digitalRead(BTN_MODE);
  if (btnModeState == LOW && lastBtnModeState == HIGH && (now - lastBtnMode) > 200) {
    lastBtnMode = now;
    mode++;
    if (mode > 6) {
      mode = 0;
      lastTick = millis();
    }
    blinkOn = true;
    lastBlink = now;
  }
  lastBtnModeState = btnModeState;

  // Nút UP
  bool btnUpState = digitalRead(BTN_UP);
  if (btnUpState == LOW && lastBtnUpState == HIGH && (now - lastBtnUp) > 200) {
    lastBtnUp = now;
    if      (mode == 0) { h++;    if (h  >= 24) h  = 0;  }
    else if (mode == 1) { h++;    if (h  >= 24) h  = 0;  }
    else if (mode == 2) { m++;    if (m  >= 60) m  = 0;  }
    else if (mode == 3) { s++;    if (s  >= 60) s  = 0;  }
    else if (mode == 4) { dd++;   if (dd > 31)  dd = 1;  }
    else if (mode == 5) { mo++;   if (mo > 12)  mo = 1;  }
    else if (mode == 6) { yyyy++;                         }
  }
  lastBtnUpState = btnUpState;

  // Nút DOWN
  bool btnDownState = digitalRead(BTN_DOWN);
  if (btnDownState == LOW && lastBtnDownState == HIGH && (now - lastBtnDown) > 200) {
    lastBtnDown = now;
    if      (mode == 0) { h--;    if (h  < 0)  h  = 23; }
    else if (mode == 1) { h--;    if (h  < 0)  h  = 23; }
    else if (mode == 2) { m--;    if (m  < 0)  m  = 59; }
    else if (mode == 3) { s--;    if (s  < 0)  s  = 59; }
    else if (mode == 4) { dd--;   if (dd < 1)  dd = 31; }
    else if (mode == 5) { mo--;   if (mo < 1)  mo = 12; }
    else if (mode == 6) { yyyy--;                        }
  }
  lastBtnDownState = btnDownState;

  // Đọc DHT mỗi 5 giây
  if (now - lastDHT >= 5000) {
    lastDHT = now;
    float t = dht.readTemperature();
    float f = dht.readHumidity();
    if (!isnan(t)) temp = t;
    if (!isnan(f)) humi = f;
  }


 // LED_HOT sáng khi quá nhiệt
  digitalWrite(LED_HOT, temp > 40.0 ? HIGH : LOW);

  // Buzzer + LED_ALARM kêu/sáng đầu mỗi giờ
  if (m == 0 && s == 0) {
    digitalWrite(LED_ALARM, HIGH);
    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);
    digitalWrite(LED_ALARM, LOW);
  }
  // Hiển thị
  lcd.setCursor(0, 0);
  lcd.print("DATE : ");
  printField(dd,   mode == 4);
  lcd.print("/");
  printField(mo,   mode == 5);
  lcd.print("/");
  printYear(yyyy,  mode == 6);

  lcd.setCursor(0, 1);
  lcd.print("TIME : ");
  printField(h, mode == 1);
  lcd.print(":");
  printField(m, mode == 2);
  lcd.print(":");
  printField(s, mode == 3);

  lcd.setCursor(0, 2);
  lcd.print("TEMP : ");
  lcd.print(temp, 1);
  lcd.print((char)223);
  lcd.print("C   ");

  lcd.setCursor(0, 3);
  lcd.print("HUMI : ");
  lcd.print(humi, 1);
  lcd.print("%   ");

  // Indicator mode
  lcd.setCursor(14, 3);
  if      (mode == 0) lcd.print("      ");
  else if (mode == 1) lcd.print("GIO   ");
  else if (mode == 2) lcd.print("PHUT  ");
  else if (mode == 3) lcd.print("GIAY  ");
  else if (mode == 4) lcd.print("NGAY  ");
  else if (mode == 5) lcd.print("THANG ");
  else if (mode == 6) lcd.print("NAM   ");

  delay(100);
}