<div align="center">
  <img src="https://media3.giphy.com/media/v1.Y2lkPTc5MGI3NjExcDQzYzU1aWRpdTFnYjdvdDFiaXVtNHZ0cXh1eDJqZ3BtcWh3OG9oayZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/VbKLoZ52QgsO82GAJc/giphy.gif" alt="IoT Animation" width="150"/>
  
  # 🚀 Smart IoT Automation Node
  
  **A powerful, reliable, and open-source ESP32-based node for your home and industrial automation needs.**
  
  [![ESP32](https://img.shields.io/badge/ESP32-WROOM--32D-red?style=for-the-badge&logo=espressif)](https://www.espressif.com/)
  [![EasyEDA](https://img.shields.io/badge/EasyEDA-Design-blue?style=for-the-badge&logo=altiumdesigner)](https://easyeda.com)
  [![License: MIT](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)
  [![Status](https://img.shields.io/badge/Status-Active-brightgreen?style=for-the-badge)](#)
</div>

---

## 🌟 Overview

The **Smart IoT Automation Node** is a highly versatile hardware platform designed to bridge the gap between physical appliances and the cloud. Built around the powerful **ESP32-WROOM-32D** module, it provides a stable environment with isolated I/O and direct relay control.

Whether you're building a smart home ecosystem, remote monitoring stations, or industrial automation loops, this node acts as the perfect backbone.

### ✨ Key Features
- **🧠 Dual-Core ESP32 Processor**: Built-in WiFi & Bluetooth (BLE).
- **🛡️ Optoisolated Inputs**: Safe signal reading via the PC817 optocoupler.
- **⚡ Power Control**: Direct control of external high-voltage/current devices via an onboard 5V Relay (SRD-05VDC-SL-C).
- **🔌 Robust Power Management**: 5V to 3.3V regulation via the AMS1117-3.3 linear regulator for stable MCU operation.
- **🛠️ Easy Integration**: Convenient terminal blocks (2-pin and 3-pin) for fast wiring.

---

## 📁 Repository Structure

```text
├── pcb/                        # EasyEDA PCB design files (.json)
├── sch/                        # EasyEDA Schematic files (.json)
├── HARDWARE_DOCS.md            # Detailed schematic & BOM breakdown
├── ROADMAP.md                  # Web App roadmap & Future Hardware versions
└── README.md                   # This file
```

---

## 🚀 Getting Started (Hardware)

This project is natively designed in **EasyEDA**. To view or modify the hardware:

1. Clone or download this repository.
2. Open [EasyEDA](https://easyeda.com/editor) or the EasyEDA Desktop Client.
3. Select **File > Open > EasyEDA...** and load the `.json` files from the `sch/` and `pcb/` directories.

---

## 📚 Documentation & Next Steps

We are building a complete ecosystem around this hardware. Dive deeper into our documentation:

- 📖 **[Hardware Documentation](./HARDWARE_DOCS.md)**: Explore the schematic breakdown, pin mappings, and BOM.
- 🗺️ **[Project Roadmap](./ROADMAP.md)**: See our plans for the upcoming Web Dashboard, firmware support (MQTT/Home Assistant), and hardware V2.0.

---

<div align="center">
  <i>Designed with ❤️ for the Open-Source IoT Community.</i>
</div>
