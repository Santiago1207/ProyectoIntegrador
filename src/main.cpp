#include <Arduino.h>
#include <ESP32Servo.h>
#include <globals.h>
#include <TCS3200Raw.h>

//Definir variable de contador
uint16_t countColors[6] = {0,0,0,0,0,0};

//Definir objeto tipo servo
Servo servo1, servo2;

void setup() {
  Serial.begin(115200);

  pinMode(TCS3200[0], OUTPUT);  pinMode(TCS3200[1], OUTPUT);
  pinMode(TCS3200[2], OUTPUT);  pinMode(TCS3200[3], OUTPUT);
  pinMode(TCS3200[5], INPUT);
  pinMode(PIN_LED, OUTPUT);

  digitalWrite(TCS3200[0], HIGH);     // escala 20 %
  digitalWrite(TCS3200[1], LOW);

  Serial.println("TCS3200 – prueba de lectura cruda");
}

void loop() {
  uint32_t R, G, B;
  readRawRGB(R, G, B);

  Serial.printf("R=%lu\tG=%lu\tB=%lu\n", R, G, B);
  delay(100);   // 10 Hz solo para visualizar; bajaremos después
}