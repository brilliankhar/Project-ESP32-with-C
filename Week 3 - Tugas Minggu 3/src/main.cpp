#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <w25q64.hpp>

#define CS_PIN 5
#define SCK_PIN 18
#define MISO_PIN 19
#define MOSI_PIN 23

#define CHIP_ID 0x9F
#define LEN_ID 4

#define BH1750_ADDRESS 0x23
#define BH1750_DATALEN 2 

#define LED_MERAH1 15
#define LED_KUNING 3
#define LED_HIJAU 4
#define LED_MERAH4 16
#define BUTTON_SW 17

#define BOOL_STR(vot) (vot ? "1" : "0")
#define STR_BOOL(val) (val == "1" ? 1 : 0)

unsigned char writePage[256] = "";
unsigned char readPage[256] = "";

byte chipId[4] = "";

w25q64 spiChip;

void bh1750Request(int address);
int bh1750Read(int address);

void readMemory();
bool automatic;
String memory_data;

byte buff[2];
unsigned short lux = 0;

void initLed(int ledNumber){
  pinMode(ledNumber, OUTPUT);
}

//fungsi LedOn 1-4
void ledOn(bool led_merah1, bool led_kuning, bool led_hijau, bool led_merah4){
  if(led_merah1 == 1){
    digitalWrite(LED_MERAH1, HIGH);
  }else{
    digitalWrite(LED_MERAH1, LOW);
  }
  if(led_kuning == 1){
    digitalWrite(LED_KUNING, HIGH);
  }else{
    digitalWrite(LED_KUNING, LOW);
  }
  if(led_hijau == 1){
    digitalWrite(LED_HIJAU, HIGH);
  }else{
    digitalWrite(LED_HIJAU, LOW);
  }
  if(led_merah4 == 1){
     digitalWrite(LED_MERAH4, HIGH);
  }else{
     digitalWrite(LED_MERAH4, LOW);
  }
  
}

void bh1750Request(int address){
  Wire.beginTransmission(address);
  Wire.write(0x10);
  Wire.endTransmission();
}

int bh1750Read(int address)
{
  int i = 0;

  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while (Wire.available())
  {
    buff[i] = Wire.read();
    i++;
  }
  Wire.endTransmission();

  return i;
}

void readMemory(){
  memory_data = "";
  spiChip.readPages(readPage, 0xFFFF, 1);
  for (int i = 0; i < 256; i++){
    if (readPage[i] > 8 && readPage[i] < 127)
      memory_data += (char)readPage[i];
  }
}
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  initLed(LED_MERAH1);
  initLed(LED_MERAH4);
  initLed(LED_KUNING);
  initLed(LED_HIJAU);
  pinMode(BUTTON_SW, INPUT_PULLUP);
  spiChip.begin();

  readMemory();
  automatic = STR_BOOL(memory_data);
  Serial.println("Sedang baca memory: " + String(automatic));
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(BUTTON_SW) == LOW){
    automatic = !automatic;
    Serial.println("Automatic State: " + String(automatic));
    ledOn(1,1,1,1);

    //Write Memory
    memcpy(writePage, BOOL_STR(automatic), 1);
    spiChip.erasePageSector(0xFFFF);
    spiChip.pageWrite(writePage, 0xFFFF);
    Serial.println("Done writing");

    readMemory();

    Serial.println("Sedang baca memory: " + memory_data);
    automatic = STR_BOOL(memory_data);
    Serial.println("Kondisi Otomatis baru: " + String(automatic));
    delay(1000);
  }

  if(automatic == 1){
    bh1750Request(BH1750_ADDRESS);
    delay(200);

    if(bh1750Read(BH1750_ADDRESS) == BH1750_DATALEN) {
      lux = (((unsigned short)buff[0] << 8)|(unsigned short)buff[1]) / 1.2;
      Serial.println("Nilai Intensitas Cahayanya:");
      Serial.print(lux);
      Serial.println("lux");
      if(lux >= 0 && lux <= 250){
        ledOn(1,1,1,1);
      }else if(lux > 250 && lux <= 500){
        ledOn(1,1,1,0);
      }else if(lux > 500 && lux <= 750){
        ledOn(1,1,0,0);
      }else if(lux > 750 && lux <= 1000){
        ledOn(1,0,0,0);
      }else{
        ledOn(0,0,0,0);
      }
    }
  }
  delay(1000);
}
  

