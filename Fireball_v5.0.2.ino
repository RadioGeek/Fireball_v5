// ==========================================================================================//
// Fireball v5.0 source code 
// Copyright 2015 by John Maca, AB5SS, all rights reserved.
//
// This code was written for a 'digital' version of the "Fireball" class of QRP transmitters
// that I designed and built for fun.  This Fireball v5.x design was my attempt to try and 
// improve on the analog 555 timer based Fireball transmitters that Andy MacAllister, W5ACM, 
// and others have built and launched on short duration high altitude balloon flights. 
// I will likely release this code as open source in the future, but for now it remains 
// closed.  See other libraries for rights associated with their distribution & use. 
//
// This version uses an Atmel ATtiny85 microcontroller running at 8MHz, an NXP PCT2075 
// (equivalent to the TI LM75A) digital temperature sensor, TI TPS61202 5V Boost power 
// converter/supply, and up to two (2) standard 5V clock oscillators the builder chooses to 
// use.  Although not yet implmented, I'm leaving scars in this code for other/different sensors, 
// including a pressure/temp sensor (like the Bosch BMP180), or effectors (like an ultra-bright 
// LED pointing toward the ground).  
//
// This version of the software periodically transmits the temperature (deg C/F) in Morse code
// the operators amatuer radio callsign, and optionally will transmit 'idle' beeps in between
// temperature transmissions. 
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. 
// ==========================================================================================//

// Include Files
#include <ctype.h>
#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include "TinyWireM.h"
#include "config.h"
#include "morse.h"


// Variables declarations
  int   TempC = 0;
  int   TempF = 0;

// ==========================================================================================//

// Watchdog Interrupt Service is executed when watchdog times out
ISR(WDT_vect) {}

// Function to put AT85 to power down for 1 second
//
void power_down_1s()
{
  unsigned char mcucr1, mcucr2;
  ACSR |= _BV(ACD);                         //disable the analog comparator
  ADCSRA &= ~_BV(ADEN);                     //disable ADC
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  wdtEnable();    // Sets WDT for 1 second
  cli();
  mcucr1 = MCUCR | _BV(BODS) | _BV(BODSE);  //turn off the brown-out detector
  mcucr2 = mcucr1 & ~_BV(BODSE);
  MCUCR = mcucr1;
  MCUCR = mcucr2;
  sei();        //ensure interrupts enabled so we can wake up again
  sleep_cpu();  // Power down cpu
  cli();
  sleep_disable();
  wdtDisable();
  sei();
  power_all_enable();
}

void wdtEnable(void)
{
    wdt_reset();
    cli();
    MCUSR = 0x00;
    WDTCR |= _BV(WDCE) | _BV(WDE);
    WDTCR  = _BV(WDP2) | _BV(WDP1) ;    // 1 sec
    WDTCR |= _BV(WDIE);
    sei();
}

//disable the wdt
void wdtDisable(void)
{
    wdt_reset();
    cli();
    MCUSR = 0x00;
    WDTCR |= _BV(WDCE) | _BV(WDE);
    WDTCR = 0x00;
    sei();
}

                                                                                                                                                                                                    
// Function: GetTemp() - Gets the temperature from the PCT2075 and stores it in 
//   variables TempNeg (true if temp < 0) and TempAbs (the absolute temp).
//
void GetTemp() {
  byte TempMSB, TempLSB;
  
  // Get Temperature
  TinyWireM.beginTransmission(PCT2075_ADDRESS);
  TinyWireM.requestFrom(PCT2075_ADDRESS, 2);
  TempMSB = TinyWireM.receive();
  TempLSB = TinyWireM.receive();
  TinyWireM.endTransmission();

//  TempMSB = 0xEF;  // TEST values 
//  TempLSB = 0x00;
  
  if (TempMSB > 0x7F) { 
    TempC = -(float((TempMSB ^ 0xFF) + 0x01));  // Convert 2's compliment negative number 
    if (TempLSB & 0x80 == 0x80) {
      TempC = TempC - 0.5;
    }
    if (TempLSB & 0x40 == 0x40) {
      TempC = TempC - 0.25;
    }  
    if (TempLSB & 0x20 == 0x20) {
      TempC = TempC - 0.125;
    }
  }
  else {
    TempC = float(TempMSB);
    if (TempLSB & 0x80 == 0x80) {
      TempC = TempC + 0.5;
    }
    if (TempLSB & 0x40 == 0x40) {
      TempC = TempC + 0.25;
    }  
    if (TempLSB & 0x20 == 0x20) {
      TempC = TempC + 0.125;
    }
  }
  TempF = round((TempC * 9 / 5) + 32.0); 
  TempC = round(TempC);
}

// Function to Enable/Shutdown the PCT2075
// Pass 0x00 for Enable and 0x01 for Shutdown
void set_PCT2075_config(byte reg_value)
{
  TinyWireM.beginTransmission(PCT2075_ADDRESS);
  TinyWireM.send(1); // Select Configuration register
  TinyWireM.send(reg_value);
  TinyWireM.endTransmission();
} 

// Function: SendTempC() - Sends the temperature in degrees C
//
void SendTempC() {
  char TempStr[6];
  
  itoa(int(TempC), TempStr, 10);
  
  for (int i=0; i < strlen(TempStr); i++) {
    SendMorse(TempStr[i]);
  }
  SendMorse('C');  
}

// Function: SendTempF() - Sends the temperature in degrees F
//
void SendTempF() {
  char TempStr[6];
  
  itoa(int(TempF), TempStr, 10);
  
  for (int i=0; i < strlen(TempStr); i++) {
    SendMorse(TempStr[i]);
  }
  SendMorse('F');  
}
    
// Function: SendCallsign() - Sends the Operator's callsign defined in config.h
//
void SendCallsign() {
  if (SEND_CALL == true) {
    char callstr[15] = CALLSIGN;
    SendMorse('D');
    SendMorse('E');
    SendMorse(' ');
    for (int i=0; i < strlen(callstr); i++) {
      SendMorse(callstr[i]);
    }
  }
  EndOfWord();
} 

// Function: SendIdleBeeps(beeps, beep_spacing) - where t is the number of seconds between beeps. Adjust 
//   for your microcontrollers true amount of delay.
//  
void SendIdleBeeps(int beeps, int beep_spacing) {
  if (IDLE_BEEPS == true) {
    delay(1100);
    for (int i=1; i <= beeps; i++) {
      digitalWrite (XMIT_PIN, HIGH);
      delay (150);
      digitalWrite (XMIT_PIN, LOW); 
//      delay (1100 * beep_spacing);
      for (int j=1; j <= beep_spacing; j++) {
        power_down_1s();
      }
    }
  }
}


void setup() {
  pinMode(XMIT_PIN, OUTPUT);   // initialize the digital pin as an output.
  TinyWireM.begin();           // initialize I2C bus.
//  set_PCT2075_config(PCT2075_SHUTDOWN);   // Shutdown PCT2075 Temperature Sensor to conserve power
  delay(2000);
}

void loop() { 
  SendCallsign();       // Will send callsign if #define SEND_CALL is set to 'true'
  for (byte i=0; i<10; i++) {  //  Loop i times.  Change code later to use millis() function in SendCallsign().  
    GetTemp();
    SendTempC();
    delay(1000);
    SendTempF();
    SendIdleBeeps(4, 5);  // Will send idle beeps if #define IDLE_BEEPS set to 'true'; e.g. 4 beeps, 5 seconds apart.
  }
}
