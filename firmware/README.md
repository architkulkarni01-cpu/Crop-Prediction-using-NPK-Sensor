#define SOIL_SENSOR_PIN 34
#define THERMISTOR_PIN 35
#define LDR_PIN 32

const int windowSize = 30;  
float soilData[windowSize], tempData[windowSize], ldrData[windowSize];
int dataIndex = 0;
bool filled = false;

// Function to calculate mean
float calculateMean(float data[], int size) {
    float sum = 0;
    int count = filled ? size : dataIndex;
    for (int i = 0; i < count; i++) sum += data[i];
    return sum / count;
}

// Function to calculate standard deviation
float calculateStdDev(float data[], int size, float mean) {
    float sum = 0;
    int count = filled ? size : dataIndex;
    for (int i = 0; i < count; i++) sum += pow(data[i] - mean, 2);
    return sqrt(sum / count);
}

// Function to detect anomaly using Z-score with a minimum change threshold
bool detectAnomaly(float value, float data[], int size, float zThreshold, float minChange) {
    float mean = calculateMean(data, size);
    float stddev = calculateStdDev(data, size, mean);
    if (stddev == 0) return false;  // Prevent division by zero
    float zScore = (value - mean) / stddev;
    return (abs(zScore) > zThreshold) && (abs(value - mean) >= minChange);
}

void setup() {
    Serial.begin(115200);
}

void loop() {
    // Read raw sensor values
    int rawSoil = analogRead(SOIL_SENSOR_PIN);
    int rawTemp = analogRead(THERMISTOR_PIN);
    int rawLDR = analogRead(LDR_PIN);

    // Convert to meaningful values
    float soilMoisture = map(rawSoil, 0, 4095, 0, 100);  
    float resistance = (4095.0 / rawTemp) - 1.0;
    resistance = 10000.0 / resistance;  
    float temperature = 1 / (log(resistance / 10000.0) / 3950 + 1 / 298.15) - 273.15;  
    float lux = map(rawLDR, 0, 4095, 0, 1000);  

    // Detect anomalies with smarter thresholds
    bool soilAnomaly = detectAnomaly(soilMoisture, soilData, windowSize, 2.0, 5.0);  // Min ±5% change
    bool tempAnomaly = detectAnomaly(temperature, tempData, windowSize, 2.0, 2.0);  // Min ±2°C change
    bool ldrAnomaly = detectAnomaly(lux, ldrData, windowSize, 2.0, 50.0);  // Min ±50 lux change

    // Store new readings
    soilData[dataIndex] = soilMoisture;
    tempData[dataIndex] = temperature;
    ldrData[dataIndex] = lux;
    dataIndex = (dataIndex + 1) % windowSize;
    if (dataIndex == 0) filled = true;

    // Print data & anomalies
    Serial.printf("Soil: %.2f%% | Temp: %.2f°C | Lux: %.2f\n", soilMoisture, temperature, lux);
    if (soilAnomaly) Serial.println("⚠ Significant Soil Moisture Anomaly Detected!");
    if (tempAnomaly) Serial.println("⚠ Significant Temperature Anomaly Detected!");
    if (ldrAnomaly) Serial.println("⚠ Significant Light Intensity Anomaly Detected!");

    delay(5000);
}

