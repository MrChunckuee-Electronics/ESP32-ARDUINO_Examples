/*******************************************************************************
 *
 *          ESP32: Manejo del LED RGB (WS2812)
 *
 *******************************************************************************
 * FileName:        ESP32-S2-Saola-1R_WS2812_RGBLed_FaddingColors.ino
 * Processor:       ESP32-S2-WROVER
 * Complier:        Arduino IDE v1.8.19
 * Blog:            http://mrchunckuee.blogspot.com/
 * Description:     Pequeño ejemplo para testear LED RGB de la board, haciendo 
 *                  degradado de los colores.
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.0.0     02/12/2024      - Creación y prueba de funcionamiento 
 ******************************************************************************/
#include <Adafruit_NeoPixel.h>

// ESP32S2 SAOLA 1R GPIO the WS2812 Led.
#define PIN        18 

//Single WS2812 config
Adafruit_NeoPixel pixels(1, PIN, NEO_GRB + NEO_KHZ800);

int colorCount = 0;
unsigned long previousMillis = 0;     
const long interval = 30;   // Time (in milliseconds) to pause between color change

void setup() {
  pixels.setBrightness(50);
  pixels.begin(); 
  pixels.show();  // WS2812 Led = Off
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    //Set the new color
    pixels.setPixelColor(0, Wheel(colorCount));

    // Updated pixel colors
    pixels.show();   

    //Change the colors and limit the end
    colorCount++;
    if (colorCount > 255)
        colorCount = 0;
  } 
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
