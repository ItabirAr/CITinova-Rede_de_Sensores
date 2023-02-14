# Sensor DHT11

<div align="center">
<img src="https://user-images.githubusercontent.com/69599494/218608958-618bacde-2512-453f-8fd6-229def22059c.png" width="500" />
</div>

## Descrição do Sensor
O DHT11 é composto por um sensor resistivo e um termistor NTC. 
O sensor resistivo mede a umidade pela variação da resistência de um material capaz de absorver umidade. Ao absorver vapor d‘água, a resistência do material diminui por causa do aumento da condutividade elétrica. 
Um termistor é um dispositivo elétrico cuja resistência elétrica altera drasticamente com a temperatura. Para o tipo NTC, a resistência interna reduz com o aumento da temperatura, geralmente utiliza-se uma Ponte de Wheatstone ou um Amplificador para obter uma aproximação linear. 

<div align="center">
<img src="https://user-images.githubusercontent.com/69599494/218611038-4041b281-14b8-4462-88db-a04b3ad94575.png" width="700" />
</div>

O DH11 realiza medições de temperatura (°C) e umidade relativa do ar (%UR). Os principais fabricantes são a  UNIVERSAL-SOLDER Electronics Ltd  e a  Guangzhou Aosong Electronics Co Ltd . O sensor deve ser alimentado por fonte de tensão entre 3,0V e 5,5V.
O DTH11 transmite dados por comunicação serial Single-Wire Two-Way, o sensor possui conversor análogo digital interno de 16 bits. Após o microcontrolador enviar um sinal de inicialização, o sensor entra em modo de execução. É transmitido um sinal de 40 bits para o Arduino, em pacotes de 8 bits: o byte. Os primeiros 4 bytes são as informações de umidade e temperatura. O último byte trata-se da soma dos 32 dígitos anteriores, para verificação de autenticidade dos dados. Em seguida, o sensor entra em modo de baixo consumo e aguarda um novo sinal do Arduino.


## Documentação

O datasheet contendo a documentação do sensor DHT11 pode ser encontrada no seguinte link: <a href="https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf">Clique aqui</a>

<h1> Informações Técnicas </h1>
	
<ul>
	<li>Tensão de operação 3 à 5.5VDC</li>
	<li>Consumo de corrente: 0.5 à 2.5µA</li>
	<li>Faixa de leitura de umidade: 20 à 90% (±5%) RH</li>
	<li>Faixa de leitura de temperatura: 0° à 50° (±2°) C</li>
	<li>Saída: Digital</li>
	<li>Dimensões 12x23.5x5.5mm</li>
<ul>
