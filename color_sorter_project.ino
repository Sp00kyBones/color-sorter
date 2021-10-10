#include <Wire.h>
#include "Adafruit_TCS34725.h"
 
/* Example code for the Adafruit TCS34725 breakout library */
 
/* Connect SCL to analog 5
Connect SDA to analog 4
Connect VDD to 3.3V DC
Connect GROUND to common ground */

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_1X);
 
void setup(void) {
Serial.begin(9600);
pin
 
if (tcs.begin()) {
Serial.println("Found sensor");
} else {
Serial.println("No TCS34725 found ... check your connections");
while (1);
}
 
// Now we're ready to get readings!
}
 
void loop(void) {
uint16_t r, g, b, c, colorTemp, lux;
 
tcs.getRawData(&r, &g, &b, &c);
colorTemp = tcs.calculateColorTemperature(r, g, b);
lux = tcs.calculateLux(r, g, b);
 
Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
Serial.println(" ");
}

//blue    Color Temp: 5885 K - Lux: 464 - R: 840 G: 797 B: 712 C: 2442
//green   Color Temp: 4223 K - Lux: 1456 - R: 892 G: 1440 B: 720 C: 3212 
//red     Color Temp: 21934 K - Lux: 65297 - R: 2430 G: 601 B: 545 C: 3468 
