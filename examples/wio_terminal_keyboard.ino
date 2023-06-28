/*******************************************
 * Wio Terminal Keyboard
 * File: {@code wio_terminal_keyboard.ino}
 * Authord: Konstantinos Rokanas
 ******************************************/

#include "TFT_eSPI.h"                     // import TFT LCD library 

TFT_eSPI tft;                             // initialise wio terminal LCD

void setup() {
  tft.begin();                            // start terminal LCD
  tft.setRotation(3);                     // set terminal LCD rotation

  // set buttons as input that interrupts program loop
  attachInterrupt(digitalPinToInterrupt(WIO_5S_RIGHT), keyboardRight, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_5S_LEFT), keyboardLeft, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_5S_UP), keyboardUp, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_5S_DOWN), keyboardDown, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_5S_PRESS), keyboardMiddle, FALLING);

}

void loop() {

}
