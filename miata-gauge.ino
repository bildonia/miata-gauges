
/*********************************************************************
Miata guages
*********************************************************************/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1325.h>

// If using software SPI, define CLK and MOSI
#define OLED_CLK 13
#define OLED_MOSI 11

// These are neede for both hardware & softare SPI
#define OLED_CS 10
#define OLED_RESET 9
#define OLED_DC 8

// this is for hardware SPI, fast! but fixed oubs
Adafruit_SSD1325 display(OLED_DC, OLED_RESET, OLED_CS);

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

int ALARM_PIN = 7;

float currentValue = -5;
boolean inverted = false;
int cycles = 1;

void setup()   {                
  Serial.begin(9600);
  Serial.println("SSD1325 OLED test");
  boolean inverted = false;
 
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin();
  // init done
  display.clearDisplay();
  display.setTextWrap(false);
  display.setTextColor(WHITE);
  display.display();
  
}

void loop() {
  //Get Data

  display.clearDisplay();
  showBoost();
  currentValue += .021 * cycles;

  if (currentValue > 30) {
    currentValue = 30;
  }
    
    
  cycles++;
}

void showBoost() {
  char label[ ] = "BOOST";
  float value = currentValue;
  float upperLimit = 14.7;
  float lowerLimit = -100;
  int rangeHigh = 20;
  int rangeLow = -20;
  int decimals = 1;
  String unit = "PSI";
  
  showData(label, value, decimals, unit, upperLimit, lowerLimit, rangeLow, rangeHigh);
  display.display();
  
  if (value >= upperLimit || value <= lowerLimit)
    enableAlarm();
  else
    disableAlarm();
}

void showIntakeTemp() {
  char label[ ] = "INTAKE";
  float value = currentValue;
  float upperLimit = 125;
  float lowerLimit = 32;
  int rangeHigh = 150;
  int rangeLow = 0;
  int decimals = 1;
  String unit = "F";
  
  showData(label, value, decimals, unit, upperLimit, lowerLimit, rangeLow, rangeHigh);
  display.display();
  
  if (value >= upperLimit || value <= lowerLimit)
    enableAlarm();
  else
    disableAlarm();
}

void enableAlarm(void) {
 
  if (cycles % 6 == 0) {
    display.invertDisplay(false);
    noTone(ALARM_PIN);
  }
  else if (cycles % 6 == 3){
    display.invertDisplay(true);
    //tone(ALARM_PIN, 1640);
  }
}

void disableAlarm(void) {
   if (inverted)
     display.invertDisplay(false);
     
   inverted = !inverted;
   noTone(ALARM_PIN);
}

void showData(char label[], float value, int decimals, String unit, float upperLimit, float lowerLimit, int rangeLow, int rangeHigh) {
  int gaugeWidth = 118;
  int gaugeX = 5;
  int gaugeY = 23;
  int gaugeLabelY = gaugeY - 8;
  
  //Print Guage labels
  display.setCursor(0, gaugeLabelY);
  display.setTextSize(1);
  display.print(rangeLow);
  display.setCursor(110, gaugeLabelY);
  display.print(rangeHigh);
    
  //Print Guage
  display.drawRect(gaugeX, gaugeY, gaugeWidth, 20, 1);
  float percentageWidth = (value - rangeLow) / (rangeHigh - rangeLow) * gaugeWidth; 
  if (percentageWidth > gaugeWidth)
    percentageWidth = gaugeWidth;
  display.fillRect(gaugeX, gaugeY, percentageWidth, 20, 1);
  
  //Print Warning Lines
  float lowerX = ((lowerLimit - rangeLow) / (rangeHigh - rangeLow) * gaugeWidth) + gaugeX; 
  float upperX = ((upperLimit - rangeLow) / (rangeHigh - rangeLow) * gaugeWidth) + gaugeX; 
  
  int start = gaugeY + 1;
  for(int i = 1; i < 5; i++) {
    if (value >= upperLimit) {
      display.drawLine(upperX, start, upperX, start + 2, BLACK);
      display.drawLine(lowerX, start, lowerX, start + 2, BLACK);
    }
    else if (value <= lowerLimit) {
      display.drawLine(upperX, start, upperX, start + 2, WHITE);
      display.drawLine(lowerX, start, lowerX, start + 2, WHITE);
    }
    else {
      display.drawLine(upperX, start, upperX, start + 2, WHITE);
      display.drawLine(lowerX, start, lowerX, start + 2, BLACK);      
    }

    start += 5;
  }
  
  //Print Label
  display.setTextSize(2);
  display.setCursor(35, 48);
  display.print(label);
  
  //Print Value
  setCursorForValue(value, 2);
  display.print(value, decimals);
  
  //Print Unit
  display.setTextSize(1);
  display.print(unit);
  
  display.display();
}

void setCursorForLabel(char label[], int fontSize) {
  int x = (7 - strlen(label)) * 5;
  display.setCursor(x, 5);
}

void setCursorForValue(float value, int fontSize) {
  int x = 0;
  int y = 5;
  
  if (fontSize == 3)
  {
      if (value <= -100 || value >= 1000)
        x = 0;
      else if (value <= -10 || value >= 100)
        x = 10;
      else if (value >= 10)
        x = 20;
      else if (value < 0)
        x = 15;
      else
        x = 25;
  }
  else
  {
      if (value <= -100 || value >= 1000)
        x = 27;
      else if (value <= -10 || value >= 100)
        x = 35;
      else if (value >= 10 || value < 0)
        x = 43;
      else
        x = 50; 
  }

    
  display.setCursor(x, y);
}
