/*
Magnetic Field Meter (Gauss)
& Polarity
I havev Used Hall effect
sensors (AH49E)
By DrakerDG (c)

https://www.youtube.com/user/DrakerDG
*/

#include <SPI.h>
#include <TFT_ST7735.h>

#define BLUE    0xF800
#define RED     0x001F
#define GREEN   0x07E0
#define CYAN    0xFFE0
#define MAGENTA 0xF81F
#define YELLOW  0x07FF

#define DC 9
#define RS 10
#define CS 11
#define pA0 A0
int vA0 = 0;
const byte x1 = 80;

TFT_ST7735 tft = TFT_ST7735(CS, DC, RS);

void Draw_Table(void);
void Print_Data(void);

void setup() {
  tft.begin();
  tft.setRotation(1);
  tft.clearScreen();
  tft.setTextWrap(true);
  tft.setTextColor(YELLOW, BLACK);
  tft.setCursor(0, 0);
  Draw_Table();
}

void loop() {
  Print_Data();
  delay(100);
}

void  Draw_Table(){
  tft.drawFastVLine(22, 0, 128, WHITE);
  for ( int i=0; i<11; i+=1){
    tft.drawFastHLine(20, 5+i*12, 4, WHITE);
    if (!(i&1)){
      tft.setCursor(0, i*12+2);
      tft.print((10.0-i)*5.0/10.0, 1);
      }
    }
  tft.drawFastHLine( 20, 125, 128, WHITE);
  tft.setCursor(x1-35, 5);
  tft.print("Magnetic Field");
  tft.setCursor(x1+20, 40);
  tft.print("Gauss");
  tft.setCursor(x1+5, 75);
  tft.print("Voltage");
  tft.setCursor(x1+30, 110);
  tft.print("VDC");
  tft.setTextSize(2);
  tft.setTextColor(WHITE, BLACK);
}

void Print_Data(){
  char strG[8];
  vA0 = analogRead(pA0);
  float vV0 = vA0*5.00/1024;
  
  float vG0 = -1000.0+(vV0-1)*2000/3;
  
  dtostrf(vG0, 7, 1, strG);
  tft.setCursor(x1-35, 20);
  tft.print(strG);
  tft.setCursor(x1, 90);
  tft.print(vV0);
  vA0 = map(vA0, 0, 1024, 0, 120);
  tft.fillRect(30, 5, 10, 120-vA0, BLACK);
  tft.fillRect(30, 125-vA0, 10, vA0, GREEN);
  tft.setCursor(x1, 55);
  /* Determines polarity of
  magnetic field */
  tft.setTextSize(1);
  if (vG0==0) tft.print("No Field");
  else if (vG0>0) tft.print("Eq Poles");
  else tft.print("Op Poles");
  tft.setTextSize(2);
}