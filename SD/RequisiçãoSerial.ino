// Inclui a biblioteca SD para acessar o cartão SD
#include <SD.h>

// Cria uma variável para representar o arquivo de dados e define o pino do chip select do cartão SD
File dataFile;
const int chipSelect = 10;

void setup() {
// Inicializa a comunicação serial e define o pino do chip select do cartão SD como saída
Serial.begin(9600);
pinMode(chipSelect, OUTPUT);

// Verifica se o cartão SD foi inicializado corretamente
if (!SD.begin(chipSelect)) {
Serial.println("Erro ao inicializar o cartão SD.");
return;
}

// Mensagem de confirmação de inicialização do programa
Serial.println("Programa iniciado.");
}

void loop() {
// Verifica se há dados disponíveis na porta serial
if (Serial.available()) {
// Lê a requisição recebida
String request = Serial.readStringUntil('\n');
// Verifica se a requisição é para obter os dados do arquivo
if (request == "getData") {
  // Abre o arquivo de dados
  dataFile = SD.open("/data.csv");
  if (dataFile) {
    // Lê os dados do arquivo e envia pela porta serial
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    // Fecha o arquivo de dados
    dataFile.close();
  } else {
    // Mensagem de erro caso não seja possível abrir o arquivo de dados
    Serial.println("Erro ao abrir arquivo de dados.");
  }
}
}
}
