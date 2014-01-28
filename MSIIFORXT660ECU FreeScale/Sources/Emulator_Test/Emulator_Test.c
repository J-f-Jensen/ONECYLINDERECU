/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Emulator_Test.c
\brief      
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Abraham Tezmol
\version    0.2
\date       21/March/2008
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
/* Input Output definitions and prototypes */ 
#include "ADC.h"

#include "Input_Output.h"

#include "Emulator_Test.h"

#include "SCI.h"

/** Variable types and common definitions */
#include "typedefs.h"
/*******************************************************************************/

extern UINT8 u8SCI_TxData[SCI_TX_MAX_SIZE];
extern UINT8 u8SCI_TxLength;
extern UINT16 au16AnalogAverage[ADC_CHANNELS_TO_SAMPLE];

/* Definition of Analog signal names in ASCII to be published on SCI */
INT8 ai8AnalogSignalName0[]= "Load     :";
INT8 ai8AnalogSignalName1[]= "RPM      :";
INT8 ai8AnalogSignalName2[]= "Fuel Wdth:";
INT8 ai8AnalogSignalName3[]= "Spark Ang:";
INT8 ai8AnalogSignalName4[]= "App State:";

/* External variables to be reported */
extern unsigned int LOAD;
extern unsigned int Engine_Speed;
extern UINT16 u16Current_Fuel1_Pulse; 
extern UINT16 u16Current_Spark1_Start; 
extern unsigned char Current_Appl_State;

