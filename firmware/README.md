# Firmware

Arduino sketch for the ESP32-based crop prediction system.

## File

- **`main.ino`** — Main firmware. Handles sensor initialization, Modbus RTU communication, moving average filtering, and rule-based crop prediction.

## Dependencies

- [Arduino IDE](https://www.arduino.cc/en/software) (v2.x recommended)
- **ModbusMaster** library — for RS485/Modbus RTU communication with the NPK sensor

Install via Arduino Library Manager: `Sketch → Include Library → Manage Libraries → search "ModbusMaster"`

## Pin Configuration

| Pin | Connected To |
|-----|--------------|
| GPIO 16 (RX2) | TTL-RS485 Converter RX |
| GPIO 17 (TX2) | TTL-RS485 Converter TX |
| GPIO 34 | Capacitive Moisture Sensor (Analog) |

## How It Works

1. **Sensor Init** — ESP32 sets up UART2 for Modbus RTU at 9600 baud and initializes the ADC pin for moisture.
2. **Buffer Init** — Fills a rolling window buffer with initial sensor readings.
3. **Loop** — Every cycle, reads N, P, K (via Modbus), reads moisture (analog), validates readings against a spike threshold, updates rolling buffers, computes moving averages, and calls the prediction function.
4. **Prediction** — Compares averaged values against crop-specific thresholds and prints the suggested crop to Serial Monitor.

## Flashing

1. Open `main.ino` in Arduino IDE.
2. Select board: `ESP32 Dev Module`.
3. Set baud rate to `9600` in Serial Monitor.
4. Upload and open Serial Monitor to view live readings and crop predictions.
