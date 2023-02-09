#define pinoLM A2 //pino do Arduino usado para a conexão
float Temperatura; //declara uma variável auxiliar para resposta do sensor

void setup()
{
  Serial.begin(9600); //inicialização do Monitor Serial
}

void loop()
{
  //Atribuição dos valores medidos
  Temperatura = (float(analogRead(pinoLM))*5/(1023))/0.01; //temperatura lida pelo sensor
  
  //Impressão dos dados no Monitor Serial
  Serial.print("Temperatura: ");
  Serial.print(Temperatura);
  Serial.println(" °C"); //temperatura em Graus Celsius

  delay(1000); //intervalo de 1 segundo
}