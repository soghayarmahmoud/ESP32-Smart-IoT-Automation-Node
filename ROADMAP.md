# 🗺️ Project Roadmap

This document outlines the strategic vision for the **Smart IoT Automation Node**. The roadmap is divided into three main pillars: **Web Application Development**, **Firmware Enhancements**, and **Hardware Upgrades**.

---

## 🌐 Web Application Roadmap

To fully utilize the hardware, we plan to build a companion Web App that provides a beautiful, user-friendly interface to control and monitor the node.

### Phase 1: Local Control (ESP32 Hosted)
- **Tech Stack:** HTML/CSS/Vanilla JS (hosted directly on SPIFFS/LittleFS).
- **Features:**
  - Responsive, mobile-first design.
  - Live state toggle for the onboard relay.
  - Real-time display of the optocoupler input status.
  - Local WiFi network setup (Captive Portal).

### Phase 2: Cloud Integration & MQTT
- **Tech Stack:** Node.js Backend, MQTT Broker (e.g., Mosquitto).
- **Features:**
  - Secure communication between the ESP32 and a central cloud server.
  - Support for multiple nodes in a single network.
  - Two-way state synchronization.
  - Over-The-Air (OTA) firmware updates via the web.

### Phase 3: Modern Global Dashboard
- **Tech Stack:** React / Next.js, Firebase or AWS.
- **Features:**
  - Centralized dashboard to manage fleets of IoT nodes.
  - User authentication and role-based access.
  - Historical data logging (e.g., when the relay was triggered, or input events).
  - Integration with third-party services via REST APIs (e.g., IFTTT, Zapier).

---

## 💻 Firmware Features (Future)

Our goal is to make the ESP32 firmware as robust and modular as possible.

- [ ] **Home Assistant Integration:** Implement MQTT Auto-Discovery for seamless integration.
- [ ] **Tasmota/ESPHome Compatibility:** Provide pre-compiled `.bin` files for popular open-source smart home platforms.
- [ ] **Advanced Scheduling:** Allow the ESP32 to store cron-like schedules locally so it operates even without internet.
- [ ] **Fail-safe Modes:** If WiFi drops, fallback to Bluetooth BLE control automatically.

---

## 🔌 Hardware Roadmap (V2.0)

While V1.0 is a strong foundation, future revisions of the PCB will focus on expanding capabilities for industrial applications.

- [ ] **DIN Rail Enclosure Compatibility:** Adjust board dimensions and mounting holes to fit standard DIN rail enclosures.
- [ ] **Dual/Quad Relays:** Increase the number of output channels to control more appliances from a single node.
- [ ] **RS485 / Modbus Support:** Add an RS485 transceiver (e.g., MAX485) to communicate with industrial sensors and PLCs.
- [ ] **Power over Ethernet (PoE):** Introduce a PoE splitter module to allow single-cable data and power delivery.
- [ ] **Onboard Current Sensing:** Add an ACS712 (or similar) IC to measure the power consumption of the device connected to the relay.

---

<div align="center">
  <i>The future is bright! Have an idea? Feel free to open an issue or contribute.</i>
</div>
