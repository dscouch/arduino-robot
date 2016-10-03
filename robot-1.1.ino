
// ---------------------------------------------------------------------------
// Robot Code
// Currently runs motors
// Adding in sonar, gyroscope, revolution counting, and possibly wifi
// ---------------------------------------------------------------------------

//Set up the sonar
#include <NewPing.h>
#define SONAR_NUM 2      // Number of sensors.  (2 in this case)
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(12, 12, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(13, 13, MAX_DISTANCE), 
};

// connect motor controller pins to Arduino digital pins
// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;

void setup()
{
  Serial.begin(115200); // Open serial monitor at 115200 baud to output results.
  
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //runDemo();
}

void runDemo()
{
  setSpeed(255);
  // this function will drive the robot in a small circle
  //do all of this 4 times
  for (int i = 0; i < 4; ++i)
  {
    //goForward(100);
    goTurn(2,20);
    stopMotors(3);
    delay(1000); // wait 1 second
  }
}

//SUBROUTINES =========================================

void setSpeed(int Speed)
{
    // set speed to 255 out of possible range 0~255
    analogWrite(enA, Speed);
    analogWrite(enB, Speed);
}

void goForward()
{
  // turn on motors forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void goBackward()
{
  // turn on motors forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void goTurn(int turnDir, int tTime)
{
  if (turnDir == 1) // 1 = left
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if (turnDir == 2) // 2 = right
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
    delay(tTime*10); // for a millisecond
}

void stopMotors(int Mtrs)
{
  if (Mtrs == 1) // 1 = left
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  } 
  else if (Mtrs == 2) // 2 = right
  {
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  } 
  else if (Mtrs == 3) // 3 = both
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}

void loop()
{
  setSpeed(255);
  int leftPing = sonar[0].ping_in();
  int rightPing = sonar[1].ping_in();
  if (leftPing == 0) { leftPing = 50; }
  if (rightPing == 0) { rightPing = 50; }
  if ((leftPing > 6) && (rightPing > 6))
  {
    goForward();
  } else if ((leftPing < 7) && (rightPing < 7))
  {
    goBackward();
    delay(100);
    goTurn(2,40);
    leftPing = 50;
    rightPing = 50;
  } else if (leftPing < 7)
  {
    goTurn(2,20);
  } else if (rightPing < 7)
  {
    goTurn(1,20);
  }
  delay(30);
}
