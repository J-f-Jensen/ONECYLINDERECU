/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Relays.c
\brief      Relays control functions
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\ThirdParty Omar Hernandez/Rodrigo Ruiz (NACURI)
\version    0.1
\date       Jun/ 2008
*/
/*******************************************************************************/

/** Seabreeze Emulator Compilation Options */
#include "Seabreeze_Emulator.h"
/** CPU initialization prototypes and definitions */
#include "Input_Output.h"
/** Variable types and common definitions */
#include "typedefs.h" 
#include "Relays.h" 


/*******************************************************************************/
/**
* \brief    Relays initialization
* \author   OH
* \param    void                 
* \return   void 
*/
void vfnRelays_Initialization(void)
{  
    vfnRelayControl(RELAY1, OFF);     
    //vfnRelayControl(RELAY2, OFF); /* Relay 2 not implemented in suitcase demo */  
    vfnRelayControl(RELAY3, OFF);                  
}                                        

/*******************************************************************************/
/**
* \brief    Relay control function
* \author   OH
* \param    u8Relay_No possible values: RELAY1, RELAY2, RELAY3  \
            u8State possible values: ON, OFF                    
* \return   void 
*/
void vfnRelayControl(UINT8 u8Relay, UINT8 u8State)
{            
    /* Actual logic state depends on defined active levels */
    
    #ifdef RELAY1
        if(u8Relay == RELAY1)   
            RIN1 = u8State;
    #endif
    
    #ifdef RELAY2
        if(u8Relay == RELAY2)   
            RIN2 = u8State;
    #endif
    
    #ifdef RELAY3
        if(u8Relay == RELAY3)   
            RIN3 = u8State;
    #endif   
}                                        

/*******************************************************************************/