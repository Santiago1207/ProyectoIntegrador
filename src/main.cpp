#include <Arduino.h>
#include <ESP32Servo.h>
#include <globals.h>
#include <TCS3200Black.h>
#include <ColorModels.h>

// ------------------- Captura de un color -------------
void captureColor(uint8_t idx) {
  float r[N_SAMPLES], g[N_SAMPLES], b[N_SAMPLES];

  Serial.printf("Capturando color %u. Mantén el dulce quieto…\n", idx);
  for (uint8_t i=0;i<N_SAMPLES;i++) {
    readNormalized(r[i], g[i], b[i]);
    delay(15);
  }

  // Ordenamos para trimming
  std::sort(r, r+N_SAMPLES);
  std::sort(g, g+N_SAMPLES);
  std::sort(b, b+N_SAMPLES);

  float sumR=0,sumG=0,sumB=0;
  for (uint8_t i=TRIM;i<N_SAMPLES-TRIM;i++) {
    sumR += r[i]; sumG += g[i]; sumB += b[i];
  }
  float muR = sumR / (N_SAMPLES-2*TRIM);
  float muG = sumG / (N_SAMPLES-2*TRIM);
  float muB = sumB / (N_SAMPLES-2*TRIM);

  // σ
  float sR=0,sG=0,sB=0;
  for (uint8_t i=TRIM;i<N_SAMPLES-TRIM;i++) {
    sR += sq(r[i]-muR);
    sG += sq(g[i]-muG);
    sB += sq(b[i]-muB);
  }
  float sdR = sqrtf(sR/(N_SAMPLES-2*TRIM));
  float sdG = sqrtf(sG/(N_SAMPLES-2*TRIM));
  float sdB = sqrtf(sB/(N_SAMPLES-2*TRIM));

  models[idx] = {{muR,muG,muB},{sdR,sdG,sdB},true};
  saveModel(idx);

  Serial.printf("Color %u entrenado: μ=[%.3f,%.3f,%.3f]  σ=[%.3f,%.3f,%.3f]\n",
                idx,muR,muG,muB, sdR,sdG,sdB);
}

// ------------------- Comandos serie ------------------
void handleCommand(String line) {
  line.trim();
  if (line=="m") {
    for (uint8_t c=0;c<N_COLORS;c++) {
      if (models[c].valid) {
        Serial.printf("%u: μ=[%.3f,%.3f,%.3f] σ=[%.3f,%.3f,%.3f]\n",
                      c, models[c].mu[0],models[c].mu[1],models[c].mu[2],
                      models[c].sigma[0],models[c].sigma[1],models[c].sigma[2]);
      } else Serial.printf("%u: <vacío>\n",c);
    }
  } else if (line.startsWith("c ")) {
    char code = line.charAt(2);
    uint8_t idx = 255;
    if (code=='r') idx=RED;
    if (code=='o') idx=ORANGE;
    if (code=='y') idx=YELLOW;
    if (code=='g') idx=GREEN;
    if (code=='b') idx=BLUE;
    if (code=='f') idx=BROWN;
    if (idx!=255) captureColor(idx);
  } else if (line=="x") {
    prefs.clear();   // borra NVS
    for (auto &m:models) m.valid=false;
    Serial.println("Modelos borrados.");
  }
}


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
  //handleCommand(line);
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