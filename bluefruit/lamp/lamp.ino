#include <Arduino.h>
#include <Adafruit_NeoPixel.h> 

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"


#include "BluefruitConfig.h"

#define NUMPIXELS      32
#define PIN_PIXELS     6
#define MAX_INTENSITY 80

// Tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_PIXELS, NEO_GRB + NEO_KHZ800);
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

uint8_t orange_r = 200; 
uint8_t orange_g = 25;
uint8_t orange_b = 4;

uint8_t blue_r = 4;
uint8_t blue_g = 25;
uint8_t blue_b = 200;

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

// The setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  //while (!Serial) {
    // Wait for serial port to connect. Needed for native USB
  //  delay(100);
  //}


  // Initialize NeoPixel library
  pixels.begin();
  pixels.clear();

  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  ble.echo(false);
  ble.sendCommandCheckOK("AT+GAPDEVNAME=" "Dragon Lamp");
  ble.verbose(false);

  Serial.println(F("Setup done"));  
}

int prev = 100;
int lvl = random(64, 191);

uint8_t r = orange_r;
uint8_t g = orange_g;
uint8_t b = orange_b;

// The loop function runs over and over again forever
void loop() {
  ble.println("AT+BLEUARTRX");
  ble.readline();
  if (strcmp(ble.buffer, "OK") == 0) {
    flicker();
  } else if (strcmp(ble.buffer, "blue") == 0) {
    r = blue_r;
    g = blue_g;
    b = blue_b;
  } else if (strcmp(ble.buffer, "orange") == 0) {
    r = orange_r;
    g = orange_g;
    b = orange_b;
  }
}

void flicker() {
  lvl = random(80, 120);
  split(prev, lvl, 32);
  prev = lvl;
}

void split(int first, int second, int offset) {
  //Serial.println("first = " + String(first) + " second = " + String(second) + " offset = " + String(offset));
  if (offset != 0) {
    int mid = ((first + second + 1) / 2 + random(-offset, offset));
    offset = offset / 2;
    split(first, mid, offset);
    split(mid, second, offset);
  } else {
    float level = pow(float(first) / 255.0, 2.7) * 255 + 0.5;
    level = level / 100.0;
    //Serial.println("level = " + String(level));
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
