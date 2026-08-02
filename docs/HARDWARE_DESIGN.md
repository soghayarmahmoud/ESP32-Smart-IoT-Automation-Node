# Hardware Design Documentation

## Overview

The Smart IoT Automation Node is a purpose-built embedded control board centered around the ESP32 microcontroller. Its design combines a relay output stage, isolated sensing capability, and a compact power distribution network into a single board that is suitable for experimentation, smart-home control, and future industrial-style deployments.

## What Has Been Accomplished

The current hardware foundation includes:

- A complete schematic concept for the ESP32-based control node.
- A PCB layout prepared in EasyEDA with logical grouping for power, switching, and signal-processing sections.
- A bill of materials and board-level documentation that capture the core components and their intended purpose.
- Manufacturing-oriented output files such as Gerber layers and drill files.

## PCB Layout and Schematic Summary

The board architecture is organized around four principal functional areas:

1. Microcontroller and radio section
   - The ESP32 module provides Wi-Fi and Bluetooth connectivity and serves as the control and communication hub.
   - The layout prioritizes a clean RF environment and keeps antenna-related clearances appropriate for stable wireless operation.

2. Power management section
   - The board accepts a 5V input and uses an AMS1117-3.3 regulator to generate a stable 3.3V rail for the ESP32 and logic circuitry.
   - Bulk and high-frequency decoupling capacitors are placed close to the regulator and the ESP32 supply pins.

3. Relay switching section
   - A 5V relay provides the switching interface for connected loads.
   - A transistor driver stage allows the ESP32 to control the coil safely without directly sourcing the relay current.
   - A flyback diode protects the switching transistor and MCU from inductive transients.

4. Isolation and sensing interface
   - The board includes an optocoupled signal input path for safe sensing from external electrical systems.
   - This section is intentionally separated from the main logic ground and control circuitry to reduce noise coupling and improve robustness.

## High-Voltage Isolation Philosophy

The isolation strategy is built around the PC817 optocoupler, which serves as a safety and noise barrier between the external signal domain and the ESP32 control domain.

The reasoning behind this design is straightforward:

- It prevents direct electrical coupling between the external input circuit and the MCU pins.
- It allows the board to safely interact with signals that may originate from noisy or electrically different environments.
- It reduces the risk of damaging the ESP32 in scenarios involving transient spikes, ground potential differences, or inadvertent miswiring.

In practical terms, the PC817 creates a controlled electrical boundary: the input side receives the external signal, while the output side drives the logic circuit in a way that is electrically isolated. This is a critical design decision for an automation node that may be connected to real-world switching systems.

## Trace Width Strategy

The PCB was designed with current-carrying requirements in mind. The following trace widths are used as design targets:

| Function | Target Width | Reason |
| --- | ---: | --- |
| High-voltage region | 60 mil | Provides additional creepage and clearance margin for 220V-related routing and safety-focused layout planning. |
| Power traces | 25 mil | Supports robust current delivery for relay and regulator paths. |
| Signal traces | 10 mil | Suitable for low-current logic and control signals. |

These values represent a practical, conservative routing strategy that prioritizes reliability and manufacturability.

## Component Placement Strategy

The layout was planned to balance electrical performance with manufacturability and signal integrity.

Key placement principles include:

- The ESP32 antenna region is kept clear of large copper areas, metal components, and routing congestion to preserve wireless performance.
- The relay and associated driver circuitry are grouped together to minimize loop area and simplify current return paths.
- The optocoupler input section is isolated from the high-current switching region to reduce interference.
- The regulator and decoupling network are placed close to the load and the MCU supply pins to ensure stable voltage delivery.

This placement strategy is especially important because the ESP32 is sensitive to local noise and should not be placed near switching components without careful separation and grounding.

## Grounding and Copper Pour Implementation

The board uses a grounded copper pour strategy that reinforces the low-impedance return path and improves noise performance.

Design highlights include:

- A continuous ground plane is used wherever practical to reduce EMI and provide stable reference potential.
- High-current and high-noise sections, such as the relay stage, are kept physically separated from the sensitive MCU and antenna area.
- Copper pour is used to improve shielding and thermal behavior while maintaining clear routing spaces for the ESP32 and related circuitry.
- The layout avoids unnecessary splits in the return path where they could introduce unwanted impedance and coupling.

## Manufacturing and Documentation Readiness

The hardware design is already documented at a level suitable for engineering review, prototyping, and future iteration. The repository includes supporting artifacts that make the design portable and reviewable:

- Schematic and PCB JSON files for EasyEDA editing.
- Gerber manufacturing files for fabrication.
- A BOM that captures key parts and their roles.

This establishes a solid baseline for future revisions, testing, and production preparation.
