# Sensor LM35

O LM35 é um sensor de temperatura linear de baixo custo, que fornece uma saída de tensão proporcional à temperatura. Ele é amplamente utilizado em sistemas de controle de temperatura devido à sua facilidade de uso e precisão.
<div align="center">
<img src="https://user-images.githubusercontent.com/69599494/218610105-95684180-fe02-4e38-80ff-034cd8dee842.png" width="500" />
</div>

## Descrição do Sensor
O LM35 é composto por um elemento termoelétrico, geralmente feito de silício, protegido por uma caixa metálica, que também funciona como um terminal de referência para a medição de tensão. Usa o princípio básico de um diodo, onde à medida que a temperatura aumenta em comparação com a temperatura de referência, a tensão através de um diodo aumenta a uma taxa conhecida (10mV/°C). Ao amplificar precisamente a mudança de tensão, gera um sinal analógico diretamente proporcional à diferença de temperatura.

<div align="center">
<img src="https://user-images.githubusercontent.com/82607547/218497691-17bba6e9-9114-4230-afa2-46485eb36501.png" width="500" />
</div>

O LM35 mede temperatura ambiente e é fabricado pela TEXAS INSTRUMENTS.
Comunica-se por Porta Serial Analógica, que entrega uma tensão proporcional a temperatura, ademais há outros 2 pinos no sensor, estes de alimentação Vcc e GND

## Documentação

O datasheet contendo a documentação do sensor LM35 pode ser encontrada no seguinte link: <a href="https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwityo-55JL9AhVVHLkGHTyLDo4QFnoECAwQAQ&url=https%3A%2F%2Fwww.ti.com%2Flit%2Fds%2Fsymlink%2Flm35.pdf&usg=AOvVaw3TDdsy2wQ-Pie-rM_tp1rB">Clique aqui</a>

Este sensor nao necessita de biblioteca para seu funcionamento 

<h2> Informações Técnicas </h2>
	
<ul>
	<li>Tensão de operação 4 à 30VDC</li>
	<li>Consumo de corrente máxima: 60µA</li>
	<li>Faixa de leitura de temperatura: -55° à 150° (±0.5°) C</li>
<ul>
