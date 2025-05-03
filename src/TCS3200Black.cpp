#include <Arduino.h>
#include <Preferences.h>          // NVS
#include <TCS3200Raw.h>           // (etapa 1) funciones readRawRGB()
#include <globals.h>

// ───────── Helpers ─────────
bool calibDataAvailable() {
  return prefs.getBool("valid", false);
}

void loadcalibData() {
  calibData.R0 = prefs.getULong("R0", 0);
  calibData.G0 = prefs.getULong("G0", 0);
  calibData.B3 = prefs.getULong("B3", 0);
  calibData.R1 = prefs.getULong("R1", 1);  // evita /0
  calibData.G1 = prefs.getULong("G1", 1);
  calibData.B4 = prefs.getULong("B4", 1);
}

void savecalibData() {
  prefs.putULong("R0", calibData.R0); prefs.putULong("G0", calibData.G0); prefs.putULong("B3", calibData.B3);
  prefs.putULong("R1", calibData.R1); prefs.putULong("G1", calibData.G1); prefs.putULong("B4", calibData.B4);
  prefs.putBool("valid", true);
  Serial.println(F("✓ Calibracion guardada."));
}

inline float norm(uint32_t x, uint32_t x0, uint32_t x1) {
  if (x <= x0 || x1 <= x0) return 0.0f;
  float v = float(x - x0) / float(x1 - x0);
  if (v < 0) v = 0; else if (v > 1) v = 1;
  return v;
}

void readNormalized(float &r_, float &g_, float &b_) {
  uint32_t R,G,B; readRawRGB(R,G,B);          // etapa 1
  r_ = norm(R, calibData.R0, calibData.R1);
  g_ = norm(G, calibData.G0, calibData.G1);
  b_ = norm(B, calibData.B3, calibData.B4);
}

// ───────── Calibracion interactiva ─────────
void doBlackcalibData() {
  Serial.println(F("→ Tomando negro…"));
  delay(300);
  readRawRGB(calibData.R0, calibData.G0, calibData.B3);
  Serial.printf("Negro  R0=%lu G0=%lu B3=%lu\n", calibData.R0, calibData.G0, calibData.B3);
}

void doWhitecalibData() {
  Serial.println(F("→ Tomando blanco…"));
  delay(300);
  readRawRGB(calibData.R1, calibData.G1, calibData.B4);
  Serial.printf("Blanco R1=%lu G1=%lu B4=%lu\n", calibData.R1, calibData.G1, calibData.B4);
  savecalibData();
}