/*

It look me a while to figure out how to use IR buttons
as push buttons (hold down for function, release to stop).
Every key sends the same hex code when held down, which
was a pain. The solution, simply put is to set a variable
equal to the last hex sent, and then run the corresponding
code when the "button held" hex is detected. It's quite a 
roundabout method, but that's the only way it worked for me.

*/

#include <IRremote.h>
#include <Servo.h>

// IR 
const int RECV_PIN = 7;
IRrecv IR(RECV_PIN);
decode_results results;

const int hold = 65535;
int key = 0;
bool open = false;

// Motor A
const int motorPin1  = 3; 
const int motorPin2  = 4; 
// Motor B
const int motorPin3  = 6; 
const int motorPin4  = 5; 

// Servos
Servo A, B, C;


void setup() {

  IR.enableIRIn();
  IR.blink13(true);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  
  A.attach(8);
  B.attach(9);
  C.attach(10);

  Serial.begin(9600);
}


void loop() {

  if (IR.decode(&results)) {
    unsigned int value = results.value;
    Serial.println(value);
    switch (value) {
      case 34935:
        key = 1;
        break;
      case 10455:
        key = 2;
        break;
      case 26775:
        key = 3;
        break;
      case 39015:
        key = 4;
        break;
      case 4335:    // hand position 1
        A.write(180);
        B.write(180);
      	break;
      case 20655:   // hand position 2
        A.write(0);
        B.write(0);
      	break;
      case 41055:   // open/close door
      	if (!open) {
          C.write(90);
          open = true;
        } else {
          C.write(180);
          open = false;
        }
      	break;
      case hold:

        if (key == 1) { // go forward
          digitalWrite(motorPin1, HIGH);
          digitalWrite(motorPin2, LOW);
          digitalWrite(motorPin3, HIGH);
          digitalWrite(motorPin4, LOW);
          delay(500);
          digitalWrite(motorPin1, LOW);
          digitalWrite(motorPin2, LOW);
          digitalWrite(motorPin3, LOW);
          digitalWrite(motorPin4, LOW);
        }
        
        if (key == 2) { // go left
          digitalWrite(motorPin1, LOW);
          digitalWrite(motorPin2, HIGH);
          digitalWrite(motorPin3, HIGH);
          digitalWrite(motorPin4, LOW);
          delay(500);
          digitalWrite(motorPin1, LOW);
          digitalWrite(motorPin2, LOW);
          digitalWrite(motorPin3, LOW);
          digitalWrite(motorPin4, LOW);
        }

        if (key == 3) { // go right
          digitalWrite(motorPin1, HIGH);
          digitalWrite(motorPin2, LOW);
          digitalWrite(motorPin3, LOW);
          digitalWrite(motorPin4, HIGH);
          delay(500);
          digitalWrite(motorPin1, LOW);
          digitalWrite(motorPin2, LOW);
          digitalWrite(motorPin3, LOW);
          digitalWrite(motorPin4, LOW);
        }

        if (key == 4) { // go backward
          digitalWrite(motorPin1, LOW);
          digitalWrite(motorPin2, HIGH);
          digitalWrite(motorPin3, LOW);
          digitalWrite(motorPin4, HIGH);
          delay(500);
          digitalWrite(motorPin1, LOW);
          digitalWrite(motorPin2, LOW);
          digitalWrite(motorPin3, LOW);
          digitalWrite(motorPin4, LOW);
        }
        break;
        
      default:
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, LOW);
    }
    IR.resume(); // get input
  }
}
