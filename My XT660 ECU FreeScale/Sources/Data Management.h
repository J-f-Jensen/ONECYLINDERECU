/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Data Management.h
\brief      Data management definitions and function prototypes
\author     Freescale Semiconductor
\author     Jesse Beeker
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


#include "Application Definitions.h"

/** Data management Initialization */
void Data_Management_Init(void);

void Data_Management(void);

/*
#pragma CODE_SEG __NEAR_SEG NON_BANKED


  void interrupt Data_Management_Digitals();
  void interrupt Data_Management_Analogs();
#pragma CODE_SEG DEFAULT
*/

//Signals array
extern const UINT8 signals_array[];
//Signals array pointer
extern UINT8 signals_pointer;


//Analog Data Variables

#if HARDWARE == REFERENCE
//Raw buffer of ADC results
  #ifdef Analog_Data_8
    extern unsigned char RAW_ADC[16];
  #else
    extern unsigned int RAW_ADC[16];
  #endif
#endif

//Throttle Position Sensor
#ifdef Analog_TPS
  #ifdef Analog_Data_8
  //8 bit TPS data
  extern unsigned char Analog_TPS_Buf[Analog_TPS_Bufsize];
  //Storage of the filtered data
  extern unsigned char Analog_TPS_Filtered;
  #else
  //10 or 12 bit data
  extern unsigned int Analog_TPS_Buf[Analog_TPS_Bufsize];
  //Storage of the filtered data
  extern unsigned int Analog_TPS_Filtered;
  #endif
//Current buffer index
extern unsigned char Analog_TPS_Index;
//Counter for measurement period
extern unsigned char Analog_TPS_Counter;
#endif



//Digital Data Variables

//Ignition Switch
#ifdef IGNSW
//Buffer for signal measurements
extern unsigned char au8IGNSW_Data_Buffer[IGNSW_BUFFER_SIZE];
//Storage of the filtered data
extern unsigned char u8IGNSW_Filtered;
//Current buffer index
extern unsigned char u8IGNSW_Buffer_Counter;
//Counter for measurement period
extern unsigned char u8IGNSW_Counter;
#endif




