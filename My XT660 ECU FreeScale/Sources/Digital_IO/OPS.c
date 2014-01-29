/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       OPS.c
\brief      Oil Pressure Switch Monitoring
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Jaime Orozco
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
/** Oil Pressure Switch function prototypes */
#include "OPS.h"
/** Input Output macros and definitions */
#include "Input_Output.h"

static UINT8 u8OPS_Collection_Rate_Counter = 0;
static UINT8 u8OPS_Buffer_Counter = 0;
UINT8 u8OPS_Counter = 0;
UINT8 u8OPS_Filtered = 0;

/** Buffer used to collect Oil Pressure Switch data */
#ifdef OPS
  UINT8  au8OPS_Data_Buffer[OPS_BUFFER_SIZE];
#endif

/*******************************************************************************/
/**
* \brief    Initializations for Oil Pressure Switch Buffer
* \author   OH 
* \param    Void
* \return   Void
*/

#ifdef OPS              
void vfnOPS_Init(void)
{ 
 
   /** Initialization of Buffer used to collect Oil Pressure Switch data */
    for(u8OPS_Counter=0; u8OPS_Counter<OPS_BUFFER_SIZE; u8OPS_Counter++)
    {
        au8OPS_Data_Buffer[u8OPS_Counter] = 0;
    }      
    u8OPS_Counter = 0;
           
}
#endif
/*******************************************************************************/
/**
* \brief    Oil Pressure Switch Monitoring periodic rate check and buffer data collection
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnOPS_Monitoring(void)
{  
 #ifdef OPS              

      au8OPS_Data_Buffer[u8OPS_Buffer_Counter] = (UINT8)(OPSR_F);
  
      u8OPS_Buffer_Counter++;  
      u8OPS_Collection_Rate_Counter = 0;

      /** Every time the buffer is full the filter algorithm is called */                 
      if(u8OPS_Buffer_Counter >= OPS_BUFFER_SIZE) 
      {
         vfnOPS_Filter();  
         u8OPS_Buffer_Counter = 0; 
      }  
         
 #endif      
}

/*******************************************************************************/
/**
* \brief    Filter algorithm of the Ignition Switch data buffer. Updates OPS_Filter var.
* \author   OH
* \param    Void
* \return   Void
*/
void vfnOPS_Filter(void)
{      
 #ifdef OPS              

       /** Checks that every value of the array is equal */  
       for(u8OPS_Counter=1; u8OPS_Counter<OPS_BUFFER_SIZE; u8OPS_Counter++)
       {
           if (au8OPS_Data_Buffer[u8OPS_Counter] != au8OPS_Data_Buffer[0])
              break;
       } 

       /** If all values are the same, puts the filtered var active or inactive */                 
       if(u8OPS_Counter == OPS_BUFFER_SIZE)
       {        
          if(au8OPS_Data_Buffer[0]) 
          {                        
             #ifdef OPS_ACTIVE_HIGH
                 u8OPS_Filtered = ON;
             #else 
                #ifdef OPS_ACTIVE_LOW             
                    u8OPS_Filtered = OFF;
                #endif
             #endif
          }          
          else
          {                        
             #ifdef OPS_ACTIVE_HIGH
                 u8OPS_Filtered = OFF;
             #else 
                #ifdef OPS_ACTIVE_LOW             
                    u8OPS_Filtered = ON;
                #endif
             #endif
          }

       }
 
  #endif      
} 
/*******************************************************************************/