#include <Arduino.h>
#define KNOB_PIN 4
#define LED_GAWAN 2
#define LED_ABANG 18
#define LED_KONENG 19
#define LED_IJO 21

int reganeADC = 0;
float voltase = 0;
float derajat = 0;

void LEDwiwitan(int ongkoLed){
  pinMode(ongkoLed, OUTPUT);
}

void ledUrip(int ongkoLed, String JenengeLed){
  digitalWrite(LED_GAWAN, LOW);
  digitalWrite(LED_ABANG, LOW);
  digitalWrite(LED_KONENG, LOW);
  digitalWrite(LED_IJO, LOW);
  digitalWrite(ongkoLed, HIGH);
  Serial.println("LED sing urip " + JenengeLed + "\n");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  LEDwiwitan(LED_GAWAN);
  LEDwiwitan(LED_ABANG);
  LEDwiwitan(LED_KONENG);
  LEDwiwitan(LED_IJO);  
}

void loop() {
  // put your main code here, to run repeatedly:
  reganeADC = analogRead(KNOB_PIN);
  String printData = "Rego ADC: " + String(reganeADC);
  Serial.println(printData);

  voltase = ((float)reganeADC / 4095) * 3.3;
  printData = "Hasil Voltasene: " + String(voltase) + " V";
  Serial.println(printData);

  derajat = ((float)voltase / 3.3) * 100;
  printData = "Hasil Derajate: " + String(derajat) + " C";
  Serial.println(printData);

  if(derajat < 10){
    ledUrip(LED_GAWAN,"BIRU");
  }else if (derajat >= 10 && derajat < 20){
    ledUrip(LED_ABANG,"ABANG");
  }else if (derajat >= 20 && derajat < 30){
    ledUrip(LED_KONENG,"KONENG");
  }else if(derajat >= 30){
    ledUrip(LED_IJO,"IJO");
  }else{
    Serial.println("Salah Kaprah.....");
  }
    delay(2000);
 
}