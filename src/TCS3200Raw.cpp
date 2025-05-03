#include <Arduino.h>
#include <globals.h>

// Duración de la ventana de conteo (µs)
constexpr uint32_t WINDOW_US = 2400;  // ≈2,4 ms  → ~400 lecturas/seg

//Declaración de todas las funciones
void setColorFilter(uint8_t,uint8_t);

//Funcion para definir la escala de frecuencia del sensor de color
void setColorFilter(uint8_t r, uint8_t g) {
    // r,g → 0 o 1  según la tabla de la hoja de datos
    digitalWrite(TCS3200[2], r);
    digitalWrite(TCS3200[3], g);
}  

//Funcion de contador de pulsos digitales
uint32_t countPulses(uint32_t window_us) {
    uint32_t start = micros(), pulses = 0, now;
    int last = digitalRead(TCS3200[5]);
    while ((now = micros()) - start < window_us) {
      int val = digitalRead(TCS3200[5]);
      if (val != last) {            // flanco
        if (val == HIGH) pulses++;  // cuenta pulsos solo en LOW→HIGH
        last = val;
      }
    }
    return pulses;
}

// ───────── Medición con y sin LED ─────────
void readRawRGB(uint32_t &R, uint32_t &G, uint32_t &B) {
    // 1) LED OFF  → ambiente
    digitalWrite(PIN_LED, LOW);
    delayMicroseconds(50);          // estabiliza
    setColorFilter(LOW, LOW);  R = countPulses(WINDOW_US);   // Red
    setColorFilter(HIGH, HIGH); G = countPulses(WINDOW_US);  // Green
    setColorFilter(LOW, HIGH); B = countPulses(WINDOW_US);   // Blue
    uint32_t Ra = R, Ga = G, Ba = B; // ambiente
  
    // 2) LED ON → señal+ambiente
    digitalWrite(PIN_LED, HIGH);
    delayMicroseconds(50);
    setColorFilter(LOW, LOW);  R = countPulses(WINDOW_US);
    setColorFilter(HIGH, HIGH); G = countPulses(WINDOW_US);
    setColorFilter(LOW, HIGH); B = countPulses(WINDOW_US);
  
    // 3) resta ambiente
    R = (R > Ra) ? (R - Ra) : 0;
    G = (G > Ga) ? (G - Ga) : 0;
    B = (B > Ba) ? (B - Ba) : 0;
  
    digitalWrite(PIN_LED, LOW);     // apaga LED al terminar
}  