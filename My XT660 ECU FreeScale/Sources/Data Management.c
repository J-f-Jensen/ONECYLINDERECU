/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Data management.c
\brief      Data Management functions.
\author     Freescale Semiconductor
\author     Jesse Beeker/ Jaime Orozco
\version    0.4
\date       November/ 2008
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

/** ADC function prototypes */
#include "ADC.h"
/** Air temperature monitoring definitions */
#include "ATEMP.h"
/** Barometric air pressure monitoring definitions */
#include "BAP.h"
/** Engine temperature monitoring definitions */
#include "ETEMP.h"
/** TILT monitoring definitions */
#include "TILT.h"
/** Manifold air pressure monitoring definitions */
#include "MAP.h"
/** Oxygen monitoring definitions */
#include "O2.h"
/** Throttle position monitoring definitions */
#include "TPS.h"
/** Battery voltage monitoring definitions */
#include "VBAT.h"


/** Clutch switch monitoring definitions */
#include "CLTCHSW.h"
/** Ignition Switch monitoring definitions */
#include "IGNSW.h"
/** Kick stand monitoring definitions */
#include "KICKSW.h"
/** ENGSTOP switch monitoring definitions */
#include "ENGSTOPSW.h"
/** Malfunction indication lamp definitions */
#include "MIL.h"
/** Neutral Gear monitoring definitions */
#include "NGEARSW.h"
/** Oxygen heater definitions */
#include "O2H.h"
/** Oil pressure switch monitoring definitions */
#include "OPS.h"


#include "Data Management.h"
#include "Application Definitions.h"



/*******************************************************************************/
/**
* \brief    Resources initialization for data management
* \author   Jaime Orozco 
* \param    void
* \return   void
*/
void Data_Management_Init()
{
    /* Initialization for monitoring of defined analog signals */
    
    #ifdef ATEMP       
        vfnATEMP_Init();    /* Air temperature */
    #endif
    
    #ifdef BAP       
        vfnBAP_Init();      /* Barometric air pressure */
    #endif
    
    #ifdef ETEMP       
        vfnETEMP_Init();    /* Engine temperature */
    #endif
    
    #ifdef TILT                       
        vfnTILT_Init();      /* TILT */ 
    #endif
    
    #ifdef MAP                       
        vfnMAP_Init();      /* Manifold air pressure */ 
    #endif
    
    #ifdef O2        
        vfnO2_Init();       /* Oxygen sensor */
    #endif
    
    #ifdef TPS       
        vfnTPS_Init();      /* Throttle position */
    #endif
    
    #ifdef VBAT        
        vfnVBAT_Init();     /* Battery Voltage */
    #endif 
    
    
    /* Initialization for Monitoring of defined digital inputs */
    
    #ifdef CLTCHSW        
        vfnCLTCHSW_Init();  /* Clutch switch */
    #endif 
    
    #ifdef IGNSW        
        vfnIGNSW_Init();    /* Ignition switch */
    #endif 
    
    #ifdef KICKSW         
        vfnKICKSW_Init();   /* Kickstand switch */
    #endif 
    
    #ifdef ENGSTOPSW         
        vfnENGSTOPSW_Init();   /* Engine ENGSTOP switch */
    #endif 
    
    #ifdef MIL        
        vfnMIL_Init();      /* Malfunction indicator lamp */
    #endif    
    
    #ifdef NGEARSW        
        vfnNGEARSW_Init();  /* Neutral gear switch */
    #endif 
    
    #ifdef O2H        
        vfnO2H_Init();      /* Oxygen heater */
    #endif 
    
    #ifdef OPS        
        vfnOPS_Init();      /* Oil pressure sensor */
    #endif 
}

/*******************************************************************************/
/**
* \brief    Data management
* \author   Jaime Orozco 
* \param    void
* \return   void
*/
void Data_Management()
{       
    /* Parse Analog signals */
    //Reference design uses S12P and does not use PIT for A/D trigger
    #if HARDWARE == REFERENCE
    //Analog data is continuously collected.  Data management just gets the latest
    //value.
    //Parse signal array to collect the latest data from the buffer
        #ifdef VBAT
        vfnVBAT_Monitoring(RAW_ADC[VBAT_ADC_CHANNEL]);        
        #endif                
        
        #ifdef TPS
        vfnTPS_Monitoring(RAW_ADC[TPS_ADC_CHANNEL]);
        #endif
        
        #ifdef ETEMP
        vfnETEMP_Monitoring(RAW_ADC[ETEMP_ADC_CHANNEL]);
        #endif
        
        #ifdef MAP
        #ifdef MAP_TIME_BASED
        vfnMAP_Monitoring(RAW_ADC[MAP_ADC_CHANNEL]);
        #endif
        #endif

        #ifdef O2 
        vfnO2_Monitoring(RAW_ADC[O2_ADC_CHANNEL]);
        #endif                                                                
        
        #ifdef ATEMP
        vfnATEMP_Monitoring(RAW_ADC[ATEMP_ADC_CHANNEL]);
        #endif                
        
        #ifdef TILT
        vfnTILT_Monitoring(RAW_ADC[TILT_ADC_CHANNEL]);
        #endif

        #ifdef BAP
        vfnBAP_Monitoring(RAW_ADC[BAP_ADC_CHANNEL]);
        #endif
    
    
    #endif

    /* Parse Digital signals */                  
    
    #ifdef CLTCHSW        
        vfnCLTCHSW_Monitoring();  /* Clutch switch */
    #endif 
    
    #ifdef IGNSW        
        vfnIGNSW_Monitoring();    /* Ignition switch */
    #endif 
    
    #ifdef KICKSW         
        vfnKICKSW_Monitoring();   /* Kickstand switch */
    #endif 
    
    #ifdef ENGSTOPSW         
        vfnENGSTOPSW_Monitoring();   /* Engine ENGSTOP switch */
    #endif 
        
    #ifdef NGEARSW        
        vfnNGEARSW_Monitoring();  /* Neutral gear switch */
    #endif         
    
    #ifdef OPS        
        vfnOPS_Monitoring();      /* Oil pressure sensor */
    #endif   
}

#pragma CODE_SEG DEFAULT