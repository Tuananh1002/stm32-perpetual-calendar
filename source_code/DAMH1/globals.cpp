#include "globals.h"

// ===== Hardware objects =====
LiquidCrystal_I2C lcd(0x27, 20, 4);
SimpleDHT11 dht11(PA15);
RTC_DS1307 rtc;

// ===== Date & time =====
int dd = 28, mo = 5, yyyy = 2026;
int h = 18, m = 5, s = 0;
int mode = 0;

// ===== Alarm settings & state =====
int alarmH = 6, alarmM = 30;
bool alarmEnabled = false;
bool alarmRinging = false;
unsigned long alarmRingStart = 0;
unsigned long lastAlarmBeep  = 0;
bool alarmBeepOn = false;
bool alarmTriggeredThisMinute = false;

// ===== Timers =====
unsigned long lastTick     = 0;
unsigned long lastDHT      = 0;
unsigned long lastBlink    = 0;
unsigned long lastBtnOnOff = 0;
unsigned long buzzerStart  = 0;

unsigned long holdStartMode  = 0;
unsigned long holdStartUp    = 0;
unsigned long holdStartDown  = 0;
unsigned long lastRepeatMode = 0;
unsigned long lastRepeatUp   = 0;
unsigned long lastRepeatDown = 0;

unsigned long lastOverHeatBlink = 0;

// ===== State flags =====
bool buzzerOn        = false;
bool blinkOn         = true;
bool overHeat        = false;
bool overHeatBlinkOn = true;
bool lastBtnModeState  = HIGH;
bool lastBtnUpState    = HIGH;
bool lastBtnDownState  = HIGH;
bool lastBtnOnOffState = HIGH;
bool systemOn = true;

// ===== Sensor readings =====
float temp = 0, humi = 0;
