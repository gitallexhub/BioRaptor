  // Program for BioRaptor controls.

  // Include stepper motor toolbox.
 #include <Stepper.h>
 #include <LiquidCrystal_I2C.h>
 #include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

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
const int Limit_Switch_OnePin     = 7;
const int Limit_Switch_TwoPin     = 8;
const int Rotary_Encoder_Pin      = 17;
const int Emergency_StopPin       = 18;

  // Define orbital zero position. ****PHYSICAL INITIAL POSITION SET FROM TEST****
int totalOrbitalMotorStepCountFromInitialPosition = digitalRead(Rotary_Encoder_Pin);

  // Potentiometer is an analog input pin.
#define Speed_PotentiometerPin      A0 

  // Define motor pin sets.
Stepper LinearStepper  = Stepper(LinearMotorStepPerRev, 9, 10, 11, 12);
Stepper OrbitalStepper = Stepper(OrbitalMotorStepPerRev, 13, 14, 15, 16);

  // Assign state variable to user input buttons to define pushed or not pushed, limit switches closed or not open, these are not constant.
int Linear_ButtonState    = 0;
int Orbital_ButtonState   = 0;
int D_1_ButtonState       = 0;
int D_2_ButtonState       = 0;
int D_3_ButtonState       = 0;
int D_4_ButtonState       = 0; 
int Limit_Switch_OneState = 0;
int Limit_Switch_TwoState = 0;
int Emergency_StopState   = 0;

  // Define step count.
int LinearMotorSteps      = 0;
int OrbitalMotorSteps     = 0;
 
void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Testing...");
  
  // Set intial state as off for all controllers.
  digitalWrite(Linear_ButtonPin,    LOW);
  digitalWrite(Orbital_ButtonPin,   LOW);
  digitalWrite(D_1_ButtonPin,       LOW);
  digitalWrite(D_2_ButtonPin,       LOW);
  digitalWrite(D_3_ButtonPin,       LOW);
  digitalWrite(D_4_ButtonPin,       LOW);
  digitalWrite(LinearMotorPin,      LOW);
  digitalWrite(OrbitalMotorPin,     LOW);
  digitalWrite(Limit_Switch_OnePin, LOW);
  digitalWrite(Limit_Switch_TwoPin, LOW);
  digitalWrite(Emergency_StopPin,   LOW);
  
  // Set user controllers as inputs.
  pinMode(Linear_ButtonPin,   INPUT);
  pinMode(Orbital_ButtonPin,  INPUT);
  pinMode(D_1_ButtonPin,      INPUT);
  pinMode(D_2_ButtonPin,      INPUT);
  pinMode(D_3_ButtonPin,      INPUT);
  pinMode(D_4_ButtonPin,      INPUT);
  pinMode(Emergency_StopPin,  INPUT
  
  // Set shaker controllers as outputs. 
  pinMode(LinearMotorPin, OUTPUT);
  pinMode(OrbitalMotorPin,OUTPUT);

  // Linear motor zeroing sequence.
    // Define states for linear motor, and both limit switches.
  Linear_ButtonState    = digitalRead(Linear_ButtonPin);
  Limit_Switch_OneState = digitalRead(Limit_Switch_OnePin);
  Limit_Switch_TwoState = digitalRead(Limit_Switch_TwoPin);
 
    // While loop for horizontal homing.
  while (Limit_Switch_TwoState != HIGH && Limit_Swtich_OneState != HIGH) {  // While the limit switches are not closed at the same time (should never happen),
    int Speed_PontentiometerState = analogRead(A0)                          // Read the potentiometer input
    LinearMotorSpeed = map(Speed_PotentiometerState, 0, 1023, 0, 350)       // Map voltages to rpm ****NEEDS TO BE VERIFIED****
    if (LinearMotorSpeed > 0) {                                             // If potentiometer reading is greater than zero,
      LinearStepper.setSpeed(LinearMotorSpeed);                             // Set linear motor speed to potentiometer input,
      LinearStepper.step(LinearMotorStepPerRev/100);                        // Send step command. ****NEEDS TO BE VERIFIED****
    }
    if (Limit_Swtich_OneState = HIGH) {                                     // If limit switch one is closed,
      LinearStepper.setSpeed(-LinearMotorSpeed);                            // Change the direction of the motor
      LinearMotorSteps = stepCount;                                         // Define number of steps the linear motor takes as the step count
      stepCount = 0;                                                        // Set initial value of steps
      LinearStepper.step(LinearMotorStepPerRev/100);                        // Send step command. ****NEEDS TO BE VERIFIED****
    }
    if (Limit_Switch_TwoState = HIGH) {                                     // If limit switch two is closed,
      NumberOfSteps = LinearMotorSteps/2;                                   // Divide number of steps taken from limit switch one to limit switch two by two,
      LinearStepper.setSpeed(LinearMotorSpeed);                             // Change motor direction,
      LinearStepper.step(NumberOfSteps/100);                                // Send step command, this should send the motor to halfway between the limit switches, i.e., the middle of the rail.
    }
  }
  
  // Shaking pattern selection. 
  // Read inputs.
 Linear_ButtonState    = digitalRead(Linear_ButtonPin);
 Orbital_ButtonState   = digitalRead(Orbital_ButtonPin);
 D_1_ButtonState       = digitalRead(D_1_ButtonState);
 D_2_ButtonState       = digitalRead(D_2_ButtonState);
 D_3_ButtonState       = digitalRead(D_3_ButtonState);
 D_4_ButtonState       = digitalRead(D_4_ButtonState); 
  
  // Shaking size selction (diamter). 
  if (D_1_ButtonState = HIGH) {
  X = D_1_NumberOfSteps;                     //***NEED ALL OF THESE TO DETERMINE THIS DISTANCE BY TEST***
    Y = D_1_SetUpSteps;                       
  else if (D_2_ButtonState = HIGH)
    X = D_2_NumberOfSteps;
    Y = D_2_SetUpSteps;
    else if (D_3_ButtonState = HIGH)
      X = D_3_NumberOfSteps;
      Y = D_3_SetUpSteps;
    else if (D_4_ButtonState = HIGH)
      X = D_4_NumberOfSteps;
      Y = D_4_SetUpSteps;
  }
  if (Speed_PotentiometerState = HIGH) {
      // Define motor speed.
  int Speed_PontentiometerState = analogRead(A0);
  MotorSpeed = map(Speed_PotentiometerState, 0, 1023, 0, 350);
  }
  if (Linear_ButtonState = HIGH) {
    i = j;
    else if (Orbital_ButtonState = HIGH)
      i = k;
    else if (Linear_ButtonState = HIGH && Orbital_ButtonState = HIGH)
          i = m;
  }
moderateSpeed = 20; 
}

