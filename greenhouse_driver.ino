#include <EEPROM.h>
#include <SimpleDHT.h>

int lightPin1 = 0;
int lightPin2 = 1;
int tempPin = 2;
int pinDHT11 = 2;
int clockPin = 9;
int latchPin = 11;
int dataPin = 12;

int lightReading1 = 0;
int lightLevel1 = 0;
int lightReading2 = 0;
int lightLevel2 = 0;

SimpleDHT11 dht11;
byte temperature = 0;
byte humidity = 0;
byte data[40] = {0};

int tempReading = 0;
double tempK = 0;
float tempC = 0;
float tempF = 0;
float temperatureF = 0;

int humid = 0;
int door1 = 0;
int door2 = 0;
int water1 = 0;
int water2 = 0;

byte settings = EEPROM.read(0);

void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, settings);
  digitalWrite(latchPin, HIGH);
}

void setup()
{
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  updateShiftRegister();
  Serial.begin(9600);
}

void loop()
{
  char incomingChar;
  
  if (Serial.available())
  {    
    incomingChar = Serial.read();
    delay(10);
    if (incomingChar == 'w')
    {
      incomingChar = Serial.read();
      delay(10);
      if (incomingChar == '1')
      {
        incomingChar = Serial.read();
        delay(10);
        switch (incomingChar)
        {
          case 'a': bitSet(settings, 0);
            break;
          case 'b': bitSet(settings, 1);
            break;
          case 'c': bitSet(settings, 2);
            break;
          case 'd': bitSet(settings, 3);
            break;
          case 'e': bitSet(settings, 4);
            break;
          case 'f': bitSet(settings, 5);
            break;
          case 'g': bitSet(settings, 6);
            break;
          case 'h': bitSet(settings, 7);
            break;
        }
        updateShiftRegister();
        delay(100);
      }
      else if (incomingChar == '0')
      {
        incomingChar = Serial.read();
        delay(10);
        switch (incomingChar)
        {
          case 'a': bitClear(settings, 0);
            break;
          case 'b': bitClear(settings, 1);
            break;
          case 'c': bitClear(settings, 2);
            break;
          case 'd': bitClear(settings, 3);
            break;
          case 'e': bitClear(settings, 4);
            break;
          case 'f': bitClear(settings, 5);
            break;
          case 'g': bitClear(settings, 6);
            break;
          case 'h': bitClear(settings, 7);
            break;
        }
        updateShiftRegister();
        delay(100);
      }
    }
    else if(incomingChar == 'r')
    {
      delay(10);
      int bit[8];
      for(int i = 0; i < 8; i++)
      {
        bit[i] = bitRead(settings, i);
      }
      lightReading1 = analogRead(lightPin1); // 1023 < reading < 0
      lightLevel1 = lightReading1 / 102; // ~10 < lightLevel < 0
      lightReading2 = analogRead(lightPin2); // 1023 < reading < 0
      lightLevel2 = lightReading2 / 102; // ~10 < lightLevel < 0
      tempReading = analogRead(tempPin);
      tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
      tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK ); //  Temp Kelvin
      tempC = tempK - 273.15;            // Convert Kelvin to Celcius
      tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
      temperatureF = (temperature *9.0) / 5.0 + 32.0; 
      humid = 0;
      
      Serial.println((int)temperatureF);
      Serial.println((int)tempF);
      Serial.println((int)humidity);
      Serial.println((int)humid);
      Serial.println((int)lightLevel1);
      Serial.println((int)lightLevel2);
      Serial.println((int)door1);
      Serial.println((int)door2);
      for(int i = 0; i < 8; i++)
      {
	Serial.println((int)bit[i]);
      }
      Serial.println((int)water1);
      Serial.println((int)water2);
      delay(100);
    }
  }
  else
  {
    delay(1000);
    if(dht11.read(pinDHT11, &temperature, &humidity, data))
      return;
    
  }
  updateShiftRegister();
  delay(100);
  EEPROM.update(0, settings);    
}
