
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 12

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0),    // red
  matrix.Color(255, 127, 0),  // orange
  matrix.Color(255, 255, 0),  // yellow
  matrix.Color(0, 255, 0),    // gren
  matrix.Color(0, 0, 255),    // blue
  matrix.Color(75, 0, 130),   // idigo
  matrix.Color(143, 0, 255)   // violet
};

const int NUM_COLORS = 7;

int x    = matrix.width();
int y    = matrix.height();
int pass = 0;

String message = "<3 <3 <3";
int messageLenCheck = message.length() * -6;

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
}

void loop() {  
  scrollText();
}

void scrollText() {
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(message);
  if(--x < messageLenCheck) {
    x = matrix.width();
    if(++pass >= NUM_COLORS) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(10);
}
