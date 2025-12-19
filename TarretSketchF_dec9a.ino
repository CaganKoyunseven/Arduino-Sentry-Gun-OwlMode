#include <Servo.h>

const int LeftTrig = 8;
const int LeftEcho = 9;
const int RightTrig = 10;
const int RightEcho = 11;
const int LaserPin = 13;
const int BuzzerPin = 6; 
const int ServoPin = 3;

Servo Turret;
const int StopPoint = 90;   
const int StepTime  = 30;   
const int SafetyLimit = 10; 

const int LeftTurnSpeed  = 35; 
const int RightTurnSpeed = 32; 

int VirtualPos = 0;        
int ScanDir = 1;            
int NearestObj = 999;
int AttackBound = 0;
int DistLeft = 0;
int DistRight = 0;

int MeasureDistance(int trig, int echo) {
  digitalWrite(trig, LOW);  delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH);
  int distance = duration * 0.034 / 2;
  if (distance == 0 || distance > 400) {
    distance = 400;
    } 
  return distance;
}

void setup() {
  pinMode(LeftTrig, OUTPUT);  
  pinMode(LeftEcho, INPUT);
  pinMode(RightTrig, OUTPUT); 
  pinMode(RightEcho, INPUT);
  pinMode(LaserPin, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
  Turret.attach(ServoPin);
  Serial.begin(9600);
 
  Turret.write(StopPoint);
  tone(BuzzerPin, 2000, 200); 
  delay(200);
  tone(BuzzerPin, 1000, 200);

  
  long StartTime = millis();
  while(millis() - StartTime < 3000){
    int tempLeft = MeasureDistance(LeftTrig, LeftEcho);
    delay(10); 
    int tempRight = MeasureDistance(RightTrig, RightEcho);
    
    if(tempLeft < NearestObj && tempLeft > 0) {
      NearestObj = tempLeft;
      }
    if(tempRight < NearestObj && tempRight > 0) {
      NearestObj = tempRight;
      }
    delay(50);
  }

  AttackBound = NearestObj - 15;
  if (AttackBound < 10) AttackBound = 10; 
  
  tone(BuzzerPin, 3000, 100); delay(100);
  tone(BuzzerPin, 3000, 100);
  delay(1000);
}

void loop() {
  DistLeft = MeasureDistance(LeftTrig, LeftEcho);
  delay(5); 
  DistRight = MeasureDistance(RightTrig, RightEcho);


  if (DistLeft < AttackBound && DistRight < AttackBound) {
      Turret.write(StopPoint);      
      digitalWrite(LaserPin, HIGH);   
      tone(BuzzerPin, 4000);          
      delay(100); 
  } 
  
  
  else if (DistLeft < AttackBound) {
      digitalWrite(LaserPin, LOW); 
      noTone(BuzzerPin);
      ScanDir = -1; 
      
      if(VirtualPos < SafetyLimit){ 
        Turret.write(StopPoint + LeftTurnSpeed); 
        VirtualPos++;                              
        delay(StepTime);   
        Turret.write(StopPoint); 
      } else {
        Turret.write(StopPoint); 
      }
  }

  
  else if (DistRight < AttackBound) {
      digitalWrite(LaserPin, LOW);
      noTone(BuzzerPin);
      ScanDir = 1; 
      
      if(VirtualPos > -SafetyLimit){ 
        Turret.write(StopPoint - RightTurnSpeed); 
        VirtualPos--;                          
        delay(StepTime);   
        Turret.write(StopPoint); 
      } else {
        Turret.write(StopPoint); 
      }
  }
  
  
  else {
      digitalWrite(LaserPin, LOW);
      noTone(BuzzerPin);
      
      if (VirtualPos >= SafetyLimit) {
        ScanDir = 1;
        }      
      if (VirtualPos <= -SafetyLimit) {
        ScanDir = -1;
        }       
      
      
      if (ScanDir == 1) { 
         if (VirtualPos > -SafetyLimit) {
             Turret.write(StopPoint - RightTurnSpeed); 
             VirtualPos--;
         }
      } 
      else { 
         if (VirtualPos < SafetyLimit) {
             Turret.write(StopPoint + LeftTurnSpeed); 
             VirtualPos++;
         }
      }
      
      delay(StepTime); 
      Turret.write(StopPoint);
      delay(20); 
  }
}
