
#include <Adafruit_LiquidCrystal.h>

int seconds = 0;

Adafruit_LiquidCrystal lcd(0);

const int tempSensorPin = A0;
const int lightSensorPin = A1;
const int buzzerPin = 8;

// Raja-arvot
const float tempThreshold = 75.0;   // Maksimilämpötila ennen hälytystä (Celsius)
const int lightThreshold = 800;  

void setup()
{
  Serial.begin(9600); 
  lcd.begin(16, 2);  // Aloitetaan LCD-näyttö
  pinMode(buzzerPin, OUTPUT);
  
  lcd.setCursor(0, 0);
  lcd.print("Energia Valvonta");
  delay(2000);
  lcd.clear();
}

void loop()
{
  // Lämpötila-anturin lukema (Celsius)
  int tempValue = analogRead(tempSensorPin);
  float temperature = (tempValue * 167.0) / 1024.0;

  // Valosensorin lukema
  int lightValue = analogRead(lightSensorPin);
  
  // Näytetään tiedot LCD:llä
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);  // Yksi desimaali
  lcd.print(" C  ");
  
  lcd.setCursor(0, 1);
  lcd.print("Light: ");
  lcd.print(lightValue);
  lcd.print("   ");
  
  // Hälytyksen logiikka
  if (temperature > tempThreshold || lightValue > lightThreshold) {
    digitalWrite(buzzerPin, HIGH);  // Summeri päälle
  } else {
    digitalWrite(buzzerPin, LOW);   // Summeri pois päältä
  }

  delay(1000);  // Päivitetään lukemat kerran sekunnissa
}