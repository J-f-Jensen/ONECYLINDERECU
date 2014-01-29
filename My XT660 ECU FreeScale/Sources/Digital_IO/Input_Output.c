/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Input_Output.c
\brief      Inputs and Outputs functions for Seabreeze Emulator board 
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Abraham Tezmol
\version    0.1
\date       12/Feb/2008
*/
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

/** Seabreeze Emulator Compilation Options */
#include "Seabreeze_Emulator.h"
/** S12X derivative information */
#include __S12X_DERIVATIVE
/** CPU initialization prototypes and definitions */
#include "Input_Output.h"
/** Variable types and common definitions */
#include "typedefs.h"   
/** Software and hardware configuration */
#include "Application Definitions.h"

/* -- Variables --------------------------------------------------------*/


/*******************************************************************************/
/**
* \brief    Inputs and Outputs Initialization to default values/configuration \n
            as per Seabreeze Emulator Hardware Test Code Specification version 0.3
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnInputs_Outputs_Init(void)
{                  
    /************* Digital Inputs Initialization ******************************/
    /* - Configuration of Data Direction Register to Input                    */
    /* - Enable Pull up/down option                                           */
    /* - Set pull/down option to specified value                              */
    /**************************************************************************/

    #if HARDWARE == REFERENCE
    /* Disconnect all output compare pins on port T */
    //OCPD = 0xFF; Not supported inS12T64
    // All OMx and OLx set to 0 instead in TCTL1 / TCTL2
    TCTL1 = 0x00;
    TCTL2 = 0x00;
        
// This is the one used right now
    //INPUTS
    /** VRSOUT1, Port T, Channel 1, Pull Down */
    DDRT_DDRT1 = INPUT;
    PERT_PERT1 = ENABLED;             
// Why? maybe I enable this    PPST_PPST1 = PULL_DOWN;         
  
// Only one VRS is used    
    /** VRSOUT2, Port T, Channel 7, Pull Down */
//    DDRT_DDRT7 = INPUT;
//    PERT_PERT7 = ENABLED;             
//    PPST_PPST7 = PULL_DOWN;             
    
    /** ENGINE_STOP_SW, Port B, Channel 0 */
// Need to find this ??    DDRB_DDRB0 = INPUT;
    
    /**  INJFLT1, Port A, Channel 0*/
// Need to find this ??    DDRA_DDRA0 = INPUT;

    /**  IGNFLT1, Port A, Channel 1 */
// Need to find this ??    DDRA_DDRA1 = INPUT;
    
    /**  RELFLT, Port A, Channel 2 */
// Need to find this ??    DDRA_DDRA2 = INPUT;
    
    /** RXDB, Port S, Channel 0, Pull Up */
// RX port burde vær nem at finde    DDRS_DDRS0 = INPUT;
//    PERS_PERS0 = ENABLED;
//    PPSS_PPSS0 = PULL_UP;
        
    /** SO, Port M, Channel 2 */
// Need to find this or ??    DDRM_DDRM2 = INPUT;


    /************* Digital Outputs Initialization *****************************/
    /* - Configuration of Data Direction Register to Output                   */
    /* - Set pin to specified value                                           */
    /**************************************************************************/
    
    
    /** EN, Port P, Channel 3 Low */
//    DDRP_DDRP3 = OUTPUT;
//    EN = LOW;
    
    /** O2HIN, Port P, Channel 2 Low*/
// Do I need this ?    DDRP_DDRP2 = OUTPUT;
//    O2HIN = LOW;
   
    /** VLAMPIN, Port P, Channel 1 */
//    DDRP_DDRP1 = OUTPUT;
//    VLAMPIN = LOW;

    /** RIN2, Port P, Channel 0 */
//    DDRP_DDRP0 = OUTPUT;
//    RIN2 = LOW;
    
    /** INJIN1, Port T, Channel 0 */
// Need to find this ?   DDRT_DDRT0 = OUTPUT;
//    INJIN1 = LOW;
    
    /** RIN1, Port T, Channel 1 */
//    DDRT_DDRT1 = OUTPUT;
//    RIN1 = LOW;
    
    /** IGNIN1, Port T, Channel 2 */
// Need to find this    DDRT_DDRT0 = OUTPUT;
//    INJIN1 = LOW;

    /** WDRFSH, Port T, Channel 4 */
// ??    DDRT_DDRT4 = OUTPUT;
//    WDRFSH = LOW;

    /** MCUTEST3, Port B, Channel 5 */
// ??    DDRB_DDRB5 = OUTPUT;
//    MCUTEST3 = LOW;
    
    /** MCUTEST2, Port B, Channel 6 */
// ??    DDRB_DDRB6 = OUTPUT;
//    MCUTEST2 = LOW;
    
    /** MCUTEST1, Port B, Channel 7 */
// ??    DDRB_DDRB7 = OUTPUT;
//    MCUTEST1 = LOW;

    /** TXDB, Port S, Channel 1 */
