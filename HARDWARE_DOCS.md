# 🔧 Hardware Documentation

This document provides a detailed technical breakdown of the **Smart IoT Automation Node**. It is intended for hardware engineers, firmware developers, and anyone looking to understand the inner workings of the board.

---

## 📑 Bill of Materials (Key Components)

The PCB is built using easily accessible and reliable SMD and through-hole components.

| Reference | Value / Part Name | Description | Package / Footprint |
|-----------|-------------------|-------------|---------------------|
| **U9** | `ESP32-WROOM-32D` | Main Microcontroller Module (WiFi/BLE) | SMD ESP32 Module |
| **U4** | `AMS1117-3.3` | Linear Voltage Regulator (5V to 3.3V) | SOT-223-3 |
| **U6** | `PC817B-FEL-S` | Optocoupler for isolated inputs | SOP-4 |
| **RLY1** | `SRD-05VDC-SL-C` | 5V Relay for load switching | TH Relay |
| **Q1** | `BC547BBU` | NPN Transistor (Relay driver) | TO-92-3 |
| **D1** | `1N4007` (S2M) | Flyback Diode for Relay protection | SMB |
| **U1, U2**| `GT-TC155A` | Tactile push buttons | SMD 4-pin |
| **U3** | `KF2EDGK-5.08MM 3PIN`| Terminal Block (3-pin) | TH 5.08mm |
| **CN1** | `A508VC-2P0G36` | Terminal Block (2-pin) | TH 5.08mm |
| **C1, C3**| `10uF` | Electrolytic Decoupling Capacitors | TH 5x8mm |
| **C2, C4**| `100nF` | Ceramic Bypass Capacitors | TH 5.00mm |

---

## ⚡ Power Management Circuit

The node is designed to be powered via a 5V supply, which is stepped down to 3.3V for the ESP32.
- **Input Power (5V):** Powers the relay directly to prevent voltage sag on the 3.3V line during relay switching.
- **Regulator (U4):** An `AMS1117-3.3` LDO is used to generate a stable 3.3V supply for the ESP32 and optocoupler output.
- **Decoupling:** `10uF` and `100nF` capacitors are placed at both the input and output of the LDO to filter high-frequency noise and provide bulk capacitance for transient loads.

---

## 🔄 Relay Control Circuit

The ESP32 GPIOs output a 3.3V logic signal with very low current capability, which is insufficient to drive a 5V relay coil directly.
- **Transistor (Q1):** A `BC547` NPN transistor is used as a low-side switch. A base resistor limits the current from the ESP32 pin.
- **Relay (RLY1):** `SRD-05VDC` is activated when Q1 conducts.
- **Flyback Diode (D1):** An `1N4007` (or S2M equivalent) diode is placed anti-parallel to the relay coil. This is crucial for clamping the high-voltage inductive spike that occurs when the relay is turned off, protecting the transistor.

---

## 🛡️ Isolated Input Circuit

To safely read external signals (especially from noisy or differing ground potentials), the node features an isolated input circuit.
- **Optocoupler (U6):** A `PC817` is utilized. When current flows through the internal LED (input side), the phototransistor turns on, pulling the ESP32 input pin low (or high depending on the pull-up/down configuration).
- **Benefits:** Protects the delicate ESP32 pins from over-voltage spikes and eliminates ground loops.

---

## 📌 Pin Allocation (ESP32)

Based on the schematic connections, here is the intended pin mapping for firmware development:

*Note: Please verify the final PCB traces for exact GPIO mappings in your EasyEDA viewer, as the ESP32-WROOM-32D exposes many multi-function pins (e.g., IO0, IO2, IO4, IO12, IO13, IO14, IO15).*

### General Recommendations for Firmware:
- **Relay Control:** Ensure the chosen GPIO is initialized as an `OUTPUT` and defaults to `LOW` during boot to prevent accidental relay triggering.
- **Optocoupler Input:** Initialize the GPIO as an `INPUT`. Depending on the hardware pull-up, you may need to enable the internal pull-up (`INPUT_PULLUP`).

---

<div align="center">
  <i>For further schematic editing, open the `.json` files in the EasyEDA editor.</i>
</div>
