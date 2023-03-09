#include <SD.h> // Biblioteca para comunicação com cartão SD

File dataFile; // Objeto que representa o arquivo de dados
const int chipSelect = 10; // Pino para seleção do cartão SD
String fileName = "/data.csv";

const int bufferSize = 10; // Tamanho do buffer de dados
int bufferIndex = 0; // Índice atual do buffer
unsigned long lastSaveTime = 0; // Último momento em que os dados foram salvos no cartão SD
unsigned long lastReadTime = 0; // Último momento em que os sensores foram lidos

// Buffers para armazenamento de dados
float temperatureBuffer[bufferSize];
float humidityBuffer[bufferSize];
int pm25Buffer[bufferSize];
int pm10Buffer[bufferSize];

void setup() {
  Serial.begin(9600); // Inicia comunicação serial com taxa de 9600 bps
  pinMode(chipSelect, OUTPUT); // Configura pino de seleção do cartão SD como saída

  // Inicializa cartão SD
  if (!SD.begin(chipSelect)) {
    Serial.println("Erro ao inicializar o cartão SD.");
    return;
  }

  // Cria arquivo de dados se ele não existir
  if (!SD.exists(fileName)) {
    dataFile = SD.open(fileName, FILE_WRITE);
    dataFile.println("Time,Temperature,Humidity,PM2.5,PM10");
    dataFile.close();
  }

  // Inicializa variável de último momento de salvamento de dados
  lastSaveTime = millis();

  // Inicializa buffers de dados com valor 0
  for (int i = 0; i < bufferSize; i++) {
    temperatureBuffer[i] = 0;
    humidityBuffer[i] = 0;
    pm25Buffer[i] = 0;
    pm10Buffer[i] = 0;
  }

  // Imprime mensagem de início do programa
  Serial.println("Programa iniciado.");
}



void loop() {
  // Obtém momento atual
  unsigned long currentTime = millis();

  // Realiza leitura dos sensores a cada 1 segundo
  if (currentTime - lastReadTime >= 1000) {
    // Simula leitura dos sensores
    float temperature = 25.6;
    float humidity = 60.10;
    int pm25 = 7.6;
    int pm10 = 15.65;
    
    // Armazena dados nos buffers
    temperatureBuffer[bufferIndex] = temperature;
    humidityBuffer[bufferIndex] = humidity;
    pm25Buffer[bufferIndex] = pm25;
    pm10Buffer[bufferIndex] = pm10;

    // Incrementa índice do buffer
    bufferIndex++;

    // Salva dados no cartão SD quando o buffer estiver cheio
    if (bufferIndex == bufferSize) {
      saveData();
      bufferIndex = 0;
    }

  // Atualiza último momento de leitura dos sensores
  lastReadTime = currentTime;
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
    dataString += String(currentTime - ((bufferSize - 1 - i) * 1000)) + ",";
    dataString += String(temperatureBuffer[i]) + ",";
    dataString += String(humidityBuffer[i]) + ",";
    dataString += String(pm25Buffer[i]) + ",";
    dataString += String(pm10Buffer[i]) + "\n";
  }

  // Abre o arquivo para escrita e escreve os dados
  dataFile = SD.open(fileName, FILE_WRITE);
  dataFile.print(dataString);
  dataFile.close();

  Serial.println("Dados salvos.");
}
