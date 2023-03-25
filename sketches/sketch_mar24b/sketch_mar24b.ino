#include <EEPROM.h>
int value;
void setup(){
  Serial.begin(115200);
  EEPROM.write(0,1);
  EEPROM.write(1,2);
  EEPROM.write(2,3);
  EEPROM.write(3,4);
}

void loop(){\
  value = EEPROM.read(0);
  Serial.println(value);
 }
