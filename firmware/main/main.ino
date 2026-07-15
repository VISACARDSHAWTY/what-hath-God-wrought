#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define PRESS 27  
#define VRX   34  
#define VRY   35 
#define BUZZER 25

LiquidCrystal_I2C lcd(0x27, 16, 2);
int row = 0;
int column = 0;

int message[48];
int length = 0;
int morse[26] = {12 , 2111 , 2121 ,211 , 1 , 1121 , 221 , 1111 , 11 , 1222 , 212 , 1211 , 22 , 21 ,222 , 1221 ,2212 , 121 , 111 , 2 , 112 , 1112 , 122 , 2112 , 2122 , 2211};
void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("ABCDEFGHIJKLMNOP");
  lcd.setCursor(0, 1);
  lcd.print("QRSTUVWXYZ_>");  
  pinMode(BUZZER, OUTPUT);
  pinMode(PRESS, INPUT_PULLUP);
  pinMode(VRX , INPUT); 
  pinMode(VRY , INPUT);
  memset(message, 0, sizeof(message));
}
void send_message() {
  
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

  if (digitalRead(PRESS) == 0) {
    if (column == 10 && row == 1) {
      if(length > 47) {
        for (int i=0 ; i<3 ; i++) {
          digitalWrite(BUZZER, HIGH);
          delay(200);
          digitalWrite(BUZZER, LOW);
          delay(20);
        }
      }
      else { 
        message[length] = -1;
        length++;
      }
    }
    else if (column == 11 && row == 1){
      send_message();
      memset(message, 0, sizeof(message));
      length = 0;
    }
    else {
      if(length > 47) {
        for (int i=0 ; i<3 ; i++) {
          digitalWrite(BUZZER, HIGH);
          delay(200);
          digitalWrite(BUZZER, LOW);
          delay(20);
        }
      }
      else { 
        message[length] = column + (row * 16);
        length++;
      }
    }
  }
}

