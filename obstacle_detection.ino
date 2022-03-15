#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo myservo; 

int pos = 0;
int duration,cm;

const int trigpin = 7;
const int echopin = 4;
const int buzzpin = 11;
const int led_green = 6;
const int led_yellow = 8;
const int led_red = 10;
const int servopin = 9;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
 
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(buzzpin, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_red, OUTPUT);

  //attach pin 9 to the servo motor
  myservo.attach(servopin);
}

void loop()
{ 
  //signal trigger
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  
  //signal echo read
  duration = pulseIn(echopin, HIGH);
  
  //convert micro seconds to centimetre
  cm = microsecondsToCentimeters(duration);

  if(cm>150 && cm<=200)
  {
    digitalWrite(led_green, HIGH);

    myservo.write(90);
    delay(15);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Obstacle");
    
    lcd.setCursor(9,0);
    lcd.print("within:");
    
    lcd.setCursor(0,1);
    
    lcd.print(cm);
    lcd.print("cm");
    
    Serial.print(cm);
    Serial.println();
    
    lcd.setCursor(11,1);
    
    lcd.print(cm*0.01);
    lcd.print("m");
    
    tone(buzzpin, 650);
    delay(300);
    noTone(buzzpin);
    delay(150);
  }
  
  else if(cm>100 && cm<=150)
  {
    digitalWrite(led_yellow, HIGH);

    myservo.write(60);
    delay(15);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Obstacle");
    
    lcd.setCursor(9,0);
    lcd.print("within:");
    
    lcd.setCursor(0,1);
    
    lcd.print(cm);
    lcd.print("cm");
    
    Serial.print(cm);
    Serial.println();
    
    lcd.setCursor(11,1);
  
    lcd.print(cm*0.01);
    lcd.print("m");
    
    tone(buzzpin, 450);
    delay(450);
    noTone(buzzpin);
    delay(150);
  }
  
  else if(cm>0 && cm<=100)
  {
    digitalWrite(led_red, HIGH);
    
    myservo.write(30);

    delay(15);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Obstacle");
    
    lcd.setCursor(9,0);
    lcd.print("within:");
    
    lcd.setCursor(0,1);
    
    lcd.print(cm);
    lcd.print("cm");
    
    Serial.print(cm);
    Serial.println();
    
    lcd.setCursor(11,1);
    
    lcd.print(cm*0.01);
    lcd.print("m");
   
    tone(buzzpin, 250);
    delay(600);
    noTone(buzzpin);
    delay(150);
  } 

  else 
  {
    for (pos = 0; pos <= 180; pos += 1) 
    { 
      myservo.write(pos);
      delay(15);                      
    }

    for (pos = 180; pos >= 0; pos -= 1) 
    { 
      myservo.write(pos);
      delay(15);                    
    }
  }
  
  digitalWrite(led_green, LOW);
  digitalWrite(led_yellow, LOW);
  digitalWrite(led_red, LOW);
}

long microsecondsToCentimeters(long microseconds) 
{
  return microseconds/29/2;
}
