/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Seabreeze_Hardware.h
\brief      Seabreeze Emulator Compilation Options.
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Abraham Tezmol
\version    0.1
\date       15/Feb/2008
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

#ifndef __SEABREEZE_EMULATOR
#define __SEABREEZE_EMULATOR

/*-- Includes ----------------------------------------------------------------*/
#include "mc9s12t64.h" //MCU definitions not in generic.h

/*-- Types Definitions -------------------------------------------------------*/

/*-- Defines -----------------------------------------------------------------*/

/** Target firmware option - Select ONLY one */
#define __EMULATOR_HARDWARE_FIRMWARE

/** S12(X) Derivative Selection - Select ONLY one */
//#define __S12P128

/*-- Macros ------------------------------------------------------------------*/

#define __S12X_DERIVATIVE <generic.h> //No header for MC9S12T64 use this instead




/** S12X derivative information */
#ifdef  __S12P128
    #define __S12X_DERIVATIVE   <mc9s12p128.h>
    #define __S12X_LINK_DERIVATIVE  "mc9s12p128"
#else    
    #ifdef  __S12XS128
        #define __S12X_DERIVATIVE   <mc9s12xs128.h>
        #define __S12X_LINK_DERIVATIVE  "mc9s12xs128"
    #else    
        #ifdef  __S12XS256
          #define __S12X_DERIVATIVE   <mc9s12xs256.h> 
          #define __S12X_LINK_DERIVATIVE  "mc9s12xs256"
        #else    
          #ifdef __S12XEP100  
            #define __S12X_DERIVATIVE   <mc9s12xep100.h>
            #define __S12X_LINK_DERIVATIVE  "mc9s12xep100"
          #endif
        #endif
    #endif
#endif
/*-- Function Prototypes -----------------------------------------------------*/

#endif /*__SEABREEZE_EMULATOR */
