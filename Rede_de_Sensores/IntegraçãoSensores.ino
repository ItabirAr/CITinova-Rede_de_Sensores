// Integração dos sensores BMP180, MQ135, LM35, UVM30A, DHT11, GY30 com interrupção
#include <TimerOne.h> //biblioteca do temporizador interno do arduino
#include <Adafruit_BMP085.h> //biblioteca do sensor BMP180
#include <MQ135.h> //biblioteca do sensor MQ135
#include <DHT.h> //biblioteca do sensor DHT11
#include <Wire.h> //bibilioteca de comunicação entre dispositivos por protocolo I2C
#include <BH1750.h> //biblioteca do sensor GY30

bool flag = false; // variável auxiliar para indicar a contagem de tempo
int p = 0; // variável auxiliar de posição dos vetores
const int tamanhoBuffer = 10; // tamanho do vetor
long bufferTempo[tamanhoBuffer]; // vetor com os dados de tempo

// ** VARIAVEIS BMP180 ** (3,3V) SDA-A4, SCL-A5
Adafruit_BMP085 bmp; // define bmp como objeto do tipo Adafruit_BMP085 (I2C)
float bufferTemperaturaBMP[tamanhoBuffer]; // vetor para os dados lidos de temperatura
int bufferPressaoBMP[tamanhoBuffer]; // vetor para os dados lidos de pressão

// ** VARIAVEIS MQ135 ** (5V) A0 
#define pinoMQ A2
MQ135 mq = MQ135(pinoMQ);
float bufferCo2MQ[tamanhoBuffer]; // vetor para os dados lidos de CO2

// ** VARIAVEIS LM35 ** (5V) A2
#define pinoLM A4
float bufferTemperaturaLM[tamanhoBuffer];  //declara um vetor para resposta do sensor

// ** VARIAVEIS UVM30A ** (3,3V ou 5V) A1
#define pinoUVM A0
int bufferUltravioletaUVM[tamanhoBuffer];   // declara um vetor para a resposta do sensor

// ** VARIAVEIS DHT11 ** (3,3V ou 5V) A3
#define pinoDHT A1 // pino usado para conexão
#define modeloDHT DHT11 // modelo do sensor
DHT dht(pinoDHT, modeloDHT); // define dht como objeto do tipo DHT
float bufferTemperaturaDHT[tamanhoBuffer]; // vetor para os dados lidos de temperatura
float bufferUmidadeDHT[tamanhoBuffer]; // vetor para os dados lidos de umidade

// ** VARIAVEIS GY30 ** (3,3V ou 5V) SDA, SLC
BH1750 gy; // define gy como objeto do tipo BH1750
float bufferIluminanciaGY[tamanhoBuffer]; // vetor para os dados lidos de iluminãncia (intensidade luminosa por área) 

void setup() {
// inicializa monitor serial
  Serial.begin(9600); 
// ** INICIALIZA BMP180 **
  if (!bmp.begin()) { 
    //se o sensor não for inicializado, apresenta a mensagem:
    Serial.println("Sensor BMP180 não foi identificado! Verifique as conexões.");
    while (1) {  //em loop (repetições) até o sensor inicializar
    } 
  }
// ** INICIALIZA DHT11 **
  dht.begin(); //inicializa o sensor DHT11
// ** INICIALIZA GY30 **
  gy.begin(); //inicializa o sensor GY30
// temporizador interno do arduino
  Timer1.initialize(1000000); // 1s
  Timer1.attachInterrupt(callback);
// *** variáveis medidas e unidades (lux = lm/m²)
  Serial.println("Tempo[ms], Temp_BMP180[°C], Pressao[Pa], Conc.CO2_MQ135[ppm], Temp_LM35[°C], IndiceUV, Temp_DHT11[°C], UmidadeRelelativa[%UR], Iluminância[lux]");
}

void callback(){
  flag = true;
}

void loop(){   
  if(flag){
    bufferTempo[p] = millis(); // milissegundos transcorridos desde que o Arduino foi ligado
    medicaoBMP();
    medicaoMQ();
    medicaoTemperaturaLM();
    bufferUltravioletaUVM[p] = medicaoUVM(); // atribui o valor do índice de radiação uv
    medicaoDHT();
    medicaoGY();
    p++;
    if (p == tamanhoBuffer-1) {
      monitorSerial(); // função que mostra os dados salvos nos vetores
      p = 0; // retorna à posição inicial dos vetores para salvar novos dados
    }
    flag = false;
  }
}



// ** FUNÇÃO BMP180 **
void medicaoBMP() {
  bufferTemperaturaBMP[p] = bmp.readTemperature(); // temperatura informada pelo sensor
  bufferPressaoBMP[p] = bmp.readPressure(); // pressão informada pelo sensor
}

// ** FUNÇÃO MQ135 **
void medicaoMQ(){     
  bufferCo2MQ[p] = mq.getPPM(); // concentração de CO2 informada pelo sensor
}

// ** FUNÇÃO LM35 **
void medicaoTemperaturaLM(){
  bufferTemperaturaLM[p] = (float(analogRead(pinoLM))*5/(1023))/0.01; // temperatura informada pelo sensor
}

// ** FUNÇÃO UVM30A **
int medicaoUVM(){
  float leituraSensorUVM = analogRead(pinoUVM)* (5000 / 1023); // atribui o nível de tensão na saída do sensor a uma variavel
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

// ** FUNÇÃO DHT11 ** (o sensor possui atraso de até 2s)
void medicaoDHT() {
  bufferTemperaturaDHT[p] = dht.readTemperature();  // temperatura informada pelo sensor
  bufferUmidadeDHT[p] = dht.readHumidity(); // umidade informada pelo sensor
  //se a for atribuido um valor não numérico, indica erro de leitura no DHT11
  if (isnan(bufferTemperaturaDHT[p]) || isnan(bufferUmidadeDHT[p])) { 
    Serial.println("Falha de leitura do DHT11");
  } 
}

// ** FUNÇÃO GY30 **
void medicaoGY(){
  bufferIluminanciaGY[p] = gy.readLightLevel(); // iluminância informada pelo sensor
  //se a for atribuido um valor não numérico, indica erro de leitura no GY30
  if (isnan(bufferIluminanciaGY[p])) { 
    Serial.println("Falha de leitura do GY30");
  } 
}

// ** MONITOR SERIAL **
void monitorSerial() { // função para imprimir  os resultados obtidos
  for(int j = 0; j < tamanhoBuffer - 1; j++) {
    Serial.print(bufferTempo[j]); //Tempo
    Serial.print(", ");
    Serial.print(bufferTemperaturaBMP[j]); //BMP180
    Serial.print(", ");
    Serial.print(bufferPressaoBMP[j]);   
    Serial.print(", ");
    Serial.print(bufferCo2MQ[j]); //MQ135   
    Serial.print(", ");
    Serial.print(bufferTemperaturaLM[j]); //LM35   
    Serial.print(", ");
    Serial.print(bufferUltravioletaUVM[j]); //UVM3OA   
    Serial.print(", ");
    Serial.print(bufferTemperaturaDHT[j]); //DHT11
    Serial.print(", ");
    Serial.print(bufferUmidadeDHT[j]);   
    Serial.print(", ");
    Serial.println(bufferIluminanciaGY[j]); //GY30
  }
}
