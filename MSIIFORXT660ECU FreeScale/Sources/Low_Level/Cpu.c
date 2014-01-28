/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Cpu.c
\brief      S12XEP100 CPU initialization, bus clock @40MHz \n
            and interrupts configuration routines
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Abraham Tezmol
\version    0.4
\date       11/Feb/2008
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
/** CPU initialization prototypes and definitions */
#include "cpu.h"
/** Variable types and common definitions */
#include "typedefs.h"   
/** Hardware variables   */
#include "Application Definitions.h"


/* -- Variables --------------------------------------------------------*/

/* Global variable that holds status of Clock */
UINT16 gu16ClockGlobalStatus;
/* Loss of Lock counter, private variable */
static UINT16 u16PLL_Loss_of_Lock_Counter;

/*******************************************************************************/
/**
* \brief    Other CPU initalization parameters
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     none
*/
void vfnCpu_init(void)
{


//Is this = CRAMON    // ?? MMCCTL1 = 1;    /* Enables Flash in the memory map */                
    // ?? DIRECT = 0;     /* Default location for direct page */              
    // ?? not in S12T64 PDF IVBR = 0xFF;    /* Default vector base address */    

    //Disable IRQ pin
    INTCR_IRQEN = 0;  // IRQCR_IRQEN is not in generic.h this is used instead
    // IRQCR_IRQEN = 0;
}

/*******************************************************************************/
/**
* \brief    PLL initialization, Bus Clock @ 40MHz
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnClock_Init(void)
{                  

  /********************************************/
  // S12T64 Extneral Oscillator code
  // 4MHz external resonator
  // 16MHz bus speed required
  // 250kHz ECLK output
  /*******************************************/
  /* Dette er oprindelige kode
  //Default mode is PEI using internal clock.
  //Transition to PEE using external clock.
  //Step 1- Configure the PLL for desired bus of 16MHz
  //set fvco to 32-48MHz
  CPMUSYNR_VCOFRQ = 0b00;
  //Set SYNDIV to 4 per fvco=2xfREF x (SYNRDIV+1)
  CPMUSYNR_SYNDIV = 4;
  
  //Step 2- Program the reference divider (REFDIV) to divide down reference 
  //frequency, if necessary.
  //set reference frequency range to 4MHz
  CPMUREFDIV_REFFRQ = 0b01;
  //set the REFDIV to 1 for divide by 2 of reference clock.
  CPMUREFDIV_REFDIV = 1;
  //No post divide of output
  CPMUPOSTDIV_POSTDIV = 0;
  
  //Step 3- Enable the external oscillator using OSCE bit 
  CPMUOSC_OSCE = 1;

  //Wait for oscillator to be up and running.
  while(!CPMUFLG_UPOSC){
    //never do this in production.  Use hardware timeout as failsafe to break loop.
  
  }
  //Oscillator is running.  Wait for PLL to lock.
  while(!CPMUFLG_LOCK){
    //never do this in production.  Use hardware timeout as failsafe to break loop.
    //Also implement loss of lock interrupts as well.
  }
  */
  
  // initalize PLL - reset default is Oscillator clock
  // 4 MHz oscillator, PLL freq = 32 MHz, 16 MHz bus, 
  //  divide by 16 for timer of 2/3 usec tic
  PLLCTL &= 0xBF;     // Turn off PLL so can change freq
  SYNR = 0x08;        // set PLL/ Bus freq to 32 / 16 MHz
  REFDV = 0x00;
  PLLCTL |= 0x40;     // Turn on PLL
  
  // wait for PLL lock
  while (!(CRGFLG & 0x08));
  
  //Bus frequency should be 16 MHz.
  
  //Output ECLK at 250kHz for validation
  //Turn on output of ECLK
// ECLKCTL_NECLK = 0;
  //Set to divide by 8
// ECLKCTL_EDIV = 7;
  //Set to divide input clock by 16
// ECLKCTL_DIV16 = 1;
    
}

/*******************************************************************************/
/**
* \brief    Clock monitor Interrupt Service routine.
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt Clock_Monitor_Isr(void)
{   
    //Loss of lock not supported for S12P yet.
    //Only development using S12XS and S12XE.
    #if HARDWARE == (EMULATOR | PROTOTYPE)

    /* Verify that IPLL Lock Interrupt Flag caused the interrupt */
    if (CRGFLG_LOCKIF == 1)
    {
        /* Clear IPLL Lock Interrupt Flag */  
        CRGFLG_LOCKIF = 1;
        /* Update Loss-of-Lock event counter */
        u16PLL_Loss_of_Lock_Counter++;
        if (u16PLL_Loss_of_Lock_Counter >= 5)
        {
            /* Set gu16ClockGlobalStatus to its appropriate status */
            gu16ClockGlobalStatus = CLOCK_STATUS_PLL_LOCK_ERROR;
            /* Configure all I/O to their default values */
            
            /* If we reach Loss-of-Lock 5 consecutive times, get into an infinite loop */
            for (;;){;}
        }
    }
    else
    {        
        /* Verify that Self Clock Mode Interrupt flag caused the interrupt */
        if (CRGFLG_SCMIF == 1)
        {
            /* Clear Self Clock Mode Interrupt Flag */
            CRGFLG_SCMIF = 1;
            /* Set gu16ClockGlobalStatus to its appropriate status */ 
            gu16ClockGlobalStatus = CLOCK_STATUS_SCM_ERROR;        
            /* If we reach SCM condition, get into an infinite loop */
            for (;;){;}                
        }
    }
   #endif
}
#pragma CODE_SEG DEFAULT    
        
/*******************************************************************************/
