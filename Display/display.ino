#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <avr/interrupt.h>


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

int temp = 25;
int umidade = 50;
int particulas = 100;
int co2 = 400;
int uv = 7;
int ct2 = 0;
volatile int currentScreen = 0;
volatile int update = 0;

const unsigned char termo [] PROGMEM = {
 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 
  0xc0, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 
  0x00, 0x01, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x60, 0x00, 
  0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x88, 0x00, 0x02, 
  0x14, 0x00, 0x05, 0x08, 0x00, 0x04, 0x02, 0x00, 0x04, 0x0a, 0x00, 0x01, 0x0c, 0x00, 0x02, 0xe4, 
  0x00, 0x00, 0x90, 0x00
};


 const unsigned char gota [] PROGMEM  = {
0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x90, 0x00, 0x01, 0x98, 0x00, 0x01, 0x08, 0x00, 0x02, 
  0x04, 0x00, 0x06, 0x06, 0x00, 0x04, 0x02, 0x00, 0x08, 0x01, 0x00, 0x08, 0x01, 0x00, 0x08, 0x01, 
  0x00, 0x10, 0x00, 0x80, 0x10, 0x00, 0x80, 0x10, 0x12, 0x80, 0x10, 0x2a, 0x80, 0x08, 0x15, 0x00, 
  0x08, 0x19, 0x00, 0x04, 0x22, 0x00, 0x03, 0x0c, 0x00, 0x00, 0x60, 0x00
};

const unsigned char sol_uv [] PROGMEM ={
  0x20, 0x08, 0x10, 0x30, 0x08, 0x10, 0x30, 0x18, 0x30, 0x18, 0x18, 0x30, 0x18, 0x18, 0x60, 0x0c, 
	0x10, 0x60, 0x0c, 0x10, 0xc0, 0x86, 0x10, 0xc0, 0xc6, 0x11, 0x80, 0x63, 0x31, 0x00, 0x33, 0x33, 
	0x10, 0x19, 0xb2, 0x30, 0x8d, 0xa6, 0x60, 0xef, 0xfd, 0xc0, 0x77, 0x1f, 0x80, 0x1c, 0x07, 0x30, 
	0xf8, 0x03, 0xe0, 0x0c, 0x01, 0x80, 0x06, 0x01, 0x00, 0x07, 0xe1, 0xf0, 0x00, 0x6f, 0xb0, 0x00, 
	0x39, 0xe0, 0x00, 0x10, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x000
};


void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();


  // Configura o timer2 para gerar uma interrupção a cada 3 segundos
  cli();
  TCCR2A = 0x00; //configura o registrador TCCR2A
  TCCR2B = 0x07; //configura o registrador TCCR2B
  TCNT2 = 56; //zera o contador do timer2
  
  //habilita a interrupção do timer2 quando o OCR2A é atingido
  TIMSK2 = 0x01;
  sei();

}

ISR(TIMER2_OVF_vect) {
   TCNT2   =    56;    //inicializa timer2    
   //aprox 12ms
   ct2+=1;
   if(ct2 == 234)
   {
     //aprox. 3seg
     ct2 = 0;
     update = 1;
   }
   
}

void loop() {
    display.clearDisplay();
    //display.display();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.setTextColor(WHITE); // Cor do texto

  if (update) {
    update = 0;
    switch(currentScreen){
    case 0:
        display.clearDisplay();      
        display.setCursor(5,5);  
        display.drawBitmap(10,10, termo, 20, 28, WHITE); //ESCREVE O TEXTO NO DISPLAY
        display.setCursor(40,10);
        display.println("Temperatura:");
        display.setCursor(60,30);
        display.print(temp);
        display.println(" C");
        display.display();
        break;
    case 1:
        display.clearDisplay();      
        display.setCursor(5,5);  
        display.drawBitmap(10,10, gota, 20, 28, WHITE); //ESCREVE O TEXTO NO DISPLAY
        display.setCursor(55,10);
        display.println("Umidade:");
        display.setCursor(60,30);
        display.print(umidade);
        display.println(" %");
        display.display();
        break;      


    case 2:
        display.clearDisplay();      
        display.setCursor(5,5);  
       // display.drawBitmap(10,10, part, 20, 28, WHITE); //ESCREVE O TEXTO NO DISPLAY
        display.setCursor(55,10);
        display.println("Particulas:");
        display.setCursor(60,30);
        display.print(particulas);
        display.println(" ug/m3");
        display.display();
        break;

    case 3:
        display.clearDisplay();      
        display.setCursor(5,5);  
        //display.drawBitmap(10,10, co2, 20, 28, WHITE); //ESCREVE O TEXTO NO DISPLAY
        display.setCursor(55,10);
        display.println("CO2:");
        display.setCursor(60,30);
        display.print(co2);
        display.println(" ppm");
        display.display();
        break;

    case 4:
        display.clearDisplay();      
        display.setCursor(5,5);  
        display.drawBitmap(10,10,sol_uv, 20, 28, WHITE); //ESCREVE O TEXTO NO DISPLAY
        display.setCursor(55,10);
        display.println("UV:");
        display.setCursor(60,30);
        display.print(uv);
        display.display();
        break;
    }
      display.display();
        if (currentScreen < 4) {
            currentScreen++;
        } else {
            currentScreen = 0;
    }
  }
}
