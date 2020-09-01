#include <Arduino.h>
#define LED_PIN_RED 4
#define LED_PIN_GREEN 19
#define LED_PIN_YELLOW 21

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_YELLOW, OUTPUT);
  pinMode(LED_PIN_GREEN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    char data = Serial.read();
    Serial.println();
    if(data == '1'){
      digitalWrite(LED_PIN_GREEN, HIGH);
      Serial.print("Hijau Nyala");
      delay(2000);
      digitalWrite(LED_PIN_GREEN, LOW);
      Serial.print("Hijau Mati");
      delay(2000);
    }
    else if(data == '2'){
      digitalWrite(LED_PIN_RED, HIGH);
      Serial.print("MERAH Nyala");
      delay(2000);
      digitalWrite(LED_PIN_RED, LOW);
      Serial.print("MERAH Mati");
      delay(2000);
    }
    else if(data == '3'){
      digitalWrite(LED_PIN_YELLOW, HIGH);
      Serial.print("Kuning Nyala");
      delay(2000);
      digitalWrite(LED_PIN_YELLOW, LOW);
      Serial.print("Kuning Mati");
      delay(2000);
    }
    else if(data == '4'){
      digitalWrite(2, HIGH);
      Serial.print("BIRU Nyala");
      delay(2000);
      digitalWrite(2, LOW);
      Serial.print("BIRU Mati");
      delay(2000);
    }


}

}

