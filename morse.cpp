// ==========================================================================================//
// Fireball v5.0 source code 
// Copyright 2015 by John Maca, AB5SS, all rights reserved.
// ==========================================================================================//
//
// This module contains the functions to send the messages using Morse code.
//

#include <Arduino.h>
#include "config.h"
#include "morse.h"

void dot() {
  digitalWrite (XMIT_PIN, HIGH);
  delay (dotLength);
  digitalWrite (XMIT_PIN, LOW); 
  delay (dotLength);
} 

void dash() {
  digitalWrite (XMIT_PIN, HIGH);
  delay (dashLength);
  digitalWrite (XMIT_PIN, LOW); 
  delay (dotLength);
}

void EndOfChar() {
  delay (pauseChar);
}

void EndOfWord() {
  delay (pauseWord);
}

void SendMorse(char tmpChar) {
  if (isalpha(tmpChar)) {
    tmpChar = toupper(tmpChar);
  }
  switch (tmpChar) {
    case '0': {
      dash(); dash(); dash(); dash(); dash(); }
      break;
    case '1': {
      dot(); dash(); dash(); dash(); dash(); }
      break;
    case '2': {
      dot(); dot(); dash(); dash(); dash(); }
      break;
    case '3': {
      dot(); dot(); dot(); dash(); dash(); }
      break;
    case '4': {
      dot(); dot(); dot(); dot(); dash(); }
      break;
    case '5': {
      dot(); dot(); dot(); dot(); dot(); }
      break;      
    case '6': {
      dash(); dot(); dot(); dot(); dot(); }
      break;
    case '7': {
      dash(); dash(); dot(); dot(); dot(); }
      break;      
    case '8': {
      dash(); dash(); dash(); dot(); dot(); }
      break; 
    case '9': {
      dash(); dash(); dash(); dash(); dot(); }
      break;  
    case 'A': {
      dot(); dash(); }
      break;    
    case 'B': {
      dash(); dot(); dot(); dot(); }
      break;    
    case 'C': {
      dash(); dot(); dash(); dot(); }
      break;    
    case 'D': {
      dash(); dot(); dot(); }
      break;    
    case 'E': {
      dot(); }
      break;    
    case 'F': {
      dot(); dot(); dash(); dot();  }
      break;    
    case 'G': {
      dash(); dash(); dot(); }
      break;    
    case 'H': {
      dot(); dot(); dot(); dot();  dot(); }
      break;    
    case 'I': {
      dot(); dot(); }
      break;    
    case 'J': {
      dot(); dash(); dash(); dash(); }
      break;    
    case 'K': {
      dash(); dot();  dash(); }
      break;    
    case 'L': {
      dot(); dash(); dot(); dot(); }
      break;    
    case 'M': {
      dash(); dash(); }
      break;    
    case 'N': {
      dash(); dot(); }
      break;    
    case 'O': {
      dash(); dash(); dash(); }
      break;    
    case 'P': {
      dot(); dash(); dash(); dot(); }
      break;    
    case 'Q': {
      dash(); dash(); dot(); dash(); }
      break;    
    case 'R': {
      dot();  dash(); dot(); }
      break;    
    case 'S': {
      dot(); dot(); dot(); }
      break;    
    case 'T': {
      dash(); }
      break;    
    case 'U': {
      dot(); dash(); dash(); }
      break;    
    case 'V': {
      dot(); dot(); dot(); dash(); }
      break;    
    case 'W': {
      dot(); dash(); dash(); }
      break;    
    case 'X': {
      dash(); dot(); dot(); dash(); }
      break;    
    case 'Y': {
      dash(); dot(); dash(); dash(); }
      break;
    case 'Z': {
      dash(); dash(); dot(); dot(); }
      break;  
    case ' ': {
      EndOfChar(); }
      break;  
    case '-': {
      dash(); dot(); dot(); dot(); dot(); dash();  }
      break;  
    case '.': {
      dot(); dash(); dot(); dash(); dot(); dash();  }
      break;  
    case '/': {
      dash(); dot(); dot(); dash(); dot(); }
      break;  
    case '?': {
      dot(); dot(); dash(); dash(); dot(); dot(); }
      break;  
    default: {
      dot(); dot(); dash(); dash(); dot(); dot(); }
  }
  EndOfChar();
}

