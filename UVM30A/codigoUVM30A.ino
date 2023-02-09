#define pinoUVM A1 //pino do Arduino usado para a conexão
float tensao; //nível de tensão de saída do sensor lido no arduino
int IndiceUV; //variável auxiliar para o Índice de Intensidade de Raios Ultravioleta

void setup() 
{
  Serial.begin(9600); //inicialização do Monitor Serial
}

int indice() //Atribuição dos valores medidos
{
  tensao = analogRead(pinoUVM); //atribui o valor lido da tensão à variável auxilar
  if (tensao >= 0 && tensao < 50) {  return 0; } 
  else if (tensao >= 50 && tensao < 227) { return 1; } 
  else if (tensao >= 227 && tensao < 318) { return 2; } 
  else if (tensao >= 318 && tensao < 408) { return 3; } 
  else if (tensao >= 408 && tensao < 503) { return 4; } 
  else if (tensao >= 503 && tensao < 606) { return 5; } 
  else if (tensao >= 606 && tensao < 698) { return 6; } 
  else if (tensao >= 698 && tensao < 795) { return 7; } 
  else if (tensao >= 795 && tensao < 881)  { return 8; } 
  else if (tensao >= 881 && tensao < 976)  { return 9; } 
  else if (tensao <= 976 && tensao < 1079) { return 10; } 
  else if (tensao > 1079) { return 11; }
}

void loop()
{
  IndiceUV = indice(); //atribui o valor do Índice de Radiação UV
  
  //Impressão dos dados no Monitor Serial
  Serial.print("Índice Ultravioleta: ");
  Serial.print(IndiceUV);
  if (IndiceUV == 1 || IndiceUV == 2) { Serial.println(", Baixo"); }
  else if (IndiceUV == 3 || IndiceUV == 4 || IndiceUV == 5) { Serial.println(", Moderado"); }
  else if (IndiceUV == 6 || IndiceUV == 7) { Serial.println(", Alto"); }
  else if (IndiceUV == 8 || IndiceUV == 9 || IndiceUV == 10)  { Serial.println(", Altíssimo"); }
  else if (IndiceUV == 11) { Serial.println(", Extremo"); }

  delay(1000); //intervalo de 1 segundo
}