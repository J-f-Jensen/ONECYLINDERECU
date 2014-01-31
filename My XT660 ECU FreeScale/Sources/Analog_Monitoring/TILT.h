/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       TILT.h
\brief      TILT sensor measurement - Lean angle CUT off.
\author     Freescale Semiconductor
\author     
\ThirdParty 
\version    0.1
\date       Sept 2013
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

#include <hidef.h>
/** MCU definitions */
#include "MCUdefinitions.h"


/** Variable types and common definitions */
#include "typedefs.h"

/* Data Sizing */
#ifdef Analog_Data_8
   #define TILT_DATA_SIZE 8
#else
   #ifdef Analog_Data_10
      #define TILT_DATA_SIZE 10
   #else
      #define TILT_DATA_SIZE 12     
   #endif
#endif

/* Define for specifing the ADC channel used for TILT - Lean angle CUT off*/
#define TILT_ADC_CHANNEL 5

/* MAF data collection rate check 
#if MAF_DATA_COLLECTION_RATE < DATA_MANAGEMENT_TASK
#error " MAF is faster than the timeout period of the Data Management Task"
#endif*/

/** Function prototypes */
 
 void vfnTILT_ADC_Filter(void);
 void vfnTILT_Monitoring(UINT16 sample);
 void vfnTILT_Init(void);

/*******************************************************************************/