/*******************************************************************************/
/**
* \brief    Send out average analog signals in ASCII representation on SCI.
*           This task should be scheduled on a 100ms periodic task to accomplish
*           a loop periodicity of 1000ms (1sec)
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnAnalogData_to_SCI(void)
{
    static UINT8 u8LoopIndex = 0;
    UINT8 u8var1;
    
    u8LoopIndex++;
    
    switch(u8LoopIndex)
    {
        case (1):
            /* Copy Analog signal name in ASCII to SCI output buffer */
            for (u8var1=0; u8var1 < 8; u8var1++)
            {
                u8SCI_TxData[u8SCI_TxLength+u8var1] = ai8AnalogSignalName0[u8var1];
            }
            /* Copy Analog signal value in ASCII to SCI output buffer */
            u8SCI_TxData[u8SCI_TxLength+u8var1] = 0x30;
            u8var1++;
            u8SCI_TxData[u8SCI_TxLength+u8var1] = 0x78;
            u8var1++;
            vfnInteger_to_Ascii((UINT16*)&LOAD, (INT8 *)&u8SCI_TxData[u8SCI_TxLength+u8var1]);
            u8var1+= 4;
            /* Put new line and carriage return characters to SCI output buffer */
            u8SCI_TxData[u8SCI_TxLength+u8var1]= 0x5F;
            u8var1++;
            u8SCI_TxData[u8SCI_TxLength+u8var1]= 0x2C;
            u8SCI_TxLength += u8var1;
            /* Copy Analog signal name in ASCII to SCI output buffer */
            for (u8var1=0; u8var1 < 8; u8var1++)
            {
                u8SCI_TxData[u8SCI_TxLength+u8var1] = ai8AnalogSignalName1[u8var1];
            }
            /* Copy Analog signal value in ASCII to SCI output buffer */
            u8SCI_TxData[u8SCI_TxLength+u8var1] = 0x30;
            u8var1++;
            u8SCI_TxData[u8SCI_TxLength+u8var1] = 0x78;
            u8var1++;
            vfnInteger_to_Ascii((UINT16*)&Engine_Speed, (INT8 *)&u8SCI_TxData[u8SCI_TxLength+u8var1]);
            u8var1+= 4;
            /* Put new line and carriage return characters to SCI output buffer */
            u8SCI_TxData[u8SCI_TxLength+u8var1]= 0x5F;
            u8var1++;
            u8SCI_TxData[u8SCI_TxLength+u8var1]= 0x2C;
            u8SCI_TxLength += u8var1;
            break;
        case (2):
            /* Copy Analog signal name in ASCII to SCI output buffer */
            for (u8var1=0; u8var1 < 8; u8var1++)
            {
                u8SCI_TxData[u8SCI_TxLength+u8var1] = ai8AnalogSignalName2[u8var1];
            }
            /* Copy Analog signal value in ASCII to SCI output buffer */
            u8SCI_TxData[u8SCI_TxLength+u8var1] = 0x30;
            u8var1++;
            u8SCI_TxData[u8SCI_TxLength+u8var1] = 0x78;
            u8var1++;
            vfnInteger_to_Ascii((UINT16*)&u16Current_Fuel1_Pulse, (INT8 *)&u8SCI_TxData[u8SCI_TxLength+u8var1]);
            u8var1+= 4;
            /* Put new line and carriage return characters to SCI output buffer */
            u8SCI_TxData[u8SCI_TxLength+u8var1]= 0x5F;
            u8var1++;
            u8SCI_TxData[u8SCI_TxLength+u8var1]= 0x2C;
            u8SCI_TxLength += u8var1;
            /* Copy Analog signal name in ASCII to SCI output buffer */
            for (u8var1=0; u8var1 < 8; u8var1++)
            {
                u8SCI_TxData[u8SCI_TxLength+u8var1] = ai8AnalogSignalName3[u8var1];
            }
            /* Copy Analog signal value in ASCII to SCI output buffer */
            u8SCI_TxData[u8SCI_TxLength+u8var1] = 0x30;
            u8var1++;
            u8SCI_TxData[u8SCI_TxLength+u8var1] = 0x78;
            u8var1++;
            vfnInteger_to_Ascii((UINT16*)&u16Current_Spark1_Start, (INT8 *)&u8SCI_TxData[u8SCI_TxLength+u8var1]);
            u8var1+= 4;
            /* Put new line and carriage return characters to SCI output buffer */
            u8SCI_TxData[u8SCI_TxLength+u8var1]= 0x5F;
            u8var1++;
            u8SCI_TxData[u8SCI_TxLength+u8var1]= 0x2C;
            u8SCI_TxLength += u8var1;
            break;
        case (3):
            /* Copy Analog signal name in ASCII to SCI output buffer */
            for (u8var1=0; u8var1 < 8; u8var1++)
            {
                u8SCI_TxData[u8SCI_TxLength+u8var1] = ai8AnalogSignalName4[u8var1];
            }
            /* Copy Analog signal value in ASCII to SCI output buffer */
            u8SCI_TxData[u8SCI_TxLength+u8var1] = 0x30;
            u8var1++;
            u8SCI_TxData[u8SCI_TxLength+u8var1] = 0x78;
            u8var1++;
            vfnInteger_to_Ascii((UINT16*)&Current_Appl_State, (INT8 *)&u8SCI_TxData[u8SCI_TxLength+u8var1]);
            u8var1+= 4;
            /* Put new line and carriage return characters to SCI output buffer */
            u8SCI_TxData[u8SCI_TxLength+u8var1]= 0x0D;
            u8var1++;
            u8SCI_TxData[u8SCI_TxLength+u8var1]= 0x0D;
            u8SCI_TxLength += u8var1;
            break;
        
        case (10):
            u8LoopIndex = 0;
            break;
            
        default:
            break;
    }
}
/*******************************************************************************/
/**
* \brief    Conversion to ASCII (8-bit integer) of a 16-bit unsigned integer
* \author   Abraham Tezmol
* \param    UINT16* pu16HexValue - 16-bit unsigned integer to be converted
            INT8 *pi8OutputString - location where ASCII conversion will be placed
* \return   void
*/
void vfnInteger_to_Ascii(UINT16* pu16HexValue, INT8 *pi8OutputString)
{
    INT8 i8TempChar;
       
    i8TempChar = (*pu16HexValue & 0xF000)>> 12;
    if (i8TempChar < 10)
    {    
        i8TempChar = i8TempChar + '0';
    }
    else
    {
        i8TempChar = i8TempChar + 0x37;  
    }
    *pi8OutputString = (UINT8) i8TempChar;
    
    i8TempChar = (*pu16HexValue & 0x0F00)>> 8;
    if (i8TempChar < 10)
    {    
        i8TempChar = i8TempChar + '0';
    }
    else
    {
        i8TempChar = i8TempChar + 0x37;
    }
    pi8OutputString++;
    *pi8OutputString = i8TempChar;
    
    i8TempChar = (*pu16HexValue & 0x00F0)>> 4;
    if (i8TempChar < 10)
    {    
        i8TempChar = i8TempChar + '0';
    }
    else
    {
        i8TempChar = i8TempChar + 0x37;
    }
    pi8OutputString++;
    *pi8OutputString = i8TempChar;
    
    i8TempChar = (*pu16HexValue & 0x000F);
    if (i8TempChar < 10)
    {    
        i8TempChar = i8TempChar + '0';
    }
    else
    {
        i8TempChar = i8TempChar + 0x37;
    }
    pi8OutputString++;
    *pi8OutputString = i8TempChar;
}     
/*******************************************************************************/
/**
* \brief    I/O mapping
* \author   OH
* \param    void
* \return   void
*/

