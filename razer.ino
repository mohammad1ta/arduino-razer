#include <Adafruit_NeoPixel.h>

#define LED_COUNT 256
#define LED_PIN D1
#define numLED 60
#define numVertical 16
#define numHorizontal 16

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

float r, g, b;
int 
  caseId = 1, 
  pointerId = 0,
  currentPointer = 0,
  ledFullMatrix[ numVertical + 1 ][ numVertical + 1 ];

// Create matrix of LED's
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

// Get LEDs address of one loop square in array
int *getSquare(int value) {

  const int maxLedCountsInSquare = ( numVertical + numHorizontal ) * 2;

  static int resultAddress[ (int) maxLedCountsInSquare ];

  int ledCounts = maxLedCountsInSquare;
  int i, j, k = 16 + value, m = 33, everyLine = ledCounts / 4;
  
  for( int a = 1; a <= maxLedCountsInSquare; a++ ) {

    if ( a <= everyLine ) {
      i = value;
      j = a;
    } else if ( a <= ( everyLine * 2 ) ) {
      i = a - ( 16 );
      j = 16 - ( value - 1 );
    } else if ( a <= everyLine * 3 ) {
      i = 16;
      j = a - k;
      k = k + 2;
    } else if ( a <= everyLine * 4 ) {
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

// Handling light mode
void razer(int squareNum) {

  int *circleList = getSquare( squareNum );
  
  int i, j;

  float sectionColor = 64 / 6, unitColor = 255 / sectionColor;

  for (int a = 1; a <= 64; a++) {

    if ( a < sectionColor ) caseId = 1;
    else if ( a < sectionColor * 2 ) caseId = 2;
    else if ( a < sectionColor * 3 ) caseId = 3;
    else if ( a < sectionColor * 4 ) caseId = 4;
    else if ( a < sectionColor * 5 ) caseId = 5;
    else caseId = 6;

    switch ( caseId ) {
      case 1:
        r = 255;
        g = g + unitColor;
        b = 0;
        break;
      case 2:
        r = r - unitColor;
        g = 255;
        b = 0;
        break;
      case 3:
        r = 0;
        g = 255;
        b = b + unitColor;
        break;
      case 4:
        r = 0;
        g = g - unitColor;
        b = 255;
        break;
      case 5:
        r = r + unitColor;
        g = 0;
        b = 255;
        break;
      case 6:
        r = 255;
        g = 0;
        b = b - unitColor;
        break;
    }

    if ( r < 0 ) r = 0;
    if ( g < 0 ) g = 0;
    if ( b < 0 ) b = 0;

    currentPointer = pointerId + a;

    if ( currentPointer > 64 ) {
      currentPointer = currentPointer - 64;
    }
      
    strip.setPixelColor( circleList[currentPointer], r, g, b );

  }

  if ( ++pointerId == 64 ) 
    pointerId = 0;

}
