/*Lab 3 Fan and LCD Screen
 * 
 */
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
volatile int state = 0;

void setup()
{
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Set up the direction and speed pins for fan
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
    
  
  
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), button, FALLING );
 cli();//stop interrupts    
//set timer4 interrupt at 1Hz
 TCCR5A = 0;// set entire TCCR1A register to 0
 TCCR5B = 0;// same for TCCR1B
 TCNT5  = 0;//initialize counter value to 0
 // set compare match register for 1hz increments
 OCR5A = 15624/1;// = (16*10^6) / (1*1024) - 1 (must be <65536)
 // turn on CTC mode
 TCCR5B |= (1 << WGM12);
 // Set CS12 and CS10 bits for 1024 prescaler
 TCCR5B |= (1 << CS12) | (1 << CS10);  
 // enable timer compare interrupt
 TIMSK5 |= (1 << OCIE4A);

sei();//allow interrupts

  clock.begin(); //Begins the Clock
  clock.setDateTime(__DATE__, __TIME__);
}



void button(){
{
 static unsigned long lastInterrupt = 0;
 unsigned long interruptTime = millis();
 if (interruptTime - lastInterrupt > 200)
 {
   Serial.write("Pressed ");
   state++;
   if (state >=7) {
    state = 0;
   }
   }
   
 
 lastInterrupt = interruptTime;
}
}


ISR(TIMER5_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
 
 Serial.write("1");
 lcd.setCursor(0,1);
 lcd.print(dt.hour);
 lcd.print(":");
 lcd.print(dt.minute);
 lcd.print(":");
 lcd.print(dt.second);
 lcd.print(" ");
 lcd.setCursor(0,0);

 
}

void loop()
{
  dt = clock.getDateTime(); // Get the time
  delay(500);

  switch (state) {
    case 0:
      digitalWrite(ENABLE,HIGH); // enable on
      digitalWrite(DIRA,HIGH); //one way
      digitalWrite(DIRB,LOW);
      lcd.setCursor(0,0);
      lcd.print("Full C  ");
      break;
     case 1:
      analogWrite(ENABLE,180); // enable on
      digitalWrite(DIRA,HIGH); //one way
      digitalWrite(DIRB,LOW);
      lcd.setCursor(0,0);
      lcd.print("3/4 C  ");
      break;
     case 2:
      analogWrite(ENABLE,100); // enable on
      digitalWrite(DIRA,HIGH); //one way
      digitalWrite(DIRB,LOW);
      lcd.setCursor(0,0);
      lcd.print("1/2 C  ");
      break;
     case 3:
      digitalWrite(ENABLE,LOW); // enable on
      digitalWrite(DIRA,HIGH); //one way
      digitalWrite(DIRB,LOW);
      lcd.setCursor(0,0);
      lcd.print("OFF     ");
      break;
     case 4:
      digitalWrite(ENABLE,HIGH); // enable on
      digitalWrite(DIRA,LOW); //one way
      digitalWrite(DIRB,HIGH);
      lcd.setCursor(0,0);
      lcd.print("Full CC ");
      break;
     case 5:
      analogWrite(ENABLE,180); // enable on
      digitalWrite(DIRA,LOW); //one way
      digitalWrite(DIRB,HIGH);
      lcd.setCursor(0,0);
      lcd.print("3/4 CC  ");
      break;
     case 6:
      analogWrite(ENABLE,100); // enable on
      digitalWrite(DIRA,LOW); //one way
      digitalWrite(DIRB,HIGH);
      lcd.setCursor(0,0);
      lcd.print("1/2 CC  ");
      break;
  }

}
