# 🌱 IoT-Powered Smart Vermiwash Dispenser for Precision Farming

An intelligent, IoT-enabled system designed to automate the dispensing of vermiwash and water based on real-time soil conditions. This project integrates sensors, relay-controlled pumps, a NodeMCU microcontroller, and the Blynk IoT platform for remote monitoring, automation, and control. Future integration of machine learning helps in predicting the required amount of vermiwash for upcoming cycles, making this solution ideal for precision farming.

---

## 🚀 Features

- 📡 **IoT Connectivity** via Blynk (Web & Mobile)
- 🌱 **Soil Moisture and pH Monitoring** using analog sensors
- ⚙️ **Automated Pump Control** for vermiwash and water
- 🔁 **Auto/Manual Mode Toggle** via app
- 📊 **Real-time Dashboard** with threshold sliders and control buttons
- 🧠 **ML-based Prediction** of required vermiwash (WIP)
- 📋 **Data Logging Ready** for future analytics and optimization

---

## 🧰 Hardware Components

| Component               | Description                                 |
|------------------------|---------------------------------------------|
| NodeMCU ESP8266        | Main microcontroller with Wi-Fi             |
| CD74HC4067 Multiplexer | Handles multiple analog inputs              |
| Soil Moisture Sensor   | Monitors soil wetness                       |
| Analog pH Sensor       | Detects soil acidity/alkalinity             |
| 2-Channel Relay Module | Controls pumps for dispensing               |
| Submersible Pumps      | Dispenses water and vermiwash               |
| Power Adapter (5V/12V) | Powers NodeMCU and pump motors              |

---

## 🖥️ Blynk Dashboard (Virtual Pins)

| Virtual Pin | Function                            |
|-------------|-------------------------------------|
| V0          | Soil Moisture                       |
| V1          | pH Level                            |
| V2          | 🔮 Predicted Vermiwash (ML Output)  |
| V3          | Vermiwash Pump Control              |
| V4          | Water Pump Control                  |
| V5          | Auto/Manual Toggle                  |
| V7          | Moisture Threshold                  |
| V8          | pH Min Threshold                    |
| V9          | pH Max Threshold                    |

---

## 🔌 Wiring Summary

- **Multiplexer (CD74HC4067)** connected to NodeMCU using D1, D2, D6, D7 as control pins.
- **Moisture & pH sensors** connected via multiplexer to A0.
- **Relay Module** connected to D5 (Vermiwash Pump) and D6 (Water Pump).
- Powered using 3.3V and VIN of NodeMCU.

---

## 🧠 Machine Learning Integration (WIP)

We are currently working on integrating a regression-based ML model to:
- Predict the required amount of vermiwash using past data (moisture, pH, time, quantity used)
- Send prediction to Blynk via Virtual Pin V2
- Optimize nutrient usage and reduce wastage

---

## 📈 Future Scope

- 🔋 Add solar power for energy efficiency
- 🌦 Integrate weather APIs for smarter irrigation
- 📡 Use LoRa/GSM modules for better rural connectivity
- 📲 Enable mobile notifications and SMS alerts
- 🧪 Expand to multi-zone field control

---

## 📷 Demo Snapshot

![vermiwash pic 4](https://github.com/user-attachments/assets/706bafba-c1de-49fe-82bd-09df88c5c8d2)
![vermiwash pic 5](https://github.com/user-attachments/assets/3bdde082-bd5b-4baf-a64e-d8ce59b0ba25)
![vermiwash pic1](https://github.com/user-attachments/assets/9a625df2-fe86-4fec-b642-7e50587df834)

---

## 🛠️ Setup & Installation

1. Clone this repo
2. Upload the code to your NodeMCU using Arduino IDE
3. Install required libraries: `Blynk`, `ESP8266WiFi`, `SimpleTimer` (or `BlynkTimer`)
4. Setup Blynk dashboard with required virtual pins
5. Connect your hardware and power it up!

---
## 📄 License

MIT License — feel free to use, modify, and improve!

---

## 🙌 Acknowledgements

- Blynk IoT Platform
- Arduino Community
- IoT and Precision Farming Innovators


