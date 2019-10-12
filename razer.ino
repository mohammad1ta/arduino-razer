#include <Adafruit_NeoPixel.h>

#define LED_COUNT 256
#define LED_PIN D1
#define numVertical 16
#define numHorizontal 16

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

float r, g, b;
int 
  caseId = 1, 
  pointerId = 0,
  currentPointer = 0,
  ledFullMatrix[ numVertical + 1 ][ numVertical + 1 ];


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

  createAddressableMatrix();

  strip.begin();
  strip.setBrightness(255);
  strip.show();
  
}

void loop() {

  razer();
  strip.show();

}

void razer() {

  int *circleList = getSquare(1);
  
  for (int a = 1; a <= 60; a++) {

    if ( a < 11 ) caseId = 1;
    else if ( a >= 11 && a < 21 ) caseId = 2;
    else if ( a >= 21 && a < 31 ) caseId = 3;
    else if ( a >= 31 && a < 41 ) caseId = 4;
    else if ( a >= 41 && a < 51 ) caseId = 5;
    else caseId = 6;

    switch ( caseId ) {
      case 1:
        r = 255;
        g = g + 25.5;
        b = 0;
        break;
      case 2:
        r = r - 25.5;
        g = 255;
        b = 0;
        break;
      case 3:
        r = 0;
        g = 255;
        b = b + 25.5;
        break;
      case 4:
        r = 0;
        g = g - 25.5;
        b = 255;
        break;
      case 5:
        r = r + 25.5;
        g = 0;
        b = 255;
        break;
      case 6:
        r = 255;
        g = 0;
        b = b - 25.5;
        break;
    }

    if ( r < 0 ) r = 0;
    if ( g < 0 ) g = 0;
    if ( b < 0 ) b = 0;

    currentPointer = pointerId + a;

    if ( currentPointer > 60 ) {
      currentPointer = currentPointer - 60;
    }
      
    strip.setPixelColor( circleList[currentPointer], r, g, b );

  }

  pointerId++;
  
  if ( pointerId == 60 ) 
    pointerId = 0;

}
