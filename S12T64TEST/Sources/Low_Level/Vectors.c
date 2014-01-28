/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Vectors.c
\brief      Interrupt service routine vectors
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Abraham Tezmol
\version    0.1
\date       08/Feb/2008
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
//#include __S12X_DERIVATIVE
/* Interrupt service routines prototypes */ 
//#include "Scheduler.h"
/* Cpu configuration interrupts definition */
#include "cpu.h"
/* SCI interrupts definition */
#include "SCI.h"
/* Crank ISR definition */
//#include "Crank_Sensing.h"
/** Spark control ISR definition */
//#include "Spark_Control.h"
/** Fuel control ISR definition */
//#include "Fuel_Control.h"

//#include "ADC.h"
//#include "Data Management.h"



/* Startup defined in Start12.c */
extern void interrupt  _Startup(void);

UINT8 Test_VAR;

/*******************************************************************************/

/* Dummy interrupt service routine */
#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt Dummy_D_Isr()
{
    Test_VAR = 0;
}



/*******************************************************************************/

/** Interrupt vectors table */
void (* near const vectors[])(void) @ 0xFF10 =  {
    
  Dummy_D_Isr,        /* 0x08  0xFF10 ivVsi           */
  Dummy_D_Isr,        /* 0x09  0xFF12 ivu8Reserved119   */
  Dummy_D_Isr,        /* 0x0A  0xFF14 ivu8Reserved118   */
  Dummy_D_Isr,        /* 0x0B  0xFF16 ivu8Reserved117   */
  Dummy_D_Isr,        /* 0x0C  0xFF18 ivu8Reserved116   */
  Dummy_D_Isr,        /* 0x0D  0xFF1A ivu8Reserved115   */
  Dummy_D_Isr,        /* 0x0E  0xFF1C ivu8Reserved114   */
  Dummy_D_Isr,        /* 0x0F  0xFF1E ivu8Reserved113   */
  Dummy_D_Isr,        /* 0x10  0xFF20 ivu8Reserved112   */
  Dummy_D_Isr,        /* 0x11  0xFF22 ivu8Reserved111   */
  Dummy_D_Isr,        /* 0x12  0xFF24 ivu8Reserved110   */
  Dummy_D_Isr,        /* 0x13  0xFF26 ivu8Reserved109   */
  Dummy_D_Isr,        /* 0x14  0xFF28 ivu8Reserved108   */
  Dummy_D_Isr,        /* 0x15  0xFF2A ivu8Reserved107   */
  Dummy_D_Isr,        /* 0x16  0xFF2C ivu8Reserved106   */
  Dummy_D_Isr,        /* 0x17  0xFF2E ivu8Reserved105   */
  Dummy_D_Isr,        /* 0x18  0xFF30 ivu8Reserved104   */
  Dummy_D_Isr,        /* 0x19  0xFF32 ivu8Reserved103   */
  Dummy_D_Isr,        /* 0x1A  0xFF34 ivu8Reserved102   */
  Dummy_D_Isr,        /* 0x1B  0xFF36 ivu8Reserved101   */
  Dummy_D_Isr,        /* 0x1C  0xFF38 ivu8Reserved100   */
  Dummy_D_Isr,        /* 0x1D  0xFF3A ivu8Reserved99    */
  Dummy_D_Isr,        /* 0x1E  0xFF3C ivu8Reserved98    */
  Dummy_D_Isr,        /* 0x1F  0xFF3E ivu8Reserved97    */
  Dummy_D_Isr,        /* 0x20  0xFF40 ivu8Reserved96    */
  Dummy_D_Isr,        /* 0x21  0xFF42 ivu8Reserved95    */
  Dummy_D_Isr,        /* 0x22  0xFF44 ivu8Reserved94    */
  Dummy_D_Isr,        /* 0x23  0xFF46 ivu8Reserved93    */
  Dummy_D_Isr,        /* 0x24  0xFF48 ivu8Reserved92    */
  Dummy_D_Isr,        /* 0x25  0xFF4A ivu8Reserved91    */
  Dummy_D_Isr,        /* 0x26  0xFF4C ivu8Reserved90    */
  Dummy_D_Isr,        /* 0x27  0xFF4E ivu8Reserved89    */
  Dummy_D_Isr,        /* 0x28  0xFF50 ivu8Reserved88    */
  Dummy_D_Isr,        /* 0x29  0xFF52 ivu8Reserved87    */
  Dummy_D_Isr,        /* 0x2A  0xFF54 ivu8Reserved86    */
  Dummy_D_Isr,        /* 0x2B  0xFF56 ivu8Reserved85    */
  Dummy_D_Isr,        /* 0x2C  0xFF58 ivu8Reserved84    */
  Dummy_D_Isr,        /* 0x2D  0xFF5A ivu8Reserved83    */
  Dummy_D_Isr,        /* 0x2E  0xFF5C ivu8Reserved82    */
  Dummy_D_Isr,        /* 0x2F  0xFF5E ivu8Reserved81    */
  Dummy_D_Isr,        /* 0x30  0xFF60 ivVxsramav      */
  Dummy_D_Isr,        /* 0x31  0xFF62 ivVxsei         */
  Dummy_D_Isr,        /* 0x32  0xFF64 ivVxst7         */
  Dummy_D_Isr,        /* 0x33  0xFF66 ivVxst6         */
  Dummy_D_Isr,        /* 0x34  0xFF68 ivVxst5         */
  Dummy_D_Isr,        /* 0x35  0xFF6A ivVxst4         */
  Dummy_D_Isr,        /* 0x36  0xFF6C ivVxst3         */
  Dummy_D_Isr,        /* 0x37  0xFF6E ivVxst2         */
  Dummy_D_Isr,        /* 0x38  0xFF70 ivVxst1         */
  Dummy_D_Isr,        /* 0x39  0xFF72 ivVxst0         */
  Dummy_D_Isr,        /* 0x3A  0xFF74 ivVpit3         */
  Dummy_D_Isr,        /* 0x3B  0xFF76 ivVpit2         */
  Dummy_D_Isr,        /* 0x3C  0xFF78 ivVpit1         */
  Dummy_D_Isr,        /* 0x3D  0xFF7A ivVpit0         */
  Dummy_D_Isr,        /* 0x3E  0xFF7C ivVu8Reserved65   */
  Dummy_D_Isr,        /* 0x3F  0xFF7E ivVapi          */
  Dummy_D_Isr,        /* 0x40  0xFF80 ivVlvi          */
  Dummy_D_Isr,        /* 0x41  0xFF82 ivVu8Reserved62   */
  Dummy_D_Isr,        /* 0x42  0xFF84 ivVu8Reserved61   */
  Dummy_D_Isr,        /* 0x43  0xFF86 ivVu8Reserved60   */
  Dummy_D_Isr,        /* 0x44  0xFF88 ivVu8Reserved59   */
  Dummy_D_Isr,        /* 0x45  0xFF8A ivVu8Reserved58   */
  Dummy_D_Isr,        /* 0x46  0xFF8C ivVpmffault3    */
  Dummy_D_Isr,        /* 0x47  0xFF8E ivVpmffault2    */
  Dummy_D_Isr,        /* 0x48  0xFF90 ivVpmffault1    */
  Dummy_D_Isr,        /* 0x49  0xFF92 ivVpmffault0    */
  Dummy_D_Isr,        /* 0x4A  0xFF94 ivVpmfgcr       */
  Dummy_D_Isr,        /* 0x4B  0xFF96 ivVpmfgbr       */
  Dummy_D_Isr,        /* 0x4C  0xFF98 ivVpmfgar       */
  Dummy_D_Isr,        /* 0x4D  0xFF9A ivVfrprot       */
  Dummy_D_Isr,        /* 0x4E  0xFF9C ivVfrchi        */
  Dummy_D_Isr,        /* 0x4F  0xFF9E ivVfrwakeup     */
  Dummy_D_Isr,        /* 0x50  0xFFA0 ivVfrrxfifob    */
  Dummy_D_Isr,        /* 0x51  0xFFA2 ivVfrrxfifoa    */
  Dummy_D_Isr,        /* 0x52  0xFFA4 ivVfrrxmessbuff */
  Dummy_D_Isr,        /* 0x53  0xFFA6 ivVfrtxmessbuff */
  Dummy_D_Isr,        /* 0x54  0xFFA8 ivVu8Reserved43   */
  Dummy_D_Isr,        /* 0x55  0xFFAA ivVu8Reserved42   */
  Dummy_D_Isr,        /* 0x56  0xFFAC ivVu8Reserved41   */
  Dummy_D_Isr,        /* 0x57  0xFFAE ivVu8Reserved40   */
  Dummy_D_Isr,        /* 0x58  0xFFB0 ivVcan0tx       */
  Dummy_D_Isr,        /* 0x59  0xFFB2 ivVcan0rx       */
  Dummy_D_Isr,        /* 0x5A  0xFFB4 ivVcan0err      */
  Dummy_D_Isr,        /* 0x5B  0xFFB6 ivVcan0wkup     */
  Dummy_D_Isr,        /* 0x5C  0xFFB8 ivVflash        */
  Dummy_D_Isr,        /* 0x5D  0xFFBA ivVeeprom       */
  Dummy_D_Isr,        /* 0x5E  0xFFBC ivVu8Reserved33   */
  Dummy_D_Isr,        /* 0x5F  0xFFBE ivVspi1         */
  Dummy_D_Isr,        /* 0x60  0xFFC0 ivVu8Reserved31   */
  Dummy_D_Isr,        /* 0x61  0xFFC2 ivVu8Reserved30   */
  Dummy_D_Isr,        /* 0x62  0xFFC4 ivVcrgscm       */
  Dummy_D_Isr,        /* 0x63  0xFFC6 ivVcrgplllck    */
  Dummy_D_Isr,        /* 0x64  0xFFC8 ivVtimpabovf    */
  Dummy_D_Isr,        /* 0x65  0xFFCA ivVtimmdcu      */
  Dummy_D_Isr,        /* 0x66  0xFFCC ivVu8Reserved25   */
  Dummy_D_Isr,        /* 0x67  0xFFCE ivVu8Reserved24   */
  Dummy_D_Isr,        /* 0x68  0xFFD0 ivVu8Reserved22  */
  Dummy_D_Isr,        /* 0x69  0xFFD2 ivVatd    */
  Dummy_D_Isr,        /* 0x6A  0xFFD4 ivVsci1         */
  SCI0_Isr,           /* 0x6B  0xFFD6 ivVsci0         */
  Dummy_D_Isr,        /* 0x6C  0xFFD8 ivVspi0         */
  Dummy_D_Isr,        /* 0x6D  0xFFDA ivVtimpaie      */
  Dummy_D_Isr,        /* 0x6E  0xFFDC ivVtimpaaovf    */
  Dummy_D_Isr,        /* 0x6F  0xFFDE ivVtimovf       */
  Dummy_D_Isr,        /* 0x70  0xFFE0 ivVtimch7       */
  Dummy_D_Isr,        /* 0x71  0xFFE2 ivVtimch6       */
  Dummy_D_Isr,        /* 0x72  0xFFE4 ivVtimch5       */
  Dummy_D_Isr,        /* 0x73  0xFFE6 ivVtimch4       */    
  Dummy_D_Isr,        /* 0x74  0xFFE8 ivVtimch3       */
  Dummy_D_Isr,        /* 0x75  0xFFEA ivVtimch2       */
  Dummy_D_Isr,        /* 0x76  0xFFEC ivVtimch1       */
  Dummy_D_Isr,        /* 0x77  0xFFEE ivVtimch0       */
  Dummy_D_Isr,        /* 0x78  0xFFF0 ivVrti          */
  Dummy_D_Isr,        /* 0x79  0xFFF2 ivVirq          */
  Dummy_D_Isr,        /* 0x7A  0xFFF4 ivVxirq         */
  Dummy_D_Isr,        /* 0x7B  0xFFF6 ivVswi          */
  Dummy_D_Isr,        /* 0x7C  0xFFF8 ivVtrap         */
  _Startup,           /* 0xFFFA  ivVcop               */
  Dummy_D_Isr//,      /* 0xFFFC  ivVclkmon            */
  //Clock_Monitor_Isr//,  /* 0xFFFC  ivVclkmon            */
  //_Startup            /* 0xFFFE  ivVreset             */
};

/*******************************************************************************/
