#include <SD.h> // Biblioteca para usar o cartão SD
#include <SPI.h> // Biblioteca para comunicar com o cartão SD via SPI
#include <Wire.h> // Biblioteca para comunicar com o RTC via I2C
#include "RTClib.h" // Biblioteca para usar o RTC
#include <Adafruit_BMP085.h> //biblioteca do sensor BMP180
#include <MQ135.h> //biblioteca do sensor MQ135
#include <DHT.h> //biblioteca do sensor DHT11
#include <Wire.h> // bibilioteca de comunicação entre dispositivos por protocolo I2C
#include <BH1750.h> //biblioteca do sensor GY30


// SD
RTC_DS1307 rtc;         // Objeto para usar o RTC
const int chipSelect = 10;    // Pino CS do cartão SD
File dataFile; // Objeto que representa o arquivo de dados
String fileName = "bmp.txt";; // Nome do arquivo
// temporização
unsigned long lastSaveTime = 0; // Último momento em que os dados foram salvos no cartão SD
unsigned long lastReadTime = 0; // Último momento em que os sensores foram lidos
int samplingTime = 5000; // tempo de amostragem em milissegundos
// Buffers para armazenamento de dados
int bufferIndex = 0; // Índice atual do buffer
const int bufferSize = 3; // Tamanho do buffer de dados
String dataString = ""; // Cria uma string 
String bufferDataHora[bufferSize] = "";

// BMP180 (5V) SDA, SCL
Adafruit_BMP085 bmp; // define bmp como objeto do tipo Adafruit_BMP085 (I2C)
float bufferTemperaturaBMP[bufferSize]; // vetor para os dados lidos de temperatura
int bufferPressaoBMP[bufferSize]; // vetor para os dados lidos de pressão
// MQ135 (5V) A2
#define pinoMQ A2
MQ135 mq = MQ135(pinoMQ);
float bufferCo2MQ[bufferSize]; // vetor para os dados lidos de CO2
// UVM30A (5V) A0
#define pinoUVM A0
int bufferUltravioletaUVM[bufferSize];   // declara um vetor para a resposta do sensor
// DHT11 (5V) A1
#define pinoDHT A1 // pino usado para conexão
#define modeloDHT DHT11 // modelo do sensor
DHT dht(pinoDHT, modeloDHT); // define dht como objeto do tipo DHT
float bufferTemperaturaDHT[bufferSize]; // vetor para os dados lidos de temperatura
float bufferUmidadeDHT[bufferSize]; // vetor para os dados lidos de umidade
// GY30 (5V) SDA, SLC
BH1750 gy; // define gy como objeto do tipo BH1750
float bufferIluminanciaGY[bufferSize]; // vetor para os dados lidos de iluminãncia (intensidade luminosa por área) 



void setup() {
  // Inicia comunicação serial com taxa de 9600 bps
  Serial.begin(9600);
  while (!Serial) {}     // Aguarda até que a porta serial esteja pronta
  Serial.println("Inicializando componentes...");
  
  // Inicialização do BMP180
  if (!bmp.begin()) { 
    // se o sensor não for inicializado, apresenta a mensagem:
    Serial.println("Sensor BMP180 não foi identificado! Verifique as conexões.");
    while (1) {
      // em loop (repetições) até o sensor inicializar
    }
  }
  
  // Inicialização do DHT11
  dht.begin(); //inicializa o sensor DHT11
  // Inicialização do GY30
  Wire.begin(); //inicializa o I2C BUS
  gy.begin(); //inicializa o sensor GY30  
  testeDHT_GY(); // Testa se os sensores DHT11 e GY30 estão recebendo dados numéricos
  
  // Inicia o cartão SD
  if (!SD.begin(chipSelect)) {  
    Serial.println("Erro ao iniciar o cartão SD");
    return;
  }
  if(SD.exists(fileName)) { // Deleta um arquivo de mesmo nome caso já exista
    SD.remove(fileName);
  }
  if (!SD.exists(fileName)) { // Cria arquivo de dados
    dataFile = SD.open(fileName, FILE_WRITE);
    dataFile.close();
  }
  
  // Inicia o RTC
  if (!rtc.begin()) {
    Serial.println("Erro ao iniciar o RTC");
    return;
  }
  if (!rtc.isrunning()) {  // Verifica se o RTC está rodando
    Serial.println("RTC não está rodando");
    rtc.adjust(DateTime(F(_DATE), F(__TIME_)));  // Ajusta o RTC com a data/hora do compilador
  }
  
  // Abre o arquivo e escreve legenda dos dados
  dataFile = SD.open(fileName, FILE_WRITE);
  dataString = "Data, Hora, TemperaturaBMP180[°C], Pressão[Pa], Conc.CO2[ppm], IndiceUV, TempDHT11[°C], UmidadeRelativa[%UR], Iluminância[lux]";
  dataFile.print(dataString);
  dataFile.close();
  
  Serial.println(dataString);
  
  // Inicializa buffers de dados com valor 0
  dataString = "";
  for (int i = 0; i < bufferSize; i++) {
    bufferDataHora[i] = "";
    bufferTemperaturaBMP[i] = 0;
    bufferPressaoBMP[i] = 0;
    bufferCo2MQ[i] = 0;
    bufferUltravioletaUVM[i] = 0;
    bufferTemperaturaDHT[i] = 0;
    bufferUmidadeDHT[i] = 0;
    bufferIluminanciaGY[i] = 0;
  }
  
  Serial.println("Programa iniciado."); // Imprime mensagem de início do programa
  lastSaveTime = millis(); // Inicializa variável de último momento de salvamento de dados
}



