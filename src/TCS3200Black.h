#ifndef TCS3200BLACK_H
#define TCS3200BLACK_H

bool calibDataAvailable();
void loadcalibData();
void doBlackcalibData();
void doWhitecalibData();
void readNormalized(float,float,float);

#endif