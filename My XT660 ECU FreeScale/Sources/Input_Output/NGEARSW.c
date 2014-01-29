/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       NGEARSW.c
\brief      Neutral Gear Monitoring
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
/** Neutral Gear function prototypes */
#include "NGEARSW.h"
/** Input Output macros and definitions */
#include "Input_Output.h"

static UINT8 u8NGEARSW_Collection_Rate_Counter = 0;
static UINT8 u8NGEARSW_Buffer_Counter = 0;
UINT8 u8NGEARSW_Counter = 0;
UINT8 u8NGEARSW_Filtered = 0;

/** Buffer used to collect Neutral Gear data */
UINT8  au8NGEARSW_Data_Buffer[NGEARSW_BUFFER_SIZE];

/*******************************************************************************/
/**
* \brief    Initializations for Neutral Gear Buffer
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnNGEARSW_Init(void)
{ 
 #ifdef NGEARSW              
 
   /** Initialization of Buffer used to collect Neutral Gear data */
    for(u8NGEARSW_Counter=0; u8NGEARSW_Counter<NGEARSW_BUFFER_SIZE; u8NGEARSW_Counter++)
    {
        au8NGEARSW_Data_Buffer[u8NGEARSW_Counter] = 0;
    }      
    u8NGEARSW_Counter = 0;
    
 #endif      
}

/*******************************************************************************/
/**
* \brief   Neutral Gear Monitoring periodic rate check and buffer data collection
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnNGEARSW_Monitoring(void)
{  
 #ifdef NGEARSW              

   /** Waits for specified rate (this function is executed every ms) */               
   if(u8NGEARSW_Collection_Rate_Counter >= NGEARSW_DATA_COLLECTION_RATE)
   {
      au8NGEARSW_Data_Buffer[u8NGEARSW_Buffer_Counter] = (UINT8)(NGEARSW_F);
  
      u8NGEARSW_Buffer_Counter++;  
      u8NGEARSW_Collection_Rate_Counter = 0;

      /** Every time the buffer is full the filter algorithm is called */                 
      if(u8NGEARSW_Buffer_Counter >= NGEARSW_BUFFER_SIZE) 
      {
         vfnNGEARSW_Filter();  
         u8NGEARSW_Buffer_Counter = 0; 
      }  
   } 
   else 
   {
      u8NGEARSW_Collection_Rate_Counter++;
   }  
   
 #endif      
}

/*******************************************************************************/
/**
* \brief    Filter algorithm of the Neutral Gear data buffer. Updates NGEARSW_Filter var.
* \author   OH
* \param    Void
* \return   Void
*/
void vfnNGEARSW_Filter(void)
{      
 #ifdef NGEARSW              

       /** Checks that every value of the array is equal */  
       for(u8NGEARSW_Counter=1; u8NGEARSW_Counter<NGEARSW_BUFFER_SIZE; u8NGEARSW_Counter++)
       {
           if (au8NGEARSW_Data_Buffer[u8NGEARSW_Counter] != au8NGEARSW_Data_Buffer[0])
              break;
       } 

       /** If all values are the same, puts the filtered var active or inactive */                 
       if(u8NGEARSW_Counter == NGEARSW_BUFFER_SIZE)
       {        
          if(au8NGEARSW_Data_Buffer[0]) 
          {                        
             #ifdef NGEARSW_ACTIVE_HIGH
                 u8NGEARSW_Filtered = ON;
             #else 
                #ifdef NGEARSW_ACTIVE_LOW             
                    u8NGEARSW_Filtered = OFF;
                #endif
             #endif
          }          
          else
          {                        
             #ifdef NGEARSW_ACTIVE_HIGH
                 u8NGEARSW_Filtered = OFF;
             #else 
                #ifdef NGEARSW_ACTIVE_LOW             
                    u8NGEARSW_Filtered = ON;
                #endif
             #endif
          }

       }
 
  #endif      
} 
/*******************************************************************************/