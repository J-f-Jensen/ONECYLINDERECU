/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       KICKSW.c
\brief      Kickstand Switch Monitoring
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
/** Kickstand Switch function prototypes */
#include "KICKSW.h"
/** Input Output macros and definitions */
#include "Input_Output.h"

static UINT8 u8KICKSW_Collection_Rate_Counter = 0;
static UINT8 u8KICKSW_Buffer_Counter = 0;
UINT8 u8KICKSW_Counter = 0;
UINT8 u8KICKSW_Filtered = 0;

/** Buffer used to collect Kickstand Switch data */
UINT8  au8KICKSW_Data_Buffer[KICKSW_BUFFER_SIZE];

/*******************************************************************************/
/**
* \brief    Initializations for Kickstand Switch Buffer
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnKICKSW_Init(void)
{ 
 #ifdef KICKSW              
 
   /** Initialization of Buffer used to collect Kickstand Switch data */
    for(u8KICKSW_Counter=0; u8KICKSW_Counter<KICKSW_BUFFER_SIZE; u8KICKSW_Counter++)
    {
        au8KICKSW_Data_Buffer[u8KICKSW_Counter] = 0;
    }      
    u8KICKSW_Counter = 0;
    
 #endif      
}

/*******************************************************************************/
/**
* \brief   Kickstand Switch Monitoring periodic rate check and buffer data collection
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnKICKSW_Monitoring(void)
{  
 #ifdef KICKSW              

   /** Waits for specified rate (this function is executed every ms) */               
   if(u8KICKSW_Collection_Rate_Counter >= KICKSW_DATA_COLLECTION_RATE)
   {
      au8KICKSW_Data_Buffer[u8KICKSW_Buffer_Counter] = (UINT8)(KICKSW_F);
  
      u8KICKSW_Buffer_Counter++;  
      u8KICKSW_Collection_Rate_Counter = 0;

      /** Every time the buffer is full the filter algorithm is called */                 
      if(u8KICKSW_Buffer_Counter >= KICKSW_BUFFER_SIZE) 
      {
         vfnKICKSW_Filter();  
         u8KICKSW_Buffer_Counter = 0; 
      }  
   } 
   else 
   {
      u8KICKSW_Collection_Rate_Counter++;
   }  
   
 #endif      
}

/*******************************************************************************/
/**
* \brief    Filter algorithm of the Kickstand Switch data buffer. Updates KICKSW_Filter var.
* \author   OH
* \param    Void
* \return   Void
*/
void vfnKICKSW_Filter(void)
{      
 #ifdef KICKSW              

       /** Checks that every value of the array is equal */  
       for(u8KICKSW_Counter=1; u8KICKSW_Counter<KICKSW_BUFFER_SIZE; u8KICKSW_Counter++)
       {
           if (au8KICKSW_Data_Buffer[u8KICKSW_Counter] != au8KICKSW_Data_Buffer[0])
              break;
       } 

       /** If all values are the same, puts the filtered var active or inactive */                 
       if(u8KICKSW_Counter == KICKSW_BUFFER_SIZE)
       {        
          if(au8KICKSW_Data_Buffer[0]) 
          {                        
             #ifdef KICKSW_ACTIVE_HIGH
                 u8KICKSW_Filtered = ON;
             #else 
                #ifdef KICKSW_ACTIVE_LOW             
                    u8KICKSW_Filtered = OFF;
                #endif
             #endif
          }          
          else
          {                        
             #ifdef KICKSW_ACTIVE_HIGH
                 u8KICKSW_Filtered = OFF;
             #else 
                #ifdef KICKSW_ACTIVE_LOW             
                    u8KICKSW_Filtered = ON;
                #endif
             #endif
          }

       }
 
  #endif      
} 
/*******************************************************************************/