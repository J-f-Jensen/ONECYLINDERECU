/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       ADC.h
\brief      Analog to Digital Converter Interface functions
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Luis Olea
\version    0.2
\date       November/ 2008
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

#ifndef __ADC_H        /*prevent duplicated includes*/
#define __ADC_H

/*-- Includes ----------------------------------------------------------------*/

/** Variable types and common definitions */
#include "typedefs.h"
/** CPU common definitions */
#include "CPU.h"

/*-- Defines -----------------------------------------------------------------*/
/* ADC channels to sample */
#define     ADC_CHANNELS_TO_SAMPLE  8
/* ADC Sample buffer depth per channel */
#define     ADC_SAMPLE_BUFFER_SIZE  16
/*Global ADC engine definitions*/
#define     ADC_CLOCK_FREQ          4000000

/*-- Types Definitions -------------------------------------------------------*/

typedef struct
{
    /* ADC conversion result buffer */
    UINT16 u16Sample[ADC_SAMPLE_BUFFER_SIZE];
}sAnalogDatachannel_t;

/*-- Macros ------------------------------------------------------------------*/
#define     ADC_PRESCALER_VALUE     ((BUS_FREQ)/(2*ADC_CLOCK_FREQ)-1)

#define vfn_convertADC_Channel(arg) ATD0CTL5_Cx = arg

#define vfnADC_Start_Conversions()   ATD0CTL5 = signals_array[0]


/*-- Function Prototypes -----------------------------------------------------*/

/** ADC Initalization */
void vfnADC_Init(void);
/** Read ADC data from conversion sequence and store it into data buffers */
void vfnADC_Read_Channels(void);
/* Read ADC data from a single channel and return the read */
UINT16 u16fnADC_Read_One_Channel(UINT8);
/* Compute the average for each analog sample buffer */
void vfnADC_Compute_Average(void);
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt ATD0_conversion_complete(void);
#pragma CODE_SEG DEFAULT
/*******************************************************************************/

#endif /* __ADC_H */