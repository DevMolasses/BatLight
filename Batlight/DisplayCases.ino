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
    case 100: displayTimerLength = 50UL;
              displayTimer = millis();
              colorWipe(strip.RED);
              break;
    case 101: displayTimerLength = 50UL;
              displayTimer = millis();
              colorWipe(strip.ORANGE);
              break;
    case 102: displayTimerLength = 50UL;
              displayTimer = millis();
              colorWipe(strip.YELLOW);
              break;
    case 103: displayTimerLength = 50UL;
              displayTimer = millis();
              colorWipe(strip.GREEN);
              break;
    case 104: displayTimerLength = 50UL;
              displayTimer = millis();
              colorWipe(strip.BLUE);
              break;
    case 105: displayTimerLength = 50UL;
              displayTimer = millis();
              colorWipe(strip.PURPLE);
              break;
    case 106: fullStripRainbow(50);
              break;
    case 107: rainbow(50);
              break;
  }
}

