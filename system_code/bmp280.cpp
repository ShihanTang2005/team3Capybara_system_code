//
// Created by TSH-STUDIO 唐诗涵 on 25-1-23.
//

#include "bmp280.h"

Adafruit_BMP280 bme;
void bmp280_setup(){
    bme.begin();
}

void bmp280_loop(){
    Serial.print("BMP pressure: ");Serial.print(bme.readPressure()/100);Serial.println("[hPa]");
    Serial.print("Altitude: ");Serial.print(bme.readAltitude(1013.25));Serial.println("[m]");
}
