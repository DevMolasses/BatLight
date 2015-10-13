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
  colorChange(strip.Q1_WHITE);
}

void readingLight() {
  colorChange(strip.FULL_WHITE);
}

void strobeLight(uint32_t color) {
  unsigned long curMillis = millis();
  if (curMillis - displayTimer > 70UL && curMillis - displayTimer <= 100UL) {
    colorChange(color);
  } else if (millis() - displayTimer > 100UL)
  {
    colorChange(strip.OFF);
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
      strip.setPixelColor(i, strip.Wheel(((i + index) % 360), 1, 1));
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
//    colorChange(strip.Wheel(hue, 1, 1));
//    delay(wait);
//  }
//}

void fullStripRainbow() {
  if (millis() - displayTimer > 50UL) {
    displayTimer = millis();
    if (index >= 360) index = 0;
    colorChange(strip.Wheel(index, 1, 1));
    index++;
  }
}

void policeEffect() {
  
}

