/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       IGNSW.h
\brief      Ignition Switch Monitoring.
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Jaime Orozco
\ThirdParty Omar Hernandez/Rodrigo Ruiz (NACURI)
\version    0.2
\date       Aug/ 2008
*/
/*******************************************************************************/

#include <hidef.h>
/** Seabreeze Emulator Compilation Options */
#include "Seabreeze_Emulator.h"
/** S12X derivative information */
#include __S12X_DERIVATIVE
/** Variable types and common definitions */
#include "typedefs.h"

/* Ignition Switch data collection rate check */
#if IGNSW_DATA_COLLECTION_RATE < DATA_MANAGEMENT_TASK
#error "Ignition Switch Data collection periodic rate is faster than the timeout period of the Data Management Task"
#endif

/** Function prototypes */
 
 void vfnIGNSW_Filter(void);
 void vfnIGNSW_Monitoring(void);
 void vfnIGNSW_Init(void);

/*******************************************************************************/