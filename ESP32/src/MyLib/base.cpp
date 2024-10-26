#include "base.h"

// SPIClass spi = SPIClass(1);
SPIClass* Myspi = &MYSPI;
// HardwareSerial PzemSerial(1);


Main::Main(long baudRate) : _baudRate(baudRate) {}

bool Main::myspiBegin() {
    Myspi->begin(_SPI_SCK, _SPI_MISO, _SPI_MOSI);
    return true;
}

void Main::myspiEnd() {
    Myspi->end();
}

void Main::setup(bool debug) {
    if(debug){
      USBSerial.begin(_baudRate);
    }
    this->rtcSetup();
    this->pzemSetup();
    this->gpsSetup();
}

String Main::chipID(){
  int chipId = 0;
    for (int i = 0; i < 17; i = i + 8) {
        chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xFF) << i;
    }
    return String(chipId);
}

char* Main::encodePayload(char* inputString){
    int encodedLen = Base64.encodedLength(strlen(inputString));
    char encodedData[encodedLen + 1];
    
    Base64.encode(encodedData, inputString, strlen(inputString));
    encodedData[encodedLen] = '\0';

    return encodedData;
}

int Main::ceil(int value1, int value2) {
  if (value1 % value2 == 0) {
    return value1 / value2;
  } else {
    return (value1 / value2) + 1;
  }
}

String Main::decodePayload(char* inputString){
  int inputStringLength = sizeof(inputString);
  int decodedLength = Base64.decodedLength(inputString, inputStringLength);
  char decodedString[decodedLength];
  Base64.decode(decodedString, inputString, inputStringLength);

  return(decodedString);
}