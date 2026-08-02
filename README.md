# Smart IoT Automation Node

A professional-grade, ESP32-based automation platform that combines robust hardware engineering, embedded firmware, and a modern web interface into a single, extensible IoT system. The project is designed to bridge high-voltage appliance control with safe, isolated sensing and a future-ready software ecosystem.

## Project Overview

The Smart IoT Automation Node is an end-to-end IoT solution intended for smart home automation, remote appliance control, and future industrial-style monitoring workflows. The current implementation focuses on a reliable hardware foundation with isolated I/O, relay control, and a software architecture that scales from local control to cloud connectivity and mobile-native experiences.

### Value Proposition

- Safe interaction with external electrical systems through an isolated input path.
- Flexible control architecture suitable for home automation and prototyping environments.
- A clean, modular foundation for firmware, web dashboards, and future mobile applications.
- A portfolio-ready hardware and software stack aligned with modern IoT engineering practices.

## High-Level Architecture

```text
+---------------------+       +----------------------------+       +----------------------------+
|  Hardware Layer     |       |  Firmware Layer            |       |  Software Layer            |
|  - ESP32 MCU        | <-->  |  - Arduino / PlatformIO   | <-->  |  - Next.js Dashboard      |
|  - Relay Output     |       |  - Web Server / MQTT      |       |  - TypeScript / Tailwind  |
|  - Optoisolated I/O |       |  - GPIO Control           |       |  - Mobile App (Future)    |
+---------------------+       +----------------------------+       +----------------------------+
```

## What Has Been Accomplished

The repository already contains the foundation for an engineered IoT node:

- A complete PCB schematic and board layout concept built in EasyEDA.
- Manufacturing-related outputs including Gerber files and a BOM.
- A hardware documentation set describing the relay driver, regulator network, optocoupler isolation path, and board layout philosophy.
- A documented roadmap for web and mobile software expansion.

## Quick Start Guide

### Hardware Setup

1. Review the schematic and PCB files in the hardware directory.
2. Open the EasyEDA project files located in the hardware/sch and hardware/pcb folders.
3. Verify the board connections for the ESP32 module, relay, regulator, and optocoupler input path.
4. Prepare a 5V power source and connect the necessary terminal blocks for the relay and isolated input lines.
5. Assemble the board and validate the relay and sensing behavior before connecting high-power loads.

### Software Setup

1. Install Visual Studio Code and the PlatformIO extension for firmware development.
2. Prepare the ESP32 toolchain and open the firmware project directory when available.
3. Install Node.js 20+ and use npm or pnpm to initialize the web dashboard project.
4. Start the frontend locally with the Next.js development server and connect it to the ESP32 device over the configured network endpoint.

## Technology Stack

- ESP32-WROOM-32D for Wi-Fi, Bluetooth, and embedded control.
- EasyEDA for schematic capture and PCB layout design.
- C++ with the Arduino framework for firmware logic.
- Next.js for the modern web dashboard experience.
- TypeScript for scalable frontend development.
- Tailwind CSS for rapid, responsive UI styling.

## Documentation Set

- [docs/HARDWARE_DESIGN.md](docs/HARDWARE_DESIGN.md) — Hardware layout, isolation design, and PCB implementation notes.
- [docs/SOFTWARE_ARCHITECTURE.md](docs/SOFTWARE_ARCHITECTURE.md) — Firmware and frontend architecture strategy.
- [docs/ROADMAP_AND_QA.md](docs/ROADMAP_AND_QA.md) — Delivery roadmap and quality assurance direction.

## Project Status

The project is currently in a strong foundation phase: hardware design and documentation are established, and the software ecosystem is being planned and expanded toward a polished, end-to-end product experience.
