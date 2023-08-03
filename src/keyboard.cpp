/*******************************************
 * Wio Terminal Keyboard
 * File: {@code keybaord.cpp}
 * Author: Konstantinos Rokanas
 ******************************************/

#include "keyboard.h"                         // include corresponding header file
#include <cstring>                            // include C standard library for use of certain string manipulation functions

// multidimensional array containing the available characters on the keyboard
const char keyboard[4][23] = {
  { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w' },
  { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W' },
  { '1', '2', '3', '4', '5', '!', '?', '@', '#', '$', '%', '_', '-', '+', '=', '^', '&', '*', '`', '~', 'x', 'y', 'z' },
  { '6', '7', '8', '9', '0', '.', ',', ';', ':', '"', '/', '(', ')', '{', '}', '[', ']', '<', '>', 'Ä', 'X', 'Y', 'Z' },
};

char input[32];                               // declare the character array that stores the user input

// variables indicating currently highlighted character
int currentXY[2] = {KEY_X + 13, KEY_Y + 80};  // x, y coords of highlighted character (initialized pointing to DEL key)
int currentChar[2] = {4, 1};                  // index values to retrieve highlighted character from keyboard array (initialized pointing to DEL key)

// function called on right button press in user input screen
void keyboardRight() {
  // if at bottom row and left side of screen, jump from DEL to SPACE key
  if (currentChar[0] == KEY_ROWS && currentChar[1] < 6) {    
    currentXY[0] = 155;
    currentChar[1] = 11;
  // if at bottom row and middle of screen, jump from SPACE to ENTER key
  } else if (currentChar[0] == KEY_ROWS && currentChar[1] > 5 && currentChar[1] < 16) {
    currentXY[0] = 272;
    currentChar[1] = 20;
  // if at bottom row and right side of screen, scroll from ENTER to DEL key
  } else if (currentChar[0] == KEY_ROWS && currentChar[1] > 16) {  
    currentXY[0] = 25;
    currentChar[1] = 1;
  // if within first four character rows, change position by 1 character to the right
  } else if (currentChar[1] != (KEY_COLUMNS - 1)) { 
    currentXY[0] += 13;
    currentChar[1] += 1;
  // if within first four character rows at rightmost column, scroll to the leftmost
  } else if (currentChar[1] == KEY_COLUMNS - 1) {
    currentXY[0] = 13;
    currentChar[1] = 0;
  }
}

// function called on left button press in user input screen
void keyboardLeft() {
  // if at bottom row and right side of screen, jump from ENTER to SPACE key
  if(currentChar[0] == KEY_ROWS && currentChar[1] > 15) {                
    currentXY[0] = 155;
    currentChar[1] = 11;
  // if at bottom row and middle of screen, jump from SPACE to DEL key
  } else if (currentChar[0] == KEY_ROWS && currentChar[1] > 5 && currentChar[1] < 16) { 
    currentXY[0] = 25;
    currentChar[1] = 1;   
  // if at bottom row and left side of screen, scroll from DEL to ENTER key
  } else if (currentChar[0] == KEY_ROWS && currentChar[1] < 6) {
    currentXY[0] = 272;
    currentChar[1] = 20;
  // if within first four character rows, change position by 1 character to the left
  } else if (currentChar[1] != 0) {                   
    currentXY[0] -= 13;
    currentChar[1] -= 1;
  // if within first four character rows at leftmost column, scroll to the rightmost
  } else if (currentChar[1] == 0) {                   
    currentXY[0] = 298;
    currentChar[1] = 22;
  }
}

// function called on up button press in user input screen
extern void keyboardUp() {
  if (currentChar[0] != 0) {                  // change position by 1 character upwards
    currentXY[1] -= 20;
    currentChar[0] -= 1;
  } else if (currentChar[0] == 0) {           // if at topmost row, scroll to bottommost 
    currentXY[1] = KEY_Y + 80;
    currentChar[0] = KEY_ROWS; 
  }
}

// function called on down button press in user input screen
extern void keyboardDown() {
  if (currentChar[0] != KEY_ROWS) {           // change position by 1 character downwards
    currentXY[1] += 20;
    currentChar[0] += 1;
  } else if (currentChar[0] == KEY_ROWS) {    // if at bottommost row, scroll to the topmost
    currentXY[1] = KEY_Y;
    currentChar[0] = 0;
  }
}

// function called on middle button press in user input screen
extern void keyboardMiddle() {
  // if selecting the DEL key, call function to remove last character of input String
  if (currentChar[0] == KEY_ROWS && currentChar[1] < 6) {    
    removeChar();
    // buttonPressed = true;
    
  // if selecting the SPACE key, call function to add space at the end of input String
  } else if (currentChar[0] == KEY_ROWS && currentChar[1] > 5 && currentChar[1] < 16) {
    addChar(' ');
    // buttonPressed = true;

  // if selecting the ENTER key, save user input string
  } else if (currentChar[0] == KEY_ROWS && currentChar[1] > 15) {
    // saveUserInput();            

  // if selecting a keyboard character, call function to add it to end of input String
  } else {
    addChar(keyboard[currentChar[0]][currentChar[1]]);
    // buttonPressed = true;
  }
}

// function to add currently highlighted character to input String array
void addChar(char character) {                
  char charString[2];                         // create a temporary character array to hold the single character
  charString[0] = character;                  // assign the selected character
  charString[1] = '\0';                       // add null terminator to make it a valid string
  strcat(input, charString);                  // concatenate existing String and new character
  }

// function to remove last character from the input String array
void removeChar() {                           
  int length;                                 // declare variable storing length of input String
  length = strlen(input);                     // determine the lenght of input String
  if (length > 0) {                           // check that input String isn't empty
    input[length - 1] = '\0';                 // if not empty, add null terminator to the last element
    }
  }

// function to import provided network String and reset the position of highlighted key
void initUserInput(char* currentVal) {
  strcpy(input, currentVal);                  // copy the contents of current input to user input character array ||| CONSIDER REMOVING

  // reset position to highlight DEL key
  currentXY[0] = KEY_X + 13;                  // reset x coordinate of highlighted key 
  currentXY[1] = KEY_Y + 80;                  // reset y coordinate of highlighted key 
  currentChar[0] = 4;                         // reset keyboard array index value (row)
  currentChar[1] = 1;                         // reset keyboard array index value (column)
}