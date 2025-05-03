#include <Arduino.h>
#include <ESP32Servo.h>
#include <globals.h>

//Definir variable de contador
int countColors[6] = {0,0,0,0,0,0};

//Definir objeto tipo servo
Servo servo1, servo2;

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}