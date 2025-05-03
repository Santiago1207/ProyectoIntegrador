#include "ColorModels.h"
#include <Preferences.h>
#include <globals.h>

ColorModel models[6];

void loadModels() {
  for (uint8_t c=0; c<6; c++) {
    char key[8];
    snprintf(key,8,"v%u",c);
    models[c].valid = prefs.getBool(key,false);
    for (uint8_t k=0;k<3;k++) {
      snprintf(key,8,"m%u%u",c,k);
      models[c].mu[k] = prefs.getFloat(key,0.0f);
      snprintf(key,8,"s%u%u",c,k);
      models[c].sigma[k] = prefs.getFloat(key,0.0f);
    }
  }
}

void saveModel(uint8_t idx) {
  char key[8];
  prefs.putBool((snprintf(key,8,"v%u",idx),key), true);
  for (uint8_t k=0;k<3;k++) {
    prefs.putFloat((snprintf(key,8,"m%u%u",idx,k),key), models[idx].mu[k]);
    prefs.putFloat((snprintf(key,8,"s%u%u",idx,k),key), models[idx].sigma[k]);
  }
}
