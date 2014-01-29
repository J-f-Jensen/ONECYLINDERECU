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
/** Neutral Gear function prototypes */
#include "NGEARSW.h"
/** Input Output macros and definitions */
#include "Input_Output.h"

static UINT8 u8NGEARSW_Collection_Rate_Counter = 0;
static UINT8 u8NGEARSW_Buffer_Counter = 0;
UINT8 u8NGEARSW_Counter = 0;
UINT8 u8NGEARSW_Filtered = 0;

/** Buffer used to collect Neutral Gear data */
#ifdef NGEARSW
  UINT8  au8NGEARSW_Data_Buffer[NGEARSW_BUFFER_SIZE];
#endif

/*******************************************************************************/
/**
* \brief    Initializations for Neutral Gear Buffer
* \author   OH 
* \param    Void
* \return   Void
*/

#ifdef NGEARSW              
void vfnNGEARSW_Init(void)
{ 
 
   /** Initialization of Buffer used to collect Neutral Gear data */
    for(u8NGEARSW_Counter=0; u8NGEARSW_Counter<NGEARSW_BUFFER_SIZE; u8NGEARSW_Counter++)
    {
        au8NGEARSW_Data_Buffer[u8NGEARSW_Counter] = 0;
    }      
    u8NGEARSW_Counter = 0;
    
}
#endif      

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

      au8NGEARSW_Data_Buffer[u8NGEARSW_Buffer_Counter] = (UINT8)(NGEARSW_F);
  
      u8NGEARSW_Buffer_Counter++;  
      u8NGEARSW_Collection_Rate_Counter = 0;

      /** Every time the buffer is full the filter algorithm is called */                 
      if(u8NGEARSW_Buffer_Counter >= NGEARSW_BUFFER_SIZE) 
      {
         vfnNGEARSW_Filter();  
         u8NGEARSW_Buffer_Counter = 0; 
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