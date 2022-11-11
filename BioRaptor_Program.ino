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
const int Linear_ButtonPin          = A3;
const int Orbital_ButtonPin         = A6;
const int D_1_ButtonPin             = A0; 
const int D_2_ButtonPin             = A1;
const int D_3_ButtonPin             = A2;
const int Limit_Switch_OnePin       = 4;
const int Limit_Switch_TwoPin       = 5;
const int Rotary_Encoder_ClickPin   = 6;
const int Rotary_Encoder_DirPin     = 7;
const int moderateSpeed             = 20;
//LCD = A4, A5 ACTUAL
//Potentiometer = A7 ACTUAL

//Encoder Pins Defined
  // Define orbital zero position. ****PHYSICAL INITIAL POSITION SET FROM TEST****
int totalOrbitalMotorStepCountFromInitialPosition = digitalRead(Rotary_Encoder_ClickPin);
int CurrentMotorDirection                         = digitalRead(Rotary_Encoder_DirPin);

  // Potentiometer is 

  // Define motor pin sets.
Stepper  LinearMotor  = Stepper(LinearMotorStepPerRev, 2,3);
Stepper OrbitalMotor = Stepper(OrbitalMotorStepPerRev, 11,12);

  // Assign state variable to user input buttons to define pushed or not pushed, limit switches closed or not open, time, these are not constant.
int Linear_ButtonState        = 0;
int Orbital_ButtonState       = 0;
int D_1_ButtonState           = 0;
int D_2_ButtonState           = 0;
int D_3_ButtonState           = 0;
int Limit_Switch_OneState     = 0;
int Limit_Switch_TwoState     = 0;
int Emergency_StopState       = 0;
int Speed_PotState            = 0;
int potValue                  = 0;
int TrxpotValue               = 0;
int  X                        = 0;
int  Y                        = 0;
int  i                        = 0;
int  j                        = 0;
int  k                        = 0;
int  m                        = 0;
int MotorSpeed                = 0;



// int LinearMotorSteps      = 0;
// int OrbitalMotorSteps     = 0;
 
void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.print("Starting System");
  delay(1500);
  lcd.clear();
  lcd.print("System On");
  delay(1000);
  lcd.clear();
//  
//  
  // Set intial state as off for all controllers.
  analogWrite(Linear_ButtonPin,    LOW);
  analogWrite(Orbital_ButtonPin,   LOW);
  analogWrite(D_1_ButtonPin,       LOW);
  analogWrite(D_2_ButtonPin,       LOW);
  analogWrite(D_3_ButtonPin,       LOW);
  digitalWrite(Limit_Switch_OnePin, LOW);
  digitalWrite(Limit_Switch_TwoPin, LOW);

  
  // Set user controllers as inputs.
  pinMode(Linear_ButtonPin,        INPUT);
  pinMode(Orbital_ButtonPin,       INPUT);
  pinMode(D_1_ButtonPin,           INPUT);
  pinMode(D_2_ButtonPin,           INPUT);
  pinMode(D_3_ButtonPin,           INPUT);
  pinMode(Limit_Switch_OnePin,     INPUT);
  pinMode(Limit_Switch_TwoPin,     INPUT);
  pinMode(A7,                      INPUT);
  pinMode(Rotary_Encoder_ClickPin, INPUT);
  pinMode(Rotary_Encoder_DirPin,   INPUT);
  
  
  // Set shaker controllers as outputs. 
 // pinMode(LinearMotor, OUTPUT);
 // pinMode(OrbitalMotor,OUTPUT);

}

