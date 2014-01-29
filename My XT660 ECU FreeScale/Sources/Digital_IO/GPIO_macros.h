/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       GPIO_macros.h
\brief      Macro definitions for registers access and I/O handling
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Jaime Orozco/Abraham Tezmol
\version    0.2
\date       7/07/2007
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

#ifndef _GPIO_MACROS_H        /*prevent duplicated includes*/
#define _GPIO_MACROS_H

/*-- Includes ----------------------------------------------------------------*/
#include "typedefs.h"

/*-- Variables ---------------------------------------------------------------*/
//UINT8 gu8LED_D25_Stat;
//UINT8 gu8LED_D26_Stat;
//UINT8 gu8LED_D27_Stat;
//UINT8 gu8LED_D28_Stat;
//UINT8 gu8LED_D29_Stat;

/*-- Types Definitions -------------------------------------------------------*/

/*-- Defines -----------------------------------------------------------------*/
#define LED_Port    PORTB
#define D22         1
#define D23         2
#define D24         4
#define D25         8
#define D26         16
#define D27         32
#define D28         64
#define D29         128

/*-- Macros ------------------------------------------------------------------*/
/* 8 bit peripheral access */
#define SET_REG8_VALUE(RegName, val)        (RegName = (UINT8)(val))
#define GET_REG8_VALUE(RegName)             (RegName)

#define TST_REG8_BITMASK(RegName, GetMask)  (RegName & (GetMask))
#define CLR_REG8_BITMASK(RegName, ClrMask)  (RegName &= ~(UINT8)(ClrMask))
#define SET_REG8_BITMASK(RegName, SetMask)  (RegName |= (UINT8)(SetMask))
#define NEG_REG8_BITMASK(RegName, InvMask)  (RegName ^= (UINT8)(InvMask))

#define SET_REG8_BITNAME(RegName, BitName)  (RegName |= RegName##_##BitName##_##MASK)
#define CLR_REG8_BITNAME(RegName, BitName)  (RegName &= ~RegName##_##BitName##_##MASK)
#define NEG_REG8_BITNAME(RegName, BitName)  (RegName ^= RegName##_##BitName##_##MASK)
#define TST_REG8_BITNAME(RegName, BitName)  (RegName & RegName##_##BitName##_##MASK)


/* 16 bit peripheral access */

#define SET_REG16_VALUE(RegName, val)       (RegName = (UINT16)(val))
#define GET_REG16_VALUE(RegName)            (RegName)

#define TST_REG16_BITMASK(RegName, GetMask) (RegName & (GetMask))
#define CLR_REG16_BITMASK(RegName, ClrMask) (RegName &= ~(UINT16)(ClrMask))
#define SET_REG16_BITMASK(RegName, SetMask) (RegName |= (UINT16)(SetMask))
#define NEG_REG16_BITMASK(RegName, InvMask) (RegName ^= (UINT16)(InvMask))

#define SET_REG16_BITNAME(RegName, BitName) (RegName |= RegName##_##BitName##_##MASK)
#define CLR_REG16_BITNAME(RegName, BitName) (RegName &= ~RegName##_##BitName##_##MASK)
#define NEG_REG16_BITNAME(RegName, BitName) (RegName ^= RegName##_##BitName##_##MASK)
#define TST_REG16_BITNAME(RegName, BitName) (RegName & RegName##_##BitName##_##MASK)


/* Indicator LEDs handling */

/** Set LED */ 
#define LED_ON(BitMask)                     (LED_Port |= (UINT8)(BitMask))
/** Clear LED */ 
#define LED_OFF(BitMask)                    (LED_Port &= ~(UINT8)(BitMask))
/** Toggle LED */ 
#define LED_TOGGLE(BitMask)                 (LED_Port ^= (UINT8)(BitMask)) 
/** Turn LED on for one cycle, this macro shall be called periodically to operate.
    It requires application to set appropriate u8LED_##x##_Stat flag to 1 */ 
#define FLASH_LED(x)                        \
{                                           \
    switch (gu8LED_##x##_Stat)              \
    {                                       \
        case (1):                           \
            LED_ON(x);                      \
            gu8LED_##x##_Stat = 0;          \
            break;                          \
        default:                            \
            LED_OFF(x);                     \
            break;                          \
    }                                       \
}
/** Turn a combination of 3 LEDs with a unique blinking pattern, 
    this macro should be called periodically to operate. */ 
#define FLASH_MAIN_LED(counter,L0,L1,L2)    \
{                                           \
    (counter)++;                            \
    switch ((counter))                      \
    {                                       \
        case  1:                            \
            LED_ON(L0);                     \
            LED_ON(L1);                     \
            break;                          \
        case  11:                            \
            LED_ON(L1);                     \
            LED_ON(L2);                     \
            break;                          \
        case  3:                            \
            LED_OFF(L0);                    \
            LED_OFF(L1);                    \
            break;                          \
        case  13:                            \
            LED_OFF(L1);                    \
            LED_OFF(L2);                    \
            break;                          \
        case 100:                            \
            (counter) = 0;                  \
            break;                          \
        default:                            \
            break;                          \
    }                                       \
}
/*-- Function Prototypes -----------------------------------------------------*/

#endif /* _GPIO_MACROS_H */

/*******************************************************************************/