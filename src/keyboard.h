/*******************************************
 * Wio Terminal Keyboard
 * File: {@code keybaord.cpp}
 * Author: Konstantinos Rokanas
 ******************************************/

#ifndef KEYBOARD_H
#define KEYBOARD_H                             // header guard

#define KEY_ROWS 4                             // number of rows of the keyboard
#define KEY_COLUMNS 23                         // number of columns of the keyboard
#define KEY_X 12                               // x position of leftmost column
#define KEY_Y 130                              // y position of topmost row

// multidimensional array containing the available characters on the keyboard
extern const char keyboard[4][23];

// character arrays that stores the user inputted Strings
extern char input[32];                         // stores the user input

// variables indicating currently highlighted character
extern int currentXY[2];                       // x, y coords of highlighted character 
extern int currentChar[2];                     // index values to retrieve highlighted character from keyboard array

// function called on right button press in user input screen
extern void keyboardRight();

// function called on left button press in user input screen
extern void keyboardLeft();

// function called on up button press in user input screen
extern void keyboardUp();

// function called on down button press in user input screen
extern void keyboardDown();

// function called on middle button press in user input screen
extern void keyboardMiddle();

// function to add currently highlighted character to input String array
extern void addChar(char character);

// function to remove last character from the input String array
extern void removeChar();

// function to import provided network credential and reset the position of highlighted key
extern void initUserInput(char* currentVal);

#endif                                         // end header guard  