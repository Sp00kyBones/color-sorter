#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <AccelStepper.h>
#include <MultiStepper.h>

// Define connections and steps per revolution:
#define dirPinL 2
#define stepPinL 3
#define LED 7
#define motor5V 8
#define dirPinR 12
#define stepPinR 11
#define stepsPerRevolution 96

//serial monitor declarations
byte gammatable[256];
bool running = false;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup()
{

  Serial.begin(9600);
  running = false;

  // Declare motor step/direction pins + LED as output
  pinMode(stepPinL, OUTPUT);
  pinMode(dirPinL, OUTPUT);
  pinMode(stepPinR, OUTPUT);
  pinMode(dirPinR, OUTPUT);
  pinMode(motor5V, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.print("\nChecking color sensor connections");
  delay(500);
  for (int x = 0; x <= 3; x++)
  {
    digitalWrite(LED, LOW);
    delay(1000);
    digitalWrite(LED, HIGH);
    Serial.print(".");
    delay(1000);
  }
  if (tcs.begin())
  {
    Serial.println("\nSensor detected");
    delay(2000);
    Serial.println("\nWould you like to start the color sorting sequence(Y/N)? ");
  }
  else
  {
    Serial.println("No TCS34725 found ... check your connections");
    while (1)
      ; // halt!
  }
  // defining parameters for red green blue readings
  for (int i = 0; i < 256; i++)
  {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
  }
}

void loop()
{

  switch (Serial.read())
  {
  case 'Y':
    running = true;
    digitalWrite(motor5V, HIGH);
    delay(1000);
    Serial.print("Motors energized \n");
    delay(3000);
    Serial.print("Commencing 'MOTOR TEST' sequence");
    delay(3000);
    // motor test sequence:
    for (int x = 0; x <= 4; x++)
    { // test sequence consists of 4 cycles

      // Stepping R-motor CW & L-motor CCW ("CRADLE" position)
      digitalWrite(dirPinR, LOW); // writing dirPin LOW = CW
      for (int i = 0; i < stepsPerRevolution * 2; i++)
      {
        digitalWrite(stepPinR, HIGH); // writing stepPin HIGH = on
        delayMicroseconds(4000);      // how fast the motor will turn, as value increases motor rotates slower
        digitalWrite(stepPinR, LOW);  // writing stepPin LOW = off
        delayMicroseconds(4000);
        digitalWrite(dirPinL, HIGH); // writing dirPin HIGH = CCW
        digitalWrite(stepPinL, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinL, LOW);
        delayMicroseconds(4000);
      }

      delay(1000);
      // Stepping R-motor CCW & L-motor CW ("RED ball" position)
      digitalWrite(dirPinR, HIGH);
      for (int i = 0; i < stepsPerRevolution; i++)
      {
        digitalWrite(stepPinR, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinR, LOW);
        delayMicroseconds(4000);
        digitalWrite(dirPinL, LOW);
        digitalWrite(stepPinL, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinL, LOW);
        delayMicroseconds(4000);
      }

      delay(1000);
      // Stepping R-motor CW & L-motor CCW (Return to "CRADLE" position)
      digitalWrite(dirPinR, LOW);
      for (int i = 0; i < stepsPerRevolution; i++)
      {
        digitalWrite(stepPinR, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinR, LOW);
        delayMicroseconds(4000);
        digitalWrite(dirPinL, HIGH);
        digitalWrite(stepPinL, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinL, LOW);
        delayMicroseconds(4000);
      }

      delay(1000);
      // Stepping R-motor CW & L-motor CW ("GREEN ball" position)
      digitalWrite(dirPinR, LOW);
      digitalWrite(dirPinL, LOW);
      for (int i = 0; i < stepsPerRevolution; i++)
      {
        digitalWrite(stepPinR, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinL, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinR, LOW);
        delayMicroseconds(4000);
        digitalWrite(stepPinL, LOW);
        delayMicroseconds(4000);
        digitalWrite(stepPinL, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinL, LOW);
        delayMicroseconds(4000);
      }

      delay(1000);
      // Stepping R-motor CCW & L-motor CCW (Return to "CRADLE" position
      digitalWrite(dirPinR, HIGH);
      digitalWrite(dirPinL, HIGH);
      for (int i = 0; i < stepsPerRevolution; i++)
      {
        digitalWrite(stepPinR, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinL, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinR, LOW);
        delayMicroseconds(4000);
        digitalWrite(stepPinL, LOW);
        delayMicroseconds(4000);
        digitalWrite(stepPinL, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinL, LOW);
        delayMicroseconds(4000);
      }

      delay(1000);
      // Stepping R-motor CCW & L-motor CCW ("BLUE ball" position)
      digitalWrite(dirPinR, HIGH);
      digitalWrite(dirPinL, HIGH);
      for (int i = 0; i < stepsPerRevolution; i++)
      {
        digitalWrite(stepPinR, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinL, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinR, LOW);
        delayMicroseconds(5000);
        digitalWrite(stepPinL, LOW);
        delayMicroseconds(4000);
        digitalWrite(stepPinR, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinR, LOW);
        delayMicroseconds(5000);
      }

      delay(1000);
      // Stepping R-motor CW & L-motor CW (Return to "CRADLE" position)
      digitalWrite(dirPinR, LOW);
      digitalWrite(dirPinL, LOW);
      for (int i = 0; i < stepsPerRevolution; i++)
      {
        digitalWrite(stepPinR, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinL, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinR, LOW);
        delayMicroseconds(4000);
        digitalWrite(stepPinL, LOW);
        delayMicroseconds(4000);
        digitalWrite(stepPinR, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinR, LOW);
        delayMicroseconds(4000);
      }

      delay(1000);
      // Stepping R-motor CW & L-motor CCW (Return to "Open" position)
      digitalWrite(dirPinR, HIGH);
      for (int i = 0; i < stepsPerRevolution * 2; i++)
      {
        digitalWrite(stepPinR, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinR, LOW);
        delayMicroseconds(4000);
        digitalWrite(dirPinL, LOW);
        digitalWrite(stepPinL, HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinL, LOW);
        delayMicroseconds(4000);
      }

      delay(1000);
      Serial.print("."); // visual indication one cycle completed
    }
  }
  if (running == true)
  {
    delay(3000);
    Serial.println("\t'MOTOR TEST' complete");
    delay(1000);
    digitalWrite(motor5V, LOW);
    Serial.println("Motor de-energized");
    delay(2000);
    Serial.println("You may now fill the hopper");
    delay(5000);
    Serial.println("After you fill the hopper, ensure that the enclosure is closed and enter Y to start sorting the balls. \t***press N to stop the process***");
    running = false;
  }
}
