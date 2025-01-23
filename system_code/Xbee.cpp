#include "Xbee.h"

// Initialize XBee communication with the specified baud rate
void Xbee::begin(unsigned long baudRate) {
    Serial1.begin(baudRate); // Use Hardware Serial1 for XBee communication
}

// Send a string of data via XBee
void Xbee::sendData(String data) {
    Serial1.println(data); // Send the data over XBee
}
