# Rede de sensores

O projeto Rede de sensores tem como objetivo a implementação de um protótipo capaz monitorar os principais poluentes atmosféricos de baixo custos, além de gerar um material didático que possibilite escolas e comunidades de replicar-la ou até mesmo servir de base para que possam gerar novos protótipos de monitoramento de ar.

# Monitoramento da qualidade do ar

A poluição atmosférica vem mostrando diversos impactos negativos, causando inúmeros impactos no meio ambiente (aquecimento global, degradação do meio ambiente, etc) como também está gerando graves problemas para a saúde humana.

<div align="center">
<img src="https://user-images.githubusercontent.com/69599494/227208746-9af10e33-3231-4a77-a198-d08794893a2b.png" width="600" />
</div>

Portanto é de extrema importância o monitoramento contínuo do ar, pois são através dos dados que são criadas normas de regulamentação que colaboram para uma melhora no bem estar social e ambiental.

<div align="center">
<img src="https://user-images.githubusercontent.com/69599494/227206817-b92bcc06-156e-4b52-8d94-a4fa242b20ac.png" width="500" />
</div>

No entanto a construção de estações de monitoramento de ar requer um alto investimento, além de a estação necessitar de manutenções rotineiras para o seu funcionamento adequado, assim gerando mais gastos.



Com isso, uma das saídas viáveis para contornar esse problema foi o uso de sensores de baixo custo.

# Sensores de baixo custo

Os sensores de baixo custo, mesmo mostrando-se inferior em relação a precisão comparados a sensores mais avançados, obtiveram êxitos em relação à eficientes para o monitoramento do ar em centros urbanos, além de demonstrar que a sua implementação é muito mais simplificada, quando comparado com modelos de monitoramentos mais avançados, outra vantagem foi a forma de armazenamento em nuvens, pois vem se tornando cada vez mais baratos, comparados a outros meios de armazenamento.

Tendo as seguintes formulações, foi se proposto no projeto, a criação de de um protótipo capaz de monitorar a qualidade do ar (realizando medidas de temperatura, número de partículas por milhão no ar, umidade relativa do ar, gases presentes, raios UV e etc. ) com um Arduino Uno, com armazenamento local em uma memória SD e enviadas para uma nuvem, assim possibilitando ter uma forma de armazenamento dos dados e ao mesmo tempo possibilitando o trabalho desses dados via rede.

<div align="center">
<img src="https://user-images.githubusercontent.com/69599494/227247901-183fb1bf-043d-4539-a6cf-8b0df642bd20.png" width="600" />
</div>

# Protótipo 

Atualmente o protótipo em desenvolvimento está sendo montado em uma protoboard, e para uma apresentação mais rápida e simplificada, foi implementado um display oled. Além dos seguintes sensores que compõem o protótipo em desenvolvimento:

<div align="center">
<img src="https://user-images.githubusercontent.com/69599494/226956983-3db41e9a-ea82-497c-b085-3198e567dc17.png" width="600" />
</div>

# Sensores 

	* MQ-135 (concentração de gases) 
	* BMP180 (Temperatura, pressão e altitude) 
	* LM35 (Temperatura)
	* UVM-30A (Raios ultravioletas) 
	* DHT11 (Temperatura e umidade relativa do ar) 
	* GY-30 (Intensidade luminosa por área) 
*PMS5003 (Sensor de concentração de partículas)

Para mais informações em relação a cada sensor, é possível encontrar mais informações nos seguintes link: 

* <a href="https://github.com/ItabirAr/CITinova-Rede_de_Sensores/tree/main/BMP180">BMP180</a>
* <a href="https://github.com/ItabirAr/CITinova-Rede_de_Sensores/tree/main/DHT11">DHT11</a>
* <a href="https://github.com/ItabirAr/CITinova-Rede_de_Sensores/tree/main/GY30">GY30</a>
* <a href="https://github.com/ItabirAr/CITinova-Rede_de_Sensores/tree/main/LM35">LM35</a>
* <a href="https://github.com/ItabirAr/CITinova-Rede_de_Sensores/tree/main/MQ135">MQ-135</a>
* <a href="https://github.com/ItabirAr/CITinova-Rede_de_Sensores/tree/main/UVM30A">UVM-30A</a>
* <a href="https://github.com/ItabirAr/CITinova-Rede_de_Sensores/tree/main/PMS5003">PMS5003</a>

Contendo duas pastas, do qual uma delas sendo o arquivo readme.md, nela estão contidos informações básicas em relação à informações técnicas, forma de funcionamento do sensor e a forma de montagem do sensor. O outro arquivo está em um formato ino, sendo um arquivo com as programações básicas na linguagem C, para o funcionamento do sensor.
