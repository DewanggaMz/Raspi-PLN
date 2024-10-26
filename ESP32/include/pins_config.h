#ifndef PINSCONFIG_H
#define PINSCONFIG_H

class PinsConfig {
  public:
    static const int RTC_SDA_PIN = 8;
    static const int RTC_SCL_PIN = 9;
    
    static const int PZEM_RX = 43;
    static const int PZEM_TX = 44;
    
    static const int SPI_MOSI = 11;
    static const int SPI_SCK  = 12;
    static const int SPI_MISO = 13;
    
    static const int SD_CS    = 5;

    static const int RS485_RX = 16;
    static const int RS485_TX = 15;

    static const int GPS_RX = 18;
    static const int GPS_TX = 17;

    static const int LORA_CS = 10;
    static const int LORA_RST   = 0;
    static const int DIO0    = 1;
    static const int DIO1    = 2;
    static const int DIO2    = 3;
    static const int DIO3    = 4;
};

#endif
