#include <Adafruit_BMP085.h> //biblioteca do sensor BMP180

Adafruit_BMP085 bmp; //define bmp como objeto do tipo Adafruit_BMP085
float Temperatura; //variável auxiliar com valores fracionados
int Pressao; //variável auxiliar tipo números inteiros
float Altitude; //variável auxiliar com valores fracionados

void setup()
{
  Serial.begin(9600); //inicialização do Monitor Serial
  //inicialização do Sensor
  if (!bmp.begin()) { // se o sensor não for inicializado, apresenta no monitor serial a mensagem:
    Serial.println("Sensor BMP180 não foi identificado! Verifique as conexões.");
    while (1) {} //em loop até o sensor inicializar
  }
}

void loop()
{
  //Atribuição dos valores medidos
  Temperatura = bmp.readTemperature(); //função que mede a temperatura
  Pressao = bmp.readPressure(); //função responsável por medir a pressão
  Altitude = bmp.readAltitude(); //função que retorna a altitude
  
  //Impressão dos dados no Monitor Serial
  Serial.print("Temperatura: ");
  Serial.print(Temperatura);
  Serial.print(" °C"); //temperatura em Graus Celsius
  Serial.print("\t"); //espaçamento entre os valores

  Serial.print("Pressão: ");
  Serial.print(Pressao);
  Serial.print(" Pa"); //pressão em Pascal
  Serial.print("\t");

  Serial.print("Altitude: ");
  Serial.print(Altitude);
  Serial.println(" m"); //pressão em Metros

  delay(1000); //intervalo de 1 segundo
}