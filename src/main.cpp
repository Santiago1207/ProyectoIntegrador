#include <Arduino.h>
#include <ESP32Servo.h>
#include <globals.h>
#include <TCS3200Black.h>

void setup()
{
  Serial.begin(115200);
  prefs.begin("TCS3200", false); // namespace

  if (calibDataAvailable())
  {
    loadcalibData();
    Serial.println(F("Calibracion cargada."));
  }
  else
  {
    Serial.println(F("Sin calibracion. Escribe 'n' y 'w' para crearla."));
  }
  Serial.println(F("Comandos: n=negro  w=blanco  r=lectura normalizada"));

  pinMode(TCS3200[0], OUTPUT);
  pinMode(TCS3200[1], OUTPUT);
  pinMode(TCS3200[2], OUTPUT);
  pinMode(TCS3200[3], OUTPUT);
  pinMode(TCS3200[5], INPUT);
  pinMode(PIN_LED, OUTPUT);

  digitalWrite(TCS3200[0], HIGH); // escala 20 %
  digitalWrite(TCS3200[1], LOW);
}

void loop()
{
  if (Serial.available())
  {
    char c = Serial.read();
    if (c == 'n')
      doBlackcalibData();
    if (c == 'w')
      doWhitecalibData();
    if (c == 'r')
    {
      float r, g, b;
      readNormalized(r, g, b);
      Serial.printf("R'=%0.3f\tG'=%0.3f\tB'=%0.3f\n", r, g, b);
    }
  }
}