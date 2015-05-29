//NSR motor control sketch
//5-26-2015
//Miles Atherly
//Use 11.1V 3000 mAh Lectron Pro LiPo battery and ___ motor

/* The motor variable in each function should be either a 0 or a 1.
 pwm in the motorGo function should be a value between 0 and 1023.
*/
 
#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 100

/*  VNH2SP30 pin definitions
 xxx[0] controls '1' outputs
 xxx[1] controls '2' outputs */

int inApin[2] = {7, 4};  // INA: Clockwise input
int inBpin[2] = {8, 9}; // INB: Counter-clockwise input
int pwmpin[2] = {5, 6}; // PWM input
int cspin[2] = {2, 3}; // CS: Current sense ANALOG input
int enpin[2] = {0, 1}; // EN: Status of switches output (Analog pin)

int BUTTON = A2; //button input pin

int ls1=11; //limit switch 1 input pin
int ls2=12; //limit switch 2 input pin


int buttonstate=0;
int ls1state=0;
int ls2state=0;


void setup() {
 Serial.begin(9600);
  
  pinMode(BUTTON, INPUT_PULLUP);  //declare input pin for button
  pinMode(ls1, INPUT_PULLUP); //declare input pin for limit switch 1
  pinMode(ls2, INPUT_PULLUP); //declare input pin for limit switch 2
  

  // Initialize digital pins as outputs
  for (int i=0; i<2; i++)
  {
    pinMode(inApin[i], OUTPUT);
    pinMode(inBpin[i], OUTPUT);
    pinMode(pwmpin[i], OUTPUT);
  }
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
   //motorGo(0, CW, 1023);
  // motorGo(1, CCW, 1023);
}


void loop() {
  buttonstate=digitalRead(BUTTON);
  ls1state=digitalRead(ls1);
  ls2state=digitalRead(ls2);
  //Serial.print("read switch input: ");
  //Serial.print(digitalRead(BUTTON));
  //Serial.print(", ");
  //Serial.print(digitalRead(ls1));
  //Serial.print(", ");
  //Serial.println(digitalRead(ls2));
  //delay(100);
  
  if(BUTTON == HIGH && ls1 == HIGH){
    motorGo(1, CW, 500);
    if(ls2 == HIGH){
      motorGo(1, CW, 0);
    }
  }
  else if(BUTTON == HIGH && ls2 == HIGH){
    motorGo(1, CCW, 500);
    if(ls1 == HIGH){
      motorGo(1, CCW, 0);
    }
  }
}


void motorOff(int motor)
{
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    // digitalWrite(inBpin[i], LOW);
  }
  analogWrite(pwmpin[motor], 0);
}


void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)
{
  if (motor <= 1)
  {
    if (direct <=4)
    {
      // Set inA[motor]
      if (direct <=1)
        digitalWrite(inApin[motor], HIGH);
      else
        digitalWrite(inApin[motor], LOW);

      // Set inB[motor]  
      if ((direct==0)||(direct==2))
        digitalWrite(inBpin[motor], HIGH);
      else
        digitalWrite(inBpin[motor], LOW);

      analogWrite(pwmpin[motor], pwm);
    }
  }
}


