
// Pin määrittelyt
const int pirPin = 2;          // PIR-liikeilmaisin
const int ldrPin = A0;         // LDR-valosensori
const int tempSensorPin = A1;  // LM35 lämpötila-anturi
const int ledPin = 3;         // LED
const int ledPin2 = 4;

// Raja-arvot
const int lightThreshold = 1; // Kirkkaus, joka raja-arvo valojen sammutukselle (LDR)
const float tempThreshold = 25.0;  // Lämpötila raja-arvo valojen sammumiselle

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Lämpötila-anturin lukeminen
  int tempValue = analogRead(tempSensorPin);
  float temperature = (tempValue * 167.0) / 1024.0;

  // Valosensorin lukeminen
  int lightValue = analogRead(ldrPin);

  // Liiketunnistin (PIR)
  int motionDetected = digitalRead(pirPin);

  // Tulostetaan Serial Monitoriin tiedot
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C\t");
  Serial.print("Light Value: ");
  Serial.print(lightValue);
  Serial.print("\tMotion: ");
  Serial.println(motionDetected);

  // Valojen ohjauslogiikka
  if (motionDetected == HIGH && lightValue < lightThreshold) {
    // Jos liikettä on, valoa ei ole tarpeeksi ja, sytytä valo
    digitalWrite(ledPin, HIGH);  // Sytytetään LED
  } else {
    // Jos ei ole liikettä tai valo on riittävä, sammutetaan valo
    digitalWrite(ledPin, LOW);   // Sammutetaan LED
  }

  // Lämpötilan sääntö: Jos lämpötila on liian korkea, sammutetaan valot
  if (temperature >= tempThreshold) {
    digitalWrite(ledPin2, LOW);   // Sammutetaan LED, jos lämpötila on yli raja-arvon
  }else{
   digitalWrite(ledPin2, HIGH); 
  }

  delay(1000); // Päivitä tiedot kerran sekunnissa
}
