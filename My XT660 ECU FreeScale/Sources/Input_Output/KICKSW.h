/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       KICKSW.h
\brief      Kickstand Switch Monitoring
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

/* Kickstand Switch Monitoring data collection rate check */
#if KICKSW_DATA_COLLECTION_RATE < DATA_MANAGEMENT_TASK
#error "Kickstand Switch Monitoring Data collection periodic rate is faster than the timeout period of the Data Management Task"
#endif

/** Function prototypes */
 
 void vfnKICKSW_Filter(void);
 void vfnKICKSW_Monitoring(void);
 void vfnKICKSW_Init(void);

/*******************************************************************************/