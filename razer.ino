#include <Adafruit_NeoPixel.h>

#define LED_COUNT 256
#define LED_PIN D1

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  
  strip.begin();
  strip.setBrightness(255);
  strip.show();
  
}

void loop() {

  strip.show();
  
}
