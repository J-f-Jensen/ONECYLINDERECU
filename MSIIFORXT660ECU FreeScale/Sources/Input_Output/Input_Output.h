/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Input_Outpu.h
\brief      Inputs and Outputs functions for Seabreeze Emulator board 
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Abraham Tezmol
\version    0.1
\date       20/March/2008
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

#ifndef _INPUT_OUTPUT_H
#define _INPUT_OUTPUT_H

/*-- Includes ----------------------------------------------------------------*/
/** Seabreeze Emulator Compilation Options */
#include "Seabreeze_Emulator.h"
/** S12X derivative information */
#include __S12X_DERIVATIVE
/** Software and hardware configuration */
#include "Application Definitions.h"

/*-- Defines -----------------------------------------------------------------*/

/* Data Direction Register definitions */
#define INPUT           0
#define OUTPUT          1
#define ANALOG_INPUT    2

/* Input pull-up and pull-down definitions */
#define PULL_DOWN       0
#define PULL_UP         1

/* Data output register definition */
#define LOW             0
#define HIGH            1


/** Ports redefinition for macros usability */
#ifndef PTA             
    #define PTA_PTA0 PORTA_PA0 
    #define PTA_PTA1 PORTA_PA1 
    #define PTA_PTA2 PORTA_PA2 
    #define PTA_PTA3 PORTA_PA3 
    #define PTA_PTA4 PORTA_PA4 
    #define PTA_PTA5 PORTA_PA5 
    #define PTA_PTA6 PORTA_PA6 
    #define PTA_PTA7 PORTA_PA7 
#endif

#ifndef PTE             
    #define PTE_PTE0 PORTE_PE0 
    #define PTE_PTE1 PORTE_PE1 
    #define PTE_PTE2 PORTE_PE2 
    #define PTE_PTE3 PORTE_PE3 
    #define PTE_PTE4 PORTE_PE4 
    #define PTE_PTE5 PORTE_PE5 
    #define PTE_PTE6 PORTE_PE6 
    #define PTE_PTE7 PORTE_PE7 
#endif

#ifndef PTB             
    #define PTB_PTB0 PORTB_PB0 
    #define PTB_PTB1 PORTB_PB1 
    #define PTB_PTB2 PORTB_PB2 
    #define PTB_PTB3 PORTB_PB3 
    #define PTB_PTB4 PORTB_PB4 
    #define PTB_PTB5 PORTB_PB5 
    #define PTB_PTB6 PORTB_PB6 
    #define PTB_PTB7 PORTB_PB7 
#endif

#ifndef PTK             
    #define PTK_PTK0 PORTK_PK0 
    #define PTK_PTK1 PORTK_PK1 
    #define PTK_PTK2 PORTK_PK2 
    #define PTK_PTK3 PORTK_PK3 
    #define PTK_PTK4 PORTK_PK4 
    #define PTK_PTK5 PORTK_PK5 
    #define PTK_PTK7 PORTK_PK7 
#endif

#ifndef DDRE_DDRE1
    #define DDRE_DDRE1  DDRE
#endif



/*-- Macros ------------------------------------------------------------------*/


#if HARDWARE == EMULATOR
/******************* Emulator Signal Name Abstraction *************************/

/* ~~~~~~~~ Digital Input signal mapping ~~~~~~~~~~~~~~~~~ */

/** VRSOUT1, Port T, Channel 6 */
#define     VRSOUT1     ((UINT16)PTT_PTT6   * 0xffff)
/** VRSOUT2, Port T, Channel 7 */
#define     VRSOUT2     ((UINT16)PTT_PTT7   * 0xffff)
/** OPSR_F, Port B, Channel 0 */
#define     OPSR_F      ((UINT16)PORTB_PB0  * 0xffff)
/** ACCPS_F, Port B, Channel 1 */   
#define     ACCPS_F     ((UINT16)PORTB_PB1  * 0xffff)
/** SFA_B, Port B, Channel 2 */   
#define     SFA_B       ((UINT16)PORTB_PB2  * 0xffff)
/** SFB_B, Port B, Channel 3 */   
#define     SFB_B       ((UINT16)PORTB_PB3  * 0xffff)
/** KEYSW_F, Port E, Channel 1 */
#define     KEYSW_F     ((UINT16)PORTE_PE1  * 0xffff)
/** RXDB, Port S, Channel 0 */
#define     RXDB        ((UINT16)PTS_PTS0   * 0xffff)
/** ENGSTOPSW_F, Port J, Channel 6 */
#define     ENGSTOPSW_F    ((UINT16)PTJ_PTJ6   * 0xffff)
/** SO, Port M, Channel 2 */
#define     SO          ((UINT16)PTM_PTM2   * 0xffff)
/** NGEARSW_F, Port P, Channel 7 */
#define     NGEARSW_F   ((UINT16)PTP_PTP7   * 0xffff)
/** CLTCHSW_F, Port P, Channel 5 */
#define     CLTCHSW_F   ((UINT16)PTP_PTP5   * 0xffff)
/** KICKSW_F, Port P, Channel 4 */
#define     KICKSW_F    ((UINT16)PTP_PTP4   * 0xffff)


