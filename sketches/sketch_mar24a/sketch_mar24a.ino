#include <Arduino_FreeRTOS.h>
#include <EEPROM.h>
int val0, val1, val2, val3;
void setup()
//Initialize the Serial Monitor with 9600 baud rate
{
Serial.begin(115200);

 xTaskCreate(Read0, "Read1", 100, NULL, 1, NULL);
 xTaskCreate(Read1, "Read2", 100, NULL, 2, NULL);
 xTaskCreate(Read2, "Read3", 100, NULL, 3, NULL);
 xTaskCreate(Idle, "Idle", 100, NULL, 0, NULL);
}

void loop()
{}

static void Read0(void* pvParameters)
{
 
  while(1)

  { 
    val0 = EEPROM.read(0);
    Serial.println(val0);

    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

static void Read1(void* pvParameters)
{
 
  while(1)

  { 
    val1 = EEPROM.read(1);
    Serial.println(val1);

    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

static void Read2(void* pvParameters)
{ 
while(1)
  { 
    val2 = EEPROM.read(2);
    Serial.println(val2);

    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

//This is the idle task which has the most higher priority and calls when no task is running.

static void Idle(void* pvParameters)

{
  while(1)
   { 
    Serial.println(F("Idle state"));
     val3 = EEPROM.read(3);
     Serial.println(val3);
    delay(50);
  }  
}
