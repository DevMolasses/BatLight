void colorChange(uint32_t color) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

//void colorWipe(uint32_t color, uint8_t wait) {
//  for (uint16_t i = 0; i < strip.numPixels(); i++) {
//    strip.setPixelColor(i, color);
//    strip.show();
//    delay(wait);
//  }
//}

void colorWipe(uint32_t color) {
  if (millis() - displayTimer > 50UL) {
    displayTimer = millis(); //reset timer to start over
    if (index >= strip.numPixels()) index = 0; //verify the index is in range
    strip.setPixelColor(index, color); //change the pixel color
    strip.show();
    index++;
  }
}

void nightLight() {
  colorChange(Q1_WHITE);
}

void readingLight() {
  colorChange(FULL_WHITE);
}

void strobeLight(uint32_t color) {
  unsigned long curMillis = millis();
  if (curMillis - displayTimer > 70UL && curMillis - displayTimer <= 100UL) {
    colorChange(color);
  } else if (millis() - displayTimer > 100UL)
  {
    colorChange(OFF);
    displayTimer = millis();
  }
}

/*
* Cycles each pixel through the colors individually
* Each pixel is 1 degree of the wheel from its neighboring pixel
* Credit to Adafruit.com for the algorithm; edited by DevMolasses
*/
void rainbow() {
  if (millis() - displayTimer > 50UL) {
    displayTimer = millis();
    if (index >= 360) index = 0;
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i + index) % 360), 1, 1));
    }
    strip.show();
  }
}

/*
* This method will cycle all the pixels simultaneously
* through all the colors of DevMolasses Wheel
*/
//void fullStripRainbow(uint8_t wait) {
//  for (int hue = 0; hue < 360; hue++) {
//    colorChange(Wheel(hue, 1, 1));
//    delay(wait);
//  }
//}

void fullStripRainbow() {
  if (millis() - displayTimer > 50UL) {
    displayTimer = millis();
    if (index >= 360) index = 0;
    colorChange(Wheel(index, 1, 1));
    index++;
  }
}

//Randomly cycles through various police effects.  Changes every 30 seconds.

void policeEffect() {
  //Divide the lights into 4 sections
  //2 Red and 2 Blue

  unsigned long curLoopTime;

  if (millis() - displayTimer > 30000UL) {
    displayTimer = millis();
    policeEffectNum = random(0, 5);
  }
  switch (policeEffectNum) {

    //All Red Then All Blue, back and forth
    case 0:
      curLoopTime = (millis() - displayTimer) % 1000;
      if (curLoopTime <= 50UL)
        changeAllSections(0, 0, 0, 0);
      else if (curLoopTime > 50UL && curLoopTime <= 500UL)
        changeAllSections(1, 1, 0, 0);
      else if (curLoopTime > 500UL && curLoopTime <= 550UL)
        changeAllSections(0, 0, 0, 0);
      else if (curLoopTime > 550UL && curLoopTime <= 1000UL)
        changeAllSections(0, 0, 1, 1);
      break;

    //Double Red then Double Blue
    case 1:
      curLoopTime = (millis() - displayTimer) % 1000;
      if (curLoopTime <= 50UL)
        changeAllSections(0, 0, 0, 0);
      else if (curLoopTime > 50UL && curLoopTime <= 250UL)
        changeAllSections(1, 1, 0, 0);
      else if (curLoopTime > 250UL && curLoopTime <= 300UL)
        changeAllSections(0, 0, 0, 0);
      else if (curLoopTime > 300UL && curLoopTime <= 500UL)
        changeAllSections(1, 1, 0, 0);
      else if (curLoopTime > 500UL && curLoopTime <= 550UL)
        changeAllSections(0, 0, 0, 0);
      else if (curLoopTime > 550UL && curLoopTime <= 750UL)
        changeAllSections(0, 0, 1, 1);
      else if (curLoopTime > 750UL && curLoopTime <= 800UL)
        changeAllSections(0, 0, 0, 0);
      else if (curLoopTime > 800UL && curLoopTime <= 1000UL)
        changeAllSections(0, 0, 1, 1);
      break;

    //Half Red & Blue then other Half of both
    case 2:
      curLoopTime = (millis() - displayTimer) % 1000;
      if (curLoopTime <= 50UL)
        changeAllSections(0, 0, 0, 0);
      else if (curLoopTime > 50UL && curLoopTime <= 500UL)
        changeAllSections(1, 0, 1, 0);
      else if (curLoopTime > 500UL && curLoopTime <= 550UL)
        changeAllSections(0, 0, 0, 0);
      else if (curLoopTime > 550UL && curLoopTime <= 1000UL)
        changeAllSections(0, 1, 0, 1);
      break;

    //Half Red & Blue then other Half of both double flash
    case 3:
      curLoopTime = (millis() - displayTimer) % 1000;
      if (curLoopTime <= 50UL)
        changeAllSections(0, 0, 0, 0);
      else if (curLoopTime > 50UL && curLoopTime <= 250UL)
        changeAllSections(1, 0, 1, 0);
      else if (curLoopTime > 250UL && curLoopTime <= 300UL)
        changeAllSections(0, 0, 0, 0);
      else if (curLoopTime > 300UL && curLoopTime <= 500UL)
        changeAllSections(1, 0, 1, 0);
      else if (curLoopTime > 500UL && curLoopTime <= 550UL)
        changeAllSections(0, 0, 0, 0);
      else if (curLoopTime > 550UL && curLoopTime <= 750UL)
        changeAllSections(0, 1, 0, 1);
      else if (curLoopTime > 750UL && curLoopTime <= 800UL)
        changeAllSections(0, 0, 0, 0);
      else if (curLoopTime > 800UL && curLoopTime <= 1000UL)
        changeAllSections(0, 1, 0, 1);
      break;

    case 4:
      curLoopTime = (millis() - displayTimer) % 300;
      if (curLoopTime <= 100UL)
        policeChase(0);
      else if (curLoopTime > 100UL && curLoopTime <= 200UL)
        policeChase(1);
      else if (curLoopTime > 200UL && curLoopTime <= 300UL)
        policeChase(2);
  }
  strip.show();
}