/* ~~~~~~~~ Digital Output signal mapping ~~~~~~~~~~~~~~~~~ */

/** RIN2, Port P, Channel 3 */
#define     RIN2        (PTP_PTP3)
/** RIN3, Port P, Channel 2 */
#define     RIN3        (PTP_PTP2)
/** EN_DB4, Port P, Channel 1 */
#define     EN_DB4      (PTP_PTP1)
/** EN_DB2, Port P, Channel 0 */
#define     EN_DB2      (PTP_PTP0)
/** INJIN1, Port T, Channel 0 */
#define     INJIN1      (PTT_PTT0)
#define     INJ1_STAT   (PTIT_PTIT0)
/** INJIN2, Port T, Channel 1 */
#define     INJIN2      (PTT_PTT1)
#define     INJ2_STAT   (PTIT_PTIT1)
/** IGNIN1, Port T, Channel 2 */
#define     IGNIN1      (PTT_PTT2)
#define     IGN1_STAT   (PTIT_PTIT2)
/** IGNIN2, Port T, Channel 3 */
#define     IGNIN2      (PTT_PTT3)
#define     IGN2_STAT   (PTIT_PTIT3)
/** RIN1, Port E, Channel 6 */
#define     RIN1        (PTE_PTE6)
/** BATSWIN, Port E, Channel 5 */
#define     BATSWIN     (PTE_PTE5)
/** O2HIN, Port A, Channel 0 */
#define     O2HIN       (PTA_PTA0)
/** LED7, Port A, Channel 1 */
#define     LED7        (PTA_PTA1)
/** LED6, Port A, Channel 2 */
#define     LED6        (PTA_PTA2)
/** LED5, Port A, Channel 3 */
#define     LED5        (PTA_PTA3)
/** LED4, Port A, Channel 4 */
#define     LED4        (PTA_PTA4)
/** H1INA, Port A, Channel 5 */
#define     H1INA       (PTA_PTA5)
/** H1INB, Port A, Channel 6 */
#define     H1INB       (PTA_PTA6)
/** VLAMPIN, Port A, Channel 7 */
#define     VLAMPIN     (PTA_PTA7)
/** TXDB, Port S, Channel 1 */
#define     TXDB        (PTS_PTS1)
/** H2INB, Port S, Channel 2 */
#define     H2INB       (PTS_PTS2)
/** H2INA, Port S, Channel 3 */
#define     H2INA       (PTS_PTS3)
/** UNUSED66, Port J, Channel 7 */
#define     UNUSED66    (PTJ_PTJ7)
/** SCLK, Port M, Channel 5 */
#define     SCLK        (PTM_PTM5)
/** SI, Port M, Channel 4 */
#define     SI          (PTM_PTM4)
/** CSB, Port M, Channel 3 */
#define     CSB         (PTM_PTM3)
/** PWREN, Port M, Channel 1 */
#define     PWREN       (PTM_PTM1)

/* ~~~~~~~~ Analog Input signal mapping ~~~~~~~~~~~~~~~~~ */

/** TPS_F, Port AD0, Channel 0 */
#define     TPS_F       (au16AnalogAverage[0])
/** MAP_F, Port AD0, Channel 1 */
#define     MAP_F       (au16AnalogAverage[1])
 /** O2IN_F, Port AD0, Channel 2 */
#define     O2IN_F      (au16AnalogAverage[2])
/** ATEMP_F, Port AD0, Channel 3 */
#define     ATEMP_F     (au16AnalogAverage[3])
/** VPWR_F, Port AD0, Channel 4 */
#define     VPWR_F      (au16AnalogAverage[4])
/** TILT_F, Port AD0, Channel 5 */
#define     TILT_F       (au16AnalogAverage[5])
/** ETEMP_F, Port AD0, Channel 6 */
#define     ETEMP_F     (au16AnalogAverage[6])
/** BAP_F, Port AD0, Channel 7 */
#define     BAP_F       (au16AnalogAverage[7])
#endif