void loop() {
 // Read shaking pattern selection (linear, orbital, or double orbital), and set up for correct shaking size, and shaking speed.
  if (i == j) { // Linear shaking only.
   LinearStepper.setSpeed(MotorSpeed);
    LinearStepper.step(X);
    LinearStepper.step(-X);
  else if (i == k) 
    OrbitalStepper.setSpeed(moderateSpeed);
    OrbitalStepper.step(-totalStepCountFromInitialPosition);
    //HOLD FOR A SEC//
    LinearStepper.setSpeed(moderateSpeed);
    LinearStepper.step(Y);
    //TIMER: HOLD FOR A SEC//
    OrbitalStepper.setSpeed(MotorSpeed);
    OrbitalStepper.step(OrbitalMotorStepPerRev);
    else if (i == m)
      OrbitalStepper.setSpeed(moderateSpeed);
      OrbitalStepper.step(-totalStepCountFromInitialPosition);
      //HOLD FOR A SEC//
      LinearStepper.setSpeed(moderateSpeed);
      LinearStepper.step(Y);
      //HOLD//
      LinearStepper.setSpeed(MotorSpeed);
      OrbitalStepper.setSpeed(MotorSpeed)
      LinearStepper.step(X);
      LinearStepper.step(-X);
      OrbitalStepper.step(OrbitalMotorStepPerRev);
  }
  if (Limit_Switch_OneState == HIGH || Limit_Switch_TwoState == HIGH) {
  digitalWrite(Linear_ButtonPin,    LOW);
  digitalWrite(Orbital_ButtonPin,   LOW);
  digitalWrite(D_1_ButtonPin,       LOW);
  digitalWrite(D_2_ButtonPin,       LOW);
  digitalWrite(D_3_ButtonPin,       LOW);
  digitalWrite(D_4_ButtonPin,       LOW);
  digitalWrite(LinearMotorPin,      LOW);
  digitalWrite(OrbitalMotorPin,     LOW);
  digitalWrite(Emergency_StopPin,   LOW);
  }
  Emergency_StopState = digitalRead(Emergency_StopPin);
  if (Emergency_StopState == HIGH) {
  digitalWrite(Linear_ButtonPin,    LOW);
  digitalWrite(Orbital_ButtonPin,   LOW);
  digitalWrite(D_1_ButtonPin,       LOW);
  digitalWrite(D_2_ButtonPin,       LOW);
  digitalWrite(D_3_ButtonPin,       LOW);
  digitalWrite(D_4_ButtonPin,       LOW);
  digitalWrite(LinearMotorPin,      LOW);
  digitalWrite(OrbitalMotorPin,     LOW);
  digitalWrite(Emergency_StopPin,   LOW);
  }
}
