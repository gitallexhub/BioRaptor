  // Program for BioRaptor controls.

  // Include stepper motor toolbox.
 #include <Stepper.h>
 #include <LiquidCrystal_I2C.h>
 #include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

  // Initialize chronological sequencing tool. 
unsigned long TimeStamp;

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
#define Speed_PotentiometerPin A0;

  // Define motor pin sets.
Stepper LinearStepper  = Stepper(LinearMotorStepPerRev, 9, 10, 11, 12);
Stepper OrbitalStepper = Stepper(OrbitalMotorStepPerRev, 13, 14, 15, 16);

  // Assign state variable to user input buttons to define pushed or not pushed, limit switches closed or not open, time, these are not constant.
int Linear_ButtonState        = 0;
int Orbital_ButtonState       = 0;
int D_1_ButtonState           = 0;
int D_2_ButtonState           = 0;
int D_3_ButtonState           = 0;
int D_4_ButtonState           = 0; 
int Limit_Switch_OneState     = 0;
int Limit_Switch_TwoState     = 0;
int Emergency_StopState       = 0;
int Speed_PontentiometerState = 0;
int SequenceTime              = 1000000;

  // Define step count. Not sure how this works.
// int LinearMotorSteps      = 0;
// int OrbitalMotorSteps     = 0;
 
void setup() {
  Serial.begin(9600);
  
  
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
  pinMode(Emergency_StopPin,  INPUT);
  pinMode(Limit_Switch_OnePin, INPUT);
  pinMode(Limit_Switch_TwoPin, INPUT);
  
  // Set shaker controllers as outputs. 
  pinMode(LinearMotorPin, OUTPUT);
  pinMode(OrbitalMotorPin,OUTPUT);

  
}

