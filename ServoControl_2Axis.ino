#include <Servo.h>

#undef SERVO_X_AXIS
#define SERVO_Y_AXIS
#define SERVO_Z_AXIS

#define SERVO_X_MIN (0)
#define SERVO_X_MAX (180)

#define SERVO_Y_MIN (0)
#define SERVO_Y_MAX (130)

#define SERVO_Z_MIN (0)
#define SERVO_Z_MAX (180)

#define SERVO_MG995_MAX_ANGLE (180)
#define SERVO_MG995_MID_ANGLE (SERVO_MG995_MAX_ANGLE/2)

#define JOYSTICK_X  (A2)
#define JOYSTICK_Y  (A1)
#define JOYSTICK_Z  (A0)

#define SERVO_X   (11)
#define SERVO_Y   (10)
#define SERVO_Z   (9)

#define SERVO_DELAY (50)

Servo MyServoX, MyServoY, MyServoZ;  // create servo object to control a servo


int nJoystick_XAxis = JOYSTICK_X;  // analog pin used to connect the potentiometer
int nJoystick_YAxis = JOYSTICK_Y;  // analog pin used to connect the potentiometer
int nJoystick_ZAxis = JOYSTICK_Z;  // analog pin used to connect the potentiometer

int nJoystick_XVal, nJoystick_YVal, nJoystick_ZVal;    // variable to read the value from the analog pin
int nJoystick_XMid, nJoystick_YMid, nJoystick_ZMid;
int nInputDelta_XAxis, nInputDelta_YAxis, nInputDelta_ZAxis;
int nFinal_XVal, nFinal_YVal, nFinal_ZVal;

void setup() {
  Serial.begin(115200);

  pinMode(JOYSTICK_Z, INPUT);
  pinMode(JOYSTICK_Y, INPUT);

  pinMode(SERVO_Z, OUTPUT);
  pinMode(SERVO_Y, OUTPUT);

  MyServoY.attach(SERVO_Y);  // attaches the servo on pin 9 to the servo object    
  MyServoZ.attach(SERVO_Z);  // attaches the servo on pin 9 to the servo object

  nJoystick_ZVal = analogRead(nJoystick_ZAxis);
  nJoystick_ZMid = map(nJoystick_ZVal, 0, 1023, 0, SERVO_MG995_MAX_ANGLE - 1);

  nJoystick_YVal = analogRead(nJoystick_YAxis);
  nJoystick_YMid = map(nJoystick_YVal, 0, 1023, 0, SERVO_MG995_MAX_ANGLE - 1);    

  Serial.print("Calibrate Mid. Value (X/Y/Z) : "); Serial.print(nJoystick_XMid); Serial.print(nJoystick_YMid); Serial.print(nJoystick_ZMid);  
}


void loop() {

#ifdef SERVO_Z_AXIS
  nJoystick_ZVal = analogRead(nJoystick_ZAxis);            // reads the value of the potentiometer (value between 0 and 1023)
  nJoystick_ZVal = map(nJoystick_ZVal, 0, 1023, 0, SERVO_MG995_MAX_ANGLE - 1);     // scale it to use it with the servo (value between 0 and 180)

  nInputDelta_ZAxis = nJoystick_ZVal - nJoystick_ZMid;
  nFinal_ZVal = SERVO_MG995_MID_ANGLE + nInputDelta_ZAxis;
    
  if( nFinal_ZVal > SERVO_Z_MAX ) {
    nFinal_ZVal = SERVO_Z_MAX;
  } else if( nFinal_ZVal < SERVO_Z_MIN ) {
    nFinal_ZVal = SERVO_Z_MIN;
  }

  MyServoZ.write(nFinal_ZVal);                  // sets the servo position according to the scaled value
  delay(SERVO_DELAY);                           // waits for the servo to get there
#endif

#ifdef SERVO_Y_AXIS
  nJoystick_YVal = analogRead(nJoystick_YAxis);            // reads the value of the potentiometer (value between 0 and 1023)
  nJoystick_YVal = map(nJoystick_YVal, 0, 1023, 0, SERVO_MG995_MAX_ANGLE - 1);     // scale it to use it with the servo (value between 0 and 180)

  nInputDelta_YAxis = nJoystick_YVal - nJoystick_YMid;
  nFinal_YVal = SERVO_MG995_MID_ANGLE + nInputDelta_YAxis;
    
  if( nFinal_YVal > SERVO_Y_MAX ) {
    nFinal_YVal = SERVO_Y_MAX;
  } else if( nFinal_YVal < SERVO_Y_MIN ) {
    nFinal_YVal = SERVO_Y_MIN;
  }

  MyServoY.write(nFinal_YVal);                  // sets the servo position according to the scaled value
  delay(SERVO_DELAY);                           // waits for the servo to get there
#endif  

  Serial.print("Calibate Value (X/Y/Z) : "); 
    Serial.print(nJoystick_XMid); Serial.print(" / ");
    Serial.print(nJoystick_YMid); Serial.print(" / ");
    Serial.print(nJoystick_ZMid); 
    Serial.print("            ");

  Serial.print("Input Value (X/Y/Z) : "); 
    Serial.print(nJoystick_XVal); Serial.print(" / ");
    Serial.print(nJoystick_YVal); Serial.print(" / ");
    Serial.print(nJoystick_ZVal); 
    Serial.print("            ");
    
  Serial.print("Final Value (X/Y/Z) : "); 
    Serial.print(nFinal_XVal); Serial.print(" / ");
    Serial.print(nFinal_YVal); Serial.print(" / ");
    Serial.print(nFinal_ZVal);
    Serial.println("            ");     
}

