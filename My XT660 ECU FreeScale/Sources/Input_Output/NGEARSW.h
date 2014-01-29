/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       NGEARSW.h
\brief      Neutral Gear Monitoring
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Jaime Orozco
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

/* Neutral Gear Monitoring data collection rate check */
#if NGEARSW_DATA_COLLECTION_RATE < DATA_MANAGEMENT_TASK
#error "Neutral Gear Monitoring Data collection periodic rate is faster than the timeout period of the Data Management Task"
#endif

/** Function prototypes */
 
 void vfnNGEARSW_Filter(void);
 void vfnNGEARSW_Monitoring(void);
 void vfnNGEARSW_Init(void);

/*******************************************************************************/