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
    
//    /* Enables Pull-up for all port B input channels */
//    PUCR_PUPBE = ENABLE;
//    
//    /* Enables Pull-up for all port E input channels */
//    PUCR_PUPEE = ENABLE;
//    
    /* Disconnect all output compare pins on port T */
    OCPD = 0xFF;    

    /** VRSOUT1, Port T, Channel 6, Pull Down */
    DDRT_DDRT6 = INPUT;
    PERT_PERT6 = ENABLE;             
    PPST_PPST6 = PULL_DOWN;         
    
    /** VRSOUT2, Port T, Channel 7, Pull Down */
    DDRT_DDRT7 = INPUT;
    PERT_PERT7 = ENABLE;             
    PPST_PPST7 = PULL_DOWN;             
    
    /** OPSR_F, Port B, Channel 0, Pull Up */
    DDRB_DDRB0 = INPUT;
    
    /** ACCPS_F, Port B, Channel 1, Pull Up */
    DDRB_DDRB1 = INPUT;
    
//    /** SFA_B, Port B, Channel 2, Pull Up */
//    DDRB_DDRB2 = INPUT;
//    
//    /** SFB_B, Port B, Channel 3, Pull Up */
//    DDRB_DDRB3 = INPUT;    
    
    /** KEYSW_F, Port E, Channel 1, Pull Up */
    DDRE_DDRE1 = INPUT;
    
    /** RXDB, Port S, Channel 0, Pull Up */
    DDRS_DDRS0 = INPUT;
    PERS_PERS0 = ENABLE;
    PPSS_PPSS0 = PULL_UP;
    
    /** KILLSW_F, Port J, Channel 6, Pull Up */
    DDRJ_DDRJ6 = INPUT;
    PERJ_PERJ6 = DISABLE;             
    //PPSJ_PPSJ6 = PULL_UP;
    
//    /** SO, Port M, Channel 2, Pull Up */
//    DDRM_DDRM2 = INPUT;
//    PERM_PERM2 = ENABLE;             
//    PPSM_PPSM2 = PULL_UP;
    
    /** NGEARSW_F, Port P, Channel 7, Pull Down */
    DDRP_DDRP7 = INPUT;
    PERP_PERP7 = ENABLE;             
    PPSP_PPSP7 = PULL_DOWN;
    
    /** CLTCHSW_F, Port P, Channel 5, Pull Down */
    DDRP_DDRP5 = INPUT;
    PERP_PERP5 = ENABLE;             
    PPSP_PPSP5 = PULL_DOWN;
    
    /** KICKSW_F, Port P, Channel 4, Pull Down */
    DDRP_DDRP4 = INPUT;
    PERP_PERP4 = ENABLE;             
    PPSP_PPSP4 = PULL_DOWN;

    /************* Digital Outputs Initialization *****************************/
    /* - Configuration of Data Direction Register to Output                   */
    /* - Set pin to specified value                                           */
    /**************************************************************************/
    
    /** RIN2, Port P, Channel 3, Low */
    DDRP_DDRP3 = OUTPUT;             
    RIN2 = LOW; 
    
    /** RIN3, Port P, Channel 2, Low */
    DDRP_DDRP2 = OUTPUT;             
    RIN3 = HIGH; 
    
    /** EN_DB4, Port P, Channel 1, High */
    DDRP_DDRP1 = OUTPUT;             
    EN_DB4 = HIGH; 
    
    /** EN_DB2, Port P, Channel 0, High */
    DDRP_DDRP0 = OUTPUT;             
    EN_DB2 = HIGH;
    
    /** INJIN1, Port T, Channel 0, Low */
    DDRT_DDRT0 = OUTPUT;             
    INJIN1 = LOW;
    
    /** INJIN2, Port T, Channel 1, Low */
    DDRT_DDRT1 = OUTPUT;             
    INJIN2 = LOW;
    
    /** IGNIN1, Port T, Channel 2, Low */
    DDRT_DDRT2 = OUTPUT;             
    IGNIN1 = LOW;
    
    /** IGNIN2, Port T, Channel 3, Low */
    DDRT_DDRT3 = OUTPUT;             
    IGNIN2 = LOW;
    
    /** RIN1, Port E, Channel 6, Low */
    DDRE_DDRE6 = OUTPUT;             
    RIN1 = HIGH;
    
    /** BATSWIN, Port E, Channel 5, Low */
    DDRE_DDRE5 = OUTPUT;             
    BATSWIN = HIGH;
    
    /** O2HIN, Port A, Channel 0, Low */
    DDRA_DDRA0 = OUTPUT;             
    O2HIN = LOW;
    
    /** LED7, Port A, Channel 1, Low */
    DDRA_DDRA1 = OUTPUT;             
    LED7 = LOW;
  
    /** LED6, Port A, Channel 2, Low */
    DDRA_DDRA2 = OUTPUT;             
    LED6 = LOW;
    
    /** LED5, Port A, Channel 3, Low */
    DDRA_DDRA3 = OUTPUT;             
    LED5 = LOW;
    
    /** LED4, Port A, Channel 4, Low */
    DDRA_DDRA4 = OUTPUT;             
    LED4 = LOW;
    
    /** H1INA, Port A, Channel 5, Low */
    DDRA_DDRA5 = OUTPUT;             
    H1INA = HIGH;
    
    /** H1INB, Port A, Channel 6, Low */
    DDRA_DDRA6 = OUTPUT;             
    H1INB = LOW;
    
    /** VLAMPIN, Port A, Channel 7, Low */
    DDRA_DDRA7 = OUTPUT;             
    VLAMPIN = HIGH;
    
    /** TXDB, Port S, Channel 1, High */
    DDRS_DDRS1 = OUTPUT;
    TXDB = HIGH;
    
    /** H2INB, Port S, Channel 2, Low */
    DDRS_DDRS2 = OUTPUT;             
    H2INB = LOW;
    
    /** H2INA, Port S, Channel 3, Low */
    DDRS_DDRS3 = OUTPUT;             
    H2INA = HIGH;
    
