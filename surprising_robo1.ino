#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
int backLight = 13;
int tempSensor = A0;
int sensorInput;
double temp;
float temperatura = 0;
int RawValue = 0;
double Voltage = 0;
double tempC = 0;
int humiditySensorOutput = 0;
int luminosidade = 0;
int umidade = 0;

const int ldrPin = 7;
const int buzzerPin = A2;
const int ledVerde = A5;
const int ledAmarelo = A4;
const int ledVermelho = A3;
int ldrValue = 0; 
const int freq = 10; 
const int duracao = 300;
const int altoFalante = 9;
int HumiPin = A1;
int Humi = 0;

void setup() {
  pinMode(tempSensor, INPUT);
  pinMode(backLight, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  ldrValue = analogRead(ldrPin); 

  // Luminosidade alta e irregular.
  if (ldrValue > 500) {
    lcd.clear();
    lcd.print("Ambiente muito claro");
    lcd.setCursor(0, 1);
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVerde, LOW); 
   for (int i = 0; i < 30; i++) { // toca por 3 segundos
    tone(buzzerPin, 1000); 
    delay(100);
  }
    noTone(buzzerPin); // interrompe do buzzer
    delay(100); 
  }
  
  // Luminosidade média.
  else if (ldrValue >= 401 && ldrValue <= 499) {
    lcd.clear();
    lcd.print("Ambiente meia luz");
    lcd.setCursor(0, 1);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW); 
    digitalWrite(ledVerde, LOW); 
    noTone(buzzerPin); 
  }
  
  // Luminosidade baixa.
  else if(ldrValue < 70) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW); 
    digitalWrite(ledVermelho, LOW); 
    noTone(buzzerPin); 
  }

  RawValue = analogRead(tempSensor);
  Voltage = (RawValue / 1023.0) * 5000;
  tempC = (Voltage - 500) * 0.1;
  Serial.print("Temperature in C = ");
  Serial.print(tempC, 1);

  humiditySensorOutput = analogRead(HumiPin);
  umidade = map(humiditySensorOutput, 0, 1023, 10, 70);
  Serial.print(" Humidity: ");
  Serial.print(umidade);
  Serial.println("%");

  if (tempC <=10) {
    lcd.clear();
    lcd.print("Temperatura BAIXA");
    lcd.setCursor(0, 1);
    lcd.print(tempC);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledAmarelo, HIGH);

  if ((tempC >= 11) && (tempC <= 14)) {
    lcd.clear();
    lcd.print("Temperatura OK");
    lcd.setCursor(0, 1);
    lcd.print(tempC);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledAmarelo, LOW);

  }

  while (tempC > 15) {
    lcd.clear();
    lcd.print("Temperatura ALTA");
    lcd.setCursor(0, 1);
    lcd.print(tempC);
    tone(altoFalante, freq, duracao);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledVerde, LOW);
    delay(1000);
    RawValue = analogRead(tempSensor);
    Voltage = (RawValue / 1023.0) * 5000;
    tempC = (Voltage - 500) * 0.1;
  }

  if (umidade < 50) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Umidade BAIXA");
    lcd.setCursor(0, 1);
    lcd.print(umidade);
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVerde, LOW);
    noTone(altoFalante);
  }

  if ((umidade >= 50) && (umidade <= 70)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Umidade OK");
    lcd.setCursor(0, 1);
    lcd.print(umidade);
  	 }
	}
}
  

