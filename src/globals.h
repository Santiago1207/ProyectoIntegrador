#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <Preferences.h>

Preferences prefs;

// Constantes para pines
constexpr uint8_t  servosPin[2] = {9, 10};
constexpr uint8_t  TCS3200[5] = {4, 5, 6, 7, 8};
constexpr uint8_t  S4 = 12;
constexpr uint8_t  PIN_LED = 19; //CAMBIAR

// Ángulos (calibrar segun la mecánica)
constexpr uint8_t  posHome1 = 88;      // posición inicial servo1
constexpr uint8_t  posSensor1 = 40;    // lleva M&M al sensor
constexpr uint8_t  posHome2 = 90;      // posición inicial servo2
constexpr uint8_t  posRedBin = 45;      // desvío Rojo
constexpr uint8_t  posYellowBin = 60;  // desvío Amarillo
constexpr uint8_t  posGreenBin = 85;  // desvío Verde
constexpr uint8_t  posCoffeeBin = 115;   // desvío Café
constexpr uint8_t  posOrangeBin = 130;  // desvío Naranja
constexpr uint8_t  posBlueBin = 135;   // desvío Azul
constexpr uint8_t  posSensor2 = 0;     //posicion de clasificacion

//RGB de los colores de los M&M
constexpr float color_calib[7][3] = {
    { 0.322, 0.322, 0.355 },  // ROJO
    { 0.383, 0.384, 0.233 },  // AMARILLO
    { 0.363, 0.363, 0.274 },  // VERDE
    { 0.386, 0.385, 0.229 },  // CAFÉ
    { 0.357, 0.359, 0.284 },  // NARANJA
    { 0.377, 0.381, 0.242 },  //AZUL
    { 0.385, 0.385, 0.230 },  //MORADO
};

// Constante para nombres de colores
const char* const colorNames[7] = { // 'const char* const' hace que tanto el puntero como el contenido sean constantes
    "ROJO", "AMARILLO", "VERDE", "CAFE", "NARANJA", "AZUL", "MORADO"
};

// ───────── Variables de calibración ─────────
struct Calib {
    uint32_t R0, G0, B3;            // negro
    uint32_t R1, G1, B4;            // blanco
} calibData;

//Variable del contador de colores, el morado no cuenta
extern uint16_t countColors[6];

#endif