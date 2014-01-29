/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       PSC.c
\brief      Power Supply Control
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
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
/** PSC function prototypes */
#include "PSC.h"
/** CPU initialization prototypes and definitions */
#include "Input_Output.h"

/*******************************************************************************/
/**
* \brief    Initializations for PSC
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnPSC_Init(void)
{            
#ifdef PSC
   
   /** Default PSC Off, same as Input_Output.c Digital Outputs Initialization ?? */
   vfnPSC_Off();      

#endif
}

/*******************************************************************************/
/**
* \brief    Puts the PSC in the active state
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnPSC_On(void)
{            
#ifdef PSC
   
  //Turn on the PSC connected to ????.  
  // ???? = ON;    

#endif
}

/*******************************************************************************/
/**
* \brief    Puts the PSC in the inactive state
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnPSC_Off(void)
{            
#ifdef PSC
   
  //Turn off the PSC connected to ???
  // ???? = OFF;   

#endif
} 
/*******************************************************************************/