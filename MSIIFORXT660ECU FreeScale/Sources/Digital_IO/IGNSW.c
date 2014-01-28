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
/** Ignition Switch function prototypes */
#include "IGNSW.h"
/** Input Output macros and definitions */
#include "Input_Output.h"

#ifdef IGNSW
static UINT8 u8IGNSW_Collection_Rate_Counter = 0;
static UINT8 u8IGNSW_Buffer_Counter = 0;
UINT8 u8IGNSW_Counter = 0;
UINT8 u8IGNSW_Filtered = 0;

/** Buffer used to collect Ignition Switch data */
  UINT8  au8IGNSW_Data_Buffer[IGNSW_BUFFER_SIZE];
#endif


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

      au8IGNSW_Data_Buffer[u8IGNSW_Buffer_Counter] = (UINT8)(KEYSW_F);
  
      u8IGNSW_Buffer_Counter++;  
      u8IGNSW_Collection_Rate_Counter = 0;

      /** Every time the buffer is full the filter algorithm is called */                 
      if(u8IGNSW_Buffer_Counter >= IGNSW_BUFFER_SIZE) 
      {
         vfnIGNSW_Filter();  
         u8IGNSW_Buffer_Counter = 0; 
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