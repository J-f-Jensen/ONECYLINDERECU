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
   
   /** Default O2HIN Off, same as Input_Output.c Digital Outputs Initialization */
   vfnO2H_Off();      
                       
#endif
}

/*******************************************************************************/
/**
* \brief    Puts the O2H in the active state
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnO2H_On(void)
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

void vfnO2H_Off(void)
{            
#ifdef O2H
   
  //Turn off the O2H connected to O2HOUT
  O2HIN = OFF;   

#endif
} 
/*******************************************************************************/