
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

 #include <avr/pgmspace.h> 
  
const unsigned char PROGMEM SPLASH_SCREEN [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x07, 0xC0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x1E, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
0x00, 0x3E, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00,
0x01, 0xFC, 0x01, 0xC0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00,
0x03, 0xF8, 0x01, 0x80, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00,
0x03, 0xE0, 0x01, 0x80, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x9E, 0x00, 0x00, 0x00, 0x00,
0x1F, 0xE0, 0x03, 0x81, 0xC7, 0x80, 0x00, 0x18, 0x00, 0x03, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00,
0x3F, 0x00, 0x07, 0x03, 0x07, 0x80, 0x00, 0x7E, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
0x3F, 0x00, 0x06, 0x06, 0x07, 0x80, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00,
0x3F, 0x00, 0x0E, 0x1E, 0x07, 0x81, 0x00, 0x06, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00,
0x1E, 0x00, 0x1C, 0x30, 0x1F, 0x8F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3C, 0xE0, 0x1F, 0x9F, 0xF0, 0x00, 0x00, 0x3F, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3F, 0xC0, 0x1F, 0x19, 0xF8, 0x02, 0x00, 0xFF, 0xE0, 0x3E, 0x03, 0xE0, 0x00, 0x00,
0x00, 0x00, 0x7F, 0x80, 0x3F, 0xB0, 0xF8, 0x06, 0x01, 0xF8, 0x78, 0x3E, 0x0F, 0xF8, 0x00, 0x00,
0x00, 0x00, 0xFF, 0x00, 0x3F, 0xF0, 0xFC, 0x07, 0x03, 0xF0, 0x7C, 0x3E, 0x1F, 0x06, 0x00, 0x00,
0x00, 0x00, 0xFE, 0x00, 0x3F, 0xF0, 0xFC, 0x07, 0x87, 0xE0, 0x3C, 0x3F, 0x1E, 0x03, 0x00, 0x00,
0x00, 0x00, 0xFC, 0x00, 0x3F, 0xE0, 0xFC, 0x07, 0x8F, 0xC0, 0x3C, 0x1F, 0xFE, 0x03, 0xC0, 0x00,
0x00, 0x03, 0xF8, 0x00, 0x1F, 0xC0, 0xFC, 0x07, 0xFF, 0x80, 0x3E, 0x1F, 0xFE, 0x03, 0xF0, 0x00,
0x00, 0x03, 0xE0, 0x00, 0x04, 0x80, 0xFC, 0x0F, 0xFF, 0x80, 0x3F, 0x9F, 0xFC, 0x01, 0xF0, 0x00,
0x00, 0x03, 0xE0, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFF, 0x80, 0x7F, 0xFF, 0xFC, 0x01, 0xF0, 0x00,
0x00, 0x07, 0xC0, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xE0, 0xFF, 0xFF, 0xFE, 0x03, 0xFE, 0x00,
0x00, 0x0F, 0x80, 0x00, 0x00, 0x00, 0x3F, 0xF0, 0x07, 0xFF, 0xC3, 0xFF, 0xFF, 0x06, 0x3F, 0x80,
0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xE0, 0x00, 0xFF, 0x80, 0xE0, 0x2F, 0xF8, 0x0B, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x07, 0xE0, 0x00, 0xE0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


int ALARM_PIN = 7;
int NEXT_BTN_PIN = 14;

float currentValue = -5;
boolean inverted = false;
int cycles = 1;
int currentScreen = 0;
int buttonPressedCycle = 0;

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
  
  //Buttons
  pinMode(NEXT_BTN_PIN, INPUT);
  
  //Splashscreen
  display.drawBitmap(0, 13, SPLASH_SCREEN, 128, 36, WHITE);
  display.display();
  delay(3000);
}

void loop() {
  //Get Data

  //Show Data
  display.clearDisplay();
  ShowCurrentScreen();
  display.display();
  
  //Listen for Events
  CheckForButtonPresses();
  
  cycles++;
}

void ShowCurrentScreen() {
  switch(currentScreen) {
    case 0:
      showBoost();
      break;
    case 1:
      showIntakeTemp();
      break;
    case 2:
      showExhaustTemp();
      break;
    case 3:
      showCoolantTemp();
      break;
    case 4:
      showAll();
      break;
    default:
      showBoost(); 
  }
  
 // currentValue += .1;

//  if (currentValue > 30) {
//    currentValue = 30;
//  }
}

