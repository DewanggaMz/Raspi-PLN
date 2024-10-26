#include "rtc_config.h"



// DateTime now = this->now();
void RTC::rtcSetup() {
  Wire.begin(_RTC_SDA_PIN, _RTC_SCL_PIN);

  if (!this->begin()) {
    USBSerial.println("Tidak dapat menemukan RTC");
    // while (1);
    return;
  }

  if (this->lostPower()) {
    USBSerial.println("RTC kehilangan daya, mengatur ulang Waktu");
    this->adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

String RTC::getDateString() {
  DateTime date = this->now();
  char buffer[20];
  sprintf(buffer, "%04d/%02d/%02d", date.year(), date.month(), date.day());
  delay(1000);
  return String(buffer);
}


String RTC::getTimeString() {
  DateTime time = this->now();
  char buffer[20];
  sprintf(buffer, "%02d:%02d:%02d", time.hour(), time.minute(), time.second());
  delay(1000);
  return String(buffer);
}

void RTC::setDateTime(int year, int month, int day, int hour, int minute, int second) {
  DateTime newDateTime(year, month, day, hour, minute, second);
  this->adjust(newDateTime);
}

uint64_t RTC::getTimestamp(){
  DateTime now = this->now();
  uint32_t unixTimestamp = now.unixtime();
  return (uint64_t)unixTimestamp * 1000;
}