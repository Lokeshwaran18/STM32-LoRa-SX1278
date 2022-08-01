//திருச்சிற்றம்பலம்
#include <SPI.h>
#include <LoRa_STM32.h>

#define SS PA4
#define RST PB0
#define DIO PA1

#define TX_P 17
#define BAND 433E6
#define ENCRYPT 0X78

  String counter;
  String temperature;
  String pressure;
  String altitude;
  String humidity;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.print("LoRa Receiver");
  LoRa.setSyncWord(ENCRYPT);
  LoRa.setPins(SS, RST, DIO);
  if (!LoRa.begin(BAND))
  {
    Serial.println("Starting LoRa failed!")
  }
}

void loop()
{
  int pos1,pos2,pos3,pos4;
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    Serial.print("Received packet:  ");
    String LoRaData = LoRa.readString();
    Serial.print(LoRaData);
    while (LoRa.available())
    {
      Serial.print((char)LoRa.read());
    }
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());

    pos1 = LoRaData.indexOf('/');
    pos2 = LoRaData.indexOf('&');
    pos3 = LoRaData.indexOf('#');
    pos4 = LoRaData.indexOf('@');
    counter = LoRaData.substring(0, pos1);
    temperature = LoRaData.substring(pos1+1,pos2);
    pressure = LoRaData.substring(pos2+1,pos3);
    altitude = LoRaData.substring(pos3+1,pos4);
    humidity = LoRaData.substring(pos4+1,LoRaData.length());
    Serial.print(F("Packet No. = "));
    Serial.println(counter)
    Serial.print(F("Temperature = "));
    Serial.print(temperature);
    Serial.println(F("*C"));
    Serial.print(F("Pressure = "));
    Serial.print(pressure);
    Serial.println(F("hPa"));
    Serial.print(F("Approx. Altitude = "));
    Serial.print(altitude);
    Serial.println(F("m"));
    Serial.print(F("Humidity = "));
    Serial.print(humidity);
    Serial.print(F("%"));
    Serial.println();    
  }
}
