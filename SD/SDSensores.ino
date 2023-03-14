// Integração Módulo SD com BMP180, MQ135, UVM30A, DHT11, GY30
#include <SD.h> // Biblioteca para comunicação com cartão SD
#include <MQ135.h> //biblioteca do sensor MQ135
#include <DHT.h> //biblioteca do sensor DHT11
#include <Wire.h> // bibilioteca de comunicação entre dispositivos por protocolo I2C
#include <BH1750.h> //biblioteca do sensor GY30

File dataFile; // Objeto que representa o arquivo de dados
const int chipSelect = 10; // Pino para seleção do cartão SD
unsigned long lastSaveTime = 0; // Último momento em que os dados foram salvos no cartão SD
unsigned long lastReadTime = 0; // Último momento em que os sensores foram lidos
String fileName = "bmp.txt";; // Nome do arquivo

// Buffers para armazenamento de dados
int bufferIndex = 0; // Índice atual do buffer
const int bufferSize = 10; // Tamanho do buffer de dados
// MQ135 (5V) A0 
#define pinoMQ A0
MQ135 mq = MQ135(pinoMQ);
float bufferCo2MQ[bufferSize]; // vetor para os dados lidos de CO2
// UVM30A (5V) A1
#define pinoUVM A1
int bufferUltravioletaUVM[bufferSize];   // declara um vetor para a resposta do sensor
// DHT11 (5V) A3
#define pinoDHT A3 // pino usado para conexão
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
  Serial.println("Inicializando componentes...");
  // Inicialização do DHT11
  dht.begin(); //inicializa o sensor DHT11
  // Inicialização do GY30
  gy.begin(); //inicializa o sensor GY30
  // Testa se os sensores DHT11 e GY30 estão recebendo dados numéricos
  testeDHT_GY();
  // Configura pino de seleção do cartão SD como saída
  pinMode(chipSelect, OUTPUT);
  // Inicializa cartão SD
  if (!SD.begin(chipSelect)) {
    Serial.println("Erro ao inicializar o cartão SD! Verifique as conexões.");
    return;
  }
  // Deleta um arquivo de mesmo nome caso já exista
  if(SD.exists(fileName)) {
    SD.remove(fileName);
  } else if (!SD.exists(fileName)) {
    // Cria arquivo de dados se ele não existir
    dataFile = SD.open(fileName, FILE_WRITE);
    dataFile.close();
  }
  // Abre o arquivo e escreve legenda dos dados
  dataFile = SD.open(fileName, FILE_WRITE);
  dataFile.println("Tempo[ms], Conc.CO2[ppm], IndiceUV, Temperatura[°C], UmidadeRelativa[%UR], Iluminância[lux]");
  dataFile.close();
  
  lastSaveTime = millis(); // Inicializa variável de último momento de salvamento de dados
  
  // Inicializa buffers de dados com valor 0
  for (int i = 0; i < bufferSize; i++) {
    bufferCo2MQ[i] = 0;
    bufferUltravioletaUVM[i] = 0;
    bufferTemperaturaDHT[i] = 0;
    bufferUmidadeDHT[i] = 0;
    bufferIluminanciaGY[i] = 0;
  }
  
  Serial.println("Programa iniciado."); // Imprime mensagem de início do programa
}


void loop() {
  unsigned long currentTime = millis(); // Obtém momento atual

  // Realiza leitura dos sensores a cada 1 segundo
  if (currentTime - lastReadTime >= 1000) {
    bufferCo2MQ[bufferIndex] = mq.getPPM(); // concentração de CO2 informada pelo sensor
    bufferUltravioletaUVM[bufferIndex] = medicaoUVM(); // atribui o valor do índice de radiação uv por meio de uma função
    bufferTemperaturaDHT[bufferIndex] = dht.readTemperature();  // temperatura informada pelo sensor
    bufferUmidadeDHT[bufferIndex] = dht.readHumidity(); // umidade informada pelo sensor
    bufferIluminanciaGY[bufferIndex] = gy.readLightLevel(); // iluminância informada pelo sensor
    bufferIndex++; // Incrementa índice do buffer

    // Salva dados no cartão SD quando o buffer estiver cheio
    if (bufferIndex == bufferSize) {
      saveData();
      testeDHT_GY();
      bufferIndex = 0;
    }

    // Atualiza último momento de leitura dos sensores
    lastReadTime = currentTime;
  }
}

// Função do UVM30A
int medicaoUVM(){
  float leituraSensorUVM = analogRead(pinoUVM); // atribui nível de tensão de saída do sensor a uma variavel
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

  // Verifica se já passaram 10 segundos desde o último salvamento de dados
  if (currentTime - lastSaveTime < 10000) {
    return;
  }

  // Atualiza o lastSaveTime com o currentTime
  lastSaveTime = currentTime;

  // Cria uma string com os dados do buffer
  String dataString = "";
  for (int i = 0; i < bufferSize; i++) {
    dataString += String(currentTime - ((bufferSize - 1 - i) * 1000)) + ", ";
    dataString += String(bufferCo2MQ[i]) + ", ";
    dataString += String(bufferUltravioletaUVM[i]) + ", ";
    dataString += String(bufferTemperaturaDHT[i]) + ", ";
    dataString += String(bufferUmidadeDHT[i]) + ", ";
    dataString += String(bufferIluminanciaGY[i]) + "\n";
  }

  // Abre o arquivo para escrita e escreve os dados
  dataFile = SD.open(fileName, FILE_WRITE);
  dataFile.print(dataString);
  dataFile.close();

  Serial.println("Dados salvos.");
}
