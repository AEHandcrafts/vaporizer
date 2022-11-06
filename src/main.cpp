#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "config.h"

AsyncWebServer server(SERVER_PORT);
bool vaporize = false;

void setup() {
    Serial.begin(9600);

    pinMode(VAPORIZER_PIN, OUTPUT);
    digitalWrite(VAPORIZER_PIN, HIGH);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) delay(100);

    server.on("/vaporize", HTTP_GET, [](AsyncWebServerRequest* request){
        vaporize = true;
        request->send(200);
    });
    server.begin();

    Serial.println("Vaporizer is up and running at http://" + WiFi.localIP().toString());
}

void loop() {
    if (vaporize) {
        digitalWrite(VAPORIZER_PIN, LOW);
        delay(VAPORIZER_DURATION);
        digitalWrite(VAPORIZER_PIN, HIGH);
        vaporize = false;
    }
}
