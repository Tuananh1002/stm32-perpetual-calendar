# 🕐 STM32 Perpetual Calendar with Environmental Monitoring & Alarm

## 📖 System Description

This project presents an embedded **perpetual calendar and clock system** built on an **STM32F103C8T6 (Blue Pill)** microcontroller.

The system keeps accurate real-time date and time using a **DS1307 RTC** module (battery-backed), while continuously monitoring ambient **temperature and humidity** through a **DHT11** sensor. All information is displayed on a **20x4 I2C LCD**, including the current date, time, temperature, humidity, and alarm status.

Users can configure the time, date, and a daily alarm directly through a **4-button interface** (ON/OFF, MODE, UP, DOWN), with press-and-hold support for fast value adjustment. The system also includes an **overheat protection feature**, automatically triggering a visual and audio warning when temperature exceeds a safe threshold, and a **configurable alarm** with automatic buzzer shutoff.

Designed as a university embedded systems capstone project, this solution demonstrates practical application of **I2C communication**, **non-blocking timing with millis()**, **state-machine-based UI navigation**, and **modular firmware architecture**.

---

## 🏗️ System Architecture Diagram

<p align="center">
  <!-- TODO: chèn ảnh sơ đồ khối / kiến trúc hệ thống (RTC - MCU - LCD - Sensor - Buttons) -->
</p>

---

## 🔁 Operation Flowchart

<p align="center">
  <!-- TODO: chèn ảnh lưu đồ thuật toán (flowchart) từ báo cáo -->
</p>

---

## 🔧 Hardware Setup

<p align="center">
  <!-- TODO: chèn ảnh mạch thực tế / breadboard / PCB của board chính -->
</p>

---

## 🖥️ Display in Operation

<p align="center">
  <!-- TODO: chèn ảnh màn hình LCD lúc hiển thị ngày giờ / chế độ chỉnh alarm -->
</p>

---

## ✨ Key Features

- ⏰ Real-time clock keeping via DS1307 (I2C), with battery backup across power loss
- 🌡️ Temperature & humidity monitoring via DHT11, polled every 10 seconds
- 🔥 Overheat protection — automatic warning screen + buzzer above 45°C
- 🔔 Configurable alarm — set hour/minute, auto-off after 30 seconds
- 🎛️ 4-button interface with press-and-hold auto-repeat for fast setting adjustment
- 📟 20x4 I2C LCD showing date, time, temperature, humidity, and alarm status simultaneously

---

## 🧩 Hardware Components

| Component | Purpose |
|---|---|
| STM32F103C8T6 (Blue Pill) | Main MCU |
| DS1307 | Real-time clock (I2C) |
| DHT11 | Temperature & humidity sensor |
| LCD 20x4 (I2C, PCF8574 backpack) | Display |
| 4x push buttons | ON/OFF, MODE, UP, DOWN |
| Buzzer | Alarm & overheat alert |
| LEDs | Overheat indicator, alarm indicator |

---

## 🗂️ Firmware Structure

The firmware is organized into functional modules rather than a single monolithic sketch:

```
source_code/DAMH1/
├── DAMH1.ino             # setup() and loop() only
├── globals.h/.cpp        # shared state, hardware objects, pin definitions
├── rtc_module.h/.cpp     # DS1307 read/write, NVRAM year workaround
├── lcd_display.h/.cpp    # all LCD rendering (main, boot, overheat screens)
├── alarm_module.h/.cpp   # alarm trigger logic and beep pattern
└── button_handler.h/.cpp # button reading, debounce, hold-to-repeat
```

**Libraries used:** `Wire`, `LiquidCrystal_I2C`, `SimpleDHT`, `RTClib`

---

## 🧠 Key Implementation Details

- **Year storage workaround:** the DS1307's native year register is unreliable on some clone modules, so the year is instead written to and read from the DS1307's onboard NVRAM.
- **Non-blocking timing:** all timers (clock tick, blink, DHT polling, button hold/repeat) use `millis()` instead of `delay()`, keeping the UI responsive while the buzzer, alarm, and sensor polling run concurrently.
- **Press-and-hold auto-repeat:** holding UP/DOWN past 600ms triggers repeated increments every 150ms.
- **State machine navigation:** a single `mode` variable (0–9) drives which field is being edited and centralizes button handling logic.

---

## 📁 Repository Structure

```
├── source_code/   # STM32 firmware (Arduino framework)
├── proteus/        # Proteus simulation files
├── wokwi/           # Wokwi simulation files
├── report/          # Full defense report (Vietnamese)
└── images/          # Circuit photos, demo screenshots
```

---

## 👤 Author

Third-year Telecommunications Engineering student, Ho Chi Minh City University of Technology and Education (HCMUTE).
