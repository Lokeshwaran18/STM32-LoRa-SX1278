//திருச்சிற்றம்பலம்
#include <Wire.h>
#include <SPI.h>
#include <LoRa_STM32.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define NSS PA4
#define RST PB0
#define DIO PA1

#define TX_P 17
#define BAND 433E6
#define ENCRYPT 0x78

int counter = 0;
String LoRaMessage = "";

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(F("LoRa Sender"));
  LoRa.setSyncWord(ENCRYPT);
  LoRa.setPins(NSS, RST, DIO);
  if (!LoRa.begin(BAND))
  {
    Serial.println(F("Starting LoRa failed !"));
    while (1);
  }
  if (!bme.begin(0X76))
  {
    Serial.println("Could not find a valid BME280 Sensor, Check wiring!");
    while(1);
  }
}


void loop()
{
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F;
  float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  float humidity = bme.readHumidity();

  Serial.print(F("Sending packet: "));
  Serial.println(counter);
  Serial.print(F("Temperature = "));
  Serial.print(temperature);
  Serial.println(F("*C");
  Serial.print(F("Pressure = "));
  Serial.print(pressure);
  Serial.println(F("hPa"));
  Serial.print(F("Approx. Altitude = "));
  Serial.print(altitude);
  Serial.println(F("m"));
  Serial.print(F("Humidity = "));
  Serial.print(humidity);
  Serial.println(F("%"));
  Serial.println();
  LoRaMessage = String(counter) + "/" + String(temperature) + "&" + String(pressure) + "#" + String(altitude) + "@" + String(humidity);
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket();
  counter++;
  delay(3000);
}
