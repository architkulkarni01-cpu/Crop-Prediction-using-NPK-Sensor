# Firmware

## Overview
This firmware runs on the ESP32 and performs real-time environmental monitoring along with anomaly detection.

It reads soil moisture, temperature (via thermistor), and light intensity (LDR), processes the data, and detects anomalies using statistical methods.

---

## Features
- ADC-based sensor data acquisition  
- Moving window data buffering  
- Mean and standard deviation calculation  
- Z-score based anomaly detection  
- Noise reduction using minimum change thresholds  

---

## Sensors Used
- Soil Moisture Sensor → GPIO 34  
- Thermistor (Temperature) → GPIO 35  
- LDR (Light Intensity) → GPIO 32  

---

## Data Processing

### Moving Window
- Window size: 30 samples  
- Maintains rolling dataset for each sensor  

### Statistical Analysis
- Mean and standard deviation computed dynamically  
- Used for anomaly detection  

### Anomaly Detection
- Z-score method applied:
  - Threshold: ±2.0  
- Minimum change filtering:
  - Soil: ±5%  
  - Temperature: ±2°C  
  - Light: ±50 lux  

---

## Output
- Sensor readings printed via Serial Monitor  
- Alerts generated when anomalies are detected  
