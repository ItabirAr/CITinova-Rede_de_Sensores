# Sensor BMP180

<div align="center">
<img src="https://user-images.githubusercontent.com/69599494/218602613-a81b8dfa-1378-4e88-936e-6c92e9419689.png" width="500" />
</div>


## Descrição do Sensor
O BMP180 é composto por um sensor piezoresistivo e um sensor MEMS de temperatura. 
O sensor piezoresistivo utiliza um diafragma de material semicondutor cuja resistência varia de acordo com a pressão. Dessa forma, a intensidade da corrente que passa pelo diafragma é proporcional à força causada pela pressão. 
O sensor de temperatura é um MEMS (Sistema Microeletromecânico) que funciona a partir de uma lente de silício que reúne a radiação infravermelha em um material semicondutor cuja informação de temperatura está correlacionada com a diminuição da resistência do material. 

<div align="center">
<img src="https://user-images.githubusercontent.com/69599494/218611909-aa7a7883-699c-4721-9f36-315690ac9bab.png" />
</div>

O BMP180 mede temperatura, altitude e pressão. Porém para esse projeto serão coletados apenas os dados de temperatura e pressão fornecidos pelo sensor. O modelo é fabricado pela BOSCH Invented For Life, ou pela TEXAS INSTRUMENTS.
Utiliza-se a Comunicação Serial I2C – Inter-Integrated Circuit – a qual utiliza dois canais para comunicação: um canal para transmissão e recepção de dados (SDA) e outro a para sincronização dos dados (SCL).


## Documentação

O datasheet contendo a documentação do sensor BMP180 pode ser encontrada no seguinte link: <a href="https://cdn-shop.adafruit.com/datasheets/BST-BMP180-DS000-09.pdf">Clique aqui</a>

<h1> Informações Técnicas </h1>
	
<ul>
	<li>CI BMP180</li>
	<li>Tensão de operação 1.8 à 3.6VDC</li>
	<li>Consumo de corrente: 0.5µA</li>
	<li>Faixa de leitura de pressão: 300 à 11001hPa(+9000 à -500m)</li>
	<li>Conexão I2C</li>
	<li>Sensor de temperatura embutido: -40 à +85°C</li>
	<li>Calibrção de fábrica</li>
	<li>Dimensões 13x10mm</li>
<ul>
