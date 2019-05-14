#include <Adafruit_NeoPixel.h> 

#define NUMPIXELS      32
#define PIN_PIXELS     6
#define MAX_INTENSITY 80

// Tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_PIXELS, NEO_GRB + NEO_KHZ800);

uint32_t orange = pixels.Color(200, 25, 4);
uint32_t blue = pixels.Color(4, 25, 200);

// The setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  //while (!Serial) {
    // Wait for serial port to connect. Needed for native USB
    //delay(100);
  //}

  // Initialize NeoPixel library
  pixels.begin();
  pixels.clear();
  
  Serial.println(F("Setup done"));  
}

int prev = 100;
int lvl = random(64, 191);

// The loop function runs over and over again forever
void loop() {
  flicker(4, 25, 200);
}

void flicker(uint8_t r, uint8_t g, uint8_t b) {
  lvl = random(80, 120);
  split(prev, lvl, 32, r, g, b);
  prev = lvl;
}

void split(int first, int second, int offset, uint8_t r, uint8_t g, uint8_t b) {
  //Serial.println("first = " + String(first) + " second = " + String(second) + " offset = " + String(offset));
  if (offset != 0) {
    int mid = ((first + second + 1) / 2 + random(-offset, offset));
    offset = offset / 2;
    split(first, mid, offset, r, g, b);
    split(mid, second, offset, r, g, b);
  } else {
    float level = pow(float(first) / 255.0, 2.7) * 255 + 0.5;
    level = level / 100.0;
    Serial.println("level = " + String(level));
    uint32_t c = pixels.Color(uint8_t(r * level), uint8_t(g * level), uint8_t(b * level));
    pixels.fill(c, 0, 0);
    pixels.show();
    delay(10);
  }
}

void pulse() {
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
