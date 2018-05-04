

#include <Servo.h>
int firstServoPin = 7;
Servo firstServo;
int secondServoPin = 8;
Servo secondServo;
int dumpTrayServo = 9;
int currentServer;
String readString;

int readScale() {
  // TODO: Make this actually call a function that returns the reading from the scale. Also correct the return type.
  return 100;
}


void switchServo() {
  // Switches the servo being used from the first to the second
  if (currentServo == firstServo) {
    currentServo = secondServo;
  } else {
    currentServo = firstServo;
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



void dispenseSolid(int servo, int amount) {
  // Dispenses solids, of a given amount.

  // Will calculate an approximation of the derivative by using the old scale value
  int oldReading = readScale();
  int newReading = readScale();
  int difference;
  int oldTime = time.millis();
  int newTime = time.millis();
  int timeDifference = 0;
  // Goes through a loop of checking the scale reading, opening or closing the things as a 
  while (true) {
     newReading = readScale();
     difference = newREading - oldReading;
     newTime= 
  }
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
