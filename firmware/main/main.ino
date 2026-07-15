#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define PRESS 27  
#define VRX   34  
#define VRY   35 

LiquidCrystal_I2C lcd(0x27, 16, 2);
int row = 0;
int column = 0;
void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("ABCDEFGHIJKLMNOP");
  lcd.setCursor(0, 1);
  lcd.print("QRSTUVWXYZ_>");  

  pinMode(PRESS, INPUT_PULLUP);
  pinMode(VRX , INPUT); 
  pinMode(VRY , INPUT);
}

void loop() {
  lcd.setCursor(column, row);
  lcd.print(" ");
  delay(100);
  lcd.setCursor(column, row);
  if ((row == 1) && (column == 10)){
    lcd.print("_");
  }
  else if ((row == 1) && (column == 11)) {
    lcd.print(">");
  }
  else {
    lcd.print((char) (65 + column + (row * 16)));
  }
  delay(100);

  int vrx = analogRead(VRX);
  int vry = analogRead(VRY);
  if (vrx > 3900) {
    if (row == 0) {
      column = (column+ 1) % 16;
    }
    else {
      column = (column+ 1) % 12;
    }
    
  }
  if (vrx < 100) {
    if (row == 0) {
      column = (column+ 15) % 16;
    }
    else {
      column = (column+ 11) % 12;
    }
  }

  if ((vry < 100) || (vry > 3900)) {
    if (row == 0) {
      row = 1;
      if (column > 11) {
        column = 11;
      }
    }
    else {
      row = 0;
    }
  } 
}