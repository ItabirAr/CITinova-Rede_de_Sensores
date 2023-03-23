#include <DHT.h> //biblioteca do sensor DHT11

#define pinoDHT A1 //pino  usado para a conexão
#define modeloDHT DHT11 //modelo do sensor
DHT dht(pinoDHT, modeloDHT); // define dht como objeto do tipo DHT
float Temperatura; //vetor para os dados lidos de temperatura
float Umidade; //vetor para os dados lidos de umidade

void setup()
{
  Serial.begin(9600); //inicialização do Monitor Serial
  dht.begin(); //inicialização o sensor DHT11
}

void loop()
{
  //Atribuição dos valores medidos
  Temperatura = dht.readTemperature(); //temperatura informada pelo sensor
  Umidade = dht.readHumidity(); //umidade informada pelo sensor

  //Impressão dos dados no Monitor Serial
  if (isnan(Temperatura) || isnan(Umidade)) { //se for atribuido um valor não numérico as variáveis, indica erro de leitura no sensor
    Serial.println("Falha de leitura do DHT11."); 
  } 
  else { //caso contrário, imprime os valores
    Serial.print("Temperatura: "); 
    Serial.print(Temperatura);
    Serial.print(" °C"); //temperatura em Graus Celsius
    Serial.print("\t"); //espaçamentos entre os dados
    Serial.print("Umidade Relativa do Ar: ");
    Serial.print(Umidade);
    Serial.println(" %UR"); //percentual de Umidade Relativa do Ar
  }
  delay(1000); //intervalo de 1 segundo
}
