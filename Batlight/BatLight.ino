#include <DevMolasses_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

/*Buttons should be driven with a pull-up resistor
 * so the switch should pull the pin to ground momentarily
 * On a high -> low transition, the button press logic will
 * execute
 */
const int BUTTON1_PIN = 2;
const int BUTTON2_PIN = 3;

const int PIXEL_PIN = 6;

const int PIXEL_COUNT = 60;

DevMolasses_NeoPixel strip = DevMolasses_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

int caseNum = 200; //initially set to off

//Thees variables are used for using the timer
//which allows the code execution to return to loop()
//to query the buttons
unsigned long displayTimer;
uint16_t index = 0;

//Button timer variables
unsigned long button1Timer;
unsigned long button2Timer;
bool oldState1 = HIGH;
bool oldState2 = HIGH;

//sleep timer
unsigned long sleepTimer;
const unsigned long sleepTimerLength = 3600000UL; //milliseconds

void setup() {
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

  //Check if both buttons are pressed
  if (newState1 == LOW && newState2 == LOW) {
    //short delay to debounce buttons
    delay(20);
    //check that both button are still pressed
    newState1 = digitalRead(BUTTON1_PIN);
    newState2 = digitalRead(BUTTON2_PIN);
    if (newState1 == LOW && newState2 == LOW) {
      caseNum=200;
      buttonPressed = true;
    }
  }
  //Check if button 1 was pressed
  else if (newState1 == LOW && oldState1 == HIGH) {
    delay(20);//Debounce
    newState1 = digitalRead(BUTTON1_PIN);
    if (newState1 == LOW) {
      if (caseNum >= 3) {
        caseNum = 0;
      } else {
        caseNum++;
      }
      buttonPressed = true;
    }
  }
  //Check if button 2 was pressed
  else if (newState2 == LOW && oldState2 == HIGH) {
    delay(20);//Debounce
    newState2 = digitalRead(BUTTON2_PIN);
    if (newState2 == LOW) {
      if (caseNum < 100 || caseNum >= 107) {
        caseNum = 100;
      } else {
        caseNum++;
      }
      buttonPressed = true;
    }
  }

  //reset the sleep timer if a button is pressed.
  if (buttonPressed) sleepTimer = millis();
  
  //turn off lights after one hour of inactivity
  if (millis() - sleepTimer > sleepTimerLength) caseNum = 200;

  //set the lights to the specified caseNum
  displayCase();
}
