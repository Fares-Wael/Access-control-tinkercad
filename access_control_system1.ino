#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20, 16, 2);
#include <Keypad.h>
const int rnums = 4;
const int cnums = 4;
char keys[rnums][cnums] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rpins[rnums] = { 2, 3, 4, 5 };
byte cpins[cnums] = { 6, 7, 8, 9 };
const byte tags[4][5] = {
  { 12, 44, 70, 88, 104 },
  { 10, 42, 56, 81, 114 },
  { 15, 94, 75, 22, 215 },
  { 33, 27, 66, 48, 119 }
};
const byte acc_tags[2][5] = {
  { 15, 94, 75, 22, 215 },
  { 33, 27, 66, 48, 119 }
};
byte serNum[5] = { 0 };
Keypad keypad(makeKeymap(keys), rpins, cpins, rnums, cnums);
byte CorrectPass[6] = { '2', '3', '6', '4', '7', '8' };
byte InsertedPass[6] = {};
byte c = 0;
byte c1 = 0;
byte Counter = 0;
byte PassCounter = 0;
byte Colcounter = 0;
byte User_pins[5] = { 10, 11, 12, 13, 14 };
byte sw_pins[4] = { A1, A2, 0, 1 };
bool isCard() {
  for (byte i = 0; i < 4; i++)
    if (digitalRead(sw_pins[i]))
      return true;
  return false;
}
bool readCardSerial() {
  for (byte i = 0; i < 4; i++)
    if (digitalRead(sw_pins[i])) {
      for (byte j = 0; j < 5; j++)
        serNum[j] = tags[i][j];
      return true;
    }
  return false;
}
void homescreen() {
  lcd.clear();
  Counter = 0;
  PassCounter = 0;
  Colcounter = 0;
  lcd.setCursor(0, 0);
  lcd.print("Enter Password :");
}
void fingerprintscreen() {
  lcd.setCursor(1, 0);
  lcd.print("Fingerprint");
  lcd.setCursor(5, 1);
  lcd.print("Required!");
}
void setup() {
  lcd.init();
  lcd.backlight();
  homescreen();
  for (byte i = 0; i <= 4; i++) {
    pinMode(User_pins[i], INPUT);
  }
  for (byte j = 0; j <= 3; j++) {
    pinMode(sw_pins[j], INPUT);
  }
  Serial.begin(9600);
}
void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key != 'D') {
      InsertedPass[Counter] = key;
      lcd.setCursor(Colcounter, 1);
      lcd.print("*");
      Colcounter++;
      if (Colcounter == 6) { Colcounter = 0; }
      Counter++;
      Serial.println(PassCounter);
      if (key == 'C') {
        lcd.clear();
        lcd.print("Reseting System");
        delay(2000);
        homescreen();
      }
    } else {
      for (byte i = 0; i <= 5; i++)
        if (InsertedPass[i] == CorrectPass[i]) PassCounter++;
      if (PassCounter >= 6) {
        lcd.setCursor(0, 1);
        lcd.print("Correct Password");
        delay(2000);
        lcd.clear();
        fingerprintscreen();
      } else {
        lcd.setCursor(0, 1);
        lcd.print("Wrong Password");
        delay(2000);
        lcd.clear();
        fingerprintscreen();
      }
    }
  }
  if (digitalRead(10)) {
    lcd.clear();
    lcd.print("User ID : 1");
    delay(2000);
    homescreen();
  }
  if (digitalRead(11)) {
    lcd.clear();
    lcd.print("User ID : 2");
    delay(2000);
    homescreen();
  }
  if (digitalRead(12)) {
    lcd.clear();
    lcd.print("User ID : 3");
    delay(2000);
    homescreen();
  }
  if (digitalRead(13)) {
    lcd.clear();
    lcd.print("User ID : 4");
    delay(2000);
    homescreen();
  }
  if (digitalRead(14)) {
    lcd.clear();
    lcd.print("User ID : 5");
    delay(2000);
  } else if (digitalRead(A1) || digitalRead(A2)) {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Wrong Card..!");
    delay(2000);
    homescreen();
  } else if (digitalRead(0) || digitalRead(1)) {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Welcome...:)");
    delay(2000);
    homescreen();
  }
}