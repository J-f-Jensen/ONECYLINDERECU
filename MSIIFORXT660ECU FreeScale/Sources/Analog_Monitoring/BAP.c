/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       BAP.c
\brief      Barometric Air Pressure Monitoring
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\ThirdParty Omar Hernandez/Rodrigo Ruiz (NACURI)
\version    0.1
\date       Jul/ 2008
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
/** BAP function prototypes */
#include "BAP.h"
/** ADC function prototypes */
#include "ADC.h"

/** Data Sizing */
#if BAP_DATA_SIZE == 8
   UINT8  BAP_Filtered = 0;
#else 
   UINT16 BAP_Filtered = 0;
#endif

static UINT8 u8BAP_Collection_Rate_Counter = 0;
static UINT8 u8BAP_Buffer_Counter = 0;
UINT8 u8BAP_Counter = 0;


/** Buffer used to collect BAP data */
#ifdef BAP
  #if BAP_DATA_SIZE == 8
    UINT8  BAP_Data_Buffer[BAP_BUFFER_SIZE];
  #else 
    UINT16 BAP_Data_Buffer[BAP_BUFFER_SIZE];  
  #endif
#endif

//Raw ADC  buffer
#if BAP_DATA_SIZE == 8
  extern UINT8 RAW_ADC[];
#else 
  extern UINT16 RAW_ADC[];
#endif

/*******************************************************************************/
/**
* \brief    Initializations for BAP functions required variables
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnBAP_Init(void)
{            
#ifdef BAP
   
   /** Initialization Buffer used to collect BAP data */
    for(u8BAP_Counter=0; u8BAP_Counter<BAP_BUFFER_SIZE; u8BAP_Counter++)
    {
        BAP_Data_Buffer[u8BAP_Counter] = 0;
    }        

#endif
}


/*******************************************************************************/
/**
* \brief    BAP Data Collection Rate
* \author   OH 
* \param    Void
* \return   Void
*/

#ifdef BAP
void vfnBAP_Monitoring(UINT16 sample)
{    

extern UINT16 samples_array[];
extern UINT8  signals_pointer;
           
  #if HARDWARE == (EMULATOR | PROTOTYPE)
         //PIT triggered collection so no need to worry about time base.

         #if BAP_DATA_SIZE == 8
            BAP_Data_Buffer[u8BAP_Buffer_Counter] = (UINT8)sample;//(UINT8)(u16fnADC_Read_One_Channel(BAP_ADC_CHANNEL));
         #else 
            BAP_Data_Buffer[u8BAP_Buffer_Counter] = sample;//u16fnADC_Read_One_Channel(BAP_ADC_CHANNEL);
         #endif
     
         u8BAP_Buffer_Counter++;  
         u8BAP_Collection_Rate_Counter = 0;
  
         if(u8BAP_Buffer_Counter >= BAP_BUFFER_SIZE) 
         {
            vfnBAP_ADC_Filter();  
            u8BAP_Buffer_Counter = 0; 
         }
  
  #else if HARDWARE == REFERENCE
      //Check for user defined timeout.
      if(u8BAP_Collection_Rate_Counter >= BAP_DATA_COLLECTION_RATE)
      {         

         #if BAP_DATA_SIZE == 8
            BAP_Data_Buffer[u8BAP_Buffer_Counter] = (UINT8)RAW_ADC[BAP_ADC_CHANNEL];//(UINT8)(u16fnADC_Read_One_Channel(BAP_ADC_CHANNEL));
         #else 
            BAP_Data_Buffer[u8BAP_Buffer_Counter] = RAW_ADC[BAP_ADC_CHANNEL];//u16fnADC_Read_One_Channel(BAP_ADC_CHANNEL);
         #endif
     
         u8BAP_Buffer_Counter++;  
         u8BAP_Collection_Rate_Counter = 0;
  
         if(u8BAP_Buffer_Counter >= BAP_BUFFER_SIZE) 
         {
            vfnBAP_ADC_Filter();  
            u8BAP_Buffer_Counter = 0; 
         }
  
      } 
      else 
      {
         u8BAP_Collection_Rate_Counter++;
      }
  
  #endif      
  
}
#endif

/*******************************************************************************/
/**
* \brief    Filters the sample buffer data with specified algorithm.
* \author   OH
* \param    Void
* \return   Void
*/

#ifdef BAP
void vfnBAP_ADC_Filter(void)
{
  
     #ifdef BAP_AVERAGE_FILTER
 
       UINT16 u16Average = 0;
    
       for(u8BAP_Counter=0; u8BAP_Counter<BAP_BUFFER_SIZE; u8BAP_Counter++)
       {
           u16Average += BAP_Data_Buffer[u8BAP_Counter];
       } 
    
       u16Average = u16Average >> 4;
           
       #if BAP_DATA_SIZE == 8
          BAP_Filtered = (UINT8)(u16Average);
       #else 
          BAP_Filtered = u16Average;
       #endif
       
     #endif
  
     #ifdef OTHER_FILTER_BAP
     
        //OTHER FILTER ALGORITHM CODE FOR BAP
       
     #endif  
  
  
}
#endif
 
/*******************************************************************************/