/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Timers.c
\brief      S12XEP100 timers configuration
            and interrupts configuration routines
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     B20740
\version    0.1
\date       December/2008
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

/** Seabreeze Emulator Compilation Options */
#include "Seabreeze_Emulator.h"
/** S12X derivative information */
#include __S12X_DERIVATIVE

/** Timer module initialization prototypes and definitions */
#include "Timers.h"
/** Variable types and common definitions */
#include "typedefs.h"   
/** Application definitions */
#include "Application Definitions.h"


/* -- Variables --------------------------------------------------------*/



/*******************************************************************************/
/**
* \brief    Periodic interrupt timers initalization 
* \author   Luis Olea
* \param    void
* \return   void
*/
void vfnPIT_init(void)
{
   
}

/*******************************************************************************/
/**
* \brief    Timer Module initalization 
* \author   Jaime Orozco
* \param    void
* \return   void
*/
void vfnTimerModule_Init(UINT8 u8Prescaler)     
{   
    TIE = 0x00;     /* Disable all timer interrupts */        
    
    /* Clear timer control registers prior to channels configuration */                           
    TCTL1 = 0x00;       
    TCTL2 = 0x00;             
   
    PACTL_PAEN = 0;     /* Pulse accumulator disabled */
    PACTL_CLK1 = 0;     /* Timer prescaler clock as timer counter clock */
    PACTL_CLK0 = 0;
           
    TSCR1_TEN = 0;    /* Disable timer counter */
    // not supported in S12T64 TSCR1_PRNT = 0;   /* Precision timer disabled */
    
    TSCR2_PR = u8Prescaler;    /* Set prescaler value */        
    
    TSCR1_TFFCA = 1;        /* Clear flag by reading channel data */                                      
    
    TSCR1_TEN = 1;         /* Enable timer counter (free running) */    
}

/*******************************************************************************/
/**
* \brief    Timer channel: Input compare configuration
* \author   Jaime Orozco
* \param    void
* \return   void
*/
void vfnTimer_Config_InputCompare(UINT8 u8Channel, UINT8 u8Action_on_Event)     
{   
   

}

/*******************************************************************************/

