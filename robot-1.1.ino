https://codeshare.io/q8sSC
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
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  runDemo();
}

void runDemo()
{
  setSpeed(255);
  // this function will drive the robot in a small circle
  //do all of this 4 times
  for (int i = 0; i < 4; ++i)
  {
    goForward(100);
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

void goForward(int fTime)
{
  // turn on motors forward
  //fTime is in mS so 100 = 1 second
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(fTime*10); // for 100 = 1 second
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
}
