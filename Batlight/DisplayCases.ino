void displayCase() {
  //Off = 200
  //ButtonA uses 0 - 99
  //ButtonB uses 100-199

  switch(caseNum){
    case 200: colorChange(strip.OFF);
              break;
    case 0:   readingLight();
              break;
    case 1:   nightLight();
              break;
    case 2:   colorChange(strip.Q2_WHITE);
              break;
    case 3:   colorChange(strip.Q3_WHITE);
              break;
    case 100: colorWipe(strip.RED);
              break;
    case 101: colorWipe(strip.ORANGE);
              break;
    case 102: colorWipe(strip.YELLOW);
              break;
    case 103: colorWipe(strip.GREEN);
              break;
    case 104: colorWipe(strip.BLUE);
              break;
    case 105: colorWipe(strip.PURPLE);
              break;
    case 106: fullStripRainbow();
              break;
    case 107: rainbow();
              break;
  }
}

