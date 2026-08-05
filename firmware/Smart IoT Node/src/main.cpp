/**
 * @file main.cpp
 * @author Mahmoud El-Soghayar
 * @brief ESP32 Smart IoT Automation Node - Firmware
 * @version 2.0
 *
 * This firmware connects the ESP32 to a local Wi-Fi network and
 * hosts a lightweight web server to toggle a high-voltage relay securely.
 *
 * v2.0 additions for Aether Core Dashboard compatibility:
 *   - GET  /api/status  — Full JSON telemetry (uptime, IP, RSSI, heap, relay state)
 *   - POST /api/relay   — Body: {"state": true/false} — controls relay
 *   - CORS headers on all responses so the browser dashboard can reach the ESP32
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "secrets.h" // Contains Wi-Fi credentials (ignored by Git)

// --- Configuration ---
#define RELAY_PIN   4    // GPIO pin connected to the relay driver (via optocoupler)
#define SERVER_PORT 80   // Default HTTP port

WebServer server(SERVER_PORT);

// CORS Helper

/**
 * @brief Attaches CORS response headers so that the Aether Core dashboard
 *        (served from any origin, including a local HTTP server) can call
 *        these endpoints without being blocked by the browser.
 */
void addCORSHeaders() {
    server.sendHeader("Access-Control-Allow-Origin",  "*");
    server.sendHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
}

// -----------------------------------------------------------------------
// Request Handlers
// -----------------------------------------------------------------------

/**
 * @brief Handles CORS preflight (HTTP OPTIONS) sent automatically by
 *        browsers before cross-origin POST requests.
 */
void handleOptions() {
    addCORSHeaders();
    server.send(204, "text/plain", "");
}

/**
 * @brief GET /api/status
 *        Returns a JSON payload with real-time system telemetry.
 *        Consumed by the Aether Core dashboard terminal and gauge widgets.
 *
 *        Response fields:
 *          status      — Always "ONLINE" when reachable
 *          relay_state — true if relay is currently energised
 *          uptime      — Human-readable uptime string (e.g. "2d 04h 15m 30s")
 *          ip_addr     — Current IP on the local network
 *          signal_dbm  — Wi-Fi RSSI in dBm
 *          mem_free    — Free heap in KB
 *          mem_total   — Total heap in KB
 *          temperature — Placeholder 24.0 °C (wire a DHT22 to expand)
 *          humidity    — Placeholder 45.0 % (wire a DHT22 to expand)
 */
void handleStatus() {
    addCORSHeaders();

    // --- Uptime ---
    unsigned long uptimeSec = millis() / 1000UL;
    unsigned long days    = uptimeSec / 86400UL;
    unsigned long hours   = (uptimeSec % 86400UL) / 3600UL;
    unsigned long minutes = (uptimeSec % 3600UL)  / 60UL;
    unsigned long seconds =  uptimeSec % 60UL;

    char uptimeStr[32];
    sprintf(uptimeStr, "%lud %02luh %02lum %02lus", days, hours, minutes, seconds);

    // --- Hardware readings ---
    bool     relayOn = (digitalRead(RELAY_PIN) == HIGH);
    int      rssi    = WiFi.RSSI();
    uint32_t freeKB  = ESP.getFreeHeap()  / 1024U;
    uint32_t totalKB = ESP.getHeapSize()  / 1024U;
    String   ip      = WiFi.localIP().toString();

    // --- Build JSON manually (no external library required) ---
    String json;
    json.reserve(256);
    json  = "{";
    json += "\"status\":\"ONLINE\",";
    json += "\"relay_state\":" + String(relayOn ? "true" : "false") + ",";
    json += "\"uptime\":\""    + String(uptimeStr) + "\",";
    json += "\"ip_addr\":\""   + ip + "\",";
    json += "\"signal_dbm\":"  + String(rssi) + ",";
    json += "\"mem_free\":"    + String(freeKB) + ",";
    json += "\"mem_total\":"   + String(totalKB) + ",";
    json += "\"temperature\":24.0,"; // Placeholder — connect DHT22 to GPIO 14 to replace
    json += "\"humidity\":45.0";     // Placeholder — connect DHT22 to GPIO 14 to replace
    json += "}";

    server.send(200, "application/json", json);
}

/**
 * @brief GET /api/on  (legacy endpoint — kept for backward compatibility)
 *        Turns the relay ON.
 */
void handleRelayOn() {
    addCORSHeaders();
    digitalWrite(RELAY_PIN, HIGH);
    server.send(200, "application/json", "{\"status\":\"success\",\"state\":\"ON\"}");
    Serial.println("[Relay] Turned ON via GET /api/on");
}

/**
 * @brief GET /api/off  (legacy endpoint — kept for backward compatibility)
 *        Turns the relay OFF.
 */
void handleRelayOff() {
    addCORSHeaders();
    digitalWrite(RELAY_PIN, LOW);
    server.send(200, "application/json", "{\"status\":\"success\",\"state\":\"OFF\"}");
    Serial.println("[Relay] Turned OFF via GET /api/off");
}

/**
 * @brief POST /api/relay
 *        Controls the relay from the Aether Core dashboard toggle.
 *        Expected request body (JSON): {"state": true} or {"state": false}
 *        Simple field extraction is used — no external JSON library needed.
 */
void handleRelayPost() {
    addCORSHeaders();

    String body  = server.arg("plain");
    bool   state = false;

    // Detect both {"state":true} and {"state": true} variants
    if (body.indexOf("\"state\":true")   >= 0 ||
        body.indexOf("\"state\": true")  >= 0) {
        state = true;
    }

    digitalWrite(RELAY_PIN, state ? HIGH : LOW);

    String response = "{\"status\":\"success\",\"state\":";
    response += state ? "true" : "false";
    response += "}";

    server.send(200, "application/json", response);
    Serial.print("[Relay] Set via POST /api/relay → ");
    Serial.println(state ? "ON" : "OFF");
}

// -----------------------------------------------------------------------
// Setup
// -----------------------------------------------------------------------
void setup() {
    // 1. Initialize Serial Monitor
    Serial.begin(115200);
    Serial.println("\n========================================");
    Serial.println("  Smart IoT Automation Node — v2.0");
    Serial.println("========================================");

    // 2. Initialize Hardware Pins
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW); // Ensure relay is OFF on boot

    // 3. Connect to Wi-Fi
    Serial.print("[WiFi] Connecting to: ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\n[WiFi] Connected!");
    Serial.print("[WiFi] IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("[WiFi] Signal (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
    Serial.println("----------------------------------------");
    Serial.println("[Dashboard] Open web-dashboard/index.html");
    Serial.println("[Dashboard] Enter this IP to connect the dashboard.");
    Serial.println("----------------------------------------");

    // 4. Register API Routes
    //    Dashboard endpoints (v2.0)
    server.on("/api/status", HTTP_GET,     handleStatus);
    server.on("/api/relay",  HTTP_POST,    handleRelayPost);
    server.on("/api/relay",  HTTP_OPTIONS, handleOptions);   // CORS preflight

    //    Legacy endpoints (v1.0 — preserved for backward compatibility)
    server.on("/api/on",  HTTP_GET, handleRelayOn);
    server.on("/api/off", HTTP_GET, handleRelayOff);

    // 5. Start the HTTP Server
    server.begin();
    Serial.println("[Server] HTTP server listening on port 80.");
}

// -----------------------------------------------------------------------
// Loop
// -----------------------------------------------------------------------
void loop() {
    server.handleClient();
}