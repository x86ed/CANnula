#include <SPI.h>
#include "mcp2515_can.h"
#include <Arduino_FreeRTOS.h>
#include <EEPROM.h>
int val0, val1, val2;
const int SPI_CS_PIN = 10;
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() 
{
Serial.begin(115200);
   while(!Serial){};
   // init can bus : baudrate = 500k
   while (CAN_OK != CAN.begin(CAN_500KBPS)) {
      Serial.println("CAN init fail, retry...");
      delay(100);
   }
   Serial.println("CAN init ok!");
  
xTaskCreate(Read, "Read", 100, NULL, 0, NULL);
xTaskCreate(Ver, "Ver", 100, NULL, 1,NULL);

}

void loop() {}

static void Read(void* pvParameters)
{
    while(1)
  { 
  Serial.println("read");
  vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

static void Ver(void* pvParameters)
{
  char buffer [6];
    while(1)
  { 
  val0 = EEPROM.read(0);
  val1 = EEPROM.read(1);
  val2 = EEPROM.read(2);
  sprintf(buffer, "v%d.%d.%d",val0,val1,val2 );
  Serial.println(buffer);

   stmp[7] = stmp[7] + 1;
   if (stmp[7] == 100) {
      stmp[7] = 0;
      stmp[6] = stmp[6] + 1;
      if (stmp[6] == 100) {
         stmp[6] = 0;
         stmp[5] = stmp[5] + 1;
      }
   }
   CAN.sendMsgBuf(0x00, 0, 8, stmp);
  vTaskDelay(100/portTICK_PERIOD_MS);
  }
}
