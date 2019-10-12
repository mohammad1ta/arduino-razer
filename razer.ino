#include <Adafruit_NeoPixel.h>

#define LED_COUNT 256
#define LED_PIN D1
#define numVertical 16
#define numHorizontal 16

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void createAddressableMatrix() {
  
  for ( int i = 1; i <= numVertical; i++ ) {

    for ( int j = 1; j <= numHorizontal; j++ ) {

      if ( i % 2 == 0 )
        ledFullMatrix[ i ][ j ] = ( i * numVertical - numVertical ) + ( numVertical - j );
      else
        ledFullMatrix[ i ][ j ] = ( i * numHorizontal - numHorizontal ) + j - 1;

    }

  }
  
}

void setup() {
  
  strip.begin();
  strip.setBrightness(255);
  strip.show();
  
  createAddressableMatrix();
  
}

void loop() {

  strip.show();
  
}
