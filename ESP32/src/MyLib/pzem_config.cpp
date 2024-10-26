#include "pzem_config.h"

HardwareSerial PzemSerial(1);

Pzem::Pzem() : PZEM004Tv30(PzemSerial, _PZEM_RX, _PZEM_TX) {}

void Pzem::pzemSetup() {
  PzemSerial.begin(9600, SERIAL_8N1, _PZEM_RX, _PZEM_TX);

  if (!PzemSerial) {
    USBSerial.println("Pzem USBSerial initialization failed");
    while (1);
  }
}


float Pzem::getVoltage() {
  float voltage = this->voltage();
  return isnan(voltage) || voltage == 0 ? 0 : voltage;
}


float Pzem::getCurrent() {
  float current = this->current();
  return isnan(current) || current == 0 ? 0 : current;
}


float Pzem::getPower() {
  float power = this->power();
  return isnan(power) || power == 0 ? 0 : power;
}


float Pzem::getEnergy() {
  float energy = this->energy();
  return isnan(energy) || energy == 0 ? 0 : energy;
}


float Pzem::getFrequency() {
  float frequency = this->frequency();
  return isnan(frequency) || frequency == 0 ? 0 : frequency;
}


float Pzem::getPf() {
  float pf = this->pf();
  return isnan(pf) || pf == 0 ? 0 : pf;
}
