/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       O2H.c
\brief      O2 Heater Drive Control
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
/** O2H function prototypes */
#include "O2H.h"
/** CPU initialization prototypes and definitions */
#include "Input_Output.h"

/*******************************************************************************/
/**
* \brief    Initializations for O2H
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnO2H_Init(void)
{            
#ifdef O2H
   
   /** Default O2HIN on */
   vfnO2H_On();      
                       
#endif
}

/*******************************************************************************/
/**
* \brief    Puts the O2H in the active state
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnO2H_On()
{            
#ifdef O2H
   
  //Turn on the O2H connected to O2HOUT  
  O2HIN = ON;   

#endif
}

/*******************************************************************************/
/**
* \brief    Puts the O2H in the inactive state
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnO2H_Off()
{            
#ifdef O2H
   
  //Turn off the O2H connected to O2HOUT
  O2HIN = OFF;   

#endif
} 
/*******************************************************************************/