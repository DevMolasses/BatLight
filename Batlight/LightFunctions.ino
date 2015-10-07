void colorChange(uint32_t color) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

void colorWipe(uint32_t color, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void nightLight() {
  colorChange(strip.Q1_WHITE);
}

void readingLight() {
  colorChange(strip.FULL_WHITE);
}

void strobeLight(uint32_t color) {
  colorChange(color);
  delay(70);
  colorChange(strip.OFF);
  delay(30);
}

/*
* Cycles each pixel through the colors individually
* Each pixel is 1 degree of the wheel from its neighboring pixel
* Credit to Adafruit.com for the algorithm; edited by DevMolasses
*/
void rainbow(uint8_t wait) {
  uint16_t i, j;
  for (j = 0; j < 360; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Wheel(((i + j) & 359), 1, 1));
    }
    strip.show();
    delay(wait);
  }
}

/*
* This method will cycle all the pixels simultaneously
* through all the colors of DevMolasses Wheel
*/
void fullStripRainbow(uint8_t wait) {
  for (int hue = 0; hue < 360; hue++) {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Wheel(hue, 1, 1));
    }
    strip.show();
    delay(wait);
  }
}

