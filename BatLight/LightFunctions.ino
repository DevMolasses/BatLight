void colorChange(uint32_t color) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

void colorWipe(uint32_t color) {
  if (millis() - displayTimer > 10UL) {
    displayTimer = millis(); //reset timer to start over
    if (index >= strip.numPixels()) index = 0; //verify the index is in range
    strip.setPixelColor(index, color); //change the pixel color
    strip.show();
    index++;
  }
}

void whiteStrobe() {
  strobeLight(FULL_WHITE);
}

void randomColorStrobe() {
  //  unsigned long curLoopTime;

  if (millis() - displayTimer > 100UL) {
    displayTimer = millis();
    colorStorage = RandomColor();
  }
  strobeLight(colorStorage);

  //  curLoopTime = (millis() - displayTimer) % 100;
  //  if (curLoopTime <= 70UL)
  //    colorChange(OFF);
  //  else if (curLoopTime > 70UL && curLoopTime <= 100UL)
  //    colorChange(colorStorage);
}

void strobeLight(uint32_t color) {
  unsigned long curLoopTime = (millis() - displayTimer) % 100;
  if (curLoopTime <= 70UL)
    colorChange(OFF);
  else if (curLoopTime > 70UL && curLoopTime <= 100UL)
    colorChange(color);
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
    index++;
  }
}

void rainbowCycle() {
  if (millis() - displayTimer > 50UL) {
    displayTimer = millis();
    if (index >= 360) index = 0;
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((((i * 360 / strip.numPixels()) + index) % 360), 1, 1));
    }
    strip.show();
    index++;
  }
}

/*
* This method will cycle all the pixels simultaneously
* through all the colors of DevMolasses Wheel
*/
void fullStripRainbow() {
  if (millis() - displayTimer > 50UL) {
    displayTimer = millis();
    if (index >= 360) index = 0;
    colorChange(Wheel(index, 1, 1));
    index++;
  }
}

void pixelScrolling() {
  if (millis() - displayTimer > 10UL) {
    displayTimer = millis();
    if (index >= strip.numPixels()) {
      index = 0;
      colorStorage = RandomColor();
    }
    colorChange(OFF);
    strip.setPixelColor(index, colorStorage);
    strip.show();
  }
}

void theaterChaseWhite() {
  if (millis() - displayTimer > 100UL) {
    if (index >= 3) index = 0;
    for (uint16_t  i = 0; i < strip.numPixels(); i++) {
      if (i % 3 == index)
        strip.setPixelColor(i, FULL_WHITE);
      else
        strip.setPixelColor(i, OFF);
    }
    strip.show();
    index++;
  }
}

void theaterChaseRainbow() {
  if (millis() - displayTimer > 100UL) {
    if (index >= 360) index = 0;
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      if (i % 3 == index % 3)
        strip.setPixelColor(i, Wheel(index, 1, 1));
      else
        strip.setPixelColor(i, OFF);
    }
    strip.show();
    index++;
  }
}

