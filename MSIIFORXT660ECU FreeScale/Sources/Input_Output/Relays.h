/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Relays.h
\brief      Relays control functions
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\ThirdParty Omar Hernandez/Rodrigo Ruiz (NACURI)
\version    0.1
\date       Jun/ 2008
*/
/*******************************************************************************/

#include <hidef.h>
/** Seabreeze Emulator Compilation Options */
#include "Seabreeze_Emulator.h"
/** S12X derivative information */
#include __S12X_DERIVATIVE
/** Variable types and common definitions */
#include "typedefs.h"

/* Define to enable Relay1 operation */
#define RELAY1  1

/* Define to enable Relay2 operation */
//#define RELAY2  2

/* Define to enable Relay3 operation */
#define RELAY3  3

/* Signals assigned to relays */
#define FUEL_PUMP   RELAY1
#define MOTOR_FAN   RELAY3

/* RELAY 2 control signal assigned to PWM channel for crank speed control */

/** Function prototypes */
 
void vfnRelays_Initialization(void); 
void vfnRelayControl(UINT8 u8Relay, UINT8 u8State);

/*******************************************************************************/