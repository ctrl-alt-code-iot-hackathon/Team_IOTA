#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
SoftwareSerial mySerial(3,4);
const int rs = 12, en = 11, d4 = 9, d5 = 8, d6 = 7, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int  buttonPin = 2;
const int lcdDisplayPin = A0;
const int lcdContrastPin = 10;

int buttonPushCounter = 0;
int buttonState = 0;     
int lastButtonState = 0;

long millis_held;
long secs_held;
long prev_secs_held;
byte previous = LOW;
unsigned long firstTime;

void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(lcdDisplayPin, OUTPUT);
  pinMode(lcdContrastPin, OUTPUT);
  lcd.begin(16, 2);
  analogWrite(lcdContrastPin, 20);
  mySerial.begin(9600);
  Serial.begin(9600);
  Serial.println("GSM SIM900A BEGIN");
  Serial.println("Enter character for control option:");
  Serial.println("Single Press : to make a call for complaint registration");
  Serial.println("Long Press : to send acknowledgement message");
  Serial.println();
  delay(100);
}



void loop()
{  
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPushCounter++;
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);      
    }
    delay(50);
  }

  if (buttonState == HIGH && lastButtonState == LOW && (millis() - firstTime) > 200) {
    firstTime = millis();
  }

  millis_held = (millis() - firstTime);
  secs_held = millis_held / 1000;
  if (buttonState == LOW && lastButtonState == HIGH) {
    if (secs_held <= 1) {
        digitalWrite(lcdDisplayPin, HIGH);
        lcd.display();
        lcd.clear();
        lcd.print("Sending");
        lcd.setCursor(0, 1);
        lcd.print("complaint...");
        SendComplaint();
        delay(5000);
        Serial.println("Complaint Sent");
        lcd.clear();
        lcd.print("Complaint Sent");
        delay(5000);
        lcd.noDisplay();
        digitalWrite(lcdDisplayPin, LOW);
      }

    if (secs_held >= 3 && buttonPushCounter>1) {
      digitalWrite(lcdDisplayPin, HIGH);
      lcd.display();
      lcd.clear();
      lcd.print("Sending");
      lcd.setCursor(0, 1);
      lcd.print("acknowledgement...");
      SendAck();
      delay(5000);
      //MakeAckCall();
      //delay(25000);
      //HangupCall();
      Serial.println("Acknowledgement Sent");
      lcd.clear();
      lcd.print("Acknowledgement Sent");
      delay(5000);
      lcd.noDisplay();
      digitalWrite(lcdDisplayPin, LOW);
    }
    }
    lastButtonState = buttonState;
    prev_secs_held = secs_held;
}


void MakeCall()
{
  mySerial.println("ATD+918320841726;");
  Serial.println("Calling  ");
  delay(5000);
}

void MakeAckCall()
{
  mySerial.println("ATD+919536076959;");
  Serial.println("Calling  ");
  delay(5000);
}

void HangupCall()
{
  mySerial.println("ATH");
  Serial.println("Hangup Call");
  delay(1000);
}

void SendAck()
{
  Serial.println("Sending acknowledgement\n");
  mySerial.println("AT+CMGF=1");
  delay(2000);
  mySerial.println("AT+CMGS=\"9536076959\"\r");
  delay(2000);
  mySerial.println("AC of SIIC meeting room has been fixed\n");
  delay(2000);
  mySerial.println((char)26);
  delay(2000);
}

void SendComplaint()
{
  Serial.println("Sending message\n");
  mySerial.println("AT+CMGF=1");
  delay(2000);
  mySerial.println("AT+CMGS=\"8320841726\"\r");
  delay(2000);
  mySerial.println("AC of SIIC meeting room is not working properly.\nPlease register the complaint.\nADDRESS:SIIC LABS, 5TH floor, BEL LAB, SRM UNIVERSITY\n");
  delay(2000);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(2000);
}
