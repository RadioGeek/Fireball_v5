// ==========================================================================================//
// Fireball v5.0 source code 
// Copyright 2015 by John Maca, AB5SS, all rights reserved.
// ==========================================================================================//
//
// This is the header file for morse.c 
//

// Definitions - Morse Code speed constants
#define MORSE_CONST 1000
#define MORSE_SPEED 9
#define dotLength   int(MORSE_CONST / MORSE_SPEED)
#define dashLength  int(MORSE_CONST / MORSE_SPEED * 3)
#define pauseChar   int(MORSE_CONST / MORSE_SPEED * 3)
#define pauseWord   int(MORSE_CONST / MORSE_SPEED * 6) //should divide by 7 for proper spacing

// Functions

void dot();
void dash();
void EndOfChar();
void EndOfWord();
void SendMorse(char tmpChar);
