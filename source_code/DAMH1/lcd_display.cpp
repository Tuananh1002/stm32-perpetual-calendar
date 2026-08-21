#include "lcd_display.h"
#include "globals.h"

void printField(int val, bool isEditing) {
  if (isEditing && !blinkOn) { lcd.print("  "); return; }
  if (val < 10) lcd.print("0");
  lcd.print(val);
}

void printYear(int val, bool isEditing) {
  if (isEditing && !blinkOn) lcd.print("    ");
  else lcd.print(val);
}

void showBootScreen() {
  lcd.clear();
  lcd.setCursor(2, 1);
  lcd.print("REAL TIME CLOCK");
  lcd.setCursor(6, 2);
  lcd.print("Starting...");
  delay(1500);

  for (int i = 2; i >= 0; i--) {
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    lcd.setCursor(8, 3);
    lcd.print(i);
    delay(1000);
  }
  lcd.clear();
}

void showOverHeatScreen() {
  if (millis() - lastOverHeatBlink >= 500) {
    lastOverHeatBlink = millis();
    overHeatBlinkOn = !overHeatBlinkOn;
    lcd.clear();
    if (overHeatBlinkOn) {
      lcd.setCursor(3, 0);  lcd.print("!! WARNING !!");
      lcd.setCursor(1, 1);  lcd.print("SYSTEM  TOO  HOT!");
      lcd.setCursor(0, 2);  lcd.print("NEED COOLING NOW!");
      lcd.setCursor(3, 3);
      lcd.print("TEMP: ");
      lcd.print(temp, 1);
      lcd.print((char)223);
      lcd.print("C");
    }
  }

  digitalWrite(LED_HOT, HIGH);  // chỉ LED_HOT, không đụng LED_ALARM

  if (!buzzerOn) {
    buzzerOn = true;
    buzzerStart = millis();
    digitalWrite(BUZZER, HIGH);
  }
  if (buzzerOn && (millis() - buzzerStart >= 300)) {
    buzzerOn = false;
    digitalWrite(BUZZER, LOW);
  }
}

void drawMainScreen() {
  lcd.setCursor(0, 0); lcd.print("DATE : ");
  printField(dd, mode==4); lcd.print("/");
  printField(mo, mode==5); lcd.print("/");
  printYear(yyyy, mode==6);

  // Góc trên phải: ký tự chuông nếu alarm bật
  lcd.setCursor(19, 0);
  if (alarmEnabled) lcd.print("*");
  else              lcd.print(" ");

  lcd.setCursor(0, 1); lcd.print("TIME : ");
  printField(h, mode==1); lcd.print(":");
  printField(m, mode==2); lcd.print(":");
  printField(s, mode==3);

  lcd.setCursor(0, 2); lcd.print("TEMP : ");
  lcd.print(temp, 1); lcd.print((char)223); lcd.print("C   ");

  lcd.setCursor(0, 3); lcd.print("HUMI : ");
  lcd.print(humi, 1); lcd.print("%   ");

  // Khi đang ở mode chỉnh báo thức (7/8/9) -> hiện giờ hẹn ở dòng 4
  if (mode == 7 || mode == 8 || mode == 9) {
    lcd.setCursor(0, 3);
    lcd.print("ALARM: ");
    printField(alarmH, mode==8); lcd.print(":");
    printField(alarmM, mode==9);
    lcd.print(alarmEnabled ? " ON " : " OFF");
    lcd.print("  ");
  }

  // Label mode ở góc dưới phải
  lcd.setCursor(14, 3);
  const char* labels[] = {"      ","GIO   ","PHUT  ","GIAY  ","NGAY  ",
                          "THANG ","NAM   ","AL:ON ","AL: h","AL: m"};
  lcd.print(labels[mode]);
}