void CheckForButtonPresses() {
  int cycleDelay = 5;
  if (cycles > (buttonPressedCycle + cycleDelay))
  {
    if (digitalRead(NEXT_BTN_PIN) > 0) {
      buttonPressedCycle = cycles;
      currentScreen += 1;    
      disableAlarm();
    }
    
    if (currentScreen > 4)
      currentScreen = 0;
  }
}

void showAll() {
  display.drawRect(0, 0, 128, 64, 1);
  
  display.setTextSize(1);
  
  drawEighth("CLT", 0, 0, 0, 0);
  display.drawLine(32, 0, 32, 32, WHITE);
  
  drawEighth("IAT", 22, 0, 32, 0);
  display.drawLine(64, 0, 64, 32, WHITE);
  
  drawEighth("EGT", 1700, 0, 64, 0);
  display.drawLine(96, 0, 96, 32, WHITE);
  
  drawEighth("AFR", 12.2, 1, 96, 0);
  display.drawLine(0, 32, 128, 32, WHITE);
     
  drawBooleanEighth("WUE", false, 0, 32);
  drawBooleanEighth("LC", true, 32, 32);
  drawBooleanEighth("A", true, 64, 32);
}

void drawEighth(String label, float value, int decimals, int startX, int startY) {
  
  switch(String(value, decimals).length())
  {
    case 2:
      display.setCursor(startX + 12, startY + 8);
      break;
    case 3:
      display.setCursor(startX + 8, startY + 8);
      break;
    case 4:
      display.setCursor(startX + 5, startY + 8);
      break;
    default:
      display.setCursor(startX + 8, startY + 8);
  }
  display.print(value, decimals);
  display.setCursor(startX + 8, startY + 18);
  display.print(label);
}

void drawBooleanEighth(String label, boolean value, int startX, int startY) {
  int circleX = startX + 16;
  int circleY = startY + 11;
  display.drawCircle(circleX, circleY, 5, WHITE);
  if (value) 
    display.fillCircle(circleX, circleY, 3, WHITE);

  switch(label.length())
  {
    case 1:
      display.setCursor(circleX - 2, circleY + 9);
      break;
    case 2:
      display.setCursor(circleX - 5, circleY + 9);
      break;
    default:
      display.setCursor(circleX - 8, circleY + 9);
  }
  display.print(label);
}

void showBoost() {
  char label[ ] = "BOOST";
  float value = currentValue;
  float upperLimit = 14.7;
  float lowerLimit = -100;
  int rangeHigh = 25;
  int rangeLow = -20;
  int decimals = 1;
  String unit = "PSI";
  
  showFullScreenData(label, value, decimals, unit, upperLimit, lowerLimit, rangeLow, rangeHigh);
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
  
  showFullScreenData(label, value, decimals, unit, upperLimit, lowerLimit, rangeLow, rangeHigh);
  display.display();
  
  if (value >= upperLimit || value <= lowerLimit)
    enableAlarm();
  else
    disableAlarm();
}

void showCoolantTemp() {
  char label[ ] = "COOLANT";
  float value = currentValue;
  float upperLimit = 240;
  float lowerLimit = 10;
  int rangeHigh = 250;
  int rangeLow = 0;
  int decimals = 1;
  String unit = "F";
  
  showFullScreenData(label, value, decimals, unit, upperLimit, lowerLimit, rangeLow, rangeHigh);
  display.display();
  
  if (value >= upperLimit || value <= lowerLimit)
    enableAlarm();
  else
    disableAlarm();
}

void showExhaustTemp() {
  char label[ ] = "EXHAUST";
  float value = currentValue;
  float upperLimit = 1100;
  float lowerLimit = 0;
  int rangeHigh = 1200;
  int rangeLow = 0;
  int decimals = 1;
  String unit = "F";
  
  showFullScreenData(label, value, decimals, unit, upperLimit, lowerLimit, rangeLow, rangeHigh);
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

void showFullScreenData(char label[], float value, int decimals, String unit, float upperLimit, float lowerLimit, int rangeLow, int rangeHigh) {
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