//    /** UNUSED66, Port J, Channel 7, High */
//    DDRJ_DDRJ7 = OUTPUT;             
//    UNUSED66 = HIGH;
//    
//    /** SCLK, Port M, Channel 5, Low */
//    DDRM_DDRM5 = OUTPUT;             
//    SCLK = LOW;
//    
//    /** SI, Port M, Channel 4, Low */
//    DDRM_DDRM4 = OUTPUT;             
//    SI = LOW;
//    
//    /** CSB, Port M, Channel 3, High */
//    DDRM_DDRM3 = OUTPUT;             
//    CSB = HIGH;
//    
//    /** PWREN, Port M, Channel 1, Low */
//    DDRM_DDRM1 = OUTPUT;             
//    PWREN = LOW;
    
    /************ Analog Inputs Initialization ********************************/
    /* - Configuration of Data Direction Register to Input                    */
    /* - Set Digital Input Enable option to 0 (disable)                       */
    /* - Disable Pull up/down option                                          */
    /**************************************************************************/
    
    /** VPWR_F, Port AD0, Channel 0 */
    DDR1AD0_DDR1AD00 = INPUT;
    ATD0DIEN_IEN0 =  DISABLE;
    PER1AD0_PER1AD00 = DISABLE;
    
    /** TPS_F, Port AD0, Channel 1 */
    DDR1AD0_DDR1AD01 = INPUT;
    ATD0DIEN_IEN1 =  DISABLE;
    PER1AD0_PER1AD01 = DISABLE;
    
    /** ETEMP_F, Port AD0, Channel 2 */
    DDR1AD0_DDR1AD02 = INPUT;
    ATD0DIEN_IEN2 =  DISABLE;
    PER1AD0_PER1AD02 = DISABLE;
    
    /** MAP_F, Port AD0, Channel 3 */
    DDR1AD0_DDR1AD03 = INPUT;
    ATD0DIEN_IEN3 =  DISABLE;
    PER1AD0_PER1AD03 = DISABLE;
    
    /** O2IN_F, Port AD0, Channel 4 */
    DDR1AD0_DDR1AD04 = INPUT;
    ATD0DIEN_IEN4 =  DISABLE;
    PER1AD0_PER1AD04 = DISABLE;
    
    /** ATEMP_F, Port AD0, Channel 5 */
    DDR1AD0_DDR1AD05 = INPUT;
    ATD0DIEN_IEN5 =  DISABLE;
    PER1AD0_PER1AD05 = DISABLE;
    
    /** MAF_F, Port AD0, Channel 6 */
    DDR1AD0_DDR1AD06 = INPUT;
    ATD0DIEN_IEN6 =  DISABLE;
    PER1AD0_PER1AD06 = DISABLE;
    
    /** BAP_F, Port AD0, Channel 7 */
    DDR1AD0_DDR1AD07 = INPUT;
    ATD0DIEN_IEN7 =  DISABLE;
    PER1AD0_PER1AD07 = DISABLE;
    
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
    
    /** UNUSED11, VDDF              - No configuration required */
    /** UNUSED12, VSS1              - No configuration required */
    /** UNUSED13, MODC/BKGD         - No configuration required */
    /** UNUSED14, XCLKSB/ECLKX2/PE7 - No configuration required */
    /** UNUSED15, VSSX2             - No configuration required */
    /** UNUSED16, VDDX2             - No configuration required */    
    /** UNUSED17, RESET_B           - No configuration required */
    /** UNUSED18, VDDR              - No configuration required */
    /** UNUSED19, VSS3              - No configuration required */
    /** UNUSED20, VSSPLL            - No configuration required */
    /** UNUSED21, EXTAL             - No configuration required */
    /** UNUSED22, XTAL              - No configuration required */
    /** UNUSED23, VDDPLL            - No configuration required */
    /** UNUSED24, XIRQB/PE0         - No configuration required */    
    /** UNUSED25, VDD               - No configuration required */
    /** UNUSED26, VSS2              - No configuration required */
    /** UNUSED27, VDDA              - No configuration required */
    /** UNUSED28, VRH               - No configuration required */
    /** UNUSED29, VRL               - No configuration required */
    /** UNUSED30, VSSA              - No configuration required */
    /** UNUSED31, TEST              - No configuration required */
    /** UNUSED32, VSSX1             - No configuration required */
    /** UNUSED33, VDDX1             - No configuration required */
    
    
    /*********** Unspecided and unbonded pins Initialization ******************/
    /* - Configuration of Data Direction Register to Output                   */
    /* - Set pin to specified value                                           */
    /**************************************************************************/
    
    /** UNUSED34, Port K, Channel 0, HIGH */
    DDRK_DDRK0 = OUTPUT;             
    PTK_PTK0 = HIGH;
    
    /** UNUSED35, Port K, Channel 1, HIGH */
    DDRK_DDRK1 = OUTPUT;             
    PTK_PTK1 = HIGH;
    
    /** UNUSED36, Port K, Channel 2, HIGH */
    DDRK_DDRK2 = OUTPUT;             
    PTK_PTK2 = HIGH;
    
    /** UNUSED37, Port K, Channel 3, HIGH */
    DDRK_DDRK3 = OUTPUT;             
    PTK_PTK3 = HIGH;
    
    /** UNUSED38, Port K, Channel 4, HIGH */
    DDRK_DDRK4 = OUTPUT;             
    PTK_PTK4 = HIGH;
    
    /** UNUSED39, Port K, Channel 5, HIGH */
    DDRK_DDRK5 = OUTPUT;             
    PTK_PTK5 = HIGH;
    
    /** UNUSED40, Port K, Channel 7, HIGH */
    DDRK_DDRK7 = OUTPUT;             
    PTK_PTK7 = HIGH;
    
    /** UNUSED41, Port H, Channel 0, HIGH */
    DDRH_DDRH0 = OUTPUT;             
    PTH_PTH0 = HIGH;
    
    /** UNUSED42, Port H, Channel 1, HIGH */
    DDRH_DDRH1 = OUTPUT;             
    PTH_PTH1 = HIGH;
    
    /** UNUSED43, Port H, Channel 2, HIGH */
    DDRH_DDRH2 = OUTPUT;             
    PTH_PTH2 = HIGH;
    
    /** UNUSED44, Port H, Channel 3, HIGH */
    DDRH_DDRH3 = OUTPUT;             
    PTH_PTH3 = HIGH;
    
    /** UNUSED45, Port H, Channel 4, HIGH */
    DDRH_DDRH4 = OUTPUT;             
    PTH_PTH4 = HIGH;
    
    /** UNUSED46, Port H, Channel 5, HIGH */
    DDRH_DDRH5 = OUTPUT;             
    PTH_PTH5 = HIGH;
    
    /** UNUSED47, Port H, Channel 6, HIGH */
    DDRH_DDRH6 = OUTPUT;             
    PTH_PTH6 = HIGH;
    
    /** UNUSED48, Port H, Channel 7, HIGH */
    DDRH_DDRH7 = OUTPUT;             
    PTH_PTH7 = HIGH;
    
    /** UNUSED49, Port J, Channel 0, HIGH */
    DDRJ_DDRJ0 = OUTPUT;             
    PTJ_PTJ0 = HIGH;
    
    /** UNUSED50, Port J, Channel 1, HIGH */
    DDRJ_DDRJ1 = OUTPUT;             
    PTJ_PTJ1 = HIGH;
    
    /** UNUSED51, Port P, Channel 6, HIGH */
    DDRP_DDRP6 = OUTPUT;             
    PTP_PTP6 = HIGH;
    
    /** UNUSED52, Port S, Channel 4, HIGH */
    DDRS_DDRS4 = OUTPUT;             
    PTS_PTS4 = HIGH;
    
    /** UNUSED53, Port S, Channel 5, HIGH */
    DDRS_DDRS5 = OUTPUT;             
    PTS_PTS5 = HIGH;
    
    /** UNUSED54, Port S, Channel 6, HIGH */
    DDRS_DDRS6 = OUTPUT;             
    PTS_PTS6 = HIGH;
    
    /** UNUSED55, Port S, Channel 7, HIGH */
    DDRS_DDRS7 = OUTPUT;             
    PTS_PTS7 = HIGH;
    
    /** UNUSED56, Port M, Channel 6, HIGH */
    DDRM_DDRM6 = OUTPUT;             
    PTM_PTM6 = HIGH;
    
    /** UNUSED57, Port M, Channel 7, HIGH */
    DDRM_DDRM7 = OUTPUT;             
    PTM_PTM7 = HIGH;
    
    /** UNUSED58, Port AD0, Channel 8, HIGH */
    DDR0AD0_DDR0AD00 = OUTPUT;
    ATD0DIEN_IEN8 =  ENABLE;
    PT0AD0_PT0AD00 = HIGH;
    
    /** UNUSED59, Port AD0, Channel 9, HIGH */
    DDR0AD0_DDR0AD01 = OUTPUT;
    ATD0DIEN_IEN9 =  ENABLE;
    PT0AD0_PT0AD01 = HIGH;
    
    /** UNUSED60, Port AD0, Channel 10, HIGH */
    DDR0AD0_DDR0AD02 = OUTPUT;
    ATD0DIEN_IEN10 =  ENABLE;
    PT0AD0_PT0AD02 = HIGH;
    
    /** UNUSED61, Port AD0, Channel 11, HIGH */
    DDR0AD0_DDR0AD03 = OUTPUT;
    ATD0DIEN_IEN11 =  ENABLE;
    PT0AD0_PT0AD03 = HIGH;
    
    /** UNUSED62, Port AD0, Channel 12, HIGH */
    DDR0AD0_DDR0AD04 = OUTPUT;
    ATD0DIEN_IEN12 =  ENABLE;
    PT0AD0_PT0AD04 = HIGH;
    
    /** UNUSED63, Port AD0, Channel 13, HIGH */
    DDR0AD0_DDR0AD05 = OUTPUT;
    ATD0DIEN_IEN13 =  ENABLE;
    PT0AD0_PT0AD05 = HIGH;
    
    /** UNUSED64, Port AD0, Channel 14, HIGH */
    DDR0AD0_DDR0AD06 = OUTPUT;
    ATD0DIEN_IEN14 =  ENABLE;
    PT0AD0_PT0AD06 = HIGH;
    
    /** UNUSED65, Port AD0, Channel 15, HIGH */
    DDR0AD0_DDR0AD07 = OUTPUT;
    ATD0DIEN_IEN15 =  ENABLE;
    PT0AD0_PT0AD07 = HIGH;
}
/*******************************************************************************/
