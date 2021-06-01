/* 
   
   An obstacle between 15 cm, it turn right.
 
 */
#include <AFMotor.h>
#include <elapsedMillis.h>
int startSwitch = 17;
int startFlag = 0;

unsigned int interval = 3000; //3 secs in ms

 //echo = A1
 //trig = A0
AF_DCMotor motor1(1,MOTOR12_8KHZ); // set up motors.
AF_DCMotor motor2(2, MOTOR12_8KHZ);

void setup() {
  //Serial.begin(9600);
  pinMode(startSwitch, INPUT);
  pinMode(A1, INPUT);
  pinMode(A0, OUTPUT);
  Serial.begin(9600); // begin serial communitication  
  
  motor1.setSpeed(80); //set the speed of the motors, between 0-255
  motor2.setSpeed (100);
}

void loop() {
  int start = digitalRead(startSwitch);
  Serial.println(start);
  if(start == 1){
    elapsedMillis timeElapsed;
    while(timeElapsed < interval){
      long distance, duration;

      digitalWrite(A0, LOW);
      delay(2);
      digitalWrite(A0, HIGH);
      delay(10);
      digitalWrite(A0, LOW);
      
      duration = pulseIn(A1, HIGH);
      distance = (duration/2)/29.1;
      
    
      if (distance < 20)
      {
        motor1.run(FORWARD);      //Right
        motor2.run (BACKWARD);
        delay(100);
      }
    
      
      else
      {
        motor1.run(FORWARD);      //Forward
        motor2.run (FORWARD);
      }
    
      delay(10);
    }
    motor1.run(RELEASE);      //Stops
    motor2.run (RELEASE);
  }  
}
