#include <MQ135.h> //biblioteca do sensor MQ135

#define pinoMQ A2 //pino do Arduino usado para a conexão
MQ135 mq = MQ135(pinoMQ); //define mq como objeto do tipo MQ135
float ConcentrCO2; //variável auxiliar para os dados lidos de CO2

void setup()
{
  Serial.begin(9600); //inicialização do Monitor Serial
}

void loop()
{
  //Atribuição dos valores medidos
  ConcentrCO2 = mq.getPPM(); //concentração de CO2 informada pelo sensor
  
  //Impressão dos dados no Monitor Serial
  Serial.print("Concentração de CO2: ");
  Serial.print(ConcentrCO2);
  Serial.println(" ppm"); //partes por milhão

  delay(1000); //intervalo de 1 segundo
}
