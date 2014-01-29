/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       MIL.h
\brief      Malfunction Indication Lamp Control
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\ThirdParty Omar Hernandez/Rodrigo Ruiz (NACURI)
\version    0.1
\date       Jul/ 2008
*/
/*******************************************************************************/

#include <hidef.h>
/** Seabreeze Emulator Compilation Options */
#include "Seabreeze_Emulator.h"
/** S12X derivative information */
#include __S12X_DERIVATIVE
/** Variable types and common definitions */
#include "typedefs.h"


/** Function prototypes */
 
 void vfnMIL_Init(void);
 void vfnMIL_On(void);
 void vfnMIL_Off(void);
 
// Previuous functions, to be deleted 
// void MIL_Init(void);
// void MIL_Set(void);
// void MIL_Clear(void);


/*******************************************************************************/