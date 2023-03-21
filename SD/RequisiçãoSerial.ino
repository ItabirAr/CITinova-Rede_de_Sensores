// Inclui a biblioteca SD para acessar o cartão SD
#include <SD.h>

// Cria uma variável para representar o arquivo de dados e define o pino do chip select do cartão SD
File dataFile;
char valueSerial;
const int chipSelect = 53;

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

void requisicaoGetData(){
  dataFile = SD.open("BMP.txt");
  if(dataFile){
    while(dataFile.available()){
      Serial.write(dataFile.read());
    }
  }
}

void requisicaoGetInterval(){
  unsigned long start_time = Serial.parseInt();
  unsigned long end_time = Serial.parseInt();
  Serial.print("Tempo inicial: ");
  Serial.println(start_time);
  Serial.print("Tempo final: ");
  Serial.println(end_time);

  dataFile = SD.open("BMP.txt");
  if(dataFile){
    while(dataFile.available()){
      String request = dataFile.readStringUntil('\n');
      String timeStr = request.substring(0, request.indexOf(','));
      unsigned long time = timeStr.toInt();
      if (time >= start_time && time <= end_time) {
        String valueStr = request.substring(request.indexOf(',') + 1);
        Serial.print("Tempo: ");
        Serial.print(time);
        Serial.print(" | Valor: ");
        Serial.println(valueStr);
      }
    }
  }
}

void loop() {
  // Verifica se há dados disponíveis na porta serial
  if (Serial.available()) {
    valueSerial = Serial.read();
    if(valueSerial == '1'){
      requisicaoGetData();
   }
    if(valueSerial == '2'){
      requisicaoGetInterval();
    }
  }
}
