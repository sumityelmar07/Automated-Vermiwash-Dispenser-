#define BLYNK_TEMPLATE_ID "TMPL345j4x99h"
#define BLYNK_TEMPLATE_NAME "Automated Vermiwash Dispenser"
#define BLYNK_AUTH_TOKEN "tO_UccTRYANEEJdbffu07UdUeWcmxiz2"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// WiFi credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "iPhone";
char pass[] = "sumit0007";

// Multiplexer select pins
const int S0 = D1;  // GPIO5
const int S1 = D2;  // GPIO4
const int S2 = D3;  // GPIO0 
const int S3 = D7;  // GPIO13
const int SIG = A0; // Analog input from multiplexer

// Relay pins
const int relayVermiwash = D5;
const int relayWater = D6;

// Thresholds (can be changed via Blynk)
int moistureThreshold = 35;
float pHMinThreshold = 3.0;
float pHMaxThreshold = 7.0;

bool autoMode = false;
BlynkTimer timer;

// Select multiplexer channel (0–15)
void selectMUXChannel(int ch) {
  digitalWrite(S0, ch & 0x01);
  digitalWrite(S1, (ch >> 1) & 0x01);
  digitalWrite(S2, (ch >> 2) & 0x01);
  digitalWrite(S3, (ch >> 3) & 0x01);
  delayMicroseconds(100);
}

// Read from selected channel with averaging
int readMuxAnalog(int channel) {
  selectMUXChannel(channel);
  int sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(SIG);
    delayMicroseconds(100);
  }
  return sum / 10;
}

// Main function to send data and control relays
void sendSensorData() {
  int moistureRaw = readMuxAnalog(4);  // CH4 = Moisture (Pin 12)
  int pHRaw = readMuxAnalog(5);        // CH5 = pH (Pin 13)

  float voltage = pHRaw * (3.3 / 1023.0);
  float pHValue = 7 + ((2.5 - voltage) * 3.5);
  int moisturePercent = map(moistureRaw, 1023, 0, 0, 100);

  // Send to Blynk
  Blynk.virtualWrite(V0, moisturePercent);
  Blynk.virtualWrite(V1, pHValue);

  Serial.print("Moisture: "); Serial.print(moisturePercent); Serial.print("%, ");
  Serial.print("pH: "); Serial.println(pHValue);

  if (autoMode) {
    bool waterON = (moisturePercent <= moistureThreshold);
    bool vermiON = (pHValue < pHMinThreshold || pHValue > pHMaxThreshold);

    digitalWrite(relayWater, waterON ? LOW : HIGH);
    digitalWrite(relayVermiwash, vermiON ? LOW : HIGH);

    if (waterON) Serial.println("Auto Mode: Moisture low → Water Pump ON");
    if (vermiON) Serial.println("Auto Mode: pH abnormal → Vermiwash Pump ON");
  }

  // Reflect relay states on Blynk
  Blynk.virtualWrite(V3, digitalRead(relayVermiwash) == LOW ? 1 : 0);
  Blynk.virtualWrite(V4, digitalRead(relayWater) == LOW ? 1 : 0);
}

// ------------------- BLYNK Virtual Pins ------------------- //
BLYNK_WRITE(V3) {  // Manual Vermiwash Pump
  if (!autoMode) digitalWrite(relayVermiwash, param.asInt() ? LOW : HIGH);
}

BLYNK_WRITE(V4) {  // Manual Water Pump
  if (!autoMode) digitalWrite(relayWater, param.asInt() ? LOW : HIGH);
}

BLYNK_WRITE(V5) {  // Auto/Manual Mode
  autoMode = param.asInt();
  digitalWrite(relayVermiwash, HIGH);  // OFF
  digitalWrite(relayWater, HIGH);      // OFF
  Blynk.virtualWrite(V3, 0);
  Blynk.virtualWrite(V4, 0);
  Serial.println(autoMode ? "Switched to AUTO mode" : "Switched to MANUAL mode");
}

BLYNK_WRITE(V7) { moistureThreshold = param.asInt(); }
BLYNK_WRITE(V8) { pHMinThreshold = param.asFloat(); }
BLYNK_WRITE(V9) { pHMaxThreshold = param.asFloat(); }

// ------------------- Setup + Loop ------------------- //
void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(relayVermiwash, OUTPUT);
  pinMode(relayWater, OUTPUT);

  digitalWrite(relayVermiwash, HIGH);
  digitalWrite(relayWater, HIGH);

  Blynk.virtualWrite(V5, 0);  // Manual mode by default
  timer.setInterval(2000L, sendSensorData);  // every 2 seconds
}

void loop() {
  Blynk.run();
  timer.run();
} 
