//
// Created by TSH-STUDIO 唐诗涵 on 25-1-23.
//

#include "bmp280.h"

Adafruit_BMP280 bme;

float bme_pressure = 0;
float bme_altitude = 0;

void bmp280_setup(){
    bme.begin();
}

void bmp280_loop(){
    bme_pressure = bme.readPressure()/100;
    bme_altitude = bme.readAltitude(1013.25);
}