void loop() {

  // Get current time. 
  TimeStamp = millis();
  // Set five seconds for zeroing sequence.
  while (TimeStamp >= 0 && TimeStamp =< 5000) {
    // Linear motor zeroing sequence.
    // Define states for linear motor, and both limit switches.
  Linear_ButtonState    = digitalRead(Linear_ButtonPin);
  Limit_Switch_OneState = digitalRead(Limit_Switch_OnePin);
  Limit_Switch_TwoState = digitalRead(Limit_Switch_TwoPin);
  Speed_PontentiometerState = analogRead(0);
 
    // While loop for horizontal homing.
  while (Limit_Switch_TwoState != HIGH) {                                   // While limit switch one is open,
      moderateSpeed = 20;                                                   // Set moderate motor speed
      LinearStepper.setSpeed(-moderateSpeed);                               // Set linear motor speed to potentiometer input,
      LinearStepper.step(LinearMotorStepPerRev/100);                        // Send step command. **** DIRECTION NEEDS TO BE VERIFIED****
    }
    if (Limit_Switch_TwoState == HIGH) {                                    // If limit switch two is closed, (while loop ends and thus, motor should stop stepping
      NumberOfSteps = 50;                                                   // Set number of steps to the halfway point (as measured through computation/test),
      LinearStepper.setSpeed(LinearMotorSpeed);                             // Change motor direction,
      LinearStepper.step(50);                                               // Send step command, this should send the motor to halfway between the limit switches, i.e., the middle of the rail.
    }
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
  // Set five seconds for selection.
while (TimeStamp > 5000 && TimeStamp =<10000) {
  // ALEX: Print on LED to make diameter selection.
  if (D_1_ButtonState == HIGH) {
  X = 15.748; //D_1_NumberOfSteps                   //***NEED ALL OF THESE TO DETERMINE THIS DISTANCE BY TEST***
    Y = 0;                       
  else if (D_2_ButtonState == HIGH)
    X = 15.748; //D_2_NumberOfSteps
    Y = 0; //Set up steps
    else if (D_3_ButtonState == HIGH)
      X = 30.177; //D_3_NumberOfSteps
      Y = 13.858; //Set up steps
    else if (D_4_ButtonState == HIGH)
      X = 43.858; //D_4_NumberOfSteps
      Y = 27.7165; //Set up steps
  }
}
  // Set motor speed.
  // Set five seconds for motor speed selection. 
while (TimeStamp >10000 && TimeStamp =< 15000) {
  // ALEX: Print on LED to make speed selection.
  if (Speed_PotentiometerState == HIGH) {
      // Define motor speed.
  int Speed_PontentiometerState = analogRead(A0);
  MotorSpeed = map(Speed_PotentiometerState, 0, 1023, 0, 350);
  }
}
  // Set shaking pattern. 
  // Set five second for pattern selection.
while (TimeStamp >15000 && TimeStamp =< 20000) {
  // ALEX: Print on LED to make shape selection. 
  if (Linear_ButtonState == HIGH) {
    i = j;
    else if (Orbital_ButtonState == HIGH)
      i = k;
    else if (Linear_ButtonState == HIGH && Orbital_ButtonState == HIGH)
          i = m;
  }
}

//Define moderate speed for set up procedures. 
moderateSpeed = 20;

// Read shaking pattern selection (linear, orbital, or double orbital), and set up for correct shaking size, and shaking speed.
if (i == j) { // Linear shaking only.
  // Set indefinite time for shaking to carry out.
  while (TimeStamp > 20000) { 
   LinearStepper.setSpeed(MotorSpeed);
    LinearStepper.step(X);
    LinearStepper.step(-X);
    // Set stopping condition. 
    if (Linear_ButtonState == HIGH) {
  digitalWrite(Linear_ButtonPin,    LOW);
  digitalWrite(Orbital_ButtonPin,   LOW);
  digitalWrite(D_1_ButtonPin,       LOW);
  digitalWrite(D_2_ButtonPin,       LOW);
  digitalWrite(D_3_ButtonPin,       LOW);
  digitalWrite(D_4_ButtonPin,       LOW);
  digitalWrite(LinearMotorPin,      LOW);
  digitalWrite(OrbitalMotorPin,     LOW);
  digitalWrite(Emergency_StopPin,   LOW);
  // Reset timer.
  TimeStamp = 0;
  // Exit loop.
  exit(0);
      // IRELAND: add rotary encoder zeroing procedure, add reset timer, add send to start of loop. 
  }
  }
  else if (i == k) // Orbital shaking only.
    // Set indefinite shaking time.
  while (TimeStamp > 20000) {
    OrbitalStepper.setSpeed(moderateSpeed);
    OrbitalStepper.step(-totalStepCountFromInitialPosition);
    delay(3000);
    LinearStepper.setSpeed(moderateSpeed);
    LinearStepper.step(Y);
    delay(3000);
    OrbitalStepper.setSpeed(MotorSpeed);
    OrbitalStepper.step(OrbitalMotorStepPerRev);
    if (Orbital_ButtonState == HIGH) {
  //stop all motion
  digitalWrite(Linear_ButtonPin,    LOW);
  digitalWrite(Orbital_ButtonPin,   LOW);
  digitalWrite(D_1_ButtonPin,       LOW);
  digitalWrite(D_2_ButtonPin,       LOW);
  digitalWrite(D_3_ButtonPin,       LOW);
  digitalWrite(D_4_ButtonPin,       LOW);
  digitalWrite(LinearMotorPin,      LOW);
  digitalWrite(OrbitalMotorPin,     LOW);
  digitalWrite(Emergency_StopPin,   LOW);
  // pause 
  delay(3000);
  // Zero orbital motor
  // Remove orbital motor shaft from diameter selction. If it is D1, it will just be zero steps horizontally
  OrbitalStepper.setSpeed(moderateSpeed);
  OrbitalStepper.step(-totalStepCountFromInitialPosition); 
  delay(3000);
  LinearStepper.setSpeed(moderateSpeed);
  LinearStepper.step(-Y);
  // Reset timer.
  TimeStamp = 0;
  // Exit loop
  exit(0);
  }  
  }
    else if (i == m) // Double orbital shaking.
      // Set indefinite shaking time.
      while (TimeStamp > 20000) {
      OrbitalStepper.setSpeed(moderateSpeed);
      OrbitalStepper.step(-totalStepCountFromInitialPosition);
      delay(3000);
      LinearStepper.setSpeed(moderateSpeed);
      LinearStepper.step(Y);
      delay(3000);
      LinearStepper.setSpeed(MotorSpeed);
      OrbitalStepper.setSpeed(MotorSpeed)
      LinearStepper.step(X);
      LinearStepper.step(-X);
      OrbitalStepper.step(OrbitalMotorStepPerRev);
        if (Orbital_ButtonState == HIGH || Linear_ButtonState == HIGH) {
  digitalWrite(Linear_ButtonPin,    LOW);
  digitalWrite(Orbital_ButtonPin,   LOW);
  digitalWrite(D_1_ButtonPin,       LOW);
  digitalWrite(D_2_ButtonPin,       LOW);
  digitalWrite(D_3_ButtonPin,       LOW);
  digitalWrite(D_4_ButtonPin,       LOW);
  digitalWrite(LinearMotorPin,      LOW);
  digitalWrite(OrbitalMotorPin,     LOW);
  digitalWrite(Emergency_StopPin,   LOW);
  // pause 
  delay(3000);
  // Zero orbital motor
  // Remove orbital motor shaft from diameter selction. If it is D1, it will just be zero steps horizontally
  OrbitalStepper.setSpeed(moderateSpeed);
  OrbitalStepper.step(-totalStepCountFromInitialPosition); 
  delay(3000);
  LinearStepper.setSpeed(moderateSpeed);
  LinearStepper.step(-Y);
  // Reset timer.
  TimeStamp = 0;
  // Exit loop
  exit(0);
        }
      }
  }
  
  // Emergency stop sequence via limit switch detection.
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

  // Emergency stop sequence via user stop. 
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
