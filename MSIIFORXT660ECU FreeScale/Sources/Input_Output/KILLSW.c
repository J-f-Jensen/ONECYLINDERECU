/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       KILLSW.c
\brief      Kill Switch Monitoring
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
/** Kill Switch function prototypes */
#include "KILLSW.h"
/** Input Output macros and definitions */
#include "Input_Output.h"

static UINT8 u8KILLSW_Collection_Rate_Counter = 0;
static UINT8 u8KILLSW_Buffer_Counter = 0;
UINT8 u8KILLSW_Counter = 0;
UINT8 u8KILLSW_Filtered = 0;

/** Buffer used to collect Kill Switch data */
UINT8  au8KILLSW_Data_Buffer[KILLSW_BUFFER_SIZE];

/*******************************************************************************/
/**
* \brief    Initializations for Kill Switch Buffer
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnKILLSW_Init(void)
{ 
 #ifdef KILLSW              
 
   /** Initialization of Buffer used to collect Kill Switch data */
    for(u8KILLSW_Counter=0; u8KILLSW_Counter<KILLSW_BUFFER_SIZE; u8KILLSW_Counter++)
    {
        au8KILLSW_Data_Buffer[u8KILLSW_Counter] = 0;
    }      
    u8KILLSW_Counter = 0;
    
 #endif      
}

/*******************************************************************************/
/**
* \brief   Kill Switch Monitoring periodic rate check and buffer data collection
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnKILLSW_Monitoring(void)
{  
 #ifdef KILLSW              

   /** Waits for specified rate (this function is executed every ms) */               
   if(u8KILLSW_Collection_Rate_Counter >= KILLSW_DATA_COLLECTION_RATE)
   {
      au8KILLSW_Data_Buffer[u8KILLSW_Buffer_Counter] = (UINT8)(KILLSW_F);
  
      u8KILLSW_Buffer_Counter++;  
      u8KILLSW_Collection_Rate_Counter = 0;

      /** Every time the buffer is full the filter algorithm is called */                 
      if(u8KILLSW_Buffer_Counter >= KILLSW_BUFFER_SIZE) 
      {
         vfnKILLSW_Filter();  
         u8KILLSW_Buffer_Counter = 0; 
      }  
   } 
   else 
   {
      u8KILLSW_Collection_Rate_Counter++;
   }  
   
 #endif      
}

/*******************************************************************************/
/**
* \brief    Filter algorithm of the Kill Switch data buffer. Updates KILLSW_Filter var.
* \author   OH
* \param    Void
* \return   Void
*/
void vfnKILLSW_Filter(void)
{      
 #ifdef KILLSW              

       /** Checks that every value of the array is equal */  
       for(u8KILLSW_Counter=1; u8KILLSW_Counter<KILLSW_BUFFER_SIZE; u8KILLSW_Counter++)
       {
           if (au8KILLSW_Data_Buffer[u8KILLSW_Counter] != au8KILLSW_Data_Buffer[0])
              break;
       } 

       /** If all values are the same, puts the filtered var active or inactive */                 
       if(u8KILLSW_Counter == KILLSW_BUFFER_SIZE)
       {        
          if(au8KILLSW_Data_Buffer[0]) 
          {                        
             #ifdef KILLSW_ACTIVE_HIGH
                 u8KILLSW_Filtered = ON;
             #else 
                #ifdef KILLSW_ACTIVE_LOW             
                    u8KILLSW_Filtered = OFF;
                #endif
             #endif
          }          
          else
          {                        
             #ifdef KILLSW_ACTIVE_HIGH
                 u8KILLSW_Filtered = OFF;
             #else 
                #ifdef KILLSW_ACTIVE_LOW             
                    u8KILLSW_Filtered = ON;
                #endif
             #endif
          }

       }
 
  #endif      
} 
/*******************************************************************************/