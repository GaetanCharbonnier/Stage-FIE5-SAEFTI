/*
#include <Arduino.h>
#include <Multichannel_Gas_GMXXX.h>
#include <Wire.h>

GAS_GMXXX<TwoWire> gas;

void setup() {
  // put your setup code here, to run once:
  //Wire.begin ();
  gas.begin(Wire, 0x08); // Essayer 0x55 ------ use the hardware I2C  
  Serial.begin(9600);
}
 
void loop() {

  Serial.println("...");
  delay(1000);
  
  // put your main code here, to run repeatedly:
  int val;
  int val2;
  int val3;
  int val4;

  // GM102B NO2 sensor
  val = gas.getGM102B();
  if (val > 999) val = 999;
  
  Serial.print("gas102B ppm = ");
  Serial.println(val);

// GM302B C2H5CH sensor
  val2 = gas.getGM302B();
  if (val2 > 999) val2 = 999;
   
  Serial.print("gas302B ppm = ");
  Serial.println(val2);

  // GM502B VOC sensor
  val3 = gas.getGM502B();
  if (val3 > 999) val3 = 999;
 
  Serial.print("gas502B ppm = ");
  Serial.println(val3);
  
  // GM702B CO sensor
  val4 = gas.getGM702B();
  if (val4 > 999) val4 = 999;
 
  Serial.print("gas702B ppm = ");
  Serial.println(val4);
  
  delay(100);
}
*/