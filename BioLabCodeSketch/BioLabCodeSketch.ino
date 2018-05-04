/*
 * Runs the Solids Handler bot
 * 
 * Connections:
 * First solid dispenser servo control pin: 7
 * Second solid dispenser servo control pin: 8
 * Dump Tray servo control pin: 9
 * 
 * Uses a PD control strategy to control flow rate
 */


// TODO: Import relevant libraries for reading scale
#include <Servo.h>
int firstServoPin = 7;
Servo firstServo;
int secondServoPin = 8;
Servo secondServo;
int dumpTrayServo = 9;
Servo currentServo;
int servoUsed = 1;
String readString;

// CHANGE THIS PARAMETER TO CONTROL FLOW RATE AND TOLERANCE
int P = 10;
int D = 10;
float epsilon = 0.03;

int readScale() {
  // TODO: Make this actually call a function that returns the reading from the scale. Also correct the return type.
  return 100;
}

/*
 * Switches the servo being used from the first to the second, and vice versa
 */
void switchServo() {
  if (currentServo == firstServo) {
    currentServo = secondServo;
  } else {
    currentServo = firstServo;
  }
}

/*
 * Sets the flow rate of a given servo. TODO: use different functions to map input values linearly to flow rates. 
 */
 void setFlowRate(Servo servo, double flowRate) {
    // Set the servo to some position, probably dependent on some f(flowRate) --> actual servo position, from 0 to 180 degrees. 
 }


/*
 * Dispenses a given amount of solids onto the scale, as accurately as it can
 */
void dispenseSolid(int servo, int amount) {
  
  // Will calculate an approximation of the derivative by using the old scale value, keeping track of the previous timesteps
  int oldReading = readScale();
  int bias = oldReading();
  int newReading;
  int difference;
  int oldTime = millis();
  int newTime;
  int timeDifference = 0;
  int error;
  int currentFlowRate = 0;
  float derivative;
  // Goes through a loop of checking the scale reading, opening or closing the things as a 
  while (true) {
     newReading = readScale();
     difference = newReading - oldReading;
     error = amount - newReading + bias;

     if (error < epsilon) {
      break;
     }
     newTime = millis();
     
     timeDifference = newTime - oldTime;

     // Approximation of the derivative of mass / time
     derivative = difference / (float) timeDifference;

     currentFlowRate += error * P + derivative * D;
     setFlowRate(currentServo, currentFlowRate);
     

     oldReading = newReading;
     oldTime = newTime;
  }
}


void setup() {
  // put your setup code here, to run once:

  // Start the Serial communications
  Serial.begin(9600);

  // Attach code to 
  firstServo.attach(firstServoPin);
  secondServo.attach(secondServoPin);
  currentServo = firstServo;

  
  
}






void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {

 
    // Allows buffer to fill.
    delay(3);
    while (Serial.available() > 0) {
      char c = Serial.read();
      readString += c;
    }

    // At this point, readString contains the message that was sent by the laptop

    // If a message was sent to tell it to switch, then switch which servo is being used
    if (readString == "switch") {
      switchServo();

    // Otherwise, assume that it's a valid input, and then convert the string to a number which represents how much you want dispensed. 
    } else {
      // Current format: line contains only the number, which contains how many grams are to be dispensed.
      int amount = readString.toInt();
      dispenseSolid(currentServo., amount);
    }
  }
}
