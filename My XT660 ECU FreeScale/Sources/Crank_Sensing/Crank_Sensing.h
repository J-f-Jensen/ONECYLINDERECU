/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Crank_Sensing.h
\brief      Crankshaft sensing definitions and function prototypes
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Jaime Orozco
\ThirdParty Omar Hernandez/Rodrigo Ruiz (NACURI)
\version    0.2
\date       May/ 2008
*/
/*******************************************************************************/
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

#include <hidef.h>
/** Seabreeze Emulator Compilation Options */
#include "Seabreeze_Emulator.h"
/** S12X derivative information */
#include __S12X_DERIVATIVE
/** Variable types and common definitions */
#include "typedefs.h"
/** GPIO mapping */
#include "Input_Output.h"
/** Application definitions */
#include "Application Definitions.h" 

#include "Cpu.h"
#include "Timers.h"


//#if HARDWARE == (EMULATOR | PROTOTYPE)
//#define PREESCALER_VALUE    6   /* Timer clock = BUS_FREQ/(2^PREESCALER_VALUE) */
//                                /* 40MHz/64 = 625kHz; timer period = 1.6us */                           
//#else if HARDWARE = REFERENCE
//#define PREESCALER_VALUE    5   /* Timer clock = BUS_FREQ/(2^PREESCALER_VALUE) */
//                                /* 20MHz/32 = 625kHz; timer period = 1.6us */                           

//#endif
                                    
//#define TIMER_FREQ          BUS_FREQ / (2^PREESCALER_VALUE)
//#define TIMER_FREQ          BUS_FREQ / 64

#define PREESCALER_VALUE    5   /* Timer clock = BUS_FREQ/(2^PREESCALER_VALUE) */
                                /* 16MHz/32 = 500kHz; timer period = 2us */  
								
//#define TIMER_FREQ          BUS_FREQ / (2^PREESCALER_VALUE)
#define TIMER_FREQ            BUS_FREQ / 32								


/* Minimum and maximum RPM result in a range of valid tooth periods,            */
///* these are calculated interms of timer tics, where one timer tic is 1.6us.    */
/* these are calculated interms of timer tics, where one timer tic is 2us.    */
/* Relationship between RPM and timer counts is:                                */
/* RPM = 60 / (Timer ticks * timer period * NUMBER_OF_TEETH)                    */

#define MAX_PERIOD_LIMIT    (UINT16)(60 * (TIMER_FREQ / RPM_MIN) / NUMBER_OF_TEETH)                                 
#define MIN_PERIOD_LIMIT    (UINT16)(60 * (TIMER_FREQ / RPM_MAX) / NUMBER_OF_TEETH)
    
/* A default timeout is set for conditions prior to getting the first 
   tooth period time.  This is set for the minimum RPM defined */   
#define DEFAULT_TIME_CRANKSHAFT_TIMEOUT MAX_PERIOD_LIMIT

// Skal dette ændres til 20 istedet for 16 ???
/* Minimum and maximum values of the gap ratio 
   are based on tooth tolerance specified */
#define MIN_GAP_RATIO  16 * GAP_RATIO - (16 * NEG_PERIOD_PERCENTAGE) / 100
#define MAX_GAP_RATIO  16 * GAP_RATIO + (16 * POS_PERIOD_PERCENTAGE) / 100


/** Timer channel assigned to crankshaft sensing */
#define CRANKSHAFT_TIMER                TIMER_CHANNEL_H     
/** Timer channel assigned to crankshaft sensing */
#define CRANKSHAFT_TIMER_COUNTER        TIMER_COUNTER     

/** Timer channel interrupt enable/disable */
#define CRANKSHAFT_INTERRUPT(SELECTOR)  CHANNEL_H_INTERRUPT(SELECTOR) 

/** Timer channel assigned to missing tooth detection*/
#define GAP_TIMER                       TIMER_CHANNEL_F  
/** Timer channel interrupt enable/disable */  
#define GAP_INTERRUPT(SELECTOR)         CHANNEL_F_INTERRUPT(SELECTOR) 

/** Timer channel assigned to timeout interrupt */
#define TIMEOUT_TIMER                   TIMER_CHANNEL_E  
/** Timer channel interrupt enable/disable */  
#define TIMEOUT_INTERRUPT(SELECTOR)     CHANNEL_E_INTERRUPT(SELECTOR) 

                            
/* EVB LEDs */
#if HARDWARE == EMULATOR
#define SYNCH_LED   LED4     /* Synchronization signal */
#define TDC_LED     LED5     /* Top dead center signal */
#endif

#define ON_STATE    LOW
#define OFF_STATE   HIGH

/* States definition */
enum
{
TOOTH_INIT,
FIRST_EDGE,
FIRST_PERIOD,
TESTING_FOR_GAP,
VALIDATING_GAP,
SYNCHRONIZED,
SYNCHRONIZED_4C
};

/** Function prototypes */

/** Timers initialization for crankshaft sensing */
void vfnInit_Crank_Sensing(void);

/** Go to first edge state */
void vfnGoTo_Crank_FirstEdge(void);

/** Got the the 4 cycle sync state */
#ifdef FOUR_STROKES
void  vfnGoTo_SYNCHRONIZED_4C(void);
#endif

/** Tooth edge time capture */
UINT8 u8Calculate_Tooth_Period(void);

/** Validates that tooth period is within valid range*/
UINT8 u8Valid_Period(void);

/** Stores the Current Tooth Period to an array*/
void vfnTooth_Period_Store(void);

/** Set timeout for next edge detection */
void vfnSet_Period_Timeout(void);

/** Validates that current period corresponds to missing tooth gap */
UINT8 u8Missing_Tooth_Gap(void);

/** Validates that current period corresponds to tooth after gap */
UINT8 u8Tooth_After_Gap(void);

/** Tooth counting */ 
void vfnIncrement_Teeth_Counter(void);


#pragma CODE_SEG __NEAR_SEG NON_BANKED
/** Crankshaft sensing state machine */
void interrupt Crank_State_Machine_Isr(void);

/** Missing tooth interrupt Service routine */
void interrupt Crank_Missing_Tooth_Isr(void);

/** Timeout interrupt service routine */
void interrupt Crank_Timeout_Isr(void);

#pragma CODE_SEG DEFAULT


/*******************************************************************************/