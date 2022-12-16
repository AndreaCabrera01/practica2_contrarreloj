#include <Arduino.h>
#include "HX711.h"
#include <LiquidCrystal_I2C.h>
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

#define BIT1 22
#define BIT2 23
#define BIT3 24

#define camion1Led 31
#define camion2Led 32
#define camion3Led 33
#define camion4Led 34
#define camion5Led 35

#define caja1 "2101"
#define caja2 "10102"
#define caja3 "50103"
#define caja4 "100104"
#define caja5 "300105"

String caja = "";

#define LCD_RS 2
#define LCD_RW 1
#define LCD_E  0
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_BACKLIGHT 3
#define LCD_COLS 16
#define LCD_ROWS 4
#define LCD_I2C_ADDRESS 0x20

LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS , LCD_RS, LCD_RW, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, LCD_BACKLIGHT, POSITIVE);
int peso = 0;
int camion = 0;

int camion1Paquetes = 0;
int camion2Paquetes = 0;
int camion3Paquetes = 0;
int camion4Paquetes = 0;
int camion5Paquetes = 0;

HX711 scale;

void setup() {
  lcd.begin(16, 4);                      
  lcd.backlight();
  pinMode(BIT1, OUTPUT);
  pinMode(BIT2, OUTPUT);
  pinMode(BIT3, OUTPUT);
  for (int i = 25; i <= 30; i++) {
    pinMode(i, INPUT);
  }

  for (int i = 31; i <= 35; i++) {
    pinMode(i, OUTPUT);
  }

  for (int i = 31; i <= 35; i++) {
    digitalWrite(i, HIGH);
  }

}

void loop() {
  //LCD:
  lcd.clear();

  //DEMUX:
  if (digitalRead(25) == HIGH) {
    caja = "2101";
    camion1Paquetes = camion1Paquetes + 10;
  }
  else if (digitalRead(26) == HIGH) {
    caja = "10102";
    camion2Paquetes = camion2Paquetes + 10;
  }
  else if (digitalRead(27) == HIGH) {
    caja = "50103";
    camion3Paquetes = camion3Paquetes + 10;
  }
  else if (digitalRead(29) == HIGH) {
    caja = "100104";
    camion4Paquetes = camion4Paquetes + 10;
  }
  else if (digitalRead(30) == HIGH) {
    caja = "300105";
    camion5Paquetes = camion5Paquetes + 10;
  } else {
    caja = "";
  }

  if (caja == caja1) {
    lcd.clear();
    digitalWrite(BIT1, HIGH);
    digitalWrite(BIT2, LOW);
    digitalWrite(BIT3, LOW);
    delay(1000);
    digitalWrite(BIT1, LOW);
    digitalWrite(BIT2, LOW);
    digitalWrite(BIT3, LOW);
    caja = "";
    lcd.setCursor(0, 0);
    lcd.print("Paquetes: ");
    lcd.setCursor(9, 0);
    lcd.print(camion1Paquetes);
    lcd.setCursor(0, 1);
    lcd.print("Camion");
    lcd.setCursor(9, 1);
    lcd.print(1);
    delay(1000);
    lcd.clear();

  } else if (caja == caja2) {
    lcd.clear();
    digitalWrite(BIT1, LOW);
    digitalWrite(BIT2, HIGH);
    digitalWrite(BIT3, LOW);
    delay(1000);
    digitalWrite(BIT1, LOW);
    digitalWrite(BIT2, LOW);
    digitalWrite(BIT3, LOW);
    caja = "";
    lcd.setCursor(0, 0);
    lcd.print("Paquetes: ");
    lcd.setCursor(9, 0);
    lcd.print(camion2Paquetes);
    lcd.setCursor(0, 1);
    lcd.print("Camion");
    lcd.setCursor(9, 1);
    lcd.print(2);
    delay(1000);
    lcd.clear();
    
  } else if (caja == caja3) {
    lcd.clear();
    digitalWrite(BIT1, HIGH);
    digitalWrite(BIT2, HIGH);
    digitalWrite(BIT3, LOW);
    delay(1000);
    digitalWrite(BIT1, LOW);
    digitalWrite(BIT2, LOW);
    digitalWrite(BIT3, LOW);
    caja = "";
    lcd.setCursor(0, 0);
    lcd.print("Paquetes: ");
    lcd.setCursor(9, 0);
    lcd.print(camion3Paquetes);
    lcd.setCursor(0, 1);
    lcd.print("Camion");
    lcd.setCursor(9, 1);
    lcd.print(3);
    delay(1000);
    lcd.clear();
    
  } else if (caja == caja4) {
    lcd.clear();
    digitalWrite(BIT1, LOW);
    digitalWrite(BIT2, LOW);
    digitalWrite(BIT3, HIGH);
    delay(1000);
    digitalWrite(BIT1, LOW);
    digitalWrite(BIT2, LOW);
    digitalWrite(BIT3, LOW);
    caja = "";
    lcd.setCursor(0, 0);
    lcd.print("Paquetes: ");
    lcd.setCursor(9, 0);
    lcd.print(camion4Paquetes);
    lcd.setCursor(0, 1);
    lcd.print("Camion");
    lcd.setCursor(9, 1);
    lcd.print(4);
    delay(1000);
    lcd.clear();
  } else if (caja == caja5) {
    lcd.clear();
    digitalWrite(BIT1, HIGH);
    digitalWrite(BIT2, LOW);
    digitalWrite(BIT3, HIGH);
    delay(1000);
    digitalWrite(BIT1, LOW);
    digitalWrite(BIT2, LOW);
    digitalWrite(BIT3, LOW);
    caja = "";
    lcd.setCursor(0, 0);
    lcd.print("Paquetes: ");
    lcd.setCursor(9, 0);
    lcd.print(camion5Paquetes);
    lcd.setCursor(0, 1);
    lcd.print("Camion");
    lcd.setCursor(9, 1);
    lcd.print(5);
    delay(1000);
    lcd.clear();
  }
  else {
    delay(100);
    digitalWrite(BIT1, LOW);
    digitalWrite(BIT2, LOW);
    digitalWrite(BIT3, LOW);
  }
  
  lcd.clear();
  validarCamion();
}
void validarCamion() {

  if (camion1Paquetes == 500) {
    camion1Paquetes = 0;
    digitalWrite(camion1Led, LOW);
    delay(10000);
    digitalWrite(camion1Led, HIGH);
  }
  if (camion2Paquetes == 500) {
    camion2Paquetes = 0;
    digitalWrite(camion2Led, LOW);
    delay(10000);
    digitalWrite(camion2Led, HIGH);
  }
  if (camion3Paquetes == 150) {
    camion3Paquetes = 0;
    digitalWrite(camion3Led, LOW);
    delay(10000);
    digitalWrite(camion3Led, HIGH);
  }
  if (camion4Paquetes == 150) {
    camion4Paquetes = 0;
    digitalWrite(camion4Led, LOW);
    delay(10000);
    digitalWrite(camion4Led, HIGH);
  }
  if (camion5Paquetes == 100) {
    camion5Paquetes = 0;
    digitalWrite(camion5Led, LOW);
    delay(10000);
    digitalWrite(camion5Led, HIGH);
  }
}
