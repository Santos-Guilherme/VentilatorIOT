//define BLYNK_PRINT Serial
//define BLYNK_DEFAULT_PORT 80
#define BLYNK_TEMPLATE_ID "TMPL2KYed0-RL"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "rZWaDMBYDbqd5CFQkthfEPMXmO2XyyRJ"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"

#define DHTPIN D5 // Pino digital conectado ao sensor DHT
#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
#define FAN_PIN D2 // relé do ventilador

char auth[] = "rZWaDMBYDbqd5CFQkthfEPMXmO2XyyRJ";
char ssid[] = "iPhone de Gabriel";
char pass[] = "123456789";

float tempDHT;
bool fanOn = false;
float val = 26.00;

// inicializa o sensor DHT.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
  Serial.println(F("Teste DHTXX!"));
  dht.begin();
}

void loop() {
  Blynk.run();
  delay(2000);
  tempDHT = dht.readTemperature();

  if (isnan(tempDHT)) {
    Serial.println("Falha ao ler o sensor DHT!");
    return;
  }

  Serial.print(F("Temperatura: "));
  Serial.print(tempDHT);
  Serial.print(F("°C "));
  Serial.println();

  Serial.println();

  if (tempDHT >= 25.00) {
    pinMode(FAN_PIN, OUTPUT);
    Serial.println("Fan ligado");
  }
  else {
    pinMode(FAN_PIN, INPUT);
    Serial.println("Fan desligado");
  }

  Blynk.virtualWrite(V1, tempDHT); // Envie a temperatura para o widget virtual V1 do Blynk
}