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

## Functionality
### Sensor Readings
```c
uint16_t read_lux();
float adc_to_lux(uint16_t adc_value);
int dht22_read(int pin, float *temperature, float *humidity);
```

### Alerts and Display
```c
void buzzer_alerta(int ativar);
void alerta(int ativar);
void exibir_no_oled(float temperature, float humidity, float lux, int condicao_adversa);
```

### Relay Control
```c
if (condicao_adversa) {
    gpio_put(RELAY_PIN, 1); // Activate relay
} else {
    gpio_put(RELAY_PIN, 0); // Deactivate relay
}
```

## Usage
- The system continuously monitors temperature, humidity, and light levels.
- If conditions exceed safe thresholds, an alert is triggered (LED & Buzzer), and the relay is activated.
- Data is displayed on the OLED screen.

## License
This project is licensed under the MIT License.

---

🚀 Developed for the **EmbarcaTech** course using the **BitDogLab (RP2040)**.
