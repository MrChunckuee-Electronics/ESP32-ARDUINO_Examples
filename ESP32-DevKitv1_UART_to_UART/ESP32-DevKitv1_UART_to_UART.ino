/*******************************************************************************
 *
 *          ESP32: Uso de puertos seriales
 *
 *******************************************************************************
 * FileName:        ESP32-DevKitv1_UART_to_UART.ino
 * Processor:       ESP32
 * Complier:        Arduino IDE v2.3.3
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Pequeño ejemplo para testear el manejo del puerto serial 2 
 *                  que incorpora el ESP32-WROOM. Como sabemos este incroporta 
 *                  tres puertos seriales por hardware: U0UXD, U1UXD y U2UXD.
 *                     - U0UXD, se usa principalmente para programar el modulo, 
 *                              pero tambien puede ser de proposito general.
 *                     - U1UXD, se usa para comunicar con una memoria SPI flash 
 *                              interna del ESP32. No recomendable para el usar.
 *                     - U2UXD, libre para proposito general.
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.0.0     17/11/2024      - Creación y prueba de funcionamiento.
 *   v1.0.1     04/12/2024      - Correecion para asegurarnos el uso de U2UXD.
 ******************************************************************************/
 
#define RXD2 16
#define TXD2 17

void setup() {
  Serial.begin(115200);
  //Formato configurar serial 1: Serial1.begin(baud-rate, protocol, RX pin, TX pin);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  Serial.println("U0UXD - Serial TXD is on pin: "+String(TX));
  Serial.println("U0UXD - Serial RXD is on pin: "+String(RX));
  
  Serial2.println("U2UXD - Serial TXD is on pin: "+String(TXD2)); 
  Serial2.println("U2UXD - Serial RXD is on pin: "+String(RXD2)); 
}

void loop() {
  // Leemos puerto 2 y enviamos al puerto 0:
  if (Serial2.available()) {
    int inByte = Serial2.read();
    Serial.write(inByte);
  }

  // Leemos puerto 0 y enviamos al puerto 2:
  if (Serial.available()) {
    int inByte = Serial.read();
    Serial2.write(inByte);
  }
}
