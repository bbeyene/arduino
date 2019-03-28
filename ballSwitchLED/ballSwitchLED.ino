//www.elegoo.com
//2016.12.08
/*****************************************/
const int ledPin = 13;//the led attach to
const int ballSwitch = 2;

void setup()
{ 
  pinMode(ledPin,OUTPUT);//initialize the ledPin as an output
  pinMode(ballSwitch,INPUT);
  digitalWrite(ballSwitch, HIGH);
} 
/******************************************/
void loop() 
{  
  int digitalVal = digitalRead(ballSwitch);
  
  if(digitalVal == LOW)
  {
    digitalWrite(ledPin,HIGH);
  }
  else
  {
    digitalWrite(ledPin,LOW);
  }
}
/**********************************************/

