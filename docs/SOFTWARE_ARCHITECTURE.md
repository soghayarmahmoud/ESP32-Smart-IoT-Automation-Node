# Software Architecture Documentation

## Overview

The Smart IoT Automation Node is being designed as an end-to-end software platform that spans embedded firmware, a web-based control dashboard, and future mobile-native experiences. The architecture reflects a pragmatic balance between low-level reliability and modern software ergonomics.

## Firmware Architecture

The firmware layer is planned around the ESP32 using the Arduino framework and PlatformIO.

### Core Responsibilities

- Drive the relay output safely and predictably.
- Read the optocoupler-based input state.
- Host a lightweight web server for local control and diagnostics.
- Publish or consume device state through MQTT for future cloud integration.
- Expose GPIO control logic in a modular, testable structure.

### Planned Firmware Structure

The firmware will likely be organized into the following logical modules:

- Core configuration and pin mapping.
- Relay control logic.
- Input sensing and debounce handling.
- Wi-Fi and networking initialization.
- Web server endpoints for state reporting and command execution.
- MQTT client integration for remote communication.

### Communication Model

The current architecture targets a simple and practical communication model:

- Local access through a web interface hosted on the ESP32.
- Optional MQTT-based communication for distributed automation systems.
- Device state updates that can be consumed by the dashboard or future mobile clients.

This provides a clear path from local control to broader cloud-based deployments without requiring a complete redesign of the firmware.

## Web Dashboard Architecture

The web dashboard is planned as a modern Next.js application built with TypeScript and Tailwind CSS.

### Design Principles

- A clean, modern interface that is easy to operate.
- A dark-mode-first visual style with glassmorphism-inspired surfaces.
- Clear separation of control, monitoring, and system status.
- Responsive behavior for desktop and mobile browsers.

### Planned Frontend Structure

The frontend can be organized into a small set of domain-focused modules:

- Dashboard overview and device status.
- Relay control panel.
- Input monitoring and event history.
- Settings and network configuration.

### Communication with the ESP32

The dashboard will communicate with the ESP32 through a lightweight API layer. The preferred approach is:

- HTTP or WebSocket-based communication for local control.
- MQTT bridging for broader integration and networked deployments.
- JSON-based state representation for device status and commands.

This approach ensures a simple interface between embedded and web layers while leaving room for future cloud orchestration features.

## Current State and Immediate Next Steps

At the present stage, the repository contains the hardware and documentation foundation. The immediate software focus is to translate the documented architecture into working firmware and a first functional dashboard experience.

### Immediate Priorities

1. Implement the ESP32 firmware skeleton with basic relay control.
2. Expose simple REST endpoints for state reporting and command execution.
3. Create the first dashboard view for device status and relay toggling.
4. Add MQTT integration as a second-stage enhancement.

## Future Software Direction

The architecture is intentionally future-proof. Once the core control loop is stable, the system can evolve into:

- A cloud-managed fleet of nodes.
- A cross-platform mobile app.
- Secure authentication and role-based access.
- OTA update support and remote diagnostics.

This positions the project not as a single-purpose demo, but as a scalable automation platform that can grow from local prototyping into a serious connected product.
