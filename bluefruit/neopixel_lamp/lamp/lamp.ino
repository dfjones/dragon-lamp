#include <Adafruit_NeoPixel.h> 

#define NUMPIXELS      32
#define PIN_PIXELS     6

#define MAX_INTENSITY  80

// Tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_PIXELS, NEO_GRB + NEO_KHZ800);

// The setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  //while (!Serial) {
    // Wait for serial port to connect. Needed for native USB
 //   delay(100);
  //}

  // Initialize NeoPixel library
  pixels.begin();
  
  Serial.println(F("Setup done"));  
}

// The loop function runs over and over again forever
void loop() {

  // Pulsing in random colors
  int r = random(256);
  int g = random(256);
  int b = random(256);
  
  for (int intensity=0 ; intensity<MAX_INTENSITY ; intensity++) {
    for (int i=0 ; i<NUMPIXELS ; i++) {
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(r / 100 * intensity, g / 100 * intensity, b / 100 * intensity));
    }

    pixels.show();
    delay(20);
  }

  for (int intensity=MAX_INTENSITY ; intensity>=0 ; intensity--) {
    for (int i=0 ; i<NUMPIXELS ; i++) {
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(r / 100 * intensity, g / 100 * intensity, b / 100 * intensity));
    }

    pixels.show();
    delay(20);
  }

  delay(500);
}