#if HARDWARE == PROTOTYPE
/******************* Prototype Signal Name Abstraction *************************/

/* ~~~~~~~~ Digital Input signal mapping ~~~~~~~~~~~~~~~~~ */

/** VRSOUT1, Port T, Channel 6 */
#define     VRSOUT1     ((UINT16)PTT_PTT6   * 0xffff)
/** VRSOUT2, Port T, Channel 7 */
#define     VRSOUT2     ((UINT16)PTT_PTT7   * 0xffff)
/** OPSR_F, Port B, Channel 0 */
#define     OPSR_F      ((UINT16)PORTB_PB0  * 0xffff)
/** ACCPS_F, Port B, Channel 1 */   
#define     RELFLT     ((UINT16)PORTB_PB1  * 0xffff)
/** RXDB, Port S, Channel 0 */
#define     RXDB        ((UINT16)PTS_PTS0   * 0xffff)
/** ENGSTOPSW_F, Port J, Channel 6 */
#define     ENGSTOPSW_F    ((UINT16)PTJ_PTJ6   * 0xffff)
/** NGEARSW_F, Port P, Channel 7 */
#define     NGEARSW_F   ((UINT16)PTP_PTP7   * 0xffff)
/** CLTCHSW_F, Port P, Channel 5 */
#define     CLTCHSW_F   ((UINT16)PTP_PTP5   * 0xffff)
/** KICKSW_F, Port P, Channel 4 */
#define     KICKSW_F    ((UINT16)PTP_PTP4   * 0xffff)


/* ~~~~~~~~ Digital Output signal mapping ~~~~~~~~~~~~~~~~~ */

#ifdef SUITCASE_DEMO
/** RIN2, Port P, Channel 3 */
#define     RIN2        (PTP_PTP3)
#endif
/** INJIN1, Port T, Channel 0 */
#define     INJIN1      (PTT_PTT0)
#define     INJ1_STAT   (PTIT_PTIT0)
/** WDFRSH, Port T, Channel 1 */
#define     WDRFSH      (PTT_PTT1)
/** IGNIN1, Port T, Channel 2 */
#define     IGNIN1      (PTT_PTT2)
#define     IGN1_STAT   (PTIT_PTIT2)
/** RIN1, Port E, Channel 6 */
#define     RIN1        (PTE_PTE6)
/** VLAMPIN, Port E, Channel 5 */
#define     VLAMPIN     (PTE_PTE5)
/** O2HIN, Port A, Channel 0 */
#define     O2HIN       (PTA_PTA0)
/** LED7, Port A, Channel 1 */
#define     LED7        (PTA_PTA1)
/** LED6, Port A, Channel 2 */
#define     LED6        (PTA_PTA2)
/** LED5, Port A, Channel 3 */
#define     LED5        (PTA_PTA3)
/** LED4, Port A, Channel 4 */
#define     LED4        (PTA_PTA4)
/** H1INA, Port A, Channel 5 */
#define     H1INA       (PTA_PTA5)
/** H1INB, Port A, Channel 6 */
#define     H1INB       (PTA_PTA6)
/** TXDB, Port S, Channel 1 */
#define     TXDB        (PTS_PTS1)
/** H2INB, Port S, Channel 2 */
#define     H2INB       (PTS_PTS2)
/** H2INA, Port S, Channel 3 */
#define     H2INA       (PTS_PTS3)
/** UNUSED66, Port J, Channel 7 */
#define     UNUSED66    (PTJ_PTJ7)

/* ~~~~~~~~ Analog Input signal mapping ~~~~~~~~~~~~~~~~~ */

/** TPS_F, Port AD0, Channel 0 */
#define     TPS_F       (au16AnalogAverage[0])
/** MAP_F, Port AD0, Channel 1 */
#define     MAP_F       (au16AnalogAverage[1])
 /** O2IN_F, Port AD0, Channel 2 */
#define     O2IN_F      (au16AnalogAverage[2])
/** ATEMP_F, Port AD0, Channel 3 */
#define     ATEMP_F     (au16AnalogAverage[3])
/** VPWR_F, Port AD0, Channel 4 */
#define     VPWR_F      (au16AnalogAverage[4])
/** TILT_F, Port AD0, Channel 5 */
#define     TILT_F       (au16AnalogAverage[5])
/** ETEMP_F, Port AD0, Channel 6 */
#define     ETEMP_F     (au16AnalogAverage[6])
/** BAP_F, Port AD0, Channel 7 */
#define     BAP_F       (au16AnalogAverage[7])

