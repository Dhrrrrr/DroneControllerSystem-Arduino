#include <SoftwareSerial.h>
SoftwareSerial Master(7,8); // TX RX

int Joystick_X = 1;
int Joystick_Y = 0;
int Joystick_Z = 4;

double anglingAmountRad = 0.2;

double standLeft, standBack;

void setup() {
  pinMode(Joystick_Z, INPUT); 
  Serial.begin(38400);  
  Master.begin(38400);

  Serial.println("starting");

  standLeft=analogRead(Joystick_X);
  standBack=analogRead(Joystick_Y);
}

double pressedDown,left,back;

int i = 0;

void loop() {
  left=analogRead(Joystick_X);
  back=analogRead(Joystick_Y);
  pressedDown=digitalRead(Joystick_Z);

  back = ProcessInput(back, standBack, anglingAmountRad);
  left = ProcessInput(left, standLeft, anglingAmountRad);
  

  
  long finalNum = 0;

  if(back > 0.1) {
    finalNum += 200;
  }
  else if (back < -0.1){

    finalNum += 100;
  }

  if(left > 0.1) {
    finalNum += 10;
  }
  else if (left < -0.1){

    finalNum += 30;
  }

  if(pressedDown != 0) {
    finalNum += 1;
  }

  

  Master.write(finalNum);
  Serial.println(finalNum);



}

double ProcessInput(int num, int standardNum, double multiplier) {
  double finalNum = num - standardNum;
  int dist = 512 - standardNum;

  if (finalNum != 0) {
    finalNum -= dist;
  }

  if (finalNum > 0) {
    finalNum += 1;
  }

  finalNum = (finalNum / 512) * multiplier;

  return finalNum;

}
