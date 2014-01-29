/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       CLTCHSW.c
\brief      Clutch Switch Monitoring
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Jaime Orozco
\ThirdParty Omar Hernandez/Rodrigo Ruiz (NACURI)
\version    0.1
\date       Jul/ 2008
*/
/*******************************************************************************/

/** Application definitions */
#include "Application Definitions.h"
/** Clutch Switch function prototypes */
#include "CLTCHSW.h"
/** Input Output macros and definitions */
#include "Input_Output.h"

static UINT8 u8CLTCHSW_Collection_Rate_Counter = 0;
static UINT8 u8CLTCHSW_Buffer_Counter = 0;
UINT8 u8CLTCHSW_Counter = 0;
UINT8 u8CLTCHSW_Filtered = 0;

/** Buffer used to collect Clutch Switch data */
UINT8  au8CLTCHSW_Data_Buffer[CLTCHSW_BUFFER_SIZE];

/*******************************************************************************/
/**
* \brief    Initializations for Clutch Switch Buffer
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnCLTCHSW_Init(void)
{ 
 #ifdef CLTCHSW              
 
   /** Initialization of Buffer used to collect Clutch Switch data */
    for(u8CLTCHSW_Counter=0; u8CLTCHSW_Counter<CLTCHSW_BUFFER_SIZE; u8CLTCHSW_Counter++)
    {
        au8CLTCHSW_Data_Buffer[u8CLTCHSW_Counter] = 0;
    }      
    u8CLTCHSW_Counter = 0;
    
 #endif      
}

/*******************************************************************************/
/**
* \brief   Clutch Switch Monitoring periodic rate check and buffer data collection
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnCLTCHSW_Monitoring(void)
{  
 #ifdef CLTCHSW              

   /** Waits for specified rate (this function is executed every ms) */               
   if(u8CLTCHSW_Collection_Rate_Counter >= CLTCHSW_DATA_COLLECTION_RATE)
   {
      au8CLTCHSW_Data_Buffer[u8CLTCHSW_Buffer_Counter] = (UINT8)(CLTCHSW_F);
  
      u8CLTCHSW_Buffer_Counter++;  
      u8CLTCHSW_Collection_Rate_Counter = 0;

      /** Every time the buffer is full the filter algorithm is called */                 
      if(u8CLTCHSW_Buffer_Counter >= CLTCHSW_BUFFER_SIZE) 
      {
         vfnCLTCHSW_Filter();  
         u8CLTCHSW_Buffer_Counter = 0; 
      }  
   } 
   else 
   {
      u8CLTCHSW_Collection_Rate_Counter++;
   }  
   
 #endif      
}

/*******************************************************************************/
/**
* \brief    Filter algorithm of the Clutch Switch data buffer. Updates CLTCHSW_Filter var.
* \author   OH
* \param    Void
* \return   Void
*/
void vfnCLTCHSW_Filter(void)
{      
 #ifdef CLTCHSW              

       /** Checks that every value of the array is equal */  
       for(u8CLTCHSW_Counter=1; u8CLTCHSW_Counter<CLTCHSW_BUFFER_SIZE; u8CLTCHSW_Counter++)
       {
           if (au8CLTCHSW_Data_Buffer[u8CLTCHSW_Counter] != au8CLTCHSW_Data_Buffer[0])
              break;
       } 

       /** If all values are the same, puts the filtered var active or inactive */                 
       if(u8CLTCHSW_Counter == CLTCHSW_BUFFER_SIZE)
       {        
          if(au8CLTCHSW_Data_Buffer[0]) 
          {                        
             #ifdef CLTCHSW_ACTIVE_HIGH
                 u8CLTCHSW_Filtered = ON;
             #else 
                #ifdef CLTCHSW_ACTIVE_LOW             
                    u8CLTCHSW_Filtered = OFF;
                #endif
             #endif
          }          
          else
          {                        
             #ifdef CLTCHSW_ACTIVE_HIGH
                 u8CLTCHSW_Filtered = OFF;
             #else 
                #ifdef CLTCHSW_ACTIVE_LOW             
                    u8CLTCHSW_Filtered = ON;
                #endif
             #endif
          }

       }
 
  #endif      
} 
/*******************************************************************************/