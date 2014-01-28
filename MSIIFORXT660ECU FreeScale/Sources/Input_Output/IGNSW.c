/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       IGNSW.c
\brief      Ignition Switch Monitoring.
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Jaime Orozco
\ThirdParty Omar Hernandez/Rodrigo Ruiz (NACURI)
\version    0.2
\date       Aug/ 2008
*/
/*******************************************************************************/

/** Application definitions */
#include "Application Definitions.h"
/** Ignition Switch function prototypes */
#include "IGNSW.h"
/** Input Output macros and definitions */
#include "Input_Output.h"

static UINT8 u8IGNSW_Collection_Rate_Counter = 0;
static UINT8 u8IGNSW_Buffer_Counter = 0;
UINT8 u8IGNSW_Counter = 0;
UINT8 u8IGNSW_Filtered = 0;

/** Buffer used to collect Ignition Switch data */
UINT8  au8IGNSW_Data_Buffer[IGNSW_BUFFER_SIZE];

/*******************************************************************************/
/**
* \brief    Initializations for Ignition Switch Buffer
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnIGNSW_Init(void)
{ 
 #ifdef IGNSW              
 
   /** Initialization of Buffer used to collect Ignition Switch data */
    for(u8IGNSW_Counter=0; u8IGNSW_Counter<IGNSW_BUFFER_SIZE; u8IGNSW_Counter++)
    {
        au8IGNSW_Data_Buffer[u8IGNSW_Counter] = 0;
    }      
    u8IGNSW_Counter = 0;
    
 #endif      
}

/*******************************************************************************/
/**
* \brief    Ignition Switch Monitoring periodic rate check and buffer data collection
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnIGNSW_Monitoring(void)
{  
 #ifdef IGNSW              

   /** Waits for specified rate (this function is executed every ms) */               
   if(u8IGNSW_Collection_Rate_Counter >= IGNSW_DATA_COLLECTION_RATE)
   {
      au8IGNSW_Data_Buffer[u8IGNSW_Buffer_Counter] = (UINT8)(KEYSW_F);
  
      u8IGNSW_Buffer_Counter++;  
      u8IGNSW_Collection_Rate_Counter = 0;

      /** Every time the buffer is full the filter algorithm is called */                 
      if(u8IGNSW_Buffer_Counter >= IGNSW_BUFFER_SIZE) 
      {
         vfnIGNSW_Filter();  
         u8IGNSW_Buffer_Counter = 0; 
      }  
   } 
   else 
   {
      u8IGNSW_Collection_Rate_Counter++;
   }  
   
 #endif      
}

/*******************************************************************************/
/**
* \brief    Filter algorithm of the Ignition Switch data buffer. Updates IGNSW_Filter var.
* \author   OH
* \param    Void
* \return   Void
*/
void vfnIGNSW_Filter(void)
{      
 #ifdef IGNSW              

       /** Checks that every value of the array is equal */  
       for(u8IGNSW_Counter=1; u8IGNSW_Counter<IGNSW_BUFFER_SIZE; u8IGNSW_Counter++)
       {
           if (au8IGNSW_Data_Buffer[u8IGNSW_Counter] != au8IGNSW_Data_Buffer[0])
              break;
       } 

       /** If all values are the same, puts the filtered var active or inactive */                 
       if(u8IGNSW_Counter == IGNSW_BUFFER_SIZE)
       {        
          if(au8IGNSW_Data_Buffer[0]) 
          {                        
             #ifdef IGNSW_ACTIVE_HIGH
                 u8IGNSW_Filtered = ON;
             #else 
                #ifdef IGNSW_ACTIVE_LOW             
                    u8IGNSW_Filtered = OFF;
                #endif
             #endif
          }          
          else
          {                        
             #ifdef IGNSW_ACTIVE_HIGH
                 u8IGNSW_Filtered = OFF;
             #else 
                #ifdef IGNSW_ACTIVE_LOW             
                    u8IGNSW_Filtered = ON;
                #endif
             #endif
          }

       }
 
  #endif      
} 
/*******************************************************************************/