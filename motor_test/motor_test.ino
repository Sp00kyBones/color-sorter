#include <AccelStepper.h>
#include <MultiStepper.h>

// Define stepper motor connections and steps per revolution:
#define dirPinL 2
#define stepPinL 3
#define dirPinR 12
#define stepPinR 11
#define stepsPerRevolution 80

//trying to control start/stop using serial
bool running = false;

void setup()
{
  Serial.begin(9600);
  running = false;
  // Declare pins as output:
  pinMode(stepPinL, OUTPUT);
  pinMode(dirPinL, OUTPUT);
  pinMode(stepPinR, OUTPUT);
  pinMode(dirPinR, OUTPUT);
}
void loop()
{

  switch (Serial.read())
  {
  case '1':
    running = true;
    Serial.print("start, ");
    break;
  case '2':
    running = false;
    Serial.print("stopped, ");
    break;
  }
  if (running = true)
  {

    // Set the spinning direction clockwise:
    digitalWrite(dirPinR, HIGH);
    // rotate right and left stepper motor to allow red ball to drop:
    for (int i = 0; i < stepsPerRevolution; i++)
    {
      // These four lines result in 1 step:
      digitalWrite(stepPinR, HIGH);
      delayMicroseconds(250);
      digitalWrite(stepPinR, LOW);
      delayMicroseconds(250);
    }
    delay(1000);
    // Set the spinning direction counterclockwise:
    digitalWrite(dirPinL, LOW);
    // Spin the stepper motor 1 revolution quickly:
    for (int i = 0; i < stepsPerRevolution; i++)
    {
      // These four lines result in 1 step:
      digitalWrite(stepPinL, HIGH);
      delayMicroseconds(250);
      digitalWrite(stepPinL, LOW);
      delayMicroseconds(250);
    }
  }
}
