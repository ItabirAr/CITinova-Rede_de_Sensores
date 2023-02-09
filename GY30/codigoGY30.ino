#include <BH1750.h> //biblioteca do sensor GY30

BH1750 gy; //define gy como objeto do tipo BH1750
float Iluminancia; // vetor para os dados lidos de iluminância (intensidade luminosa por área)

void setup()
{
  Serial.begin(9600); //inicialização do Monitor Serial
  Wire.begin();        //INICIALIZA O I2C BUS
  gy.begin(); //inicialização o sensor GY30
}

void loop()
{
  //Atribuição dos valores medidos
  Iluminancia = gy.readLightLevel(); //iluminância informada pelo sensor

  //Impressão dos dados no Monitor Serial
  if (isnan(Iluminancia)) { //se for atribuído um valor não numérico à variável, indica erro de leitura no sensor
    Serial.println("Falha de leitura do GY30."); 
  } 
  else { //caso contrário, imprime os valores
    Serial.print("Iluminância: "); //intensidade luminosa por área
    Serial.print(Iluminancia);
    Serial.println(" lux"); //lux = lm/m²
  }
  delay(1000); //intervalo de 1 segundo
}