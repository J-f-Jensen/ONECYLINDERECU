/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Engine Management.h
\brief      Engine management definitions and function prototypes
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Jaime Orozco
\version    0.1
\date       September/ 2008
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

/** Application definitions */
#include "Application Definitions.h"


/** Function prototypes */

/** Resources initialization for engine management */
void Engine_Management_Init(void);

/** Engine control: calculates the timing for spark and fuel pulses */
void Engine_Management(void);


/** Updates parameters to start fuel pulse 1 */
void vfnFuel1_Start(UINT16 u16RPM, UINT16 u16LOAD);

/** Calculates fuel pulse 1 width */
void vfnFuel1_Pulse(UINT16 u16RPM, UINT16 u16LOAD);

/** Low Level calculation for spark start angle */
UINT16 u16Calc_Spark_Start(UINT16, UINT16, UINT16);

/** Calculates spark 1 start angle */
void vfnSpark1_Start(UINT16, UINT16);

/** Calculates spark 1 dwell time */
void vfnSpark1_Dwell(void);


#ifdef TWO_CYLINDER

/** Updates parameters to start fuel pulse 2 */
void vfnFuel2_Start(UINT16 u16RPM, UINT16 u16LOAD);

/** Calculates fuel pulse 2 width */
void vfnFuel2_Pulse(UINT16 u16RPM, UINT16 u16LOAD);

/** Calculates spark 1 start angle */
void vfnSpark2_Start(UINT16 u16RPM, UINT16 u16LOAD);

/** Calculates spark 1 dwell time */
void vfnSpark2_Dwell(void);

#endif

/*******************************************************************************/