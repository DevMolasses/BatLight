#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

/*Buttons should be driven with a pull-up resistor
 * so the switch should pull the pin to ground momentarily
 * On a high -> low transition, the button press logic will
 * execute
 */
const int BUTTON1_PIN = 3;
const int BUTTON2_PIN = 4;

const int PIXEL_PIN = 6;

const int PIXEL_COUNT = 60;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

int caseNum = 200; //initially set to off
byte policeEffectNum = random(0,5);

//Thees variables are used for using the timer
//which allows the code execution to return to loop()
//to query the buttons
unsigned long displayTimer;
uint16_t index = 0;

//Button timer variables
unsigned long buttonTimer1;
unsigned long buttonTimer2;
unsigned long dualButtonTimer;
bool oldState1 = HIGH;
bool oldState2 = HIGH;
bool buttonPressed1 = false;
bool buttonPressed2 = false;
bool dualButtonPressed = false;

//sleep timer
unsigned long sleepTimer;
const unsigned long sleepTimerLength = 3600000UL; //milliseconds

//Color constants
  //Calculated with RGB = R*256*256 + G*256 + B
  const uint32_t FULL_WHITE = 16777215; //R 255, G 255, B 255
  const uint32_t Q3_WHITE = 12566463; //R 191, G 191, B 191
  const uint32_t Q2_WHITE = 8355711; //R 127, G 127, B 127
  const uint32_t Q1_WHITE = 4144959; //R 63, G 63, B 63
  const uint32_t OFF = 0; //R 0, G 0, B 0
  const uint32_t RED = 16711680; //R 255, G 0, B 0
  const uint32_t ORANGE = 16744192; //R 255, G 123, B 0
  const uint32_t YELLOW = 16776960; //R 255, G 255, B 0
  const uint32_t GREEN = 65280; //R 0, G 255, B 0
  const uint32_t TEAL = 65535; //R 0, G 255, B 255
  const uint32_t BLUE = 255; //R 0, G 0, B 255
  const uint32_t PURPLE = 8323327; //R 123, G 0, B 255
  
void setup() {
  Serial.begin(9600);
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  strip.begin();
  strip.show();
}

void loop() {
  //Get current button states
  bool newState1 = digitalRead(BUTTON1_PIN);
  bool newState2 = digitalRead(BUTTON2_PIN);
  bool buttonPressed = false;

//------------ Start of Button 1 -------------
  if (newState1 == LOW && oldState1 == HIGH) {
    buttonTimer1 = millis();
    buttonPressed1 = true;
  }
  
  if (newState1 == LOW && oldState1 == LOW && buttonPressed1 && 
      millis() - buttonTimer1 > 20UL && !buttonPressed2) {
    if (caseNum >= 3) {
        caseNum = 0;
      } else {
        caseNum++;
      }
      buttonPressed = true;
      buttonPressed1 = false;
  }
//------------- End of Button 1 --------------


//  //Check if button 1 was pressed
//  else if (newState1 == LOW && oldState1 == HIGH) {
//    delay(20);//Debounce
//    newState1 = digitalRead(BUTTON1_PIN);
//    if (newState1 == LOW) {
//      if (caseNum >= 3) {
//        caseNum = 0;
//      } else {
//        caseNum++;
//      }
//      buttonPressed = true;
//    }
//  }

//------------ Start of Button 2 -------------
  if (newState2 == LOW && oldState2 == HIGH) {
    buttonTimer2 = millis();
    buttonPressed2 = true;
  }

  if (newState2 == LOW && oldState2 == LOW && buttonPressed2 && 
      millis() - buttonTimer2 > 20UL && !buttonPressed1) {
    if (caseNum < 100 || caseNum >= 108) {
        caseNum = 100;
      } else {
        caseNum++;
      }
      buttonPressed = true;
      buttonPressed2 = false;
  }
//------------- End of Button 2 --------------

//  //Check if button 2 was pressed
//  else if (newState2 == LOW && oldState2 == HIGH) {
//    delay(20);//Debounce
//    newState2 = digitalRead(BUTTON2_PIN);
//    if (newState2 == LOW) {
//      if (caseNum < 100 || caseNum >= 107) {
//        caseNum = 100;
//      } else {
//        caseNum++;
//      }
//      buttonPressed = true;
//    }
//  }

//----------- Start of dual buttons ----------
  if (newState1 == LOW && newState2 == LOW && 
      (oldState1 == HIGH || oldState2 == HIGH)) {
    dualButtonTimer = millis();
    dualButtonPressed = true;
  }

  if (newState1 == LOW && newState2 == LOW &&
      oldState1 == LOW && oldState2 == LOW &&
      dualButtonPressed && millis() - dualButtonTimer > 2000UL) {
    caseNum=200;
  }
//------------ End of dual buttons -----------

//  //Check if both buttons are pressed
//  if (newState1 == LOW && newState2 == LOW) {
//    //short delay to debounce buttons
//    delay(20);
//    //check that both button are still pressed
//    newState1 = digitalRead(BUTTON1_PIN);
//    newState2 = digitalRead(BUTTON2_PIN);
//    if (newState1 == LOW && newState2 == LOW) {
//      caseNum=200;
//      buttonPressed = true;
//    }
//  }

  
  //reset the sleep timer if a button is pressed.
  if (buttonPressed) sleepTimer = millis();
  
  //turn off lights after one hour of inactivity
  if (millis() - sleepTimer > sleepTimerLength) caseNum = 200;
  
  oldState1 = newState1;
  oldState2 = newState2;
  //set the lights to the specified caseNum
  displayCase();
}
