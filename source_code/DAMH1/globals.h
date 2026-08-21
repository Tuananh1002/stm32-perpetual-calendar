#ifndef GLOBALS_H
#define GLOBALS_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>
#include <RTClib.h>

// ===== Hardware objects =====
extern LiquidCrystal_I2C lcd;
extern SimpleDHT11 dht11;
extern RTC_DS1307 rtc;

// ===== Pin definitions =====
#define BTN_ONOFF PA1
#define BTN_MODE  PA2
#define BTN_UP    PA3
#define BTN_DOWN  PA4
#define LED_HOT   PA12
#define LED_ALARM PA5
#define BUZZER    PA8

// ===== Timing / config constants =====
#define HOLD_DELAY      600
#define REPEAT_RATE     150
#define NVRAM_YEAR_ADDR 0
#define ALARM_DURATION  30000

// ===== Date & time =====
extern int dd, mo, yyyy;
extern int h, m, s;
extern int mode;

// ===== Alarm settings & state =====
extern int alarmH, alarmM;
extern bool alarmEnabled;
extern bool alarmRinging;
extern unsigned long alarmRingStart;
extern unsigned long lastAlarmBeep;
extern bool alarmBeepOn;
extern bool alarmTriggeredThisMinute;

// ===== Timers =====
extern unsigned long lastTick;
extern unsigned long lastDHT;
extern unsigned long lastBlink;
extern unsigned long lastBtnOnOff;
extern unsigned long buzzerStart;
extern unsigned long holdStartMode, holdStartUp, holdStartDown;
extern unsigned long lastRepeatMode, lastRepeatUp, lastRepeatDown;
extern unsigned long lastOverHeatBlink;

// ===== State flags =====
extern bool buzzerOn;
extern bool blinkOn;
extern bool overHeat;
extern bool overHeatBlinkOn;
extern bool lastBtnModeState, lastBtnUpState, lastBtnDownState, lastBtnOnOffState;
extern bool systemOn;

// ===== Sensor readings =====
extern float temp, humi;

#endif
