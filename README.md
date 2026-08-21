###### \# 🕐 STM32 Perpetual Calendar with Temperature/Humidity Monitoring \& Alarm

###### 

###### A perpetual calendar and clock system built on STM32F103C8T6, featuring real-time clock keeping, environmental monitoring, an overheat warning system, and a configurable alarm — developed as a university embedded systems capstone project (DAMH1).

###### 

###### \## 📖 Overview

###### 

###### The device displays real-time date, time, temperature, and humidity on a 20x4 I2C LCD. Time is kept accurate using a DS1307 RTC module (battery-backed), with the year stored separately in RTC NVRAM to work around a known register limitation. Users navigate settings (time, date, alarm) via push buttons, and the system triggers visual/audio warnings when ambient temperature exceeds a safe threshold.

###### 

###### \## ✨ Features

###### 

###### \- \*\*Real-time clock\*\* — DS1307 RTC with I2C, time kept between power cycles via battery backup

###### \- \*\*Temperature \& humidity monitoring\*\* — DHT11 sensor, polled every 10 seconds

###### \- \*\*Overheat protection\*\* — automatic warning screen + buzzer when temperature exceeds 45°C

###### \- \*\*Configurable alarm\*\* — set hour/minute, auto-off after 30 seconds, interruptible by any button press

###### \- \*\*4-button interface\*\* — ON/OFF, MODE (cycle settings), UP, DOWN (with press-and-hold auto-repeat for fast adjustment)

###### \- \*\*20x4 I2C LCD display\*\* — date, time, temperature, humidity, and alarm status shown simultaneously

###### 

###### \## 🔧 Hardware

###### 

###### | Component | Purpose |

###### |---|---|

###### | STM32F103C8T6 (Blue Pill) | Main MCU |

###### | DS1307 | Real-time clock (I2C) |

###### | DHT11 | Temperature \& humidity sensor |

###### | LCD 20x4 (I2C, PCF8574 backpack) | Display |

###### | 4x push buttons | ON/OFF, MODE, UP, DOWN |

###### | Buzzer | Alarm \& overheat alert |

###### | LEDs | Overheat indicator, alarm indicator |

###### 

###### \## 🏗️ System Architecture

###### 

###### ```

###### \[DS1307 RTC] --I2C--> \[STM32F103C8T6] --I2C--> \[LCD 20x4]

###### \[DHT11]       --GPIO-->      |

###### \[Buttons]     --GPIO-->      |

###### &#x20;                             +--GPIO--> \[Buzzer, LEDs]

###### ```

###### 

###### \## 🗂️ Software Structure

###### 

###### The firmware is organized into functional modules rather than a single monolithic sketch:

###### 

###### ```

###### source\_code/DAMH1/

###### ├── DAMH1.ino            # setup() and loop() only

###### ├── globals.h/.cpp       # shared state, hardware objects, pin definitions

###### ├── rtc\_module.h/.cpp    # DS1307 read/write, NVRAM year workaround

###### ├── lcd\_display.h/.cpp   # all LCD rendering (main screen, boot screen, overheat screen)

###### ├── alarm\_module.h/.cpp  # alarm trigger logic and beep pattern

###### └── button\_handler.h/.cpp # button reading, debounce, hold-to-repeat, mode actions

###### ```

###### 

###### \*\*Libraries used:\*\* `Wire`, `LiquidCrystal\_I2C`, `SimpleDHT`, `RTClib`

###### 

###### \## 🧠 Key Implementation Details

###### 

###### \- \*\*Year storage workaround:\*\* the DS1307's native year register is unreliable on some clone modules, so the year is instead written to and read from the DS1307's onboard NVRAM.

###### \- \*\*Non-blocking timing:\*\* all timers (clock tick, blink, DHT polling, button hold/repeat) use `millis()` comparisons instead of `delay()`, so the UI stays responsive while the buzzer, alarm, and sensor polling run concurrently.

###### \- \*\*Press-and-hold auto-repeat:\*\* holding UP/DOWN past 600ms triggers repeated increments every 150ms, so setting values like year doesn't require dozens of individual presses.

###### \- \*\*State machine navigation:\*\* a single `mode` variable (0–9) drives which field is being edited (time, date, alarm) and which LCD blink target is active, keeping button handling logic centralized.

###### 

###### \## 📁 Repository Structure

###### 

###### ```

###### ├── source\_code/     # STM32 firmware (Arduino framework)

###### ├── proteus/          # Proteus simulation files

###### ├── wokwi/             # Wokwi simulation files

###### ├── report/            # Full defense report (Vietnamese)

###### └── images/            # Circuit photos, demo screenshots

###### ```

###### 

###### \## 👤 Author

###### 

###### Third-year Telecommunications Engineering student, Ho Chi Minh City University of Technology and Education (HCMUTE).

