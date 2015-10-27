void displayCase() {
  //Off = 200
  //ButtonA uses 0 - 99
  //ButtonB uses 100-199

  switch(caseNum){
    case 200: colorChange(OFF);
              break;
    case 0:   readingLight();
              break;
    case 1:   nightLight();
              break;
    case 2:   colorChange(Q2_WHITE);
              break;
    case 3:   colorChange(Q3_WHITE);
              break;
    case 100: colorWipe(RED);
              break;
    case 101: colorWipe(ORANGE);
              break;
    case 102: colorWipe(YELLOW);
              break;
    case 103: colorWipe(GREEN);
              break;
    case 104: colorWipe(BLUE);
              break;
    case 105: colorWipe(PURPLE);
              break;
    case 106: fullStripRainbow();
              break;
    case 107: rainbow();
              break;
    case 108: policeEffect();
              break;
  }
}

