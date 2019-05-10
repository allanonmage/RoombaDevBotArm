//
// This was developed with Arduino 1.0.2 // used in 1.0.0 seems OK DCW 12-28-2012
// USB_Host_Shield_2.0 from Circuits@home
// PS3 USB library - developed by Kristian Lauszus  http://blog.tkjelectronics.dk/ 
//

// This code block is from PS3 example program
// #include <PS3USB.h>
#include <PS3BT.h>
#include <AFMotor.h>
USB Usb;
BTD Btd(&Usb);
/* You can create the instance of the class in two ways */
//PS3USB PS3(&Usb); // This will just create the instance
//PS3USB PS3(&Usb,0x00,0x15,0x83,0x3D,0x0A,0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch
PS3BT PS3(&Btd,0x00,0x1B,0xDC,0x00,0x3D,0x58); // Cirago tiny BT adapter
boolean printAngle;
uint8_t state = 0;
// end ps3 example program

int rxPin = 19;
int txPin = 18;
int ddPin = 24;
int ledPin = 13;
bool goingForward = false;
bool goingBack = false;
bool goingLeft = false;
bool goingRight = false;

boolean first = true;

AF_DCMotor motor1(1);  // Instantiate all the motors
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
int val0 = 0;           // variable to store the Arm 1 sensor
int val1 = 0;           // variable to store the Arm 2 sensor
int val2 = 0;           // variable to store the Arm 3 sensor
int val3 = 0;           // variable to store the Arm 4 sensor

boolean armMode = false; // semaphore for analog control of the arm


void setup(){
  pinMode(ddPin,  OUTPUT);   // sets the pins as output
  pinMode(ledPin, OUTPUT);   // sets the pins as output
  Serial1.begin(57600);
  Serial.begin(115200);
  
  // This is here for on reset to put the Roomba back to passive mode so it can be woken up again.
  // Allows for an arduino reboot to reset the Roomba if a sensor tripped.
  Serial1.write(byte(130));
  delay(50);

  // PS3 stuff
  // Serial.begin(115200);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while(1); //halt
  }  
  Serial.println(F("\r\nPS3 USB Library Started"));

  // wake up the roomba
  digitalWrite(ddPin, HIGH);
  delay(100);
  digitalWrite(ddPin, LOW);
  delay(500);
  digitalWrite(ddPin, HIGH);
  delay(2000);
  // set up ROI to receive commands  
  //Serial1.print(128, BYTE);  // START
  Serial1.write(byte(128));
  delay(50);
  //Serial1.print(130, BYTE);  // CONTROL
  Serial1.write(byte(130));
  delay(50);
  digitalWrite(ledPin, LOW);  // say we've finished setup

} // end setup


