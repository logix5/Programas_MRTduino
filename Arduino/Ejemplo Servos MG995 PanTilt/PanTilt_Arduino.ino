/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo


int potpin = 19;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int pulsador;
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status


void setup() {
  Serial.begin(9600);
  pinMode(15, INPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(5);  // attaches the servo on pin 9 to the servo object
  pulsador=0;
}

void loop() {

  // read the state of the pushbutton value:
  buttonState = digitalRead(15);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW) {
    if (pulsador==0)
    {
      Serial.println("pulsador entro con cero");
      pulsador=1;
      }
      else {
         Serial.println("pulsador entro con uno");
      pulsador=0;
      }
      delay(300);
  } 
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)

  if (pulsador==0)
  {
     
  myservo2.write(val);                  // sets the servo position according to the scaled value
  delay(15);     // waits for the servo to get there
  }
  else
  {
  myservo.write(val);                  // sets the servo position according to the scaled value
  delay(15);     // waits for the servo to get there

  }
  
}

