/** 
  Salar Hosseini, Sejin Kim, Horatiu Lazu
  Mr Wong
  September 16, 2015
  The purpose of this code is to control the execution of a sumo-bot.
*/
 
 
/* These are the variables for the ultrasonic sensors */
//const int frontSensor = 1;
//const int frontSensorB = 2;
//const int backSensor = 3;
//const int backSensorB = 4;
 
/* These variables store the motor pins, and the enable pin for the H-Bridge */
const int motor1Forward = 5;
const int motor1Backward = 6;
const int motor2Forward = 7;
const int motor2Backward = 8;
 
const int rightSensor = 9;
const int rightSensorB = 10;
const int leftSensor = 11;
const int leftSensorB = 12;
 
 
/* Minimum and maximum value for the LDR. */
const int minVal = 700;
const int maxVal = 1000;
 
/* These are the variables for the LDRs (Analog-In) */
const int LDR_PIN_TOP_LEFT = A0;
const int LDR_PIN_TOP_RIGHT = A1;
const int LDR_PIN_BOTTOM_RIGHT= A2;
const int LDR_PIN_BOTTOM_LEFT = A3;
 
/* These are the variables for the left / right motors.
   First index = power used for going forwards
   Second index = power used for going backwards */
int motor1[2] = {0,0};
int motor2[2] = {0,0};
 
/* This variable stores the maximum distance that will be taken into consideration for the first round by the robot. */
const int MAX_DISTANCE_RANGE = 50;
/* This variable is the constant speed for going straight. */
const int FORWARD_SPEED = 80;
/* This is the variable for the non-dominant turning speed. */
const int NON_DOMINANT_TURNING_SPEED = 10;
/* This is the rotation speed. */
const int ROTATION_SPEED = 255;
 
/* This variable stores the max distance to assume that the robot is being pushed. */
const int PUSHING_ROBOT = 7;
 
void setup() {
    Serial.begin(9600);
 
    /* Setup the motor pins as output */
    pinMode(motor1Forward, OUTPUT);
    pinMode(motor1Backward, OUTPUT);
    pinMode(motor2Forward, OUTPUT);
    pinMode(motor2Backward, OUTPUT);
 
    resetMotorSpeed();
  }
 
  /* This method converts the microsends to centimeters, by taking into consideration the speed of sound. */
  long microsecondsToCentimeters(long microseconds) {
    return microseconds / 29 / 2;
  }
 
  void resetMotorSpeed(){
    motor1[0] = motor1[1] = motor2[0] = motor2[1] = 0;
  }
 
  /* This method updates the speed. */
  void updateSpeed(){
     digitalWrite(motor1Forward, motor1[0]);
     digitalWrite(motor1Backward,motor1[1]);
     digitalWrite(motor2Forward,motor2[0]);
     digitalWrite(motor2Backward,motor2[1]); 
  }
 
  void goForward(int speedF){
     motor1[0] = motor2[0] = speedF;
     motor1[1] = motor2[1] = 0;
     updateSpeed();
  }
 
 /* Potential issue: When you turn back with the wheel, should the other wheel go  in the opposite direction for a sharper turn?? 
   Extra: Add a method to go backwards AND turn!*/
  void turn(int rSpeed, int lSpeed){
       motor1[0] = lSpeed;
       motor1[1] = 0;
       motor2[0] = rSpeed;
       motor2[1] = 0; 
       updateSpeed();
  }
 
  /* This is the rotation */
  void rotate(){
     motor1[0] = motor2[1] = ROTATION_SPEED;
     motor1[1] =motor2[0] = 0; 
     updateSpeed();
  }
 
  /* This method goes backwards */
  void goBackwards(int speedB){
      motor1[0] = motor2[0] = 0;
      motor1[1] =  motor2[1] = speedB;
      updateSpeed();
  }
 
  boolean inRange(int input){
      return ((minVal<= input && minVal >= input) ? (true) : (false));
  }
 
  int getReading(int sensor){
      return analogRead((sensor == 1) ? (LDR_PIN_TOP_RIGHT) : (sensor==2)?(LDR_PIN_TOP_LEFT) : (sensor==3) ? (LDR_PIN_BOTTOM_RIGHT) : (LDR_PIN_BOTTOM_LEFT));
   }
 
 
  /* int ping(int sensorNum){
      long duration, inches, cm;
      int pingPin = ((sensorNum == 1) ? (frontSensor) : (sensorNum==2) ? (rightSensor) : (sensorNum == 3) ? (leftSensor) : (backSensor));
 
      pinMode(pingPin, OUTPUT);
      digitalWrite(pingPin, LOW);
      delayMicroseconds(2);
      digitalWrite(pingPin, HIGH);
      delayMicroseconds(5);
      digitalWrite(pingPin, LOW);
 
      pinMode(pingPin, INPUT);
      duration = pulseIn(pingPin, HIGH);
 
      return microsecondsToCentimeters(duration);
   }*/
 
   boolean withinAcceptableRange(int sensor){
       if (ping2(sensor) <= MAX_DISTANCE_RANGE){ //ping2??
          return true; 
       }
       return false;
   }
 
 
   int ping2(int ultrasonic){
     //ultrasonic++;
 
     if (ultrasonic >= 3)
       ultrasonic += 2; //plus 2
    digitalWrite(ultrasonic * 2 - 1, LOW);
    delayMicroseconds(2);
 
    digitalWrite(ultrasonic * 2 - 1, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasonic * 2 - 1, LOW);
 
    double duration = pulseIn(ultrasonic *2, HIGH);
    double distance = duration / 58;
    return distance;
   }
 
   int ping4(int ultrasonic){
     //ultrasonic++;
    ultrasonic = 6;
    digitalWrite(ultrasonic * 2 - 1, LOW);
    delayMicroseconds(2);
 
    digitalWrite(ultrasonic * 2 - 1, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasonic * 2 - 1, LOW);
 
    double duration = pulseIn(ultrasonic *2, HIGH);
    double distance = duration / 58;
    return distance;
   }
 
   //1
   int ping1(int ultrasonic){
     //ultrasonic++;
    //ultrasonic = 2;
    digitalWrite(3, LOW);
    delayMicroseconds(2);
 
    digitalWrite(3, HIGH);
    delayMicroseconds(10);
    digitalWrite(3, LOW);
 
    double duration = pulseIn(4, HIGH);
    double distance = duration / 58;
    return distance;
   }
 
   void temp(){
      goForward(255);
      delay(2000);
      goBackwards(255);
      delay(2000);
      turn(255,0);
      delay(2000);
      turn(0,255);
      delay(2000);
   }
 
  /* Main method. Rules for LDR/ultrasonic:
     Top = 1 | Right = 2 | Left = 3 | Back = 4 */
  void loop() {
    //temp();
    /*if(withinAcceptableRange((1)){
        goForward(40);
    }
    else if (withinAcceptableRange(2)){
    }    */
     int dist1 = ping2(1);
    //int dist2 = ping2(2);
    //int dist3 = ping2(3);
    //int dist4 = ping1(1);
   Serial.print("Front: ");
    Serial.println(dist1);
 
    //Serial.print("Back: ");
    //Serial.println(dist2);
 
    //Serial.print("Right: ");
    //Serial.println(dist3);
 
    //Serial.print("Left: ");
    //Serial.println(dist4);
 
    //delay(1000);
  }
