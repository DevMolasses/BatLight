#include <Arduino.h>

//Randomly cycles through various police effects.  Changes every 30 seconds.

//Define the 4 sections of lights
uint16_t red1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
const byte numRed1 = sizeof(red1) / sizeof(uint16_t);
uint16_t red2[] = {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
const byte numRed2 = sizeof(red2) / sizeof(uint16_t);
uint16_t blue1[] = {30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44};
const byte numBlue1 = sizeof(blue1) / sizeof(uint16_t);
uint16_t blue2[] = {45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59};
const byte numBlue2 = sizeof(blue2) / sizeof(uint16_t);

void policeEffect() {

  unsigned long curLoopTime;

  if (millis() - displayTimer > 15000UL) {
    displayTimer = millis();
    policeEffectNum++;
    if (policeEffectNum >= 5) policeEffectNum = 0;
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

void changeAllSections(byte r1, byte r2, byte b1, byte b2) {
  changeSection(red1, numRed1, r1, RED);
  changeSection(red2, numRed2, r2, RED);
  changeSection(blue1, numBlue1, b1, BLUE);
  changeSection(blue2, numBlue2, b2, BLUE);
}

void changeSection(uint16_t section[], byte numSection, byte state, uint32_t c) {
  uint32_t color = OFF;
  if (state == 1)
    color = c;
  for (int i = 0; i < numSection; i++) {
    strip.setPixelColor(section[i], color);
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

