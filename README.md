# Crop Prediction System Using NPK Sensor

> IoT-Based Soil Monitoring & Crop Recommendation System — ESP32 + RS485 NPK Sensor + Edge Computing

---

## Overview

Traditional farming relies on guesswork for crop selection, leading to poor yields and resource waste. This project presents a **real-time, offline crop prediction system** built on the ESP32 microcontroller that reads soil Nitrogen (N), Phosphorus (P), Potassium (K), and moisture levels, then recommends the most suitable crop using a rule-based decision algorithm — entirely at the edge, no cloud required.

Designed for low-cost, rural deployment, the system is modular, energy-efficient, and future-ready for ML-based upgrades.

---

## Key Features

- Real-time NPK and soil moisture sensing
- Modbus RTU communication over RS485
- Moving average filter for noise-stable readings
- Rule-based crop prediction (Wheat, Rice, Millet, Maize, Peas, Tomato, and more)
- Fully offline — no internet or cloud dependency
- Serial Monitor output via Arduino IDE
- Low total cost: **Rs. 5128**

---

## System Architecture

![System Overview](images/System%20Overview%20Diagram.png)

![Block Diagram](images/Block%20Diagram.png)

The ESP32 initializes both sensors, collects data, applies a moving average filter, runs the prediction logic, and prints the recommended crop to the Serial Monitor.

---

## Code Flowchart

![Code Flowchart](images/Code%20Flowchart.png)

---

## Hardware Setup

![Hardware Setup 1](images/Hardware%20Setup%201.jpg)

![Hardware Setup 2](images/Hardware%20Setup%202.jpg)

---

## Hardware Components

| Component | Specification | Cost (Rs.) |
|---|---|---|
| ESP WROOM-32 | Dual-core 240 MHz, Wi-Fi, BT, 34 GPIO | 600 |
| NPK Sensor (RS485) | 0–1999 mg/kg, ±2%, Modbus RTU | 4088 |
| TTL to RS485 Converter | MAX485, up to 250 kbps | 200 |
| Capacitive Moisture Sensor | Analog, 3.3V–5V | 40 |
| 12V DC Adapter | 1A–2A, barrel jack | 200 |
| **Total** | | **5128** |

---

## Predicted Crops & Thresholds

| Crop | N (kg/ha) | P (kg/ha) | K (kg/ha) | Moisture (%) |
|------|-----------|-----------|-----------|--------------|
| Rice | ≥ 250 | ≥ 21 | ≥ 450 | > 40 |
| Wheat | ≥ 200 | ≥ 18 | ≥ 400 | > 30 |
| Maize | ≥ 180 | ≥ 18 | ≥ 400 | > 25 |
| Sugarcane | ≥ 240 | ≥ 22 | ≥ 450 | > 35 |
| Cotton | ≥ 220 | ≥ 20 | ≥ 420 | > 30 |
| Groundnut | ≥ 200 | ≥ 19 | ≥ 380 | > 28 |
| Peas | ≥ 160 | ≥ 15 | ≥ 350 | > 20 |
| Tomato | ≥ 170 | ≥ 16 | ≥ 360 | > 22 |
| Millet | < 150 | < 15 | < 350 | > 20 |
| Banana | ≥ 230 | ≥ 22 | ≥ 450 | > 35 |

---

## Results

The system was tested across five different soil samples and correctly predicted the matching crop in each case:

| Result | Crop Predicted |
|--------|---------------|
| ![Result 1](images/Result%20Prediction%201.png) | **Wheat** — N: 212.80, P: 19.30, K: 422.60, Moisture: 33.10% |
| ![Result 2](images/Result%20Prediction%202.png) | **Rice** — N: 289.30, P: 21.20, K: 455.80, Moisture: 25.60% |
| ![Result 3](images/Result%20Prediction%203.png) | **Peas** — N: 171.30, P: 17.10, K: 379.70, Moisture: 20.40% |
| ![Result 4](images/Result%20Prediction%204.png) | **Tomato** — N: 173.50, P: 16.20, K: 366.90, Moisture: 29.80% |
| ![Result 5](images/Result%20Prediction%205.png) | **Millet** — N: 155.60, P: 16.30, K: 358.90, Moisture: 41.10% |

All observed values align closely with ICAR fertilizer recommendations and local Pune agricultural guidelines. See [`results/`](results/README.md) and [`calculations/`](calculations/README.md) for full comparative analysis.

---

## Repository Structure

```
├── firmware/          # Arduino sketch (main.ino)
├── hardware/          # Circuit diagrams and wiring details
├── images/            # Block diagram, flowchart, hardware photos, result screenshots
├── calculations/      # NPK threshold derivations and comparative analysis
├── results/           # Observed vs. recommended NPK values and conclusions
└── README.md
```

---

## Future Improvements

- Integrate pH and temperature sensors for richer soil profiles
- Add GPS geotagging for field-level mapping
- Port prediction logic to a machine learning model (Random Forest / Decision Tree)
- Mobile app or IoT dashboard output (Blynk / MQTT)

---

## Authors

**Archit Kulkarni** (PRN: 1032221176) & **Samarth More** (PRN: 1032221224)  
Department of Electrical and Electronics Engineering  
Dr. Vishwanath Karad MIT World Peace University, Pune — 2024–25  
*Under the guidance of Dr. Harshali Zodpe*
