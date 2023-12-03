/*******************************************************************************
 *
 *          ESP32: Manejo del bluetooth clasico - Blink LED desde una APP 
 *
 *******************************************************************************
 * FileName:        ESP32_ClassicBT_APP_BlinkLED.ino
 * Processor:       ESP32
 * Complier:        Arduino IDE v2.2.1
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Pequeño ejemplo para testear el SP32 como bluetooth clasico, 
 *                  una vez que se recibe el dato por el bluetooth dependiendo 
 *                  del valor el LED entra o no en modo blinker.
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.0.0     03/12/2023      - Creación y prueba de funcionamiento 
 ******************************************************************************/

#include "BluetoothSerial.h"

#define USE_PIN // Uncomment this to use PIN during pairing. The pin is specified on the line below
const char *pin = "1234"; // Change this to more secure PIN.

String device_name = "MrChunckuee-BT-Test";

BluetoothSerial SerialBT;

unsigned char inSerialData;
bool ledState = true, flagLEDStatus = false;
long previousMillis = 0;  // will store last time LED was updated
long delayTime = 500;    // delayTime at which to blink (milliseconds)
unsigned long currentMillis = 0;

void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name); //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  #ifdef USE_PIN
    SerialBT.setPin(pin);
    Serial.println("Using PIN");
  #endif
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, ledState);
}

void loop() {
  if (SerialBT.available()) {
    inSerialData = SerialBT.read();
    switch (inSerialData){
      case 'a':
        flagLEDStatus = true;
      break;
      case 'b':
        flagLEDStatus = false;
      break;
      default:
      break;
    }
  }
  delay(20);
  if(flagLEDStatus){
    currentMillis = millis();
    if(currentMillis - previousMillis > delayTime) {
      previousMillis = currentMillis;
      if(ledState){
        ledState = 0;
        digitalWrite(LED_BUILTIN, ledState);
      }
      else{
        ledState = 1;
        digitalWrite(LED_BUILTIN, ledState);
      } 
    }
  }
}
