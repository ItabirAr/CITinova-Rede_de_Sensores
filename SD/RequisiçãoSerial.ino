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
    // Lê o tempo inicial e final digitado pelo usuário
    unsigned long start_time = Serial.parseInt();
    unsigned long end_time = Serial.parseInt();
    Serial.print("Tempo inicial: ");
    Serial.println(start_time);
    Serial.print("Tempo final: ");
    Serial.println(end_time);

    // Abre o arquivo de dados
    dataFile = SD.open("BMP.txt");
    if (dataFile) {
      // Lê os dados do arquivo e envia pela porta serial
      while (dataFile.available()) {
        String request = dataFile.readStringUntil('\n');
        String timeStr = request.substring(0, request.indexOf(','));
        unsigned long time = timeStr.toInt();
        if (time >= start_time && time <= end_time) {
          String valueStr = request.substring(request.indexOf(',') + 1);
          float value = valueStr.toFloat();
          Serial.print("Tempo: ");
          Serial.print(time);
          Serial.print(" | Valor: ");
          Serial.println(value);
        }
      }
      // Fecha o arquivo de dados
      dataFile.close();
    } else {
      // Mensagem de erro caso não seja possível abrir o arquivo de dados
      Serial.println("Erro ao abrir arquivo de dados.");
    }
  }
}
