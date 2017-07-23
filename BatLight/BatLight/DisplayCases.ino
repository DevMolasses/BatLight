#include <Arduino.h>

void displayCase() {
  //Off = 200
  //ButtonA uses 0 - 99
  //ButtonB uses 100-199

  switch (caseNum) {
    case 200: colorChange(OFF); break;
    case 0:   colorChange(FULL_WHITE); break;
    case 1:   colorChange(Q1_WHITE); break;
    case 2:   colorChange(Q2_WHITE); break;
    case 3:   colorChange(Q3_WHITE); break;
    case 4:   colorWipe(RED); break;
    case 5:   colorWipe(ORANGE); break;
    case 6:   colorWipe(YELLOW); break;
    case 7:   colorWipe(GREEN); break;
    case 8:   colorWipe(BLUE); break;
    case 9:   colorWipe(PURPLE); break;
    case 100: fullStripRainbow(); break;
    case 101: rainbow(); break;
    case 102: policeEffect(); break;
    case 103: pixelScrolling(); break;
    case 104: rainbowCycle(); break;
    case 105: whiteStrobe(); break;
    case 106: randomColorStrobe(); break;
    case 107: theaterChaseWhite(); break;
    case 108: theaterChaseRainbow(); break;
  }
}

