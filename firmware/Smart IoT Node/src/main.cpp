/**
 * @file main.cpp
 * @author Mahmoud El-Soghayar
 * @brief ESP32 Smart IoT Automation Node - Firmware
 * @version 1.0
 * 
 * This firmware connects the ESP32 to a local Wi-Fi network and 
 * hosts a lightweight web server to toggle a high-voltage relay securely.
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "secrets.h" // Contains Wi-Fi credentials (ignored by Git)

// --- Configuration ---
#define RELAY_PIN 4        // GPIO pin connected to the Optocoupler
#define SERVER_PORT 80     // Default HTTP port

WebServer server(SERVER_PORT);

// --- Request Handlers ---

/**
 * @brief Turns the relay ON and sends a success response.
 */
void handleRelayOn() {
    digitalWrite(RELAY_PIN, HIGH);
    server.send(200, "application/json", "{\"status\":\"success\", \"state\":\"ON\"}");
    Serial.println("Relay turned ON");
}

/**
 * @brief Turns the relay OFF and sends a success response.
 */
void handleRelayOff() {
    digitalWrite(RELAY_PIN, LOW);
    server.send(200, "application/json", "{\"status\":\"success\", \"state\":\"OFF\"}");
    Serial.println("Relay turned OFF");
}

// --- Main Setup ---
void setup() {
    // 1. Initialize Serial Monitor
    Serial.begin(115200);
    Serial.println("\nStarting Smart IoT Node...");

    // 2. Initialize Hardware Pins
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW); // Ensure relay is OFF by default

    // 3. Connect to Wi-Fi
    Serial.print("Connecting to Wi-Fi: ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\nWi-Fi Connected successfully!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // 4. Define API Routes
    server.on("/api/on", HTTP_GET, handleRelayOn);
    server.on("/api/off", HTTP_GET, handleRelayOff);

    // 5. Start the Server
    server.begin();
    Serial.println("HTTP Server is running and listening for requests.");
}

// --- Main Loop ---
void loop() {
    // Continuously listen for incoming client requests
    server.handleClient();
}