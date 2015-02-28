// original code by by daniel-boersen@hotmail.com (though perhaps he cribbed it from http://arduino.cc/en/Tutorial/ping)
// that got a working bot with 1 sensor
// tom Igoe's original code
// my mashifications to get more sensors and to 'choose' where to go
// and Andre Bellucci's refinements (to reduce repetition)
// consider adding http://arduino.cc/en/Tutorial/Knock for hitting things

#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

// this constant won't change.  It's the pin number
// http://arduino.cc/en/Tutorial/ping says add "const" at beginning
// andrea says that's necessary if we're just wanting to ensure that it can never change
const int trigPinFront = TKD5;
const int echoPinFront = TKD4; 
const int trigPinLeft = TKD2;
const int echoPinLeft = TKD1; 
const int trigPinRight = TKD0;
const int echoPinRight = TKD3; 

const char FRONTSENSOR = 'f'; // way down below when it cites character f use the name FRONTSENSOR
const char RIGHTSENSOR = 'r'; // same but right
const char LEFTSENSOR = 'l'; // same but left

void setup() {
Serial.begin(9600); //donno if I need this to talk to the robot display
Robot.begin(); // wake up robot display on the official arduino robot
Robot.beginTFT(); //turn on the display even more
Robot.beginSD(); // get the mini-SD card warmed up
pinMode(trigPinFront, OUTPUT); 
pinMode(echoPinFront, INPUT); 
pinMode(trigPinLeft, OUTPUT); 
pinMode(echoPinLeft, INPUT); 
pinMode(trigPinRight, OUTPUT); 
pinMode(echoPinRight, INPUT); 
}

//this void ping is where it cycles through each sensor and gets the distance from each sensor to an object
// The PING is triggered by a HIGH pulse of 2 or more microseconds. 
// Give a short LOW pulse beforehand to ensure a clean HIGH pulse: 
void ping(char c){ // the f, r, l constants declared above help to know which sensor we're talking about
  if(c == 'f'){
    Robot.digitalWrite(trigPinFront, LOW);
    delayMicroseconds(2);
    Robot.digitalWrite(trigPinFront, HIGH);
    delayMicroseconds(5);
    Robot.digitalWrite(trigPinFront, LOW);
  }else if(c == 'l'){
    Robot.digitalWrite(trigPinLeft, LOW);
    delayMicroseconds(2);
    Robot.digitalWrite(trigPinLeft, HIGH);
    delayMicroseconds(5);
    Robot.digitalWrite(trigPinLeft, LOW);
  }else if(c == 'r'){
    Robot.digitalWrite(trigPinRight, LOW);
    delayMicroseconds(2);
    Robot.digitalWrite(trigPinRight, HIGH);
    delayMicroseconds(5);
    Robot.digitalWrite(trigPinRight, LOW);
  }
}

void loop() {
  // just sensing the distance and printing it out to the robot screen
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
long durationFront, cmFront, durationLeft, cmLeft, durationRight, cmRight;

ping(FRONTSENSOR); //repeat for each
cmFront = microsecondsToCentimeters(pulseIn(echoPinFront, HIGH));
ping(LEFTSENSOR);
cmLeft = microsecondsToCentimeters(pulseIn(echoPinLeft, HIGH));
ping(RIGHTSENSOR);
cmRight = microsecondsToCentimeters(pulseIn(echoPinRight, HIGH));



// if distance is less than 30 cm on front sensor, turn left 
// OH I GET IT!!! JUST KEEP TURNING LEFT IF IT IS LESS THAN 30 CM 
// AND KEEP GOING FORWARD UNTIL IT IS LESS THAN 30 CM
if(cmFront < 30) { 
Robot.motorsStop();
delay(100); // just giving the machine time to catch up with the code or reverse

// prints distance on the Robot's TFT for direction 
Robot.print(" L ");
Robot.print(cmLeft);
Robot.print(" F ");
Robot.print(cmFront);
Robot.print(" R ");
Robot.print(cmRight);
Robot.print("cm");
Robot.println();

// now check to see which distance is shorter and longer
if (cmLeft > cmRight){ // if objects on left are closer, turn right
Robot.motorsWrite(128, -128); // 128 is the speed of turn
Robot.print(" Turn RIGHT! ");
delay(450); // 450 ms is enough time to turn 90 degrees

}else if(cmLeft < cmRight) // if objects on right are closer, turn left
Robot.motorsWrite(-128, 128); 
Robot.print(" Turn LEFT! ");
delay(450); 
}

else{ // if objects on right are equal, turn 180
// could be }else if(cmLeft == cmRight){ // if objects on right are equal, turn 180
Robot.motorsWrite(128, -128);
Robot.print(" Turn AROUND! "); 
delay(900); // 900 ms is enough time to turn 180 degrees
}

Robot.motorsStop(); // just giving the machine time to catch up with the code or reverse
delay(100);

// go straight for some stupid reason
Robot.motorsWrite(100, 100);
delay(100);
} // end the void()

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
