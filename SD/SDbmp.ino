#include <SD.h> // Biblioteca para comunicação com cartão SD
#include <Adafruit_BMP085.h> //biblioteca do sensor BMP180

File dataFile; // Objeto que representa o arquivo de dados
const int chipSelect = 10; // Pino para seleção do cartão SD
String filename = "bmp.txt";; // Nome do arquivo
unsigned long lastSaveTime = 0; // Último momento em que os dados foram salvos no cartão SD
unsigned long lastReadTime = 0; // Último momento em que os sensores foram lidos

// Buffers para armazenamento de dados
int bufferIndex = 0; // Índice atual do buffer
const int bufferSize = 10; // Tamanho do buffer de dados
Adafruit_BMP085 bmp; //define bmp como objeto do tipo Adafruit_BMP085
float Temperatura[bufferSize]; //variável auxiliar com valores fracionados

void setup() {
  Serial.begin(9600); // Inicia comunicação serial com taxa de 9600 bps
  //inicialização do Sensor
  if (!bmp.begin()) { // se o sensor não for inicializado, apresenta no monitor serial a mensagem:
    Serial.println("Sensor BMP180 não foi identificado! Verifique as conexões.");
    while (1) {} //em loop até o sensor inicializar
  }  
  // Configura pino de seleção do cartão SD como saída
  pinMode(chipSelect, OUTPUT);
  // Inicializa cartão SD
  if (!SD.begin(chipSelect)) {
    Serial.println("Erro ao inicializar o cartão SD.");
    return;
  }
  // Cria arquivo de dados se ele não existir
  if (!SD.exists(filename)) {
    dataFile = SD.open(filename, FILE_WRITE);
    dataFile.println("Time , Temperature");
    dataFile.close();
  }
  
  lastSaveTime = millis(); // Inicializa variável de último momento de salvamento de dados
  
  // Inicializa buffers de dados com valor 0
  for (int i = 0; i < bufferSize; i++) {
    Temperatura[bufferSize] = 0;
  }
  
  Serial.println("Programa iniciado."); // Imprime mensagem de início do programa
}


void loop() {
  unsigned long currentTime = millis(); // Obtém momento atual

  // Realiza leitura dos sensores a cada 1 segundo
  if (currentTime - lastReadTime >= 1000) {
    Temperatura[bufferSize] = bmp.readTemperature();
    bufferIndex++; // Incrementa índice do buffer

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
    dataString += String(Temperatura[i]) + "\n";
  }

  // Abre o arquivo para escrita e escreve os dados
  dataFile = SD.open("/data.csv", FILE_WRITE);
  dataFile.print(dataString);
  dataFile.close();

  Serial.println("Dados salvos.");
}
