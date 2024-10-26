#include "sdcard_config.h"

// SPIClass* sx127x_spi = &SX127X_SPI;

// void SdCard::sdCardSetup(SPIClass  spi) {

//   if (!SD.begin(_SD_CS, spi)) {
//     USBSerial.println("Gagal menginisialisasi SD card");
//     return;
//   }
//   USBSerial.println("SD card berhasil diinisialisasi");
// }

// void SdCard::sdEnd(SPIClass  spi) {
//   spi.end();
// }


void SdCard::writeFile(const char *path, const char *message) {
  File file = SD.open(path, FILE_WRITE);
  if (!file) {
    USBSerial.println("Gagal membuka file untuk menulis");
    return;
  }
  file.println(message);
  file.close();
}

bool SdCard::append(const char *path, const char *message, bool first) {
File file = SD.open(path, FILE_APPEND);
  if (!file) {
    USBSerial.println("Gagal membuka file untuk menulis.");
    return false;
  }
  if ( first ) {
    file.println("1." + String(message));
  } else {
    file.println(String(message));
  }
  
  file.close();
  return true;
}


void SdCard::readFile(const char *path, int startLine,int endLine) {
  File file = SD.open(path);
  if (!file) {
    USBSerial.println("Gagal membuka file untuk membaca");
    return;
  }
  int currentIndex = 0;

  while (file.available()) {
    String line = file.readStringUntil('\n');
    

    int posisiTitik = line.indexOf('.');
    if (posisiTitik != -1) {
      currentIndex = (line.substring(0, posisiTitik)).toInt();
    } else {
      currentIndex++;
    }

    if (currentIndex >= startLine && currentIndex <= endLine) {
      USBSerial.println(line);
    }
    if (currentIndex > endLine) {
      break;
    }
  }
  file.close();
}

String SdCard::readLastLine(const char *path) {
  File file = SD.open(path, FILE_READ);
  if (!file) {
    // USBSerial.println("Gagal membuka file untuk membaca");
    return "";
  }
  String lastLine = "";

  file.seek(0, SeekEnd);
  int fileSize = file.size(); 

  for (int i = 0; i < fileSize; i++) {
    file.seek(fileSize - 1 - i);
    char c = file.read();
    if (c == '\n' && lastLine.length() > 0) {
      break;
    }
    lastLine = c + lastLine;
  }
  file.close();
  return lastLine;
}

int SdCard::lastIndex(File file) {
  String lastLine = "";
  int lastIndex = 0;

  file.seek(0, SeekEnd);
  int fileSize = file.size(); 

  for (int i = 0; i < fileSize; i++) {
    file.seek(fileSize - 1 - i);
    char c = file.read();
    if (c == '\n' && lastLine.length() > 0) {
      break;
    }
    lastLine = c + lastLine;
  }

  int posisiTitik = lastLine.indexOf('.');
  if (posisiTitik != -1) {
    lastIndex = (lastLine.substring(0, posisiTitik)).toInt();
  } else {
    USBSerial.println("Titik tidak ditemukan dalam string.");
  }

  return lastIndex;
}

bool SdCard::writeLog(const char *path, const char *message, int limit){
  File file = SD.open(path, FILE_READ);
  if (!file) {
    append(path, message, true);
    USBSerial.println("file tidak di temukan.... membuat file baru");
    return false;
  }

  int lastIndex = this->lastIndex(file);

  if(lastIndex >= limit) {
    String newMessage = "1." + String(message);
    this->writeFile(path, newMessage.c_str());
  }else{
    String newMessage = String(lastIndex + 1) + "." + message;
    append(path, newMessage.c_str(), false);
  }

  file.close();
  return true;
}