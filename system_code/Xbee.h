#ifndef XBEE_H
#define XBEE_H

#include <Arduino.h>

class Xbee {
public:
    void begin(unsigned long baudRate); // Initialize XBee
    void sendData(String data);         // Send data via XBee
};

#endif