void loop() {
    Serial.begin(9600);
    // Get current time. 
    TimeStamp = millis();
    // Set five seconds for zeroing sequence.
    Serial.print(A3);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Horizontal Zero");
  while (TimeStamp >= 3000 && TimeStamp <= 15000) {
    // Linear motor zeroing sequence.
    // Define states for linear motor, and both limit switches.
    Linear_ButtonState    = analogRead(Linear_ButtonPin);
    Limit_Switch_OneState = digitalRead(Limit_Switch_OnePin);
    Limit_Switch_TwoState = digitalRead(Limit_Switch_TwoPin);
    Speed_PotState = analogRead(7);
 
      // While loop for horizontal homing.
      while (Limit_Switch_TwoState != HIGH) {                                   // While limit switch one is open,
                                                        // Set moderate motor speed
          LinearMotor.setSpeed(-100);                               // Set linear motor speed to potentiometer input,
          LinearMotor.step(LinearMotorStepPerRev/100);                        // Send step command. **** DIRECTION NEEDS TO BE VERIFIED****
        }
            if (Limit_Switch_TwoState == HIGH) {                                    // If limit switch two is closed, (while loop ends and thus, motor should stop stepping
              //  NumberOfSteps = 50;                                                   // Set number of steps to the halfway point (as measured through computation/test),
              LinearMotor.setSpeed(-100);                                     // Change motor direction,
              LinearMotor.step(50);                                               // Send step command, this should send the motor to halfway between the limit switches, i.e., the middle of the rail.
            }
   }

 
  // Shaking pattern selection. 
  // Read inputs.
 Linear_ButtonState    = analogRead(Linear_ButtonPin);
 Orbital_ButtonState   = analogRead(Orbital_ButtonPin);
 D_1_ButtonState       = analogRead(D_1_ButtonState);
 D_2_ButtonState       = analogRead(D_2_ButtonState);
 D_3_ButtonState       = analogRead(D_3_ButtonState);
  
  // Shaking size selction (diamter). 
  // Set five seconds for selection.
  //Print on LCD "make diameter selection"
  delay(3000);

lcd.clear();
lcd.print("10 seconds");
  while (TimeStamp > 15000 && TimeStamp <=25000) {
    lcd.print("Make diameter selection");
          // Print on LCD countdown
    if (D_1_ButtonState == HIGH) {
      X = 15.748; //D_1_NumberOfSteps
      Y = 0; //Set up steps
    }
    
    else if (D_2_ButtonState == HIGH){
      X = 30.177; //D_2_NumberOfSteps
      Y = 13.858; //Set up steps
    }
    
    else if (D_3_ButtonState == HIGH){
      X = 43.858; //D_3_NumberOfSteps
      Y = 27.7165; //Set up steps
    }
    
  }

      // Set motor speed.
      // Set five seconds for motor speed selection. 
      // print "make speed selection"
      delay(3000);
  while (TimeStamp >28000 && TimeStamp <= 38000) {
        // print countdown
    if (Speed_PotState == HIGH) {
        // Define motor speed.
        int Speed_PontentiometerState = analogRead(0);
        MotorSpeed = map(Speed_PotState, 0, 1023, 0, 350);
      }
  }
      // Set shaking pattern. 
      // Set five second for pattern selection.
  while (TimeStamp >28000 && TimeStamp <= 38000) {
       // ALEX: Print on LCD to make shape selection. 
    if (Linear_ButtonState == HIGH) {
      i = j;
    }
    
    else if (Orbital_ButtonState == HIGH){
      i = k;
    }
    else if (Linear_ButtonState == HIGH && Orbital_ButtonState == HIGH){
          i = m;
    }
}

//Define moderate speed for set up procedures. 
//moderateSpeed = 20;

// Read shaking pattern selection (linear, orbital, or double orbital), and set up for correct shaking size, and shaking speed.
  if (i == j) { // Linear shaking only.
      // Set indefinite time for shaking to carry out.
      while (TimeStamp > 38000) { 
          LinearMotor.setSpeed(MotorSpeed);
          LinearMotor.step(X);
          LinearMotor.step(-X);
          // Set stopping condition. 
            if (Linear_ButtonState == HIGH) {
                analogWrite(Linear_ButtonPin,    LOW);
                analogWrite(Orbital_ButtonPin,   LOW);
                analogWrite(D_1_ButtonPin,       LOW);
                analogWrite(D_2_ButtonPin,       LOW);
                analogWrite(D_3_ButtonPin,       LOW);
                //digitalWrite(LinearMotor,        LOW);
                //digitalWrite(OrbitalMotor,       LOW);
                // Reset timer.
                TimeStamp = 0;
                // Exit loop.
                exit(0);
              }
          }
  }
      
      else if (i == k){ // Orbital shaking only.
          // Set indefinite shaking time.
        while (TimeStamp > 38000) {
            OrbitalMotor.setSpeed(moderateSpeed);
            OrbitalMotor.step(-totalOrbitalMotorStepCountFromInitialPosition);
            delay(3000);
            LinearMotor.setSpeed(moderateSpeed);
            LinearMotor.step(Y);
            delay(3000);
            OrbitalMotor.setSpeed(MotorSpeed);
            OrbitalMotor.step(OrbitalMotorStepPerRev);
            if (Orbital_ButtonState == HIGH) {
                  //stop all motion
                  analogWrite(Linear_ButtonPin,    LOW);
                  analogWrite(Orbital_ButtonPin,   LOW);
                  analogWrite(D_1_ButtonPin,       LOW);
                  analogWrite(D_2_ButtonPin,       LOW);
                  analogWrite(D_3_ButtonPin,       LOW);
                  //digitalWrite(LinearMotor,        LOW); //2
                  //digitalWrite(OrbitalMotor,       LOW); //3
                  // pause 
                  delay(3000);
                  // Zero orbital motor
                  // Remove orbital motor shaft from diameter selction. If it is D1, it will just be zero steps horizontally
                  OrbitalMotor.setSpeed(moderateSpeed);
                  OrbitalMotor.step(-totalOrbitalMotorStepCountFromInitialPosition); 
                  delay(3000);
                  LinearMotor.setSpeed(moderateSpeed);
                  LinearMotor.step(-Y);
                  // Reset timer.
                  TimeStamp = 0;
                  // Exit loop
                  exit(0);
              }  
          }
      }

  
    else if (i == m){ // Double orbital shaking.
      // Set indefinite shaking time.
    
      
      while (TimeStamp > 38000) {
      OrbitalMotor.setSpeed(moderateSpeed);
      OrbitalMotor.step(-totalOrbitalMotorStepCountFromInitialPosition);
      delay(3000);
      LinearMotor.setSpeed(moderateSpeed);
      LinearMotor.step(Y);
      delay(3000);
      LinearMotor.setSpeed(MotorSpeed);
      OrbitalMotor.setSpeed(MotorSpeed);
      LinearMotor.step(X);
      LinearMotor.step(-X);
      OrbitalMotor.step(OrbitalMotorStepPerRev);
        if (Orbital_ButtonState == HIGH || Linear_ButtonState == HIGH) {
            analogWrite(Linear_ButtonPin,    LOW);
            analogWrite(Orbital_ButtonPin,   LOW);
            analogWrite(D_1_ButtonPin,       LOW);
            analogWrite(D_2_ButtonPin,       LOW);
            analogWrite(D_3_ButtonPin,       LOW);
            //digitalWrite(LinearMotor,        LOW);
            //digitalWrite(OrbitalMotor,       LOW);
           
            // pause 
            delay(3000);
            
            // Zero orbital motor
            // Remove orbital motor shaft from diameter selction. If it is D1, it will just be zero steps horizontally
            OrbitalMotor.setSpeed(moderateSpeed);
            OrbitalMotor.step(-totalOrbitalMotorStepCountFromInitialPosition); 
            delay(3000);
            LinearMotor.setSpeed(moderateSpeed);
            LinearMotor.step(-Y);
            
            // Reset timer.
            TimeStamp = 0;
            
            // Exit loop
            exit(0);
          }
      }
  }
  
   //Emergency stop sequence via limit switch detection.
  if (Limit_Switch_OneState == HIGH || Limit_Switch_TwoState == HIGH) {
  analogWrite(Linear_ButtonPin,    LOW);
  analogWrite(Orbital_ButtonPin,   LOW);
  analogWrite(D_1_ButtonPin,       LOW);
  analogWrite(D_2_ButtonPin,       LOW);
  analogWrite(D_3_ButtonPin,       LOW);
  digitalWrite(2,                  LOW);   //Linear Motor
  digitalWrite(3,                  LOW); //Orbital Motor
  digitalWrite(11,                 LOW); //Linear Motor
  digitalWrite(12,                 LOW); //Orbital Motor
  }
}
