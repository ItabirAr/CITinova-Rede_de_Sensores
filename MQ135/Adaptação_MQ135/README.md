# MQ-135

Inicialmente o sensor MQ-135 foi projetado para detectar uma alta variedade de gases nocivos (NH3, NOx, álcool, benzeno, fumaça e CO2). No entanto, para atender aos interesses do projeto, foram feitas adaptações para que o sensor leia apenas quantidades de CO2 presente no ar.

Sabendo-se que os valores lidos pelo sensor é uma conversão do valor lido na tensão entregue na carga resistiva, sendo que a variação da tensão depende do valor da carga resistiva presente no sensor. É de extrema importância que a resistência presente no sensor tenha um valor expressivo para que o cálculo na leitura possa ser preciso.

# Procedimento

Inicialmente para iniciar a adaptação do sensor MQ-135 para a leitura de CO2, é necessário a troca do resistor  Rs de 1K ohm para uma resistência de 22k ohm, pois a leitura de CO2 é mais sensível que outros gases, resultando em uma variação de tensão menor caso o Rs seja um valor muito baixo.


<div align="center">
<img src="https://user-images.githubusercontent.com/69599494/236005931-020d0d21-b82d-46eb-86d0-db951c83a4d3.png" width="800" />
</div>

Fazendo se a troca é possível observar com uma maior variação, pois a tensão lida é feita através do cálculo da divisão de tensão entre Rs e a resistência lida no material SnO2.

Tendo feita a seguinte troca, o restante das adaptações a partir serão as mudanças feitas através de softwares. Os dados necessários para as alterações inicialmente e descobrir o valor da resistência resultante do material SnO2 em ar limpo. Para medir tais valores inicialmente é necessário manter o sensor ligado durante um período de 24 horas e após isso utiliza-se o seguinte código, o código retornará um valor para o R0 no serial.

```
#include "MQ135.h"
configuração nula (){
Serial.begin (9600);
}
loop void() {
Sensor de gás MQ135 = MQ135(A0); // Conecta o sensor ao pino A0
float rzero = gasSensor.getRZero();
Serial.println (rzero);
atraso(1000);
}
```
Tendo o valor medido, é preciso atualizar os dados da biblioteca, e para isso basta seguir o seguinte caminho: Documentos > Arduino > bibliotecas > pasta MQ135 e abra o arquivo MQ135.h e altere os valores RLOAD e RZERO.

<div align="center">
<img src="https://user-images.githubusercontent.com/69599494/235971903-1d2a5cdd-0390-4b14-84c0-e39019cafa7b.png" width="900" />
</div>

obs: atualizar também o valor de ATMOCO2, que é um valor médio de CO2 presente na atmosfera terrestre, um valor que pode ser encontrado na internet (Para julho de 2022 foi encontrado um valor de 414.47).

<div align="center">
<img src="https://user-images.githubusercontent.com/69599494/235976325-4ea4300e-a8c2-47f1-893e-973df81a92a8.png" width="500" />
</div>

# Referência

Measuring CO2 concentration in air using Arduino and MQ-135 sensor. Disponível em: <https://circuitdigest.com/microcontroller-projects/interfacing-mq135-gas-sensor-with-arduino-to-measure-co2-levels-in-ppm>. Acesso em: 30 abr. 2023.

