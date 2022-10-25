  // Program for BioRaptor controls.

  // Include stepper motor toolbox.
 #include <Stepper.h>

  // Define steps per revolution of stepper motors (1.8 degrees per step, 360 degrees full rotation).
const int LinearMotorStepPerRev  = 200; 
const int OrbitalMotorStepPerRev = 200;
  
  // Assign pin number to controllers, these are constant values.  
const int Linear_ButtonPin        = 1;
const int Orbital_ButtonPin       = 2;
const int D_1_ButtonPin           = 3; 
const int D_2_ButtonPin           = 4;
const int D_3_ButtonPin           = 5;
const int D_4_ButtonPin           = 6;

  // Potentiometer is an analog input pin.
#define Speed_PotentiometerPin      A0 

  // Define motor pin sets.
Stepper LinearStepper  = Stepper(LinearMotorStepPerRev, 7, 8, 9, 10);
Stepper OrbitalStepper = Stepper(OrbtialMotorStepPerRev, 11, 12, 13, 14);

  // Assign state variable to user input buttons to define pushed or not pushed, these are not constant.
int Linear_ButtonState  = 0;
int Orbital_ButtonState = 0;
int D_1_ButtonState     = 0;
int D_2_ButtonState     = 0;
int D_3_ButtonState     = 0;
int D_4_ButtonState     = 0; 

  // Define step count.
int LinearMotorSteps    = 0;
int OrbitalMotorSteps   = 0;
 
void setup() {
  // Set intial state as off for all controllers.
  digitalWrite(Linear_ButtonPin,  LOW)
  digitalWrite(Orbital_ButtonPin, LOW)
  digitalWrite(D_1_ButtonPin,     LOW)
  digitalWrite(D_2_ButtonPin,     LOW)
  digitalWrite(D_3_ButtonPin,     LOW)
  digitalWrite(D_4_ButtonPin,     LOW) 
  digitalWrite(LinearMotorPin,    LOW)
  digitalWrite(OrbitalMotorPin,   LOW)
  
  // Set user controllers as inputs.
  pinMode(Linear_ButtonPin,   INPUT)
  pinMode(Orbital_ButtonPin,  INPUT)
  pinMode(D_1_ButtonPin,      INPUT)
  pinMode(D_2_ButtonPin,      INPUT)
  pinMode(D_3_ButtonPin,      INPUT)
  pinMode(D_4_ButtonPin,      INPUT)
  
  // Set shaker controllers as outputs. 
  pinMode(LinearMotorPin, OUTPUT)
  pinMode(OrbitalMotorPin,OUTPUT)

  // Linear motor zeroing sequence.
  
  if (pinMode(Linear_ButtonPin,HIGH))
  X = LinearMotorPin;
  if (

}



void loop() {
  digitaWrite(X, HIGH)
  
  // put your main code here, to run repeatedly:

}
