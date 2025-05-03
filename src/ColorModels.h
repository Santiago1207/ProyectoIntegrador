#ifndef COLORMODELS_H
#define COLORMODELS_H

#include <Arduino.h>
#include "Globals.h"    // trae enum ColorIdx

struct ColorModel {
  float mu[3];
  float sigma[3];
  bool  valid;
};

// 6 modelos en memoria RAM
extern ColorModel models[6];

// Guardar / cargar de NVS
void loadModels();
void saveModel(uint8_t idx);

#endif