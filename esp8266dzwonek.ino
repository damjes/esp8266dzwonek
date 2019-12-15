#include <ESP8266WiFi.h>

#include "tajne.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  Serial.print("Mounting FS...");

  if (!SPIFFS.begin()) {
    Serial.println("\nFailed to mount file system");
    return;
  } else {
    Serial.println(" OK!");
    Serial.print("Otwieranie pliku...");
    File plik = SPIFFS.open("/test.txt", "r");
    if (plik) {
      Serial.println(" OK!");
      Serial.println("Zawartosc:");
      String dane = plik.readString();
      Serial.println(dane);
    } else {
      Serial.println("");
      Serial.println("Failed to open config file");
    }
  }

  przygotujOTA();
  
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  robOTA();
}
