/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Vikash/Downloads/Lab13/src/Lab13.ino"
/*
 * Project Lab13
 * Description:
 * Author:
 * Date:
 */
void isr();
void setup();
void loop();
#line 7 "c:/Users/Vikash/Downloads/Lab13/src/Lab13.ino"
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
volatile bool interruptOccured = false; //must be declared volatile if used inside an isr.
uint16_t count = 0;                     // count
uint16_t count2 = 1;                    // count for num times pressed
#include "oled-wing-adafruit.h"
OledWingAdafruit display;
// setup() runs once, when the device is first turned on.
void isr()
{
  // your interrupt handler code here
  interruptOccured = true;
}
void setup()
{
  // Put initialization like pinMode and begin functions here.
  pinMode(D6, INPUT_PULLUP);         // defaults to HIGH
  pinMode(D7, INPUT);         // defaults to HIGH
  attachInterrupt(D6, isr, FALLING); // D6 will now generate an interrupt on the falling edge and will run the code in the isr
  display.setup();
  display.clearDisplay();
  display.setTextSize(1);
  
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.display();
  Serial.begin(9600);
}
bool press = false;
// loop() runs over and over again, as quickly as it can execute.
void loop()
{
 
  display.loop(); // this needs to be called each time loop is run
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  bool value = false;  // button true or false
  bool value2 = false; // button true or false
  
  value2 = digitalRead(D7);
  value = digitalRead(D6); // reads the button either true or false
 
  if (interruptOccured)
  {
       count++;
       display.print(count);
       display.display();
       interruptOccured = false;
       delay(1000);  // do some longer processing here
    
  }
  if(value2 == 0){
    if(press==true){
      interrupts(); // enables interrupt handling
      press = false;
      Serial.println("in the true");
      delay(1000);
    }
    else{
      noInterrupts();
      press = true;
      Serial.println();
      Serial.println("in the false");
      delay(1000);
    }
    
  }
  // if(value2 == false && press == true){
  //   noInterrupts();
  //   press = false;
  // }
  // if(value2 == false && press == false){
  //   interrupts(); // enables interrupt handling
  //   press = true;
  // }
  
  
  // if(value2 == true && press == true){
  //   noInterrupts(); // disables interrupt handling
  //   press = false;
  // }
  // if(value2 == true && press == false){
  //   interrupts(); // enables interrupt handling
  //   press = true;
  // }
}


// if (value2 == true && (count2 % 2 != 0))
//         {
//           count2++;
//           display.print(count);
//           display.display();
//           delay(1000);
//           noInterrupts(); // disables interrupt handling
//         }
//         if (value2 == true && (count2 % 2 == 0))
//         {
//           count2++;
//           count++;
//           display.println(count);
//           display.display();
//           delay(1000);
//           interrupts(); // enables interrupt handling
//         }