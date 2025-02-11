# EmbarcaTech Final Project

## Overview
This project is the final assignment of the **EmbarcaTech** course, utilizing a **Raspberry Pi RP2040** on a **BitDogLab** board. It is a **smart weather station** capable of automatically triggering a relay based on environmental conditions, using temperature, humidity, and light sensors.

## Features
- **Temperature and Humidity Monitoring** using a **DHT22 sensor**
- **Light Intensity Measurement** with an **LDR sensor**
- **Automatic Relay Control** based on environmental conditions
- **OLED Display Output** via **I2C communication**
- **Buzzer and LED Alerts** for abnormal conditions

## Hardware Requirements
- **BitDogLab** (RP2040-based board)
- **DHT22** (Temperature & Humidity sensor)
- **LDR Sensor** (Light sensor)
- **OLED Display** (SSD1306, I2C)
- **Relay Module**
- **Buzzer and LED Indicators**

## Pin Configuration
```c
#define LDR_PIN 28 // GPIO28 (ADC2)
#define DHT_PIN 16 // GPIO16
#define BUZZER1 10
#define BUZZER2 21
#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12
#define RELAY_PIN 17
#define SDA_PIN 14
#define SCL_PIN 15
#define I2C_PORT i2c1
```

## Installation
1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/EmbarcaTech-Final-Project.git
   ```
2. Install dependencies (if needed for your development environment).
3. Compile and flash the firmware to the BitDogLab board.

## Code Structure
- **`main.c`** → Core logic for reading sensors and controlling outputs
- **`dht22.h`** → Header file for DHT22 sensor
- **`ssd1306.h`** → Header file for OLED display
- **`hardware/adc.h`** → ADC configuration for the LDR sensor

## Simulation

<img src="https://github.com/mauriceliocb/EmbarcaTech-WeatherStation/blob/main/schematic_wokwi.png" width=40% height=40%>

You can run this project using the **Wokwi simulator** at the following link:
[Wokwi Simulation](https://wokwi.com/projects/421373840735077377)

## Library References
### SSD1306 OLED Display Library
**DASCHR.** SSD1306 OLED Display Library for Raspberry Pi Pico. Available at:  
[https://github.com/daschr/pico-ssd1306](https://github.com/daschr/pico-ssd1306)

### DHT22 Sensor Library
**VmileA.** pico_dht - DHT22 Library for Raspberry Pi Pico. Available at:  
[https://github.com/vmilea/pico_dht](https://github.com/vmilea/pico_dht)

## BitDogLab Board
For more details about the **BitDogLab** board, visit its GitHub repository:
[BitDogLab GitHub](https://github.com/BitDogLab/BitDogLab)

## License
This project is licensed under the MIT License.

---

🚀 Developed for the **EmbarcaTech** course using the **BitDogLab (RP2040)**.
