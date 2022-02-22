#include <Arduino.h>
#include <ArduinoOTA.h>

#include "config.h"
#include "ranging.h"
#include "desk.h"
#include "buttons.h"
#include "serial.h"

void setup() {
    pinMode(21, OUTPUT);
    digitalWrite(21, HIGH);

    deskSetup();
    buttonsSetup();

    serialSetup();
    Serial.println("Booting...");

    WiFi.mode(WIFI_STA);
    WiFi.setHostname(WIFI_HOSTNAME);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.println("WiFi initialized");

    ArduinoOTA.setHostname(WIFI_HOSTNAME);
    ArduinoOTA.setPassword(OTA_PASSWORD);
    ArduinoOTA.begin();

    Serial.println("OTA initialized");

    rangingSetup();

    Serial.println("Boot complete");
}

void loop() {
    serialLoop();
    rangingLoop();
    deskLoop();
}
