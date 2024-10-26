#include "gps_config.h"
#include "serial_config.h"

EspSoftwareSerial::UART GPS_Serial;

void GPS::gpsSetup(){
  GPS_Serial.begin(9600, SWSERIAL_8N1, _GPS_RX, _GPS_TX, false);
  if (!GPS_Serial) {
    USBSerial.println("GPS_Serial invalid, check config");
    while (1) {
      delay (1000);
    }
  } 
}

double GPS::getLatitude() {
  return this->location.isValid() ? this->location.lat() : 0;
}

double GPS::getLongitude() {
  return this->location.isValid() ? this->location.lng() : 0;
}

String GPS::getLocation(bool url) {
  String lat = String(this->getLatitude(), 6);
  String lon = String(this->getLongitude(), 6);
  String coordinates = lat + "," + lon;
  String urlLocation = "www.google.com/maps/place/" + coordinates;
  return url ? urlLocation : coordinates;
}

