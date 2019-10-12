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

int *getSquare(int value) {

  const int maxLedCountsInSquare = numVertical + numHorizontal + ( numVertical - 2 ) + ( numHorizontal - 2 ) + 1; // 61 mishe;

  static int resultAddress[ (int) maxLedCountsInSquare ];

  int ledCounts = maxLedCountsInSquare - ( value * 4 - 4 );

  int k = 17;
  int m = 32;
  int i, j;
  
  for( int a = 1; a <= maxLedCountsInSquare; a++ ) {

    if ( a <= 16 ) {
      i = 1;
      j = a;
    } else if ( a > 16 && a <= 31 ) {
      i = a - 15;
      j = 16;
    } else if ( a > 31 && a <= 46 ) {
      i = 16;
      j = a - k;
      k = k + 2;
    } else {
      i = a - m;
      j = 1;
      m = m + 2;
    }
    
    resultAddress[ a ] = ledFullMatrix[ i ][ j ];
    
  }

  return resultAddress;
  
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
