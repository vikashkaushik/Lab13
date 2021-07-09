/*
 * Project Lab13
 * Description: press buttons based on interrupts
 * Author: Vikash Kaushik
 * Date: 7/9/21
 */
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
bool press = false; // if interrupt button is pressed
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
  // connected to D6
  if (interruptOccured)
  {
       count++;
       display.print(count);
       display.display();
       interruptOccured = false;
       delay(1000);  // do some longer processing here
    
  }
  // if interrup t button is pressed first time it will go into tbe false, then true, and keep switching
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

}


