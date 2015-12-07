// ==========================================================================================//
// Fireball v5.0 source code 
// Copyright 2015 by John Maca, AB5SS, all rights reserved.
// ==========================================================================================//
//
// This is the config.h header file for the main Fireball v5.0 code
//

// Definitions 
#define XMIT_PIN          3    // PIN 3 for Fireball v5.0, PIN 1 for a DigiSpark demo
#define PCT2075_ADDRESS  0x48  // I2C address of NXP PCT2075
#define PCT2075_WAKEUP   0x00  // Configuration register value to enable normal operations
#define PCT2075_SHUTDOWN 0x01  // Configuration register value to shutdown device (low power mode)

#define IDLE_BEEPS       true  // Enable short beeps on the second during idle time
#define SEND_CALL        true  // Enables sending of your callsign
#define CALLSIGN      "FIREBALL 5"  // Operator's callsign

#define BODS 7                   //BOD Sleep bit in MCUCR
#define BODSE 2                  //BOD Sleep enable bit in MCUCR

