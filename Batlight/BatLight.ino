#include <DevMolasses_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

/*Buttons should be driven with a pull-up resistor
 * so the switch should pull the pin to ground momentarily
 * On a high -> low transition, the button press logic will
 * execute
 */
#define BUTTON1_PIN 2
#define BUTTON2_PIN 3

#define PIXEL_PIN 6

#define PIXEL_COUNT 60

DevMolasses_NeoPixel strip = DevMolasses_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool oldState1 = HIGH;
bool oldState2 = HIGH;
int showType = 0;
unsigned long displayTimer;
unsigned long displayTimerLength;
uint16_t index = 0;

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

  //Check if both buttons are pressed
  if (newState1 == LOW && newState2 == LOW) {
    //short delay to debounce buttons
    delay(20);
    //check that both button are still pressed
    newState1 = digitalRead(BUTTON1_PIN);
    newState2 = digitalRead(BUTTON2_PIN);
    if (newState1 == LOW && newState2 == LOW) {
      //Turn the light off
    }
  }
  //Check if button 1 was pressed
  else if (newState1 == LOW && oldState1 == HIGH) {
    delay(20);//Debounce
    newState1 = digitalRead(BUTTON1_PIN);
    if (newState1 == LOW) {
      //cycle through plain effects
    }
  }
  //Check if button 2 was pressed
  else if (newState2 == LOW && oldState2 == HIGH) {
    delay(20);//Debounce
    newState2 = digitalRead(BUTTON2_PIN);
    if (newState2 == LOW) {
      //cycle through special effects
    }
  }
}
