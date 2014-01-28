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
/** Clutch Switch function prototypes */
#include "CLTCHSW.h"
/** Input Output macros and definitions */
#include "Input_Output.h"

#ifdef CLTCHSW
static UINT8 u8CLTCHSW_Collection_Rate_Counter = 0;
static UINT8 u8CLTCHSW_Buffer_Counter = 0;
UINT8 u8CLTCHSW_Counter = 0;
UINT8 CLTCHSW_Filtered = 0;

/** Buffer used to collect Clutch Switch data */
UINT8  au8CLTCHSW_Data_Buffer[CLTCHSW_BUFFER_SIZE];
#endif

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

    au8CLTCHSW_Data_Buffer[u8CLTCHSW_Buffer_Counter] = (UINT8)(CLTCHSW_F);
  
    u8CLTCHSW_Buffer_Counter++;  
    u8CLTCHSW_Collection_Rate_Counter = 0;

    /** Every time the buffer is full the filter algorithm is called */                 
    if(u8CLTCHSW_Buffer_Counter >= CLTCHSW_BUFFER_SIZE) 
    {
        vfnCLTCHSW_Filter();  
        u8CLTCHSW_Buffer_Counter = 0; 
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
                 CLTCHSW_Filtered = ON;
             #else 
                #ifdef CLTCHSW_ACTIVE_LOW             
                    CLTCHSW_Filtered = OFF;
                #endif
             #endif
          }          
          else
          {                        
             #ifdef CLTCHSW_ACTIVE_HIGH
                 CLTCHSW_Filtered = OFF;
             #else 
                #ifdef CLTCHSW_ACTIVE_LOW             
                    CLTCHSW_Filtered = ON;
                #endif
             #endif
          }

       }
 
  #endif      
} 
/*******************************************************************************/