// TX port burde vær nem at finde    DDRS_DDRS1 = OUTPUT;
//    TXDB = LOW;
    
    /** SI, Port M, Channel 4 */
// Not used    DDRM_DDRM4 = OUTPUT;
//    SI = LOW;

    /** SCLK, Port M, Channel 5 */
// Not used    DDRM_DDRM5 = OUTPUT;
//    SCLK = LOW;
    
    /** CSB, Port M, Channel 3 */
// Not used    DDRM_DDRM3 = OUTPUT;
//    CSB = LOW;
    
    /** IN6, Port P, Channel 7 */
// ?    DDRP_DDRP7 = OUTPUT;
//    IN6 = LOW;
    
    /** IN5, Port P, Channel 5 */
// ?    DDRP_DDRP5 = OUTPUT;
//    IN5 = LOW;

    /************ Analog Inputs Initialization ********************************/
    /* - Configuration of Data Direction Register to Input                    */
    /* - Set Digital Input Enable option to 0 (disable)                       */
    /* - Disable Pull up/down option                                          */
    /**************************************************************************/

// This configuration is not nessesary on S12T64 MCU and will not be converted
    
    
    /** TPS_F, Port AD0, Channel 0 */
//    DDR1AD_DDR1AD0 = INPUT;
//    ATDDIEN_IEN0 =  DISABLED;
//    PER1AD_PER1AD0 = DISABLED;
    
    /** MAP_F, Port AD0, Channel 1 */
//    DDR1AD_DDR1AD1 = INPUT;
//    ATDDIEN_IEN1 =  DISABLED;
//    PER1AD_PER1AD1 = DISABLED;
    
    /** O2IN_F, Port AD0, Channel 2 */
//    DDR1AD_DDR1AD2 = INPUT;
//    ATDDIEN_IEN2 =  DISABLED;
//    PER1AD_PER1AD2 = DISABLED;
    
    /** ATEMP_F, Port AD0, Channel 3 */
//    DDR1AD_DDR1AD3 = INPUT;
//    ATDDIEN_IEN3 =  DISABLED;
//    PER1AD_PER1AD3 = DISABLED;
    
    /** VPWR_F, Port AD0, Channel 4 */
//    DDR1AD_DDR1AD4 = INPUT;
//    ATDDIEN_IEN4 =  DISABLED;
//    PER1AD_PER1AD4 = DISABLED;
    
    /** TILT_F, Port AD0, Channel 5 */
//    DDR1AD_DDR1AD5 = INPUT;
//    ATDDIEN_IEN5 =  DISABLED;
//    PER1AD_PER1AD5 = DISABLED;
 
    /** ETEMP_F, Port AD0, Channel 7 */
//    DDR1AD_DDR1AD7 = INPUT;
//    ATDDIEN_IEN7 =  DISABLED;
//    PER1AD_PER1AD7 = DISABLED;
    
    /************ Unused pins Initialization **********************************/
    /* - Configuration of Data Direction Register to Output                   */
    /* - Set pin to specified value                                           */
    /**************************************************************************/
    
//    /** UNUSED1, Port T, Channel 4, High */
//    DDRT_DDRT4 = OUTPUT;             
//    PTT_PTT4 = HIGH;
//    
//    /** UNUSED2, Port T, Channel 5, High */
//    DDRT_DDRT5 = OUTPUT;             
//    PTT_PTT5 = HIGH;
//    
//    /** UNUSED3, Port B, Channel 4, High */
//    DDRB_DDRB4 = OUTPUT;             
//    PTB_PTB4 = HIGH;
//    
//    /** UNUSED4, Port B, Channel 5, High */
//    DDRB_DDRB5 = OUTPUT;             
//    PTB_PTB5 = HIGH;
//    
//    /** UNUSED5, Port B, Channel 6, High */
//    DDRB_DDRB6 = OUTPUT;             
//    PTB_PTB6 = HIGH;
//    
//    /** UNUSED6, Port B, Channel 7, High */
//    DDRB_DDRB7 = OUTPUT;             
//    PTB_PTB7 = HIGH;
//    
//    /** UNUSED7, Port E, Channel 4, High */
//    DDRE_DDRE4 = OUTPUT;             
//    PTE_PTE4 = HIGH;
//
//    /** UNUSED8, Port E, Channel 3, High */
//    DDRE_DDRE3 = OUTPUT;             
//    PTE_PTE3 = HIGH;
//    
//    /** UNUSED9, Port E, Channel 2, High */
//    DDRE_DDRE2 = OUTPUT;             
//    PTE_PTE2 = HIGH;
//    
//    /** UNUSED10, Port M, Channel 0, Low */
//    DDRM_DDRM0 = OUTPUT;             
//    PTM_PTM0 = LOW;
        
    
    #endif
}
/*******************************************************************************/
