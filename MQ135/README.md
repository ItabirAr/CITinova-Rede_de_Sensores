# Sensor MQ-135

O sensor MQ135 será utilizado para medir a concentração de gás CO2. Este sensor é projetado especificamente para detectar gases poluentes, como dióxido de carbono, e fornecer uma leitura precisa da concentração de gás no ar. 

<div align="center">
<img src="https://github.com/ItabirAr/CITinova-ITABIRAR/issues/6#issue-1583246030" width="500" />
</div>


## Descrição do Sensor
Trata-se de um sensor semicondutor do tipo MOS (metal oxide semiconductor). O material sensível do sensor é o SnO2 (óxido de estanho), que possui baixa condutividade quando exposta ao ar limpo. À medida que surgem algum tipos de gases, sua condutividade aumenta com a concentração desses gases. Colocando-se então esse material entre dois eletrodos e em série com uma resistência conhecida e, aplicando-se uma tensão elétrica constante sobre esse conjunto, obtém-se na saída uma tensão elétrica proporcional à concentração de gases. Quanto maior a concentração de gás, maior será a tensão de saída. O sensor tem uma temperatura de funcionamento padrão que é fornecida por um eletrodo de aquecimento

<div align="center">
<img src="https://user-images.githubusercontent.com/82607547/217800135-6a3f9601-1a80-42e7-b663-99c64d0111f0.png" width="700" />
</div>

O sensor MQ-135 é capaz de detectar gases tóxicos no ar, podendo detectar concentrações entre 10 e 300 ppm (partes por milhão) de amônia e álcool e entre 10 e 1000 ppm de benzeno no ar. A sua sensibilidade é ajustada por um trimpot acoplado a sua placa. Em concentrações normais do gás, a saída digital do sensor permanece desligada, quando o ponto de ajuste (setpoint) é ultrapassado, a saída digital é ligada permanecendo em nível alto. Além da saída digital, o sensor possui saída analógica, possibilitando a leitura da concentração medida de gases no ar com precisão. Sempre que alimentado, o LED de alimentação permanecerá aceso, já o LED da saída digital é acionado quando o valor lido pelo sensor superar o ponto de ajuste. O trimpot é o variador da sensibilidade na qual aciona a saída digital.

## Documentação
O datasheet contendo a documentação do sensor MQ-135 pode ser encontrado no seguinte link: <a href="https://pdf1.alldatasheet.com/datasheet-pdf/view/1307647/WINSEN/MQ135.html">Clique aqui</a> 

Para o sensor medir concentrações de CO2 é importante atentar a algumas configurações que devem ser realizadas previamente, as informações e procedimentos pode ser encontrados no seguinte link: <a href="https://circuitdigest.com/microcontroller-projects/interfacing-mq135-gas-sensor-with-arduino-to-measure-co2-levels-in-ppm">Clique aqui</a> 

A biblioteca utilizada no código pode ser encontrada no seguinte link: <a href="https://www.arduinolibraries.info/libraries/mq135">Clique aqui</a> 

## Informações tecnicas
<ul>
	<li>Tensão de operação: 5VDC</li>
	<li>Faixa de detecção amônia: 10ppm à 300ppm</li>
	<li>Faixa de detecção benzeno: 10ppm à 1000ppm</li>
	<li>Faixa de detecção álcool: 10ppm à 300ppm</li>
	<li>Saídas: Digital e analógica</li>
	<li>Dimensões 40x25x22mm</li>
<ul>
