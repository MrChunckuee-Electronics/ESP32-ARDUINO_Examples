/*******************************************************************************
 *
 *          ESP32: Manejo del LED RGB (WS2812)
 *
 *******************************************************************************
 * FileName:        ESP32-S2-Saola-1R_WS2812_RGBLed_Colors.ino
 * Processor:       ESP32-S2-WROVER
 * Complier:        Arduino IDE v1.8.19
 * Blog:            http://mrchunckuee.blogspot.com/
 * Description:     Pequeño ejemplo para testear LED RGB de la board
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
uint32_t patternColorsLED[] = {0x000000, 0x0000FF, 0x00FF00, 0x00FFFF, 0xFF0000, 0xFF00FF, 0xFFFF00, 0xFFFFF, };
unsigned long previousMillis = 0;     
const long interval = 500;   // Time (in milliseconds) to pause between color change

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
    pixels.setPixelColor(0, patternColorsLED[colorCount]);

    // Updated pixel colors
    pixels.show();   

    //Change the colors and limit the end
    colorCount++;
    if (colorCount > 7)
        colorCount = 0;
  } 
}