#define ON_16     0xFFFF


/** Analog Input threshols */
#define TPS_F_THRESHOLD     0x07FF 
#define ATEMP_F_THRESHOLD   0x07FF 
#define ETEMP_F_THRESHOLD   0x07FF 
#define O2IN_F_THRESHOLD    0x07FF 
#define MAF_F_THRESHOLD     0x07FF 
#define ACCPS_F_THRESHOLD   0x07FF
#define VRSOUT1_F_THRESHOLD    0x07FF
#define VRSOUT2_F_THRESHOLD    0x07FF


void vfnIO_Mapping(void)
{

  if (KEYSW_F == ON_16) 
  {
    O2HIN  =   ON;
  } 
  else 
  {
    O2HIN  =   OFF;
  }
    
  if (VRSOUT1 > VRSOUT1_F_THRESHOLD || VRSOUT2 > VRSOUT2_F_THRESHOLD)      
  {
    VLAMPIN  =  ON;         
  } 
  else 
  {
    VLAMPIN  =   OFF;
  } 
 

  if (TPS_F > TPS_F_THRESHOLD) 
  {
    H2INB  =  ON;
  } 
  else 
  {
    H2INB  =   OFF;
  }          

  
  if (ATEMP_F > ATEMP_F_THRESHOLD) 
  {
    H2INA  =  ON;
  } 
  else 
  {
    H2INA  =   OFF;
  }          

  if (ETEMP_F > ETEMP_F_THRESHOLD) 
  {
    H1INB  =  ON;
  } 
  else 
  {
    H1INB  =   OFF;
  }          

  if (O2IN_F > O2IN_F_THRESHOLD) 
  {
    H1INA  =  ON;
  } 
  else 
  {
    H1INA  =   OFF;
  }          

  if (MAF_F > MAF_F_THRESHOLD) 
  {
    INJIN1  =  ON;
  } 
  else 
  {
    INJIN1  =   OFF;
  }          

  if (OPSR_F == ON_16) 
  {
    INJIN2  =  ON;
  } 
  else 
  {
    INJIN2  =   OFF;
  }           


  if (KICKSW_F == ON_16) 
  {
    IGNIN2  =  ON;
  } 
  else 
  {
    IGNIN2  =   OFF;
  }          
  

  if (CLTCHSW_F == ON_16) 
  {
    IGNIN1  =  ON;
  } 
  else 
  {
    IGNIN1  =   OFF;
  }             


  if (NGEARSW_F == ON_16) 
  {
    RIN1  =  ON;
  } 
  else 
  {
    RIN1  =   OFF;
  }          


  if (KILLSW_F == ON_16) 
  {
    RIN2  =  ON;
  } 
  else 
  {
    RIN2  =   OFF;
  }          


  if (MAF_F > ACCPS_F_THRESHOLD) //    signal ACCPS_F changed to MAF_F 
  {
    RIN3  =  ON;
  } 
  else 
  {
    RIN3  =   OFF;
  }          
  

}
     
/*******************************************************************************/
