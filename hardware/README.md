# Hardware

Circuit design, pin connections, and hardware setup for the Crop Prediction System.

## Components

| Component | Key Specs |
|---|---|
| **ESP WROOM-32** | Dual-core 240 MHz, 520 KB SRAM, 34 GPIO, 12-bit ADC |
| **NPK Sensor** | RS485 / Modbus RTU, 0–1999 mg/kg range, ±2% accuracy |
| **TTL-RS485 Converter** | MAX485 chip, half-duplex, up to 1200 m range |
| **Capacitive Moisture Sensor** | Analog output, 3.3V–5V, ~5 mA operating current |
| **12V DC Adapter** | Centre-positive barrel jack, 100–240V AC input |

## Wiring Summary

- **NPK Sensor A/B** → TTL-RS485 Converter A/B → ESP32 UART2 (GPIO 16 RX / GPIO 17 TX)
- **Moisture Sensor OUT** → ESP32 GPIO 34 (ADC)
- **NPK Sensor & RS485 Converter** powered from 12V DC adapter
- **ESP32** powered via USB or regulated 5V from the 12V supply

## Hardware Setup

![Hardware Setup 1](../images/Hardware%20Setup%201.jpg)

![Hardware Setup 2](../images/Hardware%20Setup%202.jpg)

## Circuit Notes

- The ESP32 runs at 3.3V logic. The TTL-RS485 converter bridges the 3.3V UART signals to RS485 differential levels required by the NPK sensor.
- The NPK sensor requires 5–30V DC; power it directly from the 12V adapter.
- The capacitive moisture sensor is preferred over resistive types as it does not corrode in soil.
