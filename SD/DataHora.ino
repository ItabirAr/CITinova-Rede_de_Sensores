#include <SD.h>         // Biblioteca para usar o cartão SD
#include <SPI.h>        // Biblioteca para comunicar com o cartão SD via SPI
#include <Wire.h>       // Biblioteca para comunicar com o RTC via I2C
#include "RTClib.h"     // Biblioteca para usar o RTC

RTC_DS1307 rtc;         // Objeto para usar o RTC

const int chipSelect = 10;    // Pino CS do cartão SD

void setup() {
  Serial.begin(9600);    // Inicia a comunicação serial
  while (!Serial) {}     // Aguarda até que a porta serial esteja pronta
  
  if (!SD.begin(chipSelect)) {  // Inicia o cartão SD
    Serial.println("Erro ao iniciar o cartão SD");
    return;
  }
  
  if (!rtc.begin()) {     // Inicia o RTC
    Serial.println("Erro ao iniciar o RTC");
    return;
  }

  if (!rtc.isrunning()) {  // Verifica se o RTC está rodando
    Serial.println("RTC não está rodando");
    rtc.adjust(DateTime(F(_DATE), F(__TIME_)));  // Ajusta o RTC com a data/hora do compilador
  }
}

void loop() {
  DateTime now = rtc.now();   // Lê a data/hora atual do RTC

  // Cria uma string com a data/hora formatada
  String dateTimeStr = String(now.year(), DEC) + "/" + 
                       String(now.month(), DEC) + "/" + 
                       String(now.day(), DEC) + " " + 
                       String(now.hour(), DEC) + ":" + 
                       String(now.minute(), DEC) + ":" + 
                       String(now.second(), DEC);
                       
  // Salva a string no cartão SD
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dateTimeStr);
    dataFile.close();
  }
  
  // Exibe a string no monitor serial
  Serial.println(dateTimeStr);
  
  delay(1000);   // Espera um segundo antes de ler novamente o RTC
}
