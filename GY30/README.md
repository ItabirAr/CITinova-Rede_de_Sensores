# Sensor GY30
<div align="center">
<img src="https://user-images.githubusercontent.com/69599494/218609888-cdbe3b4e-4b05-440e-baa5-784ad7eef5c6.png" width="500" />
</div>

## Descrição do Sensor
Esse sensor é baseado em um semicondutor do tipo fotodiodo que, quando exposto a uma fonte de luz, absorve fótons e os converte em corrente elétrica. Portanto o sinal elétrico gerado pode ser relacionado ao nível de luminosidade do ambiente monitorado. Como o sinal gerado é muito pequeno, ele precisa ser condicionado, o que é feito através de um amplificador de sinal. Em seguida, esse sinal precisa ser preparado para ser transmitido, por isso ele passa por um conversor analógico-digital e depois por um processador que calcula o índice de luminosidade com base na quantidade de luz absorvida. Por fim, o índice de luminosidade é transmitido para ser armazenado.

<div align="center">
<img src="https://user-images.githubusercontent.com/69599494/218612254-b1d88baa-f4b7-4e95-94b6-afbc4eee3f64.png" />
</div>

O sensor, fabricado por ROHM Semiconductor, foi projetado para detectar o espectro de luz visível ao olho humano com sensibilidade de pico em 560 nm, que está no espectro verde. Agama completa abrange aproximadamente 400 nm a 700 nm. O sensor funciona bem com amaioria das luzes brancas visíveis, incluindo a luz solar, incandescente, fluorescente, halógena e LED branca. Tem boa rejeição de UV e IR.
O I2C utiliza dois canais para comunicação. A diferença é que, nesse caso, um canal é de transmissão e recepção de dados e outro é para sincronização dos mesmos. Em relação aos dois canais de comunicação, temos: o canal de dados seriais, chamado de serial data (SDA); e o canal de sincronização, chamado serial clock (SCL). Simplificadamente, o Clock é um sinal que oscila entre nível alto e baixo rapidamente. Então, essa oscilação é utilizada para sincronizar os dispositivos a cada vez que o clock apresentar certo estado.


## Documentação

O datasheet contendo a documentação do sensor BMP180 pode ser encontrada no seguinte link: <a href="https://www.mouser.com/datasheet/2/348/bh1750fvi-e-186247.pdf">Clique aqui</a>

<h1> Informações Técnicas </h1>
	
<ul>
	<li>Tensão de operação 3 à 5VDC</li>
	<li>Faixa de leitura de luminosidade: 1 à 65535lx(±20%)</li>
	<li>Conexão I2C</li>
	<li>Dimensões 33x20x3mm</li>
<ul>
