//www.elegoo.com
//2016.12.9

#include <SimpleDHT.h>

int pinDHT11 = 2;
int lightPin = 0;
int latchPin = 11;
int clockPin = 9;
int dataPin = 12;

byte trigger = 0;
int lightLevel = 0;
int lightReading = 0;

SimpleDHT11 dht11;
byte temperature = 0;
byte humidity = 0;
byte data[40] = {0};

void setup()
{
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}
void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, trigger);
  digitalWrite(latchPin, HIGH);
}
void loop()
{
  if ((dht11.read(pinDHT11, &temperature, &humidity, data))) {
    //Serial.print("Read DHT11 failed");
    return;
  }
  else {
    Serial.print("Sample OK: ");
    Serial.print((int)temperature);
    Serial.print(" ");
    Serial.print((int)humidity); 
    Serial.print("   \n");
  }

  lightReading  = analogRead(lightPin); // 1023 < reading < 0
  lightLevel = lightReading / 102;  // ~10 < lightLevel < 0
  if (lightLevel < 3) trigger = 128; // 10000000
  else trigger = 0; // 00000000
  if ((int)temperature > 27) trigger += 64; //01000000
  else trigger += 0; // 00000000

  updateShiftRegister();
  delay(1000);
}


