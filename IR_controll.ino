#include <IRremote.h>
#include <Servo.h>

// IR 
const int RECV_PIN = 7;
IRrecv IR(RECV_PIN);
decode_results results;

const int hold = 65535;
int key = 0;
bool open = false;

//Motor A
const int motorPin1  = 3; 
const int motorPin2  = 4; 
//Motor B
const int motorPin3  = 6; 
const int motorPin4  = 5; 

Servo A, B, C;


void setup() {

  // IR
  IR.enableIRIn();
  IR.blink13(true);


  //Set pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  
  // Servos
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
      
      case 4335:
        A.write(180);
        B.write(180);
      	break;
      
      case 20655:
        A.write(0);
        B.write(0);
      	break;
      
      case 41055:
      	if (!open) {
          C.write(90);
          open = true;
        } else {
          C.write(180);
          open = false;
        }
      	break;

      case hold:

        if (key == 1) {
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

        if (key == 2) {
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

        if (key == 3) {
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

        if (key == 4) {
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

    IR.resume();
  }
}
