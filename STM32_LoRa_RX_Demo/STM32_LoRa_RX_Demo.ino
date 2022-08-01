//திருச்சிற்றம்பலம்
#include <SPI.h>
#include <LoRa_STM32.h>

#define SS PA4
#define RST PB0
#define DIO PA1

#define TX_P 17
#define BAND 433E6
#define ENCRYPT 0X78

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Receiver");
  LoRa.setTxPower(TX_P);
  LoRa.setSyncWord(ENCRYPT);
  LoRa.setPins(SS, RST, DIO);

  if (!LoRa.begin(BAND))
  {
    Serial.println("Starting LoRa failed!");
    while(1);
  }
}

void loop()
{
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    Serial.print("Received packet '");
    while (LoRa.available())
    {
      Serial.print((char)LoRa.read());
    }
    Serial.print("' with RSSI ");
    Serial.print(LoRa.packetRssi());
   } 
}
