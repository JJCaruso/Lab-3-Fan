//www.elegoo.com
//2018.10.24
#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>

DS3231 clock;
RTCDateTime dt;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#define ENABLE 5
#define DIRA 3
#define DIRB 4

const byte interruptPin = 2;
volatile int state = 2;

void setup()
{
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Set up the direction and speed pins for fan
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
    
  
  
  pinMode(interruptPin, INPUT);
  //attachInterrupt(digitalPinToInterrupt(interruptPin), button, CHANGE );
      
  /*noInterrupts();//stop interrupts

  //set timer4 interrupt at 1Hz
  TCCR3A = 0;// set entire TCCR1A register to 0
  //TCCR3B = 0;// same for TCCR1B
  TCNT3  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR3A = 10000;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR3B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR3B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK3 |= (1 << OCIE1A);
  interrupts();//allow interrupts
  */

  clock.begin(); //Begins the Clock
  clock.setDateTime(__DATE__, __TIME__);
}



/*void button()
{
  state++;
  if (state >= 7){
    state = 0;
  }
  delay(100);
}
*/

/*  ISR(TIMER4_COMPA_vect){  //timer4 interrupt 1Hz

  state++;
  
}*/


void loop()
{
  dt = clock.getDateTime(); // Get the time
  lcd.setCursor(0,1);
  lcd.print(dt.hour);
  lcd.print(":");
  lcd.print(dt.minute);
  lcd.print(":");
  lcd.print(dt.second);
  lcd.print(" ");
 
  switch (state)
  {
    case 0: //Full speed clockwise
     lcd.setCursor(0,0);
     digitalWrite(ENABLE,HIGH);
     digitalWrite(DIRA,HIGH);
     digitalWrite(DIRB,LOW);
     lcd.print("Full C");
     lcd.setCursor(0,1);
     lcd.print(dt.hour);
     lcd.print(":");
     lcd.print(dt.minute);
     lcd.print(":");
     lcd.print(dt.second);
     break;
     
     case 1: //3/4 speed clockwise
     analogWrite(ENABLE,170);
     digitalWrite(DIRA,HIGH);
     digitalWrite(DIRB,LOW);
     lcd.setCursor(0,0);
     lcd.print("3/4 C");
     lcd.setCursor(0,1);
     lcd.setCursor(0,1);
     lcd.print(dt.hour);
     lcd.print(":");
     lcd.print(dt.minute);
     lcd.print(":");
     lcd.print(dt.second);
     break;
     
     case 2: //1/2 speed clockwise
     analogWrite(ENABLE,128);
     digitalWrite(DIRA,HIGH);
     digitalWrite(DIRB,LOW);
     lcd.setCursor(0,0);
     lcd.print("1/2 C");
     lcd.setCursor(0,1);
     lcd.print(dt.hour);
     lcd.print(":");
     lcd.print(dt.minute);
     lcd.print(":");
     lcd.print(dt.second);
     break;
     
     case 3: //stopp
     analogWrite(ENABLE,LOW);
     digitalWrite(DIRA,HIGH);
     digitalWrite(DIRB,LOW);
     lcd.setCursor(0,0);
     lcd.print("Off    ");
     lcd.setCursor(0,1);
     lcd.setCursor(0,1);
     lcd.print(dt.hour);
     lcd.print(":");
     lcd.print(dt.minute);
     lcd.print(":");
     lcd.print(dt.second);
     break; 
     
     case 4: //Full CC
     digitalWrite(ENABLE,HIGH);
     digitalWrite(DIRA,LOW);
     digitalWrite(DIRB,HIGH);
     lcd.setCursor(0,0);
     lcd.print("Full CC");
     lcd.setCursor(0,1);
     lcd.setCursor(0,1);
     lcd.print(dt.hour);
     lcd.print(":");
     lcd.print(dt.minute);
     lcd.print(":");
     lcd.print(dt.second);
     break; 
     
     case 5: //3/4 CC
     analogWrite(ENABLE,170);
     digitalWrite(DIRA,LOW);
     digitalWrite(DIRB,HIGH);
     lcd.setCursor(0,0);
     lcd.print("3/4 CC");
     lcd.setCursor(0,1);
     lcd.setCursor(0,1);
     lcd.print(dt.hour);
     lcd.print(":");
     lcd.print(dt.minute);
     lcd.print(":");
     lcd.print(dt.second);
     break; 
     
     case 6: //1/2 CC
     analogWrite(ENABLE,128);
     digitalWrite(DIRA,LOW);
     digitalWrite(DIRB,HIGH);
     lcd.setCursor(0,0);
     lcd.print("1/2 CC");
     lcd.setCursor(0,1);
     lcd.setCursor(0,1);
     lcd.print(dt.hour);
     lcd.print(":");
     lcd.print(dt.minute);
     lcd.print(":");
     lcd.print(dt.second);
     break; 
  }
}
