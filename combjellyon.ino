void combjellyon() {
 
  unsigned long currentMillis = millis();
  prevcp = cp-1;
  
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
    previousMillis = millis();  

  strip.setPixelColor(cp, 0, 255, 0);
  strip.setPixelColor(cp+1, 0, 255, 0);
  strip.setPixelColor(cp+2, 255, 0, 0);
  strip.setPixelColor(cp+3, 255, 0, 0);
  strip.setPixelColor(cp+4, 0, 0, 255);
  strip.setPixelColor(cp+5, 0, 0, 255);
  strip.show();
 
    cp++;
    strip.setPixelColor(prevcp, 0, 0, 0);
    strip.show();
  }

  if (cp == NUM_PIXELS) {
    cp = 0;
  }     
  
}

