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
/*                                                                             */
/* All software, source code, included documentation, and any implied know-how */
/* are property of Freescale Semiconductor and therefore considered            */ 
/* CONFIDENTIAL INFORMATION.                                                   */
/*                                                                             */
/* This confidential information is disclosed FOR DEMONSTRATION PURPOSES ONLY. */
/*                                                                             */
/* All Confidential Information remains the property of Freescale Semiconductor*/
/* and will not be copied or reproduced without the express written permission */
/* of the Discloser, except for copies that are absolutely necessary in order  */
/* to fulfill the Purpose.                                                     */
/*                                                                             */
/* Services performed by FREESCALE in this matter are performed AS IS and      */
/* without any warranty. CUSTOMER retains the final decision relative to the   */
/* total design and functionality of the end product.                          */
/*                                                                             */
/* FREESCALE neither guarantees nor will be held liable by CUSTOMER for the    */
/* success of this project.                                                    */
/*                                                                             */
/* FREESCALE disclaims all warranties, express, implied or statutory including,*/
/* but not limited to, implied warranty of merchantability or fitness for a    */
/* particular purpose on any hardware, software ore advise supplied to the     */
/* project by FREESCALE, and or any product resulting from FREESCALE services. */
/*                                                                             */
/* In no event shall FREESCALE be liable for incidental or consequential       */
/* damages arising out of this agreement. CUSTOMER agrees to hold FREESCALE    */
/* harmless against any and all claims demands or actions by anyone on account */
/* of any damage,or injury, whether commercial, contractual, or tortuous,      */
/* rising directly or indirectly as a result of the advise or assistance       */
/* supplied CUSTOMER in connectionwith product, services or goods supplied     */
/* under this Agreement.                                                       */
/*                                                                             */
/*******************************************************************************/

/** MCU definitions */
#include "MCUdefinitions.h"
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
    #ifndef SUITCASE_DEMO
    //Suitcase demo uses RELAY 2 module pin to drive crankshaft motor.
    //Control is elsewhere
    vfnRelayControl(RELAY2, OFF); 
    #endif
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
    
    #ifdef R1
        if(u8Relay == RELAY1)   
            RIN1 = u8State;
    #endif
    
    #ifdef R2
        if(u8Relay == RELAY2)   
            RIN2 = u8State;
    #endif
    
    #ifdef R3
        if(u8Relay == RELAY3)   
            RIN3 = u8State;
    #endif   
}                                        

/*******************************************************************************/