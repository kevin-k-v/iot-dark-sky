int x = 0;
int y = 0;
int m = 101;      //101 => AUTO MODE by default
#define triacPulse 10
#define ZVC 2

void dimmer()
{
  if((m>20 && m<101) || y<950)
  {
    delayMicroseconds(x);
    digitalWrite(triacPulse, HIGH);
   
    delayMicroseconds(50);
    digitalWrite(triacPulse, LOW);
  }
}

void loop() 
{
    while(Serial.available() > 0)
   {
       m = Serial.read();
   }
   
     if(m==101)   //AUTO
    {
      y = analogRead(A0);
      x = map(y,0,1023, 200, 7200);
    }
    else          //MANUAL
    {
        x = map(m,1,100,7200,200);
    }
   attachInterrupt(digitalPinToInterrupt(ZVC), dimmer, FALLING);
}

void setup() 
{
  Serial.begin(9600);
  pinMode(ZVC, INPUT_PULLUP);
  pinMode(triacPulse, OUTPUT);
}
