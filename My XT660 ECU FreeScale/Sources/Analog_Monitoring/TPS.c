/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       TPS.c
\brief      Throttle Position Monitoring.
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\ThirdParty Omar Hernandez/Rodrigo Ruiz (NACURI)
\version    0.1
\date       Jun/ 2008
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

/** Application definitions */
#include "Application Definitions.h"
/** TPS function prototypes */
#include "TPS.h"
/** ADC function prototypes */
#include "ADC.h"

/** Data Sizing */
#if TPS_DATA_SIZE == 8
   UINT8  TPS_Filtered = 0;
#else 
   UINT16 TPS_Filtered = 0;
#endif

static UINT8 u8TPS_Collection_Rate_Counter = 0;
static UINT8 u8TPS_Buffer_Counter = 0;
UINT8 u8TPS_Counter = 0;


/** Buffer used to collect TPS data */
#ifdef TPS
  #if TPS_DATA_SIZE == 8
    UINT8  TPS_Data_Buffer[TPS_BUFFER_SIZE];
  #else 
    UINT16 TPS_Data_Buffer[TPS_BUFFER_SIZE];  
  #endif
#endif

//Raw ADC  buffer
#if TPS_DATA_SIZE == 8
  extern UINT8 RAW_ADC[];
#else 
  extern UINT16 RAW_ADC[];
#endif

/*******************************************************************************/
/**
* \brief    Initializations for throttle position sensing
* \author   OH 
* \param    Void
* \return   Void
*/
void vfnTPS_Init(void)
{            
#ifdef TPS
   
   /** Initialization Buffer used to collect TPS data */
    for(u8TPS_Counter=0; u8TPS_Counter<TPS_BUFFER_SIZE; u8TPS_Counter++)
    {
        TPS_Data_Buffer[u8TPS_Counter] = 0;
    }        

#endif
}

/*******************************************************************************/
/**
* \brief    Requirement X
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnTPS_Monitoring(UINT16 sample)
{    

extern UINT16 samples_array[];
extern UINT8  signals_pointer;
           
#ifdef TPS
 
  #if HARDWARE == (EMULATOR | PROTOTYPE)
         //PIT triggered collection so no need to worry about time base.

         #if TPS_DATA_SIZE == 8
            TPS_Data_Buffer[u8TPS_Buffer_Counter] = (UINT8)sample;//(UINT8)(u16fnADC_Read_One_Channel(TPS_ADC_CHANNEL));
         #else 
            TPS_Data_Buffer[u8TPS_Buffer_Counter] = sample;//u16fnADC_Read_One_Channel(TPS_ADC_CHANNEL);
         #endif
     
         u8TPS_Buffer_Counter++;  
         u8TPS_Collection_Rate_Counter = 0;
  
         if(u8TPS_Buffer_Counter >= TPS_BUFFER_SIZE) 
         {
            vfnTPS_ADC_Filter();  
            u8TPS_Buffer_Counter = 0; 
         }
  
  #else if HARDWARE == REFERENCE
      //Check for user defined timeout.
      if(u8TPS_Collection_Rate_Counter >= TPS_DATA_COLLECTION_RATE)
      {         

         #if TPS_DATA_SIZE == 8
            TPS_Data_Buffer[u8TPS_Buffer_Counter] = (UINT8)RAW_ADC[TPS_ADC_CHANNEL];//(UINT8)(u16fnADC_Read_One_Channel(TPS_ADC_CHANNEL));
         #else 
            TPS_Data_Buffer[u8TPS_Buffer_Counter] = RAW_ADC[TPS_ADC_CHANNEL];//u16fnADC_Read_One_Channel(TPS_ADC_CHANNEL);
         #endif
     
         u8TPS_Buffer_Counter++;  
         u8TPS_Collection_Rate_Counter = 0;
  
         if(u8TPS_Buffer_Counter >= TPS_BUFFER_SIZE) 
         {
            vfnTPS_ADC_Filter();  
            u8TPS_Buffer_Counter = 0; 
         }
  
      } 
      else 
      {
         u8TPS_Collection_Rate_Counter++;
      }
  
  #endif      

#endif
}

/*******************************************************************************/
/**
* \brief    Compute the average for specific analog sample buffer.
* \author   OH
* \param    Channel to calculate
* \return   Average calculation
*/
void vfnTPS_ADC_Filter(void)
{
  #ifdef TPS
  
     #ifdef TPS_AVERAGE_FILTER
 
       UINT32 u32Average = 0;
    
       for(u8TPS_Counter=0; u8TPS_Counter<TPS_BUFFER_SIZE; u8TPS_Counter++)
       {
           u32Average += TPS_Data_Buffer[u8TPS_Counter];
       } 
    
       u32Average = u32Average >> 4;
                  
       #if TPS_DATA_SIZE == 8
          TPS_Filtered = (UINT8)(u32Average);
       #else 
          TPS_Filtered = (UINT16)(u32Average);
       #endif
       
     #endif
  
     #ifdef OTHER_FILTER
     
        //OTHER FILTER ALGORITHM CODE 
       
     #endif  
  
  #endif
} 
/*******************************************************************************/