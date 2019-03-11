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
  Serial.println("1 press : to make a call for complaint registration");
  Serial.println("3 presses : to send acknowledgement message");
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
      digitalWrite(lcdDisplayPin, HIGH);
      lcd.display();
      lcd.clear();
      lcd.print("Sending");
      lcd.setCursor(0, 1);
      lcd.print("complaint...");
      MakeCall();
      delay(25000);
      HangupCall();
      lcd.clear();
      lcd.print("Complaint Sent");
      delay(5000);
      lcd.noDisplay();
      digitalWrite(lcdDisplayPin, LOW);
    }
    delay(50);
  }
  lastButtonState = buttonState;
}


void MakeCall()
{
  mySerial.println("ATD+919536076959;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  Serial.println("Calling  "); // print response over serial port
  delay(5000);
}

void HangupCall()
{
  mySerial.println("ATH");
  Serial.println("Hangup Call");
  delay(1000);
}
