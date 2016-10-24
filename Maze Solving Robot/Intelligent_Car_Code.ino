/* Salar Hosseini, Sejin Kim, Jerry Liu
Mr. Wong
June 9, 2015
This program is used to make a car follow a black line (on a white surface) that is used to simulate a maze. The car will use LDR inputs to detect the line, and use the motor/wheels to navigate through the maze. */

const int motor1Pin1 = 8;    
const int motor1Pin2 = 9;    
const int motor2Pin1 = 10;    
const int motor2Pin2 = 11;  
const int enablePin1 = 2;
const int enablePin2 = 12;
int value = 0, input = A1;
const int lightSensitivity = 15;
boolean blackFound = false;
int timer2 = 0;

void setup ()
{
  //set enable pins and motor pins as output
  pinMode (enablePin1, OUTPUT);
  pinMode (enablePin2, OUTPUT);
  pinMode (motor1Pin1, OUTPUT);
  pinMode (motor1Pin2, OUTPUT);
  pinMode (motor2Pin1, OUTPUT);
  pinMode (motor2Pin2, OUTPUT);
  //set enable pins to be high
  digitalWrite (enablePin1, HIGH);
  digitalWrite (enablePin2, HIGH);
  Serial.begin(9600); //used to print on the Serial monitor
}

void loop ()
{
  value = analogRead (input);
  //Serial.print (value);
  if (blackFound) //if black has already been found
  {
    //turn right
    analogWrite (motor1Pin2, 90); //left high
    digitalWrite (motor2Pin2, LOW); //right low
    if (value > lightSensitivity)
       timer2 = 0;
  }
  if (timer2 >= 500 && blackFound) //done turning right
    blackFound = false;
  if (blackFound == false) //needs to look for black
  {
      //turn left
      digitalWrite (motor1Pin2, LOW); //left low
      analogWrite (motor2Pin2, 60); //right high
      if (value > lightSensitivity)
      {
        blackFound = true;
        timer2 = 0; //useless?
      }
  }
  timer2 += 10;
}