//Define the sections
uint16_t red1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
const byte numRed1 = sizeof(red1) / sizeof(uint16_t);
uint16_t red2[] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
const byte numRed2 = sizeof(red2) / sizeof(uint16_t);
uint16_t blue1[] = {31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45};
const byte numBlue1 = sizeof(blue1) / sizeof(uint16_t);
uint16_t blue2[] = {46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60};
const byte numBlue2 = sizeof(blue2) / sizeof(uint16_t);

void changeAllSections(byte r1, byte r2, byte b1, byte b2) {
  changeSection(red1, r1);
  changeSection(red2, r2);
  changeSection(blue1, b1);
  changeSection(blue2, b2);
}

void changeSection(uint16_t section[], byte state) {
  uint32_t color;
  if (state = 0) {
    color = OFF;
  } else if (state = 1) {
    color = RED;
  } else return;
  for (int i = 0; i < sizeof(section) - 1; i++) {
    strip.setPixelColor(i, color);
  }
}

void policeChase(byte p) {
  //Merge the sorted arrays
  byte i, j, k;

  uint16_t red[numRed1 + numRed2];
  j = 0; k = 0;
  for (i = 0; i < numRed1 + numRed2; i++) {
    if (k == numRed2 || (j < numRed1 && red1[j] < red2[k])) {
      red[i] = red1[j];
      j++;
    } else {
      red[i] = red2[k];
      k++;
    }
  }
  uint16_t blue[numBlue1 + numBlue2];
  j = 0; k = 0;
  for (i = 0; i < numBlue1 + numBlue2; i++) {
    if (k == numBlue2 || (j < numBlue1 && blue1[j] < blue2[k])) {
      blue[i] = blue1[j];
      j++;
    } else {
      blue[i] = blue2[k];
      k++;
    }
  }
  //Loop through both colors and set pixels
  for (i = 0; i < numRed1 + numRed2; i++) {
    if (i % 3 == p)
      strip.setPixelColor(red[i], RED);
    else
      strip.setPixelColor(red[i], OFF);
  }
  for (i = 0; i < numBlue1 + numBlue2; i++) {
    if (i % 3 == p)
      strip.setPixelColor(blue[i], BLUE);
    else
      strip.setPixelColor(blue[i], OFF);
  }
}