void loop() {
  unsigned long currentTime = millis(); // Obtém momento atual

  // Realiza leitura dos sensores a cada X segundos
  if (currentTime - lastReadTime >= samplingTime) {
    bufferDataHora[bufferIndex] = rtcDataHora(); // data e hora em tempo real
    bufferTemperaturaBMP[bufferIndex] = bmp.readTemperature(); // temperatura informada pelo sensor
    bufferPressaoBMP[bufferIndex] = bmp.readPressure(); // pressão informada pelo sensor
    bufferCo2MQ[bufferIndex] = mq.getPPM(); // concentração de CO2 informada pelo sensor
    bufferUltravioletaUVM[bufferIndex] = medicaoUVM(); // atribui o valor do índice de radiação uv por meio de uma função
    bufferTemperaturaDHT[bufferIndex] = dht.readTemperature();  // temperatura informada pelo sensor
    bufferUmidadeDHT[bufferIndex] = dht.readHumidity(); // umidade informada pelo sensor
    bufferIluminanciaGY[bufferIndex] = gy.readLightLevel(); // iluminância informada pelo sensor
    bufferIndex++; // Incrementa índice do buffer

    // Salva dados no cartão SD quando o buffer estiver cheio
    if (bufferIndex == bufferSize) {
      testeDHT_GY();
      saveData();
      bufferIndex = 0;
    }

    // Atualiza último momento de leitura dos sensores
    lastReadTime = currentTime;
  }

}


// Função para leitura de Data e Hora em tempo real
String rtcDataHora() {
  DateTime now = rtc.now(); // Lê a data/hora atual do RTC
  // Cria uma string com a data e hora formatadas
  String dateTime = "";
  dateTime += String(now.year(), DEC) + "/";
  dateTime += String(now.month(), DEC) + "/";
  dateTime += String(now.day(), DEC) + ", ";
  dateTime += String(now.hour(), DEC) + ":";
  dateTime += String(now.minute(), DEC) + ":";
  dateTime += String(now.second(), DEC);
  return dateTime;
}

// Função do UVM30A
int medicaoUVM(){
  float leituraSensorUVM = analogRead(pinoUVM)*(5000/1023); // atribui nível de tensão de saída do sensor a uma variavel
  if (leituraSensorUVM >= 0 && leituraSensorUVM < 50) {
    return 0;
  } else if (leituraSensorUVM >= 50 && leituraSensorUVM < 227) {
    return 1;
  } else if (leituraSensorUVM >= 227 && leituraSensorUVM < 318) {
    return 2;
  } else if (leituraSensorUVM >= 318 && leituraSensorUVM < 408) {
    return 3;
  } else if (leituraSensorUVM >= 408 && leituraSensorUVM < 503) {
    return 4;
  } else if (leituraSensorUVM >= 503 && leituraSensorUVM < 606) {
    return 5;
  } else if (leituraSensorUVM >= 606 && leituraSensorUVM < 698) {
    return 6;
  } else if (leituraSensorUVM >= 698 && leituraSensorUVM < 795) {
    return 7;
  } else if (leituraSensorUVM >= 795 && leituraSensorUVM < 881) {
    return 8;
  } else if (leituraSensorUVM >= 881 && leituraSensorUVM < 976) {
    return 9;
  } else if (leituraSensorUVM <= 976 && leituraSensorUVM < 1079) {
    return 10;
  } else if (leituraSensorUVM > 1079) {
    return 11;
  }
}



void testeDHT_GY() {
  float temperaturaDHT = dht.readTemperature();  // temperatura informada pelo sensor
  float umidadeDHT = dht.readHumidity(); // umidade informada pelo sensor
  if (isnan(temperaturaDHT) || isnan(umidadeDHT)) { 
    //se a for atribuido um valor não numérico, indica erro de leitura no DHT11
    Serial.println("Falha de leitura do DHT11! Verifique as conexões.");
  }
  float iluminanciaGY = gy.readLightLevel(); // iluminância informada pelo sensor
  if (isnan(iluminanciaGY)) { 
    //se a for atribuido um valor não numérico, indica erro de leitura no GY30
    Serial.println("Falha de leitura do GY30! Verifique as conexões.");
  }
}


void saveData() {
  // Obtém momento atual
  unsigned long currentTime = millis();

  // Verifica se já passaram X segundos desde o último salvamento de dados
  if (currentTime - lastSaveTime < ((bufferSize + 1)*samplingTime) ) {
    return;
  }

  // Atualiza o lastSaveTime com o currentTime
  lastSaveTime = currentTime;

  // Atribui os dados do buffer
  for (int i = 0; i < bufferSize; i++) {
    dataString += String(bufferDataHora[i]) + ", "; 
    dataString += String(bufferTemperaturaBMP[i]) + ", ";
    dataString += String(bufferPressaoBMP[i]) + ", ";
    dataString += String(bufferCo2MQ[i]) + ", ";
    dataString += String(bufferUltravioletaUVM[i]) + ", ";
    dataString += String(bufferTemperaturaDHT[i]) + ", ";
    dataString += String(bufferUmidadeDHT[i]) + ", ";
    dataString += String(bufferIluminanciaGY[i]) + "\n";
  }

  // Abre o arquivo para escrita e salva no Cartão SD
  File dataFile = SD.open(fileName, FILE_WRITE);
  if (dataFile) {
    dataFile.print(dataString);
    dataFile.close();
  }

  // Exibe no Monitor Serial
  Serial.print(dataString);
  dataString = "";
  Serial.println("Dados salvos.");
}
