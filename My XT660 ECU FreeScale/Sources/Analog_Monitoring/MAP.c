/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       MAP.c
\brief      Manifold Absolute Pressure Monitoring.
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
/** MAP function prototypes */
#include "MAP.h"
/** ADC function prototypes */
#include "ADC.h"

/** Data Sizing */
#if MAP_DATA_SIZE == 8
   UINT8  MAP_Filtered = 0;
#else 
   UINT16 MAP_Filtered = 0;
#endif

static UINT8 u8MAP_Collection_Rate_Counter = 0;
static UINT8 u8MAP_Buffer_Counter = 0;
UINT8 u8MAP_Counter = 0;


/** Buffer used to collect MAP data */
#ifdef MAP
  #if MAP_DATA_SIZE == 8
    UINT8  MAP_Data_Buffer[MAP_BUFFER_SIZE];
  #else 
    UINT16 MAP_Data_Buffer[MAP_BUFFER_SIZE];  
  #endif
#endif


/** variable used tooth based data collection */
extern UINT8 u8Teeth_Counter;

//Raw ADC  buffer
#if MAP_DATA_SIZE == 8
  extern UINT8 RAW_ADC[];
#else 
  extern UINT16 RAW_ADC[];
#endif


/*******************************************************************************/
/**
* \brief    Initializations for MAP
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnMAP_Init(void)
{            
#ifdef MAP
   
   /** Initialization Buffer used to collect MAP data */
    for(u8MAP_Counter=0; u8MAP_Counter<MAP_BUFFER_SIZE; u8MAP_Counter++)
    {
        MAP_Data_Buffer[u8MAP_Counter] = 0;
    }        


#endif
}


/*******************************************************************************/
/**
* \brief    MAP Data Collection Rate. Time or tooth based.
* \author   OH 
* \param    Void
* \return   Void
*/

#ifdef MAP
void vfnMAP_Monitoring(UINT16 sample)
{    

extern UINT16 samples_array[];
extern UINT8  signals_pointer;
           

   #ifdef MAP_TIME_BASED
      //Check for user defined timeout.
      if(u8MAP_Collection_Rate_Counter >= MAP_DATA_COLLECTION_RATE)
      {         

         #if MAP_DATA_SIZE == 8
            MAP_Data_Buffer[u8MAP_Buffer_Counter] = (UINT8)RAW_ADC[MAP_ADC_CHANNEL];//(UINT8)(u16fnADC_Read_One_Channel(MAP_ADC_CHANNEL));
         #else 
            MAP_Data_Buffer[u8MAP_Buffer_Counter] = RAW_ADC[MAP_ADC_CHANNEL];//u16fnADC_Read_One_Channel(MAP_ADC_CHANNEL);
         #endif
     
         u8MAP_Buffer_Counter++;  
         u8MAP_Collection_Rate_Counter = 0;
  
         if(u8MAP_Buffer_Counter >= MAP_BUFFER_SIZE) 
         {
            vfnMAP_ADC_Filter();  
            u8MAP_Buffer_Counter = 0; 
         }
  
      } 
      else 
      {
         u8MAP_Collection_Rate_Counter++;
      }
  
   #endif

   #ifdef MAP_TOOTH_BASED
      //Only collect data for specific teeth.
      if((u8Teeth_Counter >= MAP_TOOTH_START) && (u8Teeth_Counter <= (MAP_TOOTH_END))) 
      {       
         //The current tooth is in the range for data collection.
         //Now make sure you only collect one data value fo each tooth.
         //Number of samples/teeth used for sampling must equal the size of the buffer.
         //Compare the buffer counter to the difference in current tooth and starting
         //MAP tooth.  Since we will increment the buffer counter after we accept a 
         //sample, it will only match once per tooth.  
         if(u8MAP_Buffer_Counter == (u8Teeth_Counter - MAP_TOOTH_START)){
          //This is the first sample for this tooth.
          //Store to the buffer.
         
          //Data comes from the raw buffer
          #if MAP_DATA_SIZE == 8
            MAP_Data_Buffer[u8MAP_Buffer_Counter] =(UINT8)RAW_ADC[MAP_ADC_CHANNEL];
          #else 
            MAP_Data_Buffer[u8MAP_Buffer_Counter] = RAW_ADC[MAP_ADC_CHANNEL];
          #endif
          
          //Increment the buffer counter.  Also limits the acceptance of data
          //to once per tooth.
          u8MAP_Buffer_Counter++;  
         }
         
         if(u8Teeth_Counter == (MAP_TOOTH_END)) 
         {
            u8MAP_Buffer_Counter = 0; 
         }
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
#ifdef MAP
void vfnMAP_ADC_Filter(void)
{
  
     #ifdef AVERAGE_FILTER_MAP
 
       UINT16 u16Average = 0;
    
       for(u8MAP_Counter=0; u8MAP_Counter<MAP_BUFFER_SIZE; u8MAP_Counter++)
       {
           u16Average += MAP_Data_Buffer[u8MAP_Counter];
       } 
    
       u16Average = u16Average >> 4;
           
       #if MAP_DATA_SIZE == 8
          MAP_Filtered = (UINT8)(u16Average);
       #else 
          MAP_Filtered = u16Average;
       #endif
       
     #endif
  
     #ifdef OTHER_FILTER_MAP
     
        //OTHER FILTER ALGORITHM CODE 
       
     #endif  
  
  
}
#endif
 
/*******************************************************************************/