void loop(){
  Usb.Task();
  
  if (first){
    Serial.println("First entry into the loop, ready for action!!");
    goForward();
    delay(100);
    goStop();
    first = false;
    digitalWrite(ledPin, HIGH);
  } // end first
    
    if(Serial.available()){
     int inVal = Serial.parseInt();
     if (inVal == 0){
         motor1.setSpeed(0);       // turn off motors
         motor2.setSpeed(0);   
         motor3.setSpeed(0);    
         motor4.setSpeed(0);
     } // end if
     
     if (inVal == 1){ // motor 1 forward
        motor1.setSpeed(200);     // set the speed to 100/255
        motor1.run(FORWARD);
        delay(250);
        motor1.setSpeed(0);
     } // end if
     
     if (inVal == 2){ // motor 1 backward
        motor1.setSpeed(200);     // set the speed to 100/255
        motor1.run(BACKWARD);
        delay(250);
        motor1.setSpeed(0);
     } // end if
     
     if (inVal == 3){ // motor 2 forward
        motor2.setSpeed(200);     // set the speed to 100/255
        motor2.run(FORWARD);
        delay(250);
        motor2.setSpeed(0);
     } // end if
     
     if (inVal == 4){ // motor 2 backward
        motor2.setSpeed(200);     // set the speed to 100/255
        motor2.run(BACKWARD);
        delay(250);
        motor2.setSpeed(0);
     } // end if
     
     if (inVal == 5){ // motor 3 forward
        motor3.setSpeed(200);     // set the speed to 100/255
        motor3.run(FORWARD);
        delay(250);
        motor3.setSpeed(0);
     } // end if
     
     if (inVal == 6){ // motor 3 backward
        motor3.setSpeed(200);     // set the speed to 100/255
        motor3.run(BACKWARD);
        delay(250);
        motor3.setSpeed(0);
     } // end if
     
     if (inVal == 7){ // motor 4 forward
        motor4.setSpeed(200);     // set the speed to 100/255
        motor4.run(FORWARD);
        delay(250);
        motor4.setSpeed(0);
     } // end if
     
     if (inVal == 8){ // motor 4 backward
        motor4.setSpeed(200);     // set the speed to 100/255
        motor4.run(BACKWARD);
        delay(250);
        motor4.setSpeed(0);
     } // end if
    } // end keyboard input

    if(PS3.getButtonClick(SELECT)) {
        Serial.println("SELECT Press registered");
        
        if(armMode){
          armMode = false;
          PS3.setLedOff(LED5);
          Serial.println("ArmMode disengaged");
        }
        else{
          PS3.setLedOn(LED6);
          armMode = true;
          Serial.println("ArmMode engaged!!");
        }
      }
      
      if(armMode){
               
        if(PS3.getAngle(Roll) < 150){ // move motor 1 left
          Serial.println(PS3.getAngle(Roll));
          motor1.setSpeed(255);     // set the speed to 100/255
          motor1.run(BACKWARD);
          delay(5);
          motor1.setSpeed(0);
        } // end left
        
        if(PS3.getAngle(Roll) > 210){ // move motor 2 right
          Serial.println(PS3.getAngle(Roll));
          motor1.setSpeed(255);     // set the speed to 100/255
          motor1.run(FORWARD);
          delay(5);
          motor1.setSpeed(0);
        } // end right
        
        if(PS3.getAngle(Pitch) < 150){ // move motor 2 up
          Serial.println(PS3.getAngle(Pitch));
          motor2.setSpeed(255);     // set the speed to 100/255
          motor2.run(FORWARD);
          delay(5);
          motor2.setSpeed(0);
        } // end up
        
        if(PS3.getAngle(Pitch) > 210){ // move motor 2 down
          Serial.println(PS3.getAngle(Pitch));
          motor2.setSpeed(255);     // set the speed to 100/255
          motor2.run(BACKWARD);
          delay(5);
          motor2.setSpeed(0);
        } // end down
        
        if(PS3.getAnalogHat(LeftHatY) < 117){ // move motor 3 up
          Serial.println(PS3.getAnalogHat(LeftHatY));
          motor3.setSpeed(255);     // set the speed to 100/255
          motor3.run(FORWARD);
          delay(5);
          motor3.setSpeed(0);
        } // end
        
        if(PS3.getAnalogHat(LeftHatY) > 138){ // move motor 3 down
          Serial.println(PS3.getAnalogHat(LeftHatY));
          motor3.setSpeed(255);     // set the speed to 100/255
          motor3.run(BACKWARD);
          delay(5);
          motor3.setSpeed(0);
        } // end
        
        if(PS3.getAnalogHat(RightHatY) < 117){ // move motor 4 up
          Serial.println(PS3.getAnalogHat(LeftHatY));
          motor4.setSpeed(255);     // set the speed to 100/255
          motor4.run(FORWARD);
          delay(5);
          motor4.setSpeed(0);
        } // end
        
        if(PS3.getAnalogHat(RightHatY) > 138){ // move motor 4 down
          Serial.println(PS3.getAnalogHat(LeftHatY));
          motor4.setSpeed(255);     // set the speed to 100/255
          motor4.run(BACKWARD);
          delay(5);
          motor4.setSpeed(0);
        } // end
        
        
        
      } // end armmode
      


    
    if(PS3.getButtonPress(UP)) {
      Serial.println("Up Press registered");
      if(!goingForward){
        goForward();
        goingForward = true;
        PS3.setAllOff();
        PS3.setLedOn(LED1);
        } //
      }
    if(!PS3.getButtonPress(UP)) {
      if(goingForward){
        goStop();
        goingForward = false;
      }
      }
      
    if(PS3.getButtonPress(DOWN)) {
      if(!goingBack){
        goBackward();
        goingBack = true;
        PS3.setAllOff();
        PS3.setLedOn(LED2);
      }
    }

    if(!PS3.getButtonPress(DOWN)) {
      if(goingBack){
        goStop();
        goingBack = false;
      }
    }
    
    if(PS3.getButtonPress(LEFT)) {
      if(!goingLeft){
        spinLeft();
        goingLeft = true;
        PS3.setAllOff();
        PS3.setLedOn(LED3);
      }
    }

    if(!PS3.getButtonPress(LEFT)) {
      if(goingLeft){
        goStop();
        goingLeft = false;
      }
    }
    
    if(PS3.getButtonPress(RIGHT)) {
      if(!goingRight){
        spinRight();
        goingRight = true;
        PS3.setAllOff();
        PS3.setLedOn(LED4);
      }
    }

    if(!PS3.getButtonPress(RIGHT)) {
      if(goingRight){
        goStop();
        goingRight = false;
      }
    }
    
    
  
} // end loop

