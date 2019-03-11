#include <SoftwareSerial.h>
SoftwareSerial mySerial(3,4);

const int  buttonPin = 2;

int buttonPushCounter = 0;
int buttonState = 0;     
int lastButtonState = 0;

void setup()
{
  pinMode(buttonPin, INPUT);
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
      MakeCall();
      delay(25000);
      HangupCall();
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
