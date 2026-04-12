#define RXD2 16  // ESP32 UART2 RX (through voltage divider)
#define TXD2 17  // ESP32 UART2 TX
#define DE_RE 5 // Connected to both DE and RE on RS485 module

#define SOIL_MOISTURE_PIN 34 // ADC pin on ESP32

#define NUM_SAMPLES 5

// Conversion factor from mg/kg to kg/ha
// Assumes 15cm sampling depth and soil bulk density of 1.3 g/cm³
// 1 mg/kg ≈ 1.95 kg/ha with these assumptions
#define MG_KG_TO_KG_HA 1.95

const byte N_CMD[] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte P_CMD[] = {0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte K_CMD[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

byte values[11];

HardwareSerial modbus(2); // Use UART2

// Previous values for filtering
byte prevN = 0, prevP = 0, prevK = 0;
float prevMoisture = 0;

// Moving average buffers
byte nBuffer[NUM_SAMPLES], pBuffer[NUM_SAMPLES], kBuffer[NUM_SAMPLES];
float mBuffer[NUM_SAMPLES];

void setup() {
  Serial.begin(115200);
  modbus.begin(9600, SERIAL_8N1, RXD2, TXD2);

  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, LOW); // start in receive mode
  pinMode(SOIL_MOISTURE_PIN, INPUT);

  Serial.println("Initializing...");
  initBuffers();
  Serial.println("Setup complete!");
}

void loop() {
  Serial.println("Reading sensor values...");

  for (int i = 0; i < NUM_SAMPLES; i++) {
    shiftBuffers();

    nBuffer[NUM_SAMPLES - 1] = readNPK(N_CMD);
    delay(250);
    pBuffer[NUM_SAMPLES - 1] = readNPK(P_CMD);
    delay(250);
    kBuffer[NUM_SAMPLES - 1] = readNPK(K_CMD);
    delay(250);

    int raw = analogRead(SOIL_MOISTURE_PIN);
    mBuffer[NUM_SAMPLES - 1] = map(raw, 4095, 0, 0, 100);

    delay(250);
  }

  byte nitrogen = validateReading(avgBuffer(nBuffer), prevN, 20);
  byte phosphorus = validateReading(avgBuffer(pBuffer), prevP, 20);
  byte potassium = validateReading(avgBuffer(kBuffer), prevK, 20);
  float moisture = validateReadingFloat(avgBufferFloat(mBuffer), prevMoisture, 20);

  prevN = nitrogen;
  prevP = phosphorus;
  prevK = potassium;
  prevMoisture = moisture;

  // Convert mg/kg to kg/ha for display and prediction
  float nitrogenKgHa = nitrogen * MG_KG_TO_KG_HA;
  float phosphorusKgHa = phosphorus * MG_KG_TO_KG_HA;
  float potassiumKgHa = potassium * MG_KG_TO_KG_HA;

  Serial.println("------ Sensor Values ------");
  Serial.print("Nitrogen   : "); Serial.print(nitrogenKgHa); Serial.println(" kg/ha");
  Serial.print("Phosphorus : "); Serial.print(phosphorusKgHa); Serial.println(" kg/ha");
  Serial.print("Potassium  : "); Serial.print(potassiumKgHa); Serial.println(" kg/ha");
  Serial.print("Soil Moist : "); Serial.print(moisture); Serial.println(" %");

  predictCrop(nitrogenKgHa, phosphorusKgHa, potassiumKgHa, moisture);
  Serial.println("---------------------------");

  Serial.println("Waiting 60 seconds for next cycle...");
  delay(60000);
}

// ------------------ Helper Functions ------------------

byte readNPK(const byte command[]) {
  digitalWrite(DE_RE, HIGH);
  delay(10);
  modbus.write(command, 8);
  digitalWrite(DE_RE, LOW);

  delay(100);
  byte value = 0;
  if (modbus.available() >= 7) {
    for (byte i = 0; i < 7; i++) {
      values[i] = modbus.read();
    }
    value = values[4];
  }
  return value;
}

void predictCrop(float n, float p, float k, float m) {
  String crop = "Unknown";

  // Using thresholds based on the average values provided:
  // N avg: 224.7 kg/ha, P avg: 21.6 kg/ha, K avg: 484.2 kg/ha
  
  if (n >= 250 && p >= 21 && k >= 450 && m > 40) crop = "Rice";
  else if (n >= 200 && p >= 18 && k >= 400 && m > 30) crop = "Wheat";
  else if (n < 150 && p < 15 && k < 350 && m > 20) crop = "Millet";
  else if (n >= 240 && p >= 22 && k >= 450 && m > 35) crop = "Sugarcane";
  else if (n >= 180 && p >= 18 && k >= 400 && m > 25) crop = "Maize";
  else if (n >= 160 && p >= 15 && k >= 350 && m > 20) crop = "Peas";
  else if (n >= 220 && p >= 20 && k >= 420 && m > 30) crop = "Cotton";
  else if (n >= 200 && p >= 19 && k >= 380 && m > 28) crop = "Groundnut";
  else if (n >= 230 && p >= 22 && k >= 450 && m > 35) crop = "Banana";
  else if (n >= 170 && p >= 16 && k >= 360 && m > 22) crop = "Tomato";

  Serial.print("Suggested Crop: ");
  Serial.println(crop);
}

void initBuffers() {
  byte initN = readNPK(N_CMD);
  byte initP = readNPK(P_CMD);
  byte initK = readNPK(K_CMD);
  float initM = map(analogRead(SOIL_MOISTURE_PIN), 4095, 0, 0, 100);

  for (int i = 0; i < NUM_SAMPLES; i++) {
    nBuffer[i] = initN;
    pBuffer[i] = initP;
    kBuffer[i] = initK;
    mBuffer[i] = initM;
  }

  prevN = initN;
  prevP = initP;
  prevK = initK;
  prevMoisture = initM;
}

void shiftBuffers() {
  for (int i = 0; i < NUM_SAMPLES - 1; i++) {
    nBuffer[i] = nBuffer[i + 1];
    pBuffer[i] = pBuffer[i + 1];
    kBuffer[i] = kBuffer[i + 1];
    mBuffer[i] = mBuffer[i + 1];
  }
}

byte avgBuffer(byte buf[]) {
  int sum = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) sum += buf[i];
  return sum / NUM_SAMPLES;
}

float avgBufferFloat(float buf[]) {
  float sum = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) sum += buf[i];
  return sum / NUM_SAMPLES;
}

byte validateReading(byte curr, byte prev, byte thresholdPercent) {
  if (prev == 0) return curr;
  float threshold = prev * (thresholdPercent / 100.0);
  return (abs(curr - prev) > threshold) ? prev : curr;
}

float validateReadingFloat(float curr, float prev, byte thresholdPercent) {
  if (prev == 0) return curr;
  float threshold = prev * (thresholdPercent / 100.0);
  return (abs(curr - prev) > threshold) ? prev : curr;
}