void goForward() {
  /*
  Serial1.print(137, BYTE);   // DRIVE
  Serial1.print(0x00,BYTE);   // 0x00c8 == 200
  Serial1.print(0xc8,BYTE);
  Serial1.print(0x80,BYTE);
  Serial1.print(0x00,BYTE);
  */
  //Serial.println("Forward");
  Serial1.write(byte(137));
  Serial1.write(byte(0x00));
  Serial1.write(byte(0xc8));
  Serial1.write(byte(0x80));
  Serial1.write(byte(0x00));
}
void goBackward() {
  /*
  Serial1.print(137, BYTE);   // DRIVE
  Serial1.print(0xff,BYTE);   // 0xff38 == -200
  Serial1.print(0x38,BYTE);
  Serial1.print(0x80,BYTE);
  Serial1.print(0x00,BYTE);
  */
  Serial1.write(byte(137));
  Serial1.write(byte(0xff));
  Serial1.write(byte(0x38));
  Serial1.write(byte(0x80));
  Serial1.write(byte(0x00));
}
void spinLeft() {
  /*
  Serial1.print(137, BYTE);   // DRIVE
  Serial1.print(0x00,BYTE);   // 0x00c8 == 200
  Serial1.print(0xc8,BYTE);
  Serial1.print(0x00,BYTE);
  Serial1.print(0x01,BYTE);   // 0x0001 == spin left
  */
  Serial1.write(byte(137));
  Serial1.write(byte(0x00));
  Serial1.write(byte(0xc8));
  Serial1.write(byte(0x00));
  Serial1.write(byte(0x01));
}
void spinRight() {
  /*
  Serial1.print(137, BYTE);   // DRIVE
  Serial1.print(0x00,BYTE);   // 0x00c8 == 200
  Serial1.print(0xc8,BYTE);
  Serial1.print(0xff,BYTE);
  Serial1.print(0xff,BYTE);   // 0xffff == -1 == spin right
  */
  Serial1.write(byte(137));
  Serial1.write(byte(0x00));
  Serial1.write(byte(0xc8));
  Serial1.write(byte(0xff));
  Serial1.write(byte(0xff));
}

void goStop() {
  /*
  Serial1.print(137, BYTE);   // DRIVE
  Serial1.print(0x00,BYTE);   // 
  Serial1.print(0x00,BYTE);
  Serial1.print(0x00,BYTE);
  Serial1.print(0x00,BYTE);   // 
  Serial.println("Stop");
  */
  Serial1.write(byte(137));
  Serial1.write(byte(0x00));
  Serial1.write(byte(0x00));
  Serial1.write(byte(0x00));
  Serial1.write(byte(0x00));
}