#endif

#if HARDWARE == REFERENCE
/******************* Reference Design Signal Name Abstraction *************************/

/* ~~~~~~~~ Digital Input signal mapping ~~~~~~~~~~~~~~~~~ */

/** VRSOUT1, Port T, Channel 6 */
#define     VRSOUT1     ((UINT16)PTT_PTT6   * 0xffff)
/** VRSOUT2, Port T, Channel 7 */
#define     VRSOUT2     ((UINT16)PTT_PTT7   * 0xffff)
/** OPSR_F, Port B, Channel 0 */
#define     ENGSTOP_F      ((UINT16)PORTB_PB0  * 0xffff)
/** INJFLT1, Port A, Channel 1 */
#define     INJFLT1        ((UINT16)PTA_PTA0  * 0xffff))
/** IGNFLT1, Port A, Channel 1 */
#define     IGNFLT1        ((UINT16)PTA_PTA1* 0xffff)
/** RELFLT, Port A, Channel 2 */
#define     RELFLT        ((UINT16)PTA_PTA2* 0xffff)
/** RXDB, Port S, Channel 0 */
#define     RXDB        ((UINT16)PTS_PTS0   * 0xffff)
/** SO, Port M, Channel 2 */
#define     SO          ((UINT16)PTM_PTM2   * 0xffff)


/* ~~~~~~~~ Digital Output signal mapping ~~~~~~~~~~~~~~~~~ */


/** EN, Port P, Channel 3 */
#define     EN   (PTP_PTP3)
/** O2HIN, Port P, Channel 2 */
#define     O2HIN        (PTP_PTP2)
/** VLAMPIN, Port P, Channel 1 */
#define     VLAMPIN      (PTP_PTP1)
/** RIN2, Port P, Channel 0 */
#define     RIN2        (PTP_PTP0)
/** INJIN1, Port T, Channel 0 */
#define     INJIN1      (PTT_PTT0)
#define     INJ1_STAT   (PTIT_PTIT0)
/** RIN1, Port T, Channel 1 */
#define     RIN1      (PTT_PTT1)
#define     RIN1_STAT   (PTIT_PTIT1)
/** IGNIN1, Port T, Channel 2 */
#define     IGNIN1      (PTT_PTT2)
#define     IGN1_STAT   (PTIT_PTIT2)
/** WDRFSH, Port T, Channel 4 */
#define     WDRFSH      (PTT_PTT4)
/** MCUTEST3, Port B, Channel 5 */
#define     MCUTEST3      (PTB_PTB5)
/** MCUTEST2, Port B, Channel 6 */
#define     MCUTEST2      (PTB_PTB6)
/** MCUTEST1, Port B, Channel 7 */
#define     MCUTEST1      (PTB_PTB7)
/** TXDB, Port S, Channel 1 */
#define     TXDB        (PTS_PTS1)
/** SI, Port M, Channel 4 */
#define     SI          (PTM_PTM4)
/** SCLK, Port M, Channel 5 */
#define     SCLK        (PTM_PTM5)
/** CSB, Port M, Channel 3 */
#define     CSB         (PTM_PTM3)
/** IN6, Port P, Channel 7 */
#define     IN6   (PTP_PTP7)
/** IN5, Port P, Channel 5 */
#define     IN5   (PTP_PTP5)

/* ~~~~~~~~ Analog Input signal mapping ~~~~~~~~~~~~~~~~~ */

/** TPS_F, Port AD0, Channel 0 */
#define     TPS_F       (au16AnalogAverage[0])
/** MAP_F, Port AD0, Channel 1 */
#define     MAP_F       (au16AnalogAverage[1])
 /** O2IN_F, Port AD0, Channel 2 */
#define     O2IN_F      (au16AnalogAverage[2])
/** ATEMP_F, Port AD0, Channel 3 */
#define     ATEMP_F     (au16AnalogAverage[3])
/** VPWR_F, Port AD0, Channel 4 */
#define     VPWR_F      (au16AnalogAverage[4])
/** TILT_F, Port AD0, Channel 5 */
#define     TILT_F       (au16AnalogAverage[5])
/** ETEMP_F, Port AD0, Channel 6 */
#define     ETEMP_F     (au16AnalogAverage[6])








#endif

/******************************************************************************/

/******************************************************************************/


/*-- Function Prototypes -----------------------------------------------------*/

/** Inputs and Outputs Initialization to default values/configuration */
void vfnInputs_Outputs_Init(void);


#endif /* _INPUT_OUTPUT_H */

/*******************************************************************************/