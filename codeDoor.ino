#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>

// LCD-näyttö
Adafruit_LiquidCrystal lcd(0);

// Servo
Servo myservo;  // Servo-objekti oven avaamiseksi
const int servoPin = 10;  // Servo on liitetty pinniin 10

// PIN-koodi tarkistus
const String correctPin = "1234";  // Oikea PIN-koodi
String enteredPin = "";  // Syötetty PIN-koodi

// Keypad-määrittely
const byte ROW_NUM    = 4;  // 4 riviä
const byte COLUMN_NUM = 4;  // 4 saraketta
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte pin_rows[ROW_NUM] = {9, 8, 7, 6};  // Rivi pinnit
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2};  // Sarake pinnit

// Näppäimistön lukeminen
char getKey() {
  for (byte row = 0; row < ROW_NUM; row++) {
    pinMode(pin_rows[row], OUTPUT);
    digitalWrite(pin_rows[row], LOW);
    
    for (byte col = 0; col < COLUMN_NUM; col++) {
      pinMode(pin_column[col], INPUT_PULLUP);
      if (digitalRead(pin_column[col]) == LOW) {
        while (digitalRead(pin_column[col]) == LOW);  // Odota, että näppäin vapautetaan
        return keys[row][col];
      }
    }
    digitalWrite(pin_rows[row], HIGH);
  }
  return '\0';
}

void setup() {
  // Alustetaan seriaalimonitori
  Serial.begin(9600);

  // Alustetaan LCD-näyttö
  lcd.begin(16, 2);  // LCD
  //lcd.backlight();   // Taustavalo päälle
  lcd.setCursor(0, 0);
  lcd.print("Oven avaus");

  // Alustetaan servo
  myservo.attach(servoPin);  // Liitä servomoottori

  delay(2000);  // Odotetaan, että näyttö tulee näkyviin
  lcd.clear();
}

void loop() {
  // Lukee käyttäjän syöttämän PIN-koodin
  char key = getKey();
  
  if (key) {
    Serial.println(key);  // Tulostetaan painettu näppäin
    if (key == '#') {
      Serial.println("Syötetyt numerot: " + enteredPin);
      if (enteredPin == correctPin) {
        openDoor();
      } else {
        lcd.clear();
        lcd.print("Virheellinen PIN");
        delay(2000);
        enteredPin = "";
        lcd.clear();
        lcd.print("Oven avaus");
      }
    } else if (key == '*') {
      enteredPin = "";
      lcd.clear();
      lcd.print("PIN tyhjennetty");
      delay(2000);
      lcd.clear();
      lcd.print("Oven avaus");
    } else {
      enteredPin += key;
    }
  }
  
}

// Funktio oven avaamiseksi
void openDoor() {
  lcd.clear();
  lcd.print("Ovi avattu!");
  myservo.write(90);  // Avaa ovi 90 astetta
  delay(5000);  // Pidä ovi auki 5 sekuntia
  myservo.write(0);  // Sulje ovi
  lcd.clear();
  lcd.print("Ovi suljettu");
  delay(2000);
  lcd.clear();
  lcd.print("Oven avaus");
}
