
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BluefruitLE_UART.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define MATRIX_PIN 12 // NM data pin
#define RX_PIN    9   // BLE 'TXO' pin
#define CTS_PIN   10  // BLE 'CTS' pin

SoftwareSerial    ser(RX_PIN, -1);
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, MATRIX_PIN,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS    + NEO_MATRIX_ZIGZAG,
  NEO_GRB               + NEO_KHZ800);
  
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

int x                 = matrix.width();
int pass              = 0;
boolean gotNewMessage = false;

String message = "<3 <3 <3";
int messageLenCheck = message.length() * -6;

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);

  pinMode(CTS_PIN, OUTPUT);
  digitalWrite(CTS_PIN, HIGH);
  ser.begin(9600);
}

void loop() {
  int c;
  String newMessage;
    
  digitalWrite(CTS_PIN, LOW); // okay to send data
  while((c = ser.read()) > 0){
    Serial.print(char(c));
    gotNewMessage = true;
    newMessage += char(c);
  }
  digitalWrite(CTS_PIN, HIGH);

  if(gotNewMessage) {
    message = newMessage;
    gotNewMessage = false;
  }

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
