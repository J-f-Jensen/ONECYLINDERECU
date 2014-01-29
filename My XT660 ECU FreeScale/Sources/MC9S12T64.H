#ifndef _MC9S12T64_H
#define _MC9S12T64_H

/* Types definition */
typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long dword;
typedef unsigned long dlong[2];

#define REG_BASE 0x0000                /* Base address for the I/O register block */

#pragma MESSAGE DISABLE C1106 /* WARNING C1106: Non-standard bitfield type */

//not in generic.h
//#define pPORTA   ((volatile unsigned char*)(0x0000))

//Redefine port A + B + E
#define PORTA_PA0 PORTA_BIT0
#define PORTA_PA1 PORTA_BIT1
#define PORTA_PA2 PORTA_BIT2
#define PORTA_PA3 PORTA_BIT3
#define PORTA_PA4 PORTA_BIT4
#define PORTA_PA5 PORTA_BIT5
#define PORTA_PA6 PORTA_BIT6
#define PORTA_PA7 PORTA_BIT7

#define PORTB_PB0 PORTB_BIT0
#define PORTB_PB1 PORTB_BIT1
#define PORTB_PB2 PORTB_BIT2
#define PORTB_PB3 PORTB_BIT3
#define PORTB_PB4 PORTB_BIT4
#define PORTB_PB5 PORTB_BIT5
#define PORTB_PB6 PORTB_BIT6
#define PORTB_PB7 PORTB_BIT7

#define PORTE_PE0 PORTE_BIT0
#define PORTE_PE1 PORTE_BIT1
#define PORTE_PE2 PORTE_BIT2
#define PORTE_PE3 PORTE_BIT3
#define PORTE_PE4 PORTE_BIT4
#define PORTE_PE5 PORTE_BIT5
#define PORTE_PE6 PORTE_BIT6
#define PORTE_PE7 PORTE_BIT7

#define DDRA_DDRA0 DDRA_BIT0
#define DDRA_DDRA1 DDRA_BIT1
#define DDRA_DDRA2 DDRA_BIT2
#define DDRA_DDRA3 DDRA_BIT3
#define DDRA_DDRA4 DDRA_BIT4
#define DDRA_DDRA5 DDRA_BIT5
#define DDRA_DDRA6 DDRA_BIT6
#define DDRA_DDRA7 DDRA_BIT7

#define DDRB_DDRB0 DDRB_BIT0
#define DDRB_DDRB1 DDRB_BIT1
#define DDRB_DDRB2 DDRB_BIT2
#define DDRB_DDRB3 DDRB_BIT3
#define DDRB_DDRB4 DDRB_BIT4
#define DDRB_DDRB5 DDRB_BIT5
#define DDRB_DDRB6 DDRB_BIT6
#define DDRB_DDRB7 DDRB_BIT7

#define DDRE_DDRE0 DDRE_BIT0
#define DDRE_DDRE1 DDRE_BIT1
#define DDRE_DDRE2 DDRE_BIT2
#define DDRE_DDRE3 DDRE_BIT3
#define DDRE_DDRE4 DDRE_BIT4
#define DDRE_DDRE5 DDRE_BIT5
#define DDRE_DDRE6 DDRE_BIT6
#define DDRE_DDRE7 DDRE_BIT7


/*
#define pPTT     ((volatile unsigned char*)(0x00E0))
#define pPTP     ((volatile unsigned char*)(0x00F0))
#define pDDRT    ((volatile unsigned char*)(0x00E2))
#define pDDRP    ((volatile unsigned char*)(0x00F2))
#define pTC0    ((volatile unsigned short*)(0x0050))
#define pTC1    ((volatile unsigned short*)(0x0052))
#define pTC2    ((volatile unsigned short*)(0x0054))
#define pTC3    ((volatile unsigned short*)(0x0056))
#define pTC4    ((volatile unsigned short*)(0x0058))
#define pTC5    ((volatile unsigned short*)(0x005A))
#define pTC6    ((volatile unsigned short*)(0x005C))
#define pTC7    ((volatile unsigned short*)(0x005E))
*/

//#define TIOS   (*((volatile unsigned char*)(0x0040)))   //timer input cap/output comp select
//#define CFORC  (*((volatile unsigned char*)(0x0041)))   //timer compare force register
//#define TCNT   (*((volatile unsigned short*)(0x0044)))  //timer count register
//#define TCTL1  (*((volatile unsigned char*)(0x0048)))   //timer control register 1
//#define TCTL2  (*((volatile unsigned char*)(0x0049)))   //timer control register 2
//#define TIE    (*((volatile unsigned char*)(0x004C)))   //timer interrupt enable register
//#define TSCR1  (*((volatile unsigned char*)(0x0046)))   //timer system control register 1
//#define TSCR2  (*((volatile unsigned char*)(0x004D)))   //timer system control register 2

//#define PWME   (*((volatile unsigned char*)(0x00A0)))   //PWM enable register
//#define PWMPOL (*((volatile unsigned char*)(0x00A1)))   //PWM polarity register
//#define PWMCLK (*((volatile unsigned char*)(0x00A2)))   //PWM clock select register
//#define PWMPRCLK (*((volatile unsigned char*)(0x00A3))) //PWM prescale clock select register
//#define PWMCAE  (*((volatile unsigned char*)(0x00A4)))  //PWM center align enable register
//#define PWMSCLA (*((volatile unsigned char*)(0x00A8)))  //PWM scale A register
//#define PWMSCLB (*((volatile unsigned char*)(0x00A9)))  //PWM scale A register

//#define PWMDTY2 (*((volatile unsigned char*)(0x00BE)))  //PWM channel duty register
//#define PWMDTY3 (*((volatile unsigned char*)(0x00BF)))  //PWM channel duty register
//#define PWMDTY4 (*((volatile unsigned char*)(0x00C0)))  //PWM channel duty register

//#define PWMPER2 (*((volatile unsigned char*)(0x00B6)))  //PWM channel period register
//#define PWMPER3 (*((volatile unsigned char*)(0x00B7)))  //PWM channel period register
//#define PWMPER4 (*((volatile unsigned char*)(0x00B8)))  //PWM channel period register

//#define PWMCNT0 (*((volatile unsigned char*)(0x00AC)))  //PWM channel counter register
//#define PWMCNT1 (*((volatile unsigned char*)(0x00AD)))  //PWM channel counter register
//#define PWMCNT2 (*((volatile unsigned char*)(0x00AE)))  //PWM channel counter register
//#define PWMCNT3 (*((volatile unsigned char*)(0x00AF)))  //PWM channel counter register
//#define PWMCNT4 (*((volatile unsigned char*)(0x00B0)))  //PWM channel counter register

//#define TCTL1  (*((volatile unsigned char*)(0x0048)))   //timer control register 1
//#define TCTL2  (*((volatile unsigned char*)(0x0049)))   //timer control register 2
//#define TCTL3  (*((volatile unsigned char*)(0x004A)))   //timer control register 3
//#define TCTL4  (*((volatile unsigned char*)(0x004B)))   //timer control register 4

//#define TC0    (*((volatile unsigned short*)(0x0050)))  //TIMER CHANNEL REGISTER
//#define TC1    (*((volatile unsigned short*)(0x0052)))  //TIMER CHANNEL REGISTER
//#define TC2    (*((volatile unsigned short*)(0x0054)))  //TIMER CHANNEL REGISTER
//#define TC3    (*((volatile unsigned short*)(0x0056)))  //TIMER CHANNEL REGISTER
//#define TC4    (*((volatile unsigned short*)(0x0058)))  //TIMER CHANNEL REGISTER
//#define TC5    (*((volatile unsigned short*)(0x005A)))  //TIMER CHANNEL REGISTER
//#define TC6    (*((volatile unsigned short*)(0x005C)))  //TIMER CHANNEL REGISTER
//#define TC7    (*((volatile unsigned short*)(0x005E)))  //TIMER CHANNEL REGISTER

//#define TFLG1  (*((volatile unsigned char*)(0x004E)))   //main timer interrupt flag 1
//#define TFLG2  (*((volatile unsigned char*)(0x004F)))   //main timer interrupt flag 2


/*** TC0 - Timer Input Capture/Output Compare Register 0; 0x00000050 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TC0Hi - Timer Input Capture/Output Compare Register 0 High; 0x00000050 ***/
    union {
      byte Byte;
    } TC0HiSTR;
    #define TC0Hi                       _TC0.Overlap_STR.TC0HiSTR.Byte
    

    /*** TC0Lo - Timer Input Capture/Output Compare Register 0 Low; 0x00000051 ***/
    union {
      byte Byte;
    } TC0LoSTR;
    #define TC0Lo                       _TC0.Overlap_STR.TC0LoSTR.Byte
    
  } Overlap_STR;

} TC0STR;
extern volatile TC0STR _TC0 @(REG_BASE + 0x00000050UL);
#define TC0                             _TC0.Word
/* TC_ARR: Access 8 TCx registers in an array */
#define TC_ARR                          ((volatile word *) &TC0)


/*** TC1 - Timer Input Capture/Output Compare Register 1; 0x00000052 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TC1Hi - Timer Input Capture/Output Compare Register 1 High; 0x00000052 ***/
    union {
      byte Byte;
    } TC1HiSTR;
    #define TC1Hi                       _TC1.Overlap_STR.TC1HiSTR.Byte
    

    /*** TC1Lo - Timer Input Capture/Output Compare Register 1 Low; 0x00000053 ***/
    union {
      byte Byte;
    } TC1LoSTR;
    #define TC1Lo                       _TC1.Overlap_STR.TC1LoSTR.Byte
    
  } Overlap_STR;

} TC1STR;
extern volatile TC1STR _TC1 @(REG_BASE + 0x00000052UL);
#define TC1                             _TC1.Word


/*** TC2 - Timer Input Capture/Output Compare Register 2; 0x00000054 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TC2Hi - Timer Input Capture/Output Compare Register 2 High; 0x00000054 ***/
    union {
      byte Byte;
    } TC2HiSTR;
    #define TC2Hi                       _TC2.Overlap_STR.TC2HiSTR.Byte
    

    /*** TC2Lo - Timer Input Capture/Output Compare Register 2 Low; 0x00000055 ***/
    union {
      byte Byte;
    } TC2LoSTR;
    #define TC2Lo                       _TC2.Overlap_STR.TC2LoSTR.Byte
    
  } Overlap_STR;

} TC2STR;
extern volatile TC2STR _TC2 @(REG_BASE + 0x00000054UL);
#define TC2                             _TC2.Word


/*** TC3 - Timer Input Capture/Output Compare Register 3; 0x00000056 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TC3Hi - Timer Input Capture/Output Compare Register 3 High; 0x00000056 ***/
    union {
      byte Byte;
    } TC3HiSTR;
    #define TC3Hi                       _TC3.Overlap_STR.TC3HiSTR.Byte
    

    /*** TC3Lo - Timer Input Capture/Output Compare Register 3 Low; 0x00000057 ***/
    union {
      byte Byte;
    } TC3LoSTR;
    #define TC3Lo                       _TC3.Overlap_STR.TC3LoSTR.Byte
    
  } Overlap_STR;

} TC3STR;
extern volatile TC3STR _TC3 @(REG_BASE + 0x00000056UL);
#define TC3                             _TC3.Word


/*** TC4 - Timer Input Capture/Output Compare Register 4; 0x00000058 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TC4Hi - Timer Input Capture/Output Compare Register 4 High; 0x00000058 ***/
    union {
      byte Byte;
    } TC4HiSTR;
    #define TC4Hi                       _TC4.Overlap_STR.TC4HiSTR.Byte
    

    /*** TC4Lo - Timer Input Capture/Output Compare Register 4 Low; 0x00000059 ***/
    union {
      byte Byte;
    } TC4LoSTR;
    #define TC4Lo                       _TC4.Overlap_STR.TC4LoSTR.Byte
    
  } Overlap_STR;

} TC4STR;
extern volatile TC4STR _TC4 @(REG_BASE + 0x00000058UL);
#define TC4                             _TC4.Word


/*** TC5 - Timer Input Capture/Output Compare Register 5; 0x0000005A ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TC5Hi - Timer Input Capture/Output Compare Register 5 High; 0x0000005A ***/
    union {
      byte Byte;
    } TC5HiSTR;
    #define TC5Hi                       _TC5.Overlap_STR.TC5HiSTR.Byte
    

    /*** TC5Lo - Timer Input Capture/Output Compare Register 5 Low; 0x0000005B ***/
    union {
      byte Byte;
    } TC5LoSTR;
    #define TC5Lo                       _TC5.Overlap_STR.TC5LoSTR.Byte
    
  } Overlap_STR;

} TC5STR;
extern volatile TC5STR _TC5 @(REG_BASE + 0x0000005AUL);
#define TC5                             _TC5.Word


/*** TC6 - Timer Input Capture/Output Compare Register 6; 0x0000005C ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TC6Hi - Timer Input Capture/Output Compare Register 6 High; 0x0000005C ***/
    union {
      byte Byte;
    } TC6HiSTR;
    #define TC6Hi                       _TC6.Overlap_STR.TC6HiSTR.Byte
    

    /*** TC6Lo - Timer Input Capture/Output Compare Register 6 Low; 0x0000005D ***/
    union {
      byte Byte;
    } TC6LoSTR;
    #define TC6Lo                       _TC6.Overlap_STR.TC6LoSTR.Byte
    
  } Overlap_STR;

} TC6STR;
extern volatile TC6STR _TC6 @(REG_BASE + 0x0000005CUL);
#define TC6                             _TC6.Word


/*** TC7 - Timer Input Capture/Output Compare Register 7; 0x0000005E ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TC7Hi - Timer Input Capture/Output Compare Register 7 High; 0x0000005E ***/
    union {
      byte Byte;
    } TC7HiSTR;
    #define TC7Hi                       _TC7.Overlap_STR.TC7HiSTR.Byte
    

    /*** TC7Lo - Timer Input Capture/Output Compare Register 7 Low; 0x0000005F ***/
    union {
      byte Byte;
    } TC7LoSTR;
    #define TC7Lo                       _TC7.Overlap_STR.TC7LoSTR.Byte
    
  } Overlap_STR;

} TC7STR;
extern volatile TC7STR _TC7 @(REG_BASE + 0x0000005EUL);
#define TC7                             _TC7.Word

/*** TIOS - Timer Input Capture/Output Compare Select; 0x00000040 ***/
typedef union {
  byte Byte;
  struct {
    byte IOS0        :1;                                       /* Input Capture or Output Compare Channel Configuration Bit 0 */
    byte IOS1        :1;                                       /* Input Capture or Output Compare Channel Configuration Bit 1 */
    byte IOS2        :1;                                       /* Input Capture or Output Compare Channel Configuration Bit 2 */
    byte IOS3        :1;                                       /* Input Capture or Output Compare Channel Configuration Bit 3 */
    byte IOS4        :1;                                       /* Input Capture or Output Compare Channel Configuration Bit 4 */
    byte IOS5        :1;                                       /* Input Capture or Output Compare Channel Configuration Bit 5 */
    byte IOS6        :1;                                       /* Input Capture or Output Compare Channel Configuration Bit 6 */
    byte IOS7        :1;                                       /* Input Capture or Output Compare Channel Configuration Bit 7 */
  } Bits;
} TIOSSTR;
extern volatile TIOSSTR _TIOS @(REG_BASE + 0x00000040UL);
#define TIOS                            _TIOS.Byte
#define TIOS_IOS0                       _TIOS.Bits.IOS0
#define TIOS_IOS1                       _TIOS.Bits.IOS1
#define TIOS_IOS2                       _TIOS.Bits.IOS2
#define TIOS_IOS3                       _TIOS.Bits.IOS3
#define TIOS_IOS4                       _TIOS.Bits.IOS4
#define TIOS_IOS5                       _TIOS.Bits.IOS5
#define TIOS_IOS6                       _TIOS.Bits.IOS6
#define TIOS_IOS7                       _TIOS.Bits.IOS7

#define TIOS_IOS0_MASK                  1U
#define TIOS_IOS1_MASK                  2U
#define TIOS_IOS2_MASK                  4U
#define TIOS_IOS3_MASK                  8U
#define TIOS_IOS4_MASK                  16U
#define TIOS_IOS5_MASK                  32U
#define TIOS_IOS6_MASK                  64U
#define TIOS_IOS7_MASK                  128U

/*** CFORC - Timer Compare Force Register; 0x00000041 ***/
typedef union {
  byte Byte;
  struct {
    byte FOC0        :1;                                       /* Force Output Compare Action for Channel 0 */
    byte FOC1        :1;                                       /* Force Output Compare Action for Channel 1 */
    byte FOC2        :1;                                       /* Force Output Compare Action for Channel 2 */
    byte FOC3        :1;                                       /* Force Output Compare Action for Channel 3 */
    byte FOC4        :1;                                       /* Force Output Compare Action for Channel 4 */
    byte FOC5        :1;                                       /* Force Output Compare Action for Channel 5 */
    byte FOC6        :1;                                       /* Force Output Compare Action for Channel 6 */
    byte FOC7        :1;                                       /* Force Output Compare Action for Channel 7 */
  } Bits;
} CFORCSTR;
extern volatile CFORCSTR _CFORC @(REG_BASE + 0x00000041UL);
#define CFORC                           _CFORC.Byte
#define CFORC_FOC0                      _CFORC.Bits.FOC0
#define CFORC_FOC1                      _CFORC.Bits.FOC1
#define CFORC_FOC2                      _CFORC.Bits.FOC2
#define CFORC_FOC3                      _CFORC.Bits.FOC3
#define CFORC_FOC4                      _CFORC.Bits.FOC4
#define CFORC_FOC5                      _CFORC.Bits.FOC5
#define CFORC_FOC6                      _CFORC.Bits.FOC6
#define CFORC_FOC7                      _CFORC.Bits.FOC7

#define CFORC_FOC0_MASK                 1U
#define CFORC_FOC1_MASK                 2U
#define CFORC_FOC2_MASK                 4U
#define CFORC_FOC3_MASK                 8U
#define CFORC_FOC4_MASK                 16U
#define CFORC_FOC5_MASK                 32U
#define CFORC_FOC6_MASK                 64U
#define CFORC_FOC7_MASK                 128U

/*** TCNT - Timer Count Register; 0x00000044 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TCNTHi - Timer Count Register High; 0x00000044 ***/
    union {
      byte Byte;
    } TCNTHiSTR;
    #define TCNTHi                      _TCNT.Overlap_STR.TCNTHiSTR.Byte
    

    /*** TCNTLo - Timer Count Register Low; 0x00000045 ***/
    union {
      byte Byte;
    } TCNTLoSTR;
    #define TCNTLo                      _TCNT.Overlap_STR.TCNTLoSTR.Byte
    
  } Overlap_STR;

} TCNTSTR;
extern volatile TCNTSTR _TCNT @(REG_BASE + 0x00000044UL);
#define TCNT                            _TCNT.Word

/*** TSCR1 - Timer System Control Register1; 0x00000046 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte TFFCA       :1;                                       /* Timer Fast Flag Clear All */
    byte TSFRZ       :1;                                       /* Timer and Modulus Counter Stop While in Freeze Mode */
    byte TSWAI       :1;                                       /* Timer Module Stops While in Wait */
    byte TEN         :1;                                       /* Timer Enable */
  } Bits;
} TSCR1STR;
extern volatile TSCR1STR _TSCR1 @(REG_BASE + 0x00000046UL);
#define TSCR1                           _TSCR1.Byte
#define TSCR1_TFFCA                     _TSCR1.Bits.TFFCA
#define TSCR1_TSFRZ                     _TSCR1.Bits.TSFRZ
#define TSCR1_TSWAI                     _TSCR1.Bits.TSWAI
#define TSCR1_TEN                       _TSCR1.Bits.TEN

#define TSCR1_TFFCA_MASK                16U
#define TSCR1_TSFRZ_MASK                32U
#define TSCR1_TSWAI_MASK                64U
#define TSCR1_TEN_MASK                  128U

/*** TCTL1 - Timer Control Register 1; 0x00000048 ***/
typedef union {
  byte Byte;
  struct {
    byte OL4         :1;                                       /* Output Level Bit 4 */
    byte OM4         :1;                                       /* Output Mode Bit 4 */
    byte OL5         :1;                                       /* Output Level Bit 5 */
    byte OM5         :1;                                       /* Output Mode Bit 5 */
    byte OL6         :1;                                       /* Output Level Bit 6 */
    byte OM6         :1;                                       /* Output Mode Bit 6 */
    byte OL7         :1;                                       /* Output Level Bit 7 */
    byte OM7         :1;                                       /* Output Mode Bit 7 */
  } Bits;
} TCTL1STR;
extern volatile TCTL1STR _TCTL1 @(REG_BASE + 0x00000048UL);
#define TCTL1                           _TCTL1.Byte
#define TCTL1_OL4                       _TCTL1.Bits.OL4
#define TCTL1_OM4                       _TCTL1.Bits.OM4
#define TCTL1_OL5                       _TCTL1.Bits.OL5
#define TCTL1_OM5                       _TCTL1.Bits.OM5
#define TCTL1_OL6                       _TCTL1.Bits.OL6
#define TCTL1_OM6                       _TCTL1.Bits.OM6
#define TCTL1_OL7                       _TCTL1.Bits.OL7
#define TCTL1_OM7                       _TCTL1.Bits.OM7

#define TCTL1_OL4_MASK                  1U
#define TCTL1_OM4_MASK                  2U
#define TCTL1_OL5_MASK                  4U
#define TCTL1_OM5_MASK                  8U
#define TCTL1_OL6_MASK                  16U
#define TCTL1_OM6_MASK                  32U
#define TCTL1_OL7_MASK                  64U
#define TCTL1_OM7_MASK                  128U


/*** TCTL2 - Timer Control Register 2; 0x00000049 ***/
typedef union {
  byte Byte;
  struct {
    byte OL0         :1;                                       /* Output Level Bit 0 */
    byte OM0         :1;                                       /* Output Mode Bit 0 */
    byte OL1         :1;                                       /* Output Level Bit 1 */
    byte OM1         :1;                                       /* Output Mode Bit 1 */
    byte OL2         :1;                                       /* Output Level Bit 2 */
    byte OM2         :1;                                       /* Output Mode Bit 2 */
    byte OL3         :1;                                       /* Output Level Bit 3 */
    byte OM3         :1;                                       /* Output Mode Bit 3 */
  } Bits;
} TCTL2STR;
extern volatile TCTL2STR _TCTL2 @(REG_BASE + 0x00000049UL);
#define TCTL2                           _TCTL2.Byte
#define TCTL2_OL0                       _TCTL2.Bits.OL0
#define TCTL2_OM0                       _TCTL2.Bits.OM0
#define TCTL2_OL1                       _TCTL2.Bits.OL1
#define TCTL2_OM1                       _TCTL2.Bits.OM1
#define TCTL2_OL2                       _TCTL2.Bits.OL2
#define TCTL2_OM2                       _TCTL2.Bits.OM2
#define TCTL2_OL3                       _TCTL2.Bits.OL3
#define TCTL2_OM3                       _TCTL2.Bits.OM3

#define TCTL2_OL0_MASK                  1U
#define TCTL2_OM0_MASK                  2U
#define TCTL2_OL1_MASK                  4U
#define TCTL2_OM1_MASK                  8U
#define TCTL2_OL2_MASK                  16U
#define TCTL2_OM2_MASK                  32U
#define TCTL2_OL3_MASK                  64U
#define TCTL2_OM3_MASK                  128U


/*** TCTL3 - Timer Control Register 3; 0x0000004A ***/
typedef union {
  byte Byte;
  struct {
    byte EDG4A       :1;                                       /* Input Capture Edge Control 4A */
    byte EDG4B       :1;                                       /* Input Capture Edge Control 4B */
    byte EDG5A       :1;                                       /* Input Capture Edge Control 5A */
    byte EDG5B       :1;                                       /* Input Capture Edge Control 5B */
    byte EDG6A       :1;                                       /* Input Capture Edge Control 6A */
    byte EDG6B       :1;                                       /* Input Capture Edge Control 6B */
    byte EDG7A       :1;                                       /* Input Capture Edge Control 7A */
    byte EDG7B       :1;                                       /* Input Capture Edge Control 7B */
  } Bits;
  struct {
    byte grpEDG4x :2;
    byte grpEDG5x :2;
    byte grpEDG6x :2;
    byte grpEDG7x :2;
  } MergedBits;
} TCTL3STR;
extern volatile TCTL3STR _TCTL3 @(REG_BASE + 0x0000004AUL);
#define TCTL3                           _TCTL3.Byte
#define TCTL3_EDG4A                     _TCTL3.Bits.EDG4A
#define TCTL3_EDG4B                     _TCTL3.Bits.EDG4B
#define TCTL3_EDG5A                     _TCTL3.Bits.EDG5A
#define TCTL3_EDG5B                     _TCTL3.Bits.EDG5B
#define TCTL3_EDG6A                     _TCTL3.Bits.EDG6A
#define TCTL3_EDG6B                     _TCTL3.Bits.EDG6B
#define TCTL3_EDG7A                     _TCTL3.Bits.EDG7A
#define TCTL3_EDG7B                     _TCTL3.Bits.EDG7B
#define TCTL3_EDG4x                     _TCTL3.MergedBits.grpEDG4x
#define TCTL3_EDG5x                     _TCTL3.MergedBits.grpEDG5x
#define TCTL3_EDG6x                     _TCTL3.MergedBits.grpEDG6x
#define TCTL3_EDG7x                     _TCTL3.MergedBits.grpEDG7x

#define TCTL3_EDG4A_MASK                1U
#define TCTL3_EDG4B_MASK                2U
#define TCTL3_EDG5A_MASK                4U
#define TCTL3_EDG5B_MASK                8U
#define TCTL3_EDG6A_MASK                16U
#define TCTL3_EDG6B_MASK                32U
#define TCTL3_EDG7A_MASK                64U
#define TCTL3_EDG7B_MASK                128U
#define TCTL3_EDG4x_MASK                3U
#define TCTL3_EDG4x_BITNUM              0U
#define TCTL3_EDG5x_MASK                12U
#define TCTL3_EDG5x_BITNUM              2U
#define TCTL3_EDG6x_MASK                48U
#define TCTL3_EDG6x_BITNUM              4U
#define TCTL3_EDG7x_MASK                192U
#define TCTL3_EDG7x_BITNUM              6U

/*** TCTL4 - Timer Control Register 4; 0x0000004B ***/
typedef union {
  byte Byte;
  struct {
    byte EDG0A       :1;                                       /* Input Capture Edge Control 0A */
    byte EDG0B       :1;                                       /* Input Capture Edge Control 0B */
    byte EDG1A       :1;                                       /* Input Capture Edge Control 1A */
    byte EDG1B       :1;                                       /* Input Capture Edge Control 1B */
    byte EDG2A       :1;                                       /* Input Capture Edge Control 2A */
    byte EDG2B       :1;                                       /* Input Capture Edge Control 2B */
    byte EDG3A       :1;                                       /* Input Capture Edge Control 3A */
    byte EDG3B       :1;                                       /* Input Capture Edge Control 3B */
  } Bits;
  struct {
    byte grpEDG0x :2;
    byte grpEDG1x :2;
    byte grpEDG2x :2;
    byte grpEDG3x :2;
  } MergedBits;
} TCTL4STR;
extern volatile TCTL4STR _TCTL4 @(REG_BASE + 0x0000004BUL);
#define TCTL4                           _TCTL4.Byte
#define TCTL4_EDG0A                     _TCTL4.Bits.EDG0A
#define TCTL4_EDG0B                     _TCTL4.Bits.EDG0B
#define TCTL4_EDG1A                     _TCTL4.Bits.EDG1A
#define TCTL4_EDG1B                     _TCTL4.Bits.EDG1B
#define TCTL4_EDG2A                     _TCTL4.Bits.EDG2A
#define TCTL4_EDG2B                     _TCTL4.Bits.EDG2B
#define TCTL4_EDG3A                     _TCTL4.Bits.EDG3A
#define TCTL4_EDG3B                     _TCTL4.Bits.EDG3B
#define TCTL4_EDG0x                     _TCTL4.MergedBits.grpEDG0x
#define TCTL4_EDG1x                     _TCTL4.MergedBits.grpEDG1x
#define TCTL4_EDG2x                     _TCTL4.MergedBits.grpEDG2x
#define TCTL4_EDG3x                     _TCTL4.MergedBits.grpEDG3x

#define TCTL4_EDG0A_MASK                1U
#define TCTL4_EDG0B_MASK                2U
#define TCTL4_EDG1A_MASK                4U
#define TCTL4_EDG1B_MASK                8U
#define TCTL4_EDG2A_MASK                16U
#define TCTL4_EDG2B_MASK                32U
#define TCTL4_EDG3A_MASK                64U
#define TCTL4_EDG3B_MASK                128U
#define TCTL4_EDG0x_MASK                3U
#define TCTL4_EDG0x_BITNUM              0U
#define TCTL4_EDG1x_MASK                12U
#define TCTL4_EDG1x_BITNUM              2U
#define TCTL4_EDG2x_MASK                48U
#define TCTL4_EDG2x_BITNUM              4U
#define TCTL4_EDG3x_MASK                192U
#define TCTL4_EDG3x_BITNUM              6U

/*** TIE - Timer Interrupt Enable Register; 0x0000004C ***/
typedef union {
  byte Byte;
  struct {
    byte C0I         :1;                                       /* Input Capture/Output Compare Interrupt Enable Bit 0 */
    byte C1I         :1;                                       /* Input Capture/Output Compare Interrupt Enable Bit 1 */
    byte C2I         :1;                                       /* Input Capture/Output Compare Interrupt Enable Bit 2 */
    byte C3I         :1;                                       /* Input Capture/Output Compare Interrupt Enable Bit 3 */
    byte C4I         :1;                                       /* Input Capture/Output Compare Interrupt Enable Bit 4 */
    byte C5I         :1;                                       /* Input Capture/Output Compare Interrupt Enable Bit 5 */
    byte C6I         :1;                                       /* Input Capture/Output Compare Interrupt Enable Bit 6 */
    byte C7I         :1;                                       /* Input Capture/Output Compare Interrupt Enable Bit 7 */
  } Bits;
} TIESTR;
extern volatile TIESTR _TIE @(REG_BASE + 0x0000004CUL);
#define TIE                             _TIE.Byte
#define TIE_C0I                         _TIE.Bits.C0I
#define TIE_C1I                         _TIE.Bits.C1I
#define TIE_C2I                         _TIE.Bits.C2I
#define TIE_C3I                         _TIE.Bits.C3I
#define TIE_C4I                         _TIE.Bits.C4I
#define TIE_C5I                         _TIE.Bits.C5I
#define TIE_C6I                         _TIE.Bits.C6I
#define TIE_C7I                         _TIE.Bits.C7I

#define TIE_C0I_MASK                    1U
#define TIE_C1I_MASK                    2U
#define TIE_C2I_MASK                    4U
#define TIE_C3I_MASK                    8U
#define TIE_C4I_MASK                    16U
#define TIE_C5I_MASK                    32U
#define TIE_C6I_MASK                    64U
#define TIE_C7I_MASK                    128U

/*** TSCR2 - Timer System Control Register 2; 0x0000004D ***/
typedef union {
  byte Byte;
  struct {
    byte PR0         :1;                                       /* Timer Prescaler Select Bit 0 */
    byte PR1         :1;                                       /* Timer Prescaler Select Bit 1 */
    byte PR2         :1;                                       /* Timer Prescaler Select Bit 2 */
    byte TCRE        :1;                                       /* Timer Counter Reset Enable */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte TOI         :1;                                       /* Timer Overflow Interrupt Enable */
  } Bits;
  struct {
    byte grpPR   :3;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} TSCR2STR;
extern volatile TSCR2STR _TSCR2 @(REG_BASE + 0x0000004DUL);
#define TSCR2                           _TSCR2.Byte
#define TSCR2_PR0                       _TSCR2.Bits.PR0
#define TSCR2_PR1                       _TSCR2.Bits.PR1
#define TSCR2_PR2                       _TSCR2.Bits.PR2
#define TSCR2_TCRE                      _TSCR2.Bits.TCRE
#define TSCR2_TOI                       _TSCR2.Bits.TOI
#define TSCR2_PR                        _TSCR2.MergedBits.grpPR

#define TSCR2_PR0_MASK                  1U
#define TSCR2_PR1_MASK                  2U
#define TSCR2_PR2_MASK                  4U
#define TSCR2_TCRE_MASK                 8U
#define TSCR2_TOI_MASK                  128U
#define TSCR2_PR_MASK                   7U
#define TSCR2_PR_BITNUM                 0U


/*** TFLG1 - Main Timer Interrupt Flag 1; 0x0000004E ***/
typedef union {
  byte Byte;
  struct {
    byte C0F         :1;                                       /* Input Capture/Output Compare Channel Flag 0 */
    byte C1F         :1;                                       /* Input Capture/Output Compare Channel Flag 1 */
    byte C2F         :1;                                       /* Input Capture/Output Compare Channel Flag 2 */
    byte C3F         :1;                                       /* Input Capture/Output Compare Channel Flag 3 */
    byte C4F         :1;                                       /* Input Capture/Output Compare Channel Flag 4 */
    byte C5F         :1;                                       /* Input Capture/Output Compare Channel Flag 5 */
    byte C6F         :1;                                       /* Input Capture/Output Compare Channel Flag 6 */
    byte C7F         :1;                                       /* Input Capture/Output Compare Channel Flag 7 */
  } Bits;
} TFLG1STR;
extern volatile TFLG1STR _TFLG1 @(REG_BASE + 0x0000004EUL);
#define TFLG1                           _TFLG1.Byte
#define TFLG1_C0F                       _TFLG1.Bits.C0F
#define TFLG1_C1F                       _TFLG1.Bits.C1F
#define TFLG1_C2F                       _TFLG1.Bits.C2F
#define TFLG1_C3F                       _TFLG1.Bits.C3F
#define TFLG1_C4F                       _TFLG1.Bits.C4F
#define TFLG1_C5F                       _TFLG1.Bits.C5F
#define TFLG1_C6F                       _TFLG1.Bits.C6F
#define TFLG1_C7F                       _TFLG1.Bits.C7F

#define TFLG1_C0F_MASK                  1U
#define TFLG1_C1F_MASK                  2U
#define TFLG1_C2F_MASK                  4U
#define TFLG1_C3F_MASK                  8U
#define TFLG1_C4F_MASK                  16U
#define TFLG1_C5F_MASK                  32U
#define TFLG1_C6F_MASK                  64U
#define TFLG1_C7F_MASK                  128U


/*** TFLG2 - Main Timer Interrupt Flag 2; 0x0000004F ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte TOF         :1;                                       /* Timer Overflow Flag */
  } Bits;
} TFLG2STR;
extern volatile TFLG2STR _TFLG2 @(REG_BASE + 0x0000004FUL);
#define TFLG2                           _TFLG2.Byte
#define TFLG2_TOF                       _TFLG2.Bits.TOF

#define TFLG2_TOF_MASK                  128U

/*** PACTL - 16-Bit Pulse Accumulator A Control Register; 0x00000060 ***/
typedef union {
  byte Byte;
  struct {
    byte PAI         :1;                                       /* Pulse Accumulator Input Interrupt enable */
    byte PAOVI       :1;                                       /* Pulse Accumulator A Overflow Interrupt enable */
    byte CLK0        :1;                                       /* Clock Select Bit 0 */
    byte CLK1        :1;                                       /* Clock Select Bit 1 */
    byte PEDGE       :1;                                       /* Pulse Accumulator Edge Control */
    byte PAMOD       :1;                                       /* Pulse Accumulator Mode */
    byte PAEN        :1;                                       /* Pulse Accumulator A System Enable */
    byte             :1; 
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpCLK  :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} PACTLSTR;
extern volatile PACTLSTR _PACTL @(REG_BASE + 0x00000060UL);
#define PACTL                           _PACTL.Byte
#define PACTL_PAI                       _PACTL.Bits.PAI
#define PACTL_PAOVI                     _PACTL.Bits.PAOVI
#define PACTL_CLK0                      _PACTL.Bits.CLK0
#define PACTL_CLK1                      _PACTL.Bits.CLK1
#define PACTL_PEDGE                     _PACTL.Bits.PEDGE
#define PACTL_PAMOD                     _PACTL.Bits.PAMOD
#define PACTL_PAEN                      _PACTL.Bits.PAEN
#define PACTL_CLK                       _PACTL.MergedBits.grpCLK

#define PACTL_PAI_MASK                  1U
#define PACTL_PAOVI_MASK                2U
#define PACTL_CLK0_MASK                 4U
#define PACTL_CLK1_MASK                 8U
#define PACTL_PEDGE_MASK                16U
#define PACTL_PAMOD_MASK                32U
#define PACTL_PAEN_MASK                 64U
#define PACTL_CLK_MASK                  12U
#define PACTL_CLK_BITNUM                2U

/*** PWME - PWM Enable Register; 0x000000A0 ***/
typedef union {
  byte Byte;
  struct {
    byte PWME0       :1;                                       /* Pulse Width Channel 0 Enable */
    byte PWME1       :1;                                       /* Pulse Width Channel 1 Enable */
    byte PWME2       :1;                                       /* Pulse Width Channel 2 Enable */
    byte PWME3       :1;                                       /* Pulse Width Channel 3 Enable */
    byte PWME4       :1;                                       /* Pulse Width Channel 4 Enable */
    byte PWME5       :1;                                       /* Pulse Width Channel 5 Enable */
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpPWME :6;
    byte         :1;
    byte         :1;
  } MergedBits;
} PWMESTR;
extern volatile PWMESTR _PWME @(REG_BASE + 0x000000A0UL);
#define PWME                            _PWME.Byte
#define PWME_PWME0                      _PWME.Bits.PWME0
#define PWME_PWME1                      _PWME.Bits.PWME1
#define PWME_PWME2                      _PWME.Bits.PWME2
#define PWME_PWME3                      _PWME.Bits.PWME3
#define PWME_PWME4                      _PWME.Bits.PWME4
#define PWME_PWME5                      _PWME.Bits.PWME5
#define PWME_PWME                       _PWME.MergedBits.grpPWME

#define PWME_PWME0_MASK                 1U
#define PWME_PWME1_MASK                 2U
#define PWME_PWME2_MASK                 4U
#define PWME_PWME3_MASK                 8U
#define PWME_PWME4_MASK                 16U
#define PWME_PWME5_MASK                 32U
#define PWME_PWME_MASK                  63U
#define PWME_PWME_BITNUM                0U


/*** PWMPOL - PWM Polarity Register; 0x000000A1 ***/
typedef union {
  byte Byte;
  struct {
    byte PPOL0       :1;                                       /* Pulse Width Channel 0 Polarity */
    byte PPOL1       :1;                                       /* Pulse Width Channel 1 Polarity */
    byte PPOL2       :1;                                       /* Pulse Width Channel 2 Polarity */
    byte PPOL3       :1;                                       /* Pulse Width Channel 3 Polarity */
    byte PPOL4       :1;                                       /* Pulse Width Channel 4 Polarity */
    byte PPOL5       :1;                                       /* Pulse Width Channel 5 Polarity */
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpPPOL :6;
    byte         :1;
    byte         :1;
  } MergedBits;
} PWMPOLSTR;
extern volatile PWMPOLSTR _PWMPOL @(REG_BASE + 0x000000A1UL);
#define PWMPOL                          _PWMPOL.Byte
#define PWMPOL_PPOL0                    _PWMPOL.Bits.PPOL0
#define PWMPOL_PPOL1                    _PWMPOL.Bits.PPOL1
#define PWMPOL_PPOL2                    _PWMPOL.Bits.PPOL2
#define PWMPOL_PPOL3                    _PWMPOL.Bits.PPOL3
#define PWMPOL_PPOL4                    _PWMPOL.Bits.PPOL4
#define PWMPOL_PPOL5                    _PWMPOL.Bits.PPOL5
#define PWMPOL_PPOL                     _PWMPOL.MergedBits.grpPPOL

#define PWMPOL_PPOL0_MASK               1U
#define PWMPOL_PPOL1_MASK               2U
#define PWMPOL_PPOL2_MASK               4U
#define PWMPOL_PPOL3_MASK               8U
#define PWMPOL_PPOL4_MASK               16U
#define PWMPOL_PPOL5_MASK               32U
#define PWMPOL_PPOL_MASK                63U
#define PWMPOL_PPOL_BITNUM              0U


/*** PWMCLK - PWM Clock Select Register; 0x000000A2 ***/
typedef union {
  byte Byte;
  struct {
    byte PCLK0       :1;                                       /* Pulse Width Channel 0 Clock Select */
    byte PCLK1       :1;                                       /* Pulse Width Channel 1 Clock Select */
    byte PCLK2       :1;                                       /* Pulse Width Channel 2 Clock Select */
    byte PCLK3       :1;                                       /* Pulse Width Channel 3 Clock Select */
    byte PCLK4       :1;                                       /* Pulse Width Channel 4 Clock Select */
    byte PCLK5       :1;                                       /* Pulse Width Channel 5 Clock Select */
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpPCLK :6;
    byte         :1;
    byte         :1;
  } MergedBits;
} PWMCLKSTR;
extern volatile PWMCLKSTR _PWMCLK @(REG_BASE + 0x000000A2UL);
#define PWMCLK                          _PWMCLK.Byte
#define PWMCLK_PCLK0                    _PWMCLK.Bits.PCLK0
#define PWMCLK_PCLK1                    _PWMCLK.Bits.PCLK1
#define PWMCLK_PCLK2                    _PWMCLK.Bits.PCLK2
#define PWMCLK_PCLK3                    _PWMCLK.Bits.PCLK3
#define PWMCLK_PCLK4                    _PWMCLK.Bits.PCLK4
#define PWMCLK_PCLK5                    _PWMCLK.Bits.PCLK5
#define PWMCLK_PCLK                     _PWMCLK.MergedBits.grpPCLK

#define PWMCLK_PCLK0_MASK               1U
#define PWMCLK_PCLK1_MASK               2U
#define PWMCLK_PCLK2_MASK               4U
#define PWMCLK_PCLK3_MASK               8U
#define PWMCLK_PCLK4_MASK               16U
#define PWMCLK_PCLK5_MASK               32U
#define PWMCLK_PCLK_MASK                63U
#define PWMCLK_PCLK_BITNUM              0U


/*** PWMPRCLK - PWM Prescale Clock Select Register; 0x000000A3 ***/
typedef union {
  byte Byte;
  struct {
    byte PCKA0       :1;                                       /* Prescaler Select for Clock A 0 */
    byte PCKA1       :1;                                       /* Prescaler Select for Clock A 1 */
    byte PCKA2       :1;                                       /* Prescaler Select for Clock A 2 */
    byte             :1; 
    byte PCKB0       :1;                                       /* Prescaler Select for Clock B 0 */
    byte PCKB1       :1;                                       /* Prescaler Select for Clock B 1 */
    byte PCKB2       :1;                                       /* Prescaler Select for Clock B 2 */
    byte             :1; 
  } Bits;
  struct {
    byte grpPCKA :3;
    byte         :1;
    byte grpPCKB :3;
    byte         :1;
  } MergedBits;
} PWMPRCLKSTR;
extern volatile PWMPRCLKSTR _PWMPRCLK @(REG_BASE + 0x000000A3UL);
#define PWMPRCLK                        _PWMPRCLK.Byte
#define PWMPRCLK_PCKA0                  _PWMPRCLK.Bits.PCKA0
#define PWMPRCLK_PCKA1                  _PWMPRCLK.Bits.PCKA1
#define PWMPRCLK_PCKA2                  _PWMPRCLK.Bits.PCKA2
#define PWMPRCLK_PCKB0                  _PWMPRCLK.Bits.PCKB0
#define PWMPRCLK_PCKB1                  _PWMPRCLK.Bits.PCKB1
#define PWMPRCLK_PCKB2                  _PWMPRCLK.Bits.PCKB2
#define PWMPRCLK_PCKA                   _PWMPRCLK.MergedBits.grpPCKA
#define PWMPRCLK_PCKB                   _PWMPRCLK.MergedBits.grpPCKB

#define PWMPRCLK_PCKA0_MASK             1U
#define PWMPRCLK_PCKA1_MASK             2U
#define PWMPRCLK_PCKA2_MASK             4U
#define PWMPRCLK_PCKB0_MASK             16U
#define PWMPRCLK_PCKB1_MASK             32U
#define PWMPRCLK_PCKB2_MASK             64U
#define PWMPRCLK_PCKA_MASK              7U
#define PWMPRCLK_PCKA_BITNUM            0U
#define PWMPRCLK_PCKB_MASK              112U
#define PWMPRCLK_PCKB_BITNUM            4U


/*** PWMCAE - PWM Center Align Enable Register; 0x000000A4 ***/
typedef union {
  byte Byte;
  struct {
    byte CAE0        :1;                                       /* Center Aligned Output Mode on channel 0 */
    byte CAE1        :1;                                       /* Center Aligned Output Mode on channel 1 */
    byte CAE2        :1;                                       /* Center Aligned Output Mode on channel 2 */
    byte CAE3        :1;                                       /* Center Aligned Output Mode on channel 3 */
    byte CAE4        :1;                                       /* Center Aligned Output Mode on channel 4 */
    byte CAE5        :1;                                       /* Center Aligned Output Mode on channel 5 */
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpCAE  :6;
    byte         :1;
    byte         :1;
  } MergedBits;
} PWMCAESTR;
extern volatile PWMCAESTR _PWMCAE @(REG_BASE + 0x000000A4UL);
#define PWMCAE                          _PWMCAE.Byte
#define PWMCAE_CAE0                     _PWMCAE.Bits.CAE0
#define PWMCAE_CAE1                     _PWMCAE.Bits.CAE1
#define PWMCAE_CAE2                     _PWMCAE.Bits.CAE2
#define PWMCAE_CAE3                     _PWMCAE.Bits.CAE3
#define PWMCAE_CAE4                     _PWMCAE.Bits.CAE4
#define PWMCAE_CAE5                     _PWMCAE.Bits.CAE5
#define PWMCAE_CAE                      _PWMCAE.MergedBits.grpCAE

#define PWMCAE_CAE0_MASK                1U
#define PWMCAE_CAE1_MASK                2U
#define PWMCAE_CAE2_MASK                4U
#define PWMCAE_CAE3_MASK                8U
#define PWMCAE_CAE4_MASK                16U
#define PWMCAE_CAE5_MASK                32U
#define PWMCAE_CAE_MASK                 63U
#define PWMCAE_CAE_BITNUM               0U


/*** PWMCTL - PWM Control Register; 0x000000A5 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte PFRZ        :1;                                       /* PWM Counters Stop in Freeze Mode */
    byte PSWAI       :1;                                       /* PWM Stops in Wait Mode */
    byte CON01       :1;                                       /* Concatenate channels 0 and 1 */
    byte CON23       :1;                                       /* Concatenate channels 2 and 3 */
    byte CON45       :1;                                       /* Concatenate channels 4 and 5 */
    byte             :1; 
  } Bits;
} PWMCTLSTR;
extern volatile PWMCTLSTR _PWMCTL @(REG_BASE + 0x000000A5UL);
#define PWMCTL                          _PWMCTL.Byte
#define PWMCTL_PFRZ                     _PWMCTL.Bits.PFRZ
#define PWMCTL_PSWAI                    _PWMCTL.Bits.PSWAI
#define PWMCTL_CON01                    _PWMCTL.Bits.CON01
#define PWMCTL_CON23                    _PWMCTL.Bits.CON23
#define PWMCTL_CON45                    _PWMCTL.Bits.CON45

#define PWMCTL_PFRZ_MASK                4U
#define PWMCTL_PSWAI_MASK               8U
#define PWMCTL_CON01_MASK               16U
#define PWMCTL_CON23_MASK               32U
#define PWMCTL_CON45_MASK               64U


/*** PWMSCLA - PWM Scale A Register; 0x000000A8 ***/
typedef union {
  byte Byte;
  struct {
    byte BIT0        :1;                                       /* PWM Scale A Bit 0 */
    byte BIT1        :1;                                       /* PWM Scale A Bit 1 */
    byte BIT2        :1;                                       /* PWM Scale A Bit 2 */
    byte BIT3        :1;                                       /* PWM Scale A Bit 3 */
    byte BIT4        :1;                                       /* PWM Scale A Bit 4 */
    byte BIT5        :1;                                       /* PWM Scale A Bit 5 */
    byte BIT6        :1;                                       /* PWM Scale A Bit 6 */
    byte BIT7        :1;                                       /* PWM Scale A Bit 7 */
  } Bits;
} PWMSCLASTR;
extern volatile PWMSCLASTR _PWMSCLA @(REG_BASE + 0x000000A8UL);
#define PWMSCLA                         _PWMSCLA.Byte
#define PWMSCLA_BIT0                    _PWMSCLA.Bits.BIT0
#define PWMSCLA_BIT1                    _PWMSCLA.Bits.BIT1
#define PWMSCLA_BIT2                    _PWMSCLA.Bits.BIT2
#define PWMSCLA_BIT3                    _PWMSCLA.Bits.BIT3
#define PWMSCLA_BIT4                    _PWMSCLA.Bits.BIT4
#define PWMSCLA_BIT5                    _PWMSCLA.Bits.BIT5
#define PWMSCLA_BIT6                    _PWMSCLA.Bits.BIT6
#define PWMSCLA_BIT7                    _PWMSCLA.Bits.BIT7

#define PWMSCLA_BIT0_MASK               1U
#define PWMSCLA_BIT1_MASK               2U
#define PWMSCLA_BIT2_MASK               4U
#define PWMSCLA_BIT3_MASK               8U
#define PWMSCLA_BIT4_MASK               16U
#define PWMSCLA_BIT5_MASK               32U
#define PWMSCLA_BIT6_MASK               64U
#define PWMSCLA_BIT7_MASK               128U


/*** PWMSCLB - PWM Scale B Register; 0x000000A9 ***/
typedef union {
  byte Byte;
  struct {
    byte BIT0        :1;                                       /* PWM Scale B Bit 0 */
    byte BIT1        :1;                                       /* PWM Scale B Bit 1 */
    byte BIT2        :1;                                       /* PWM Scale B Bit 2 */
    byte BIT3        :1;                                       /* PWM Scale B Bit 3 */
    byte BIT4        :1;                                       /* PWM Scale B Bit 4 */
    byte BIT5        :1;                                       /* PWM Scale B Bit 5 */
    byte BIT6        :1;                                       /* PWM Scale B Bit 6 */
    byte BIT7        :1;                                       /* PWM Scale B Bit 7 */
  } Bits;
} PWMSCLBSTR;
extern volatile PWMSCLBSTR _PWMSCLB @(REG_BASE + 0x000000A9UL);
#define PWMSCLB                         _PWMSCLB.Byte
#define PWMSCLB_BIT0                    _PWMSCLB.Bits.BIT0
#define PWMSCLB_BIT1                    _PWMSCLB.Bits.BIT1
#define PWMSCLB_BIT2                    _PWMSCLB.Bits.BIT2
#define PWMSCLB_BIT3                    _PWMSCLB.Bits.BIT3
#define PWMSCLB_BIT4                    _PWMSCLB.Bits.BIT4
#define PWMSCLB_BIT5                    _PWMSCLB.Bits.BIT5
#define PWMSCLB_BIT6                    _PWMSCLB.Bits.BIT6
#define PWMSCLB_BIT7                    _PWMSCLB.Bits.BIT7

#define PWMSCLB_BIT0_MASK               1U
#define PWMSCLB_BIT1_MASK               2U
#define PWMSCLB_BIT2_MASK               4U
#define PWMSCLB_BIT3_MASK               8U
#define PWMSCLB_BIT4_MASK               16U
#define PWMSCLB_BIT5_MASK               32U
#define PWMSCLB_BIT6_MASK               64U
#define PWMSCLB_BIT7_MASK               128U


/*** PWMCNT01 - PWM Channel Counter 01 Register; 0x000000AC ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** PWMCNT0 - PWM Channel Counter 0 Register; 0x000000AC ***/
    union {
      byte Byte;
    } PWMCNT0STR;
    #define PWMCNT0                     _PWMCNT01.Overlap_STR.PWMCNT0STR.Byte
    /* PWMCNT_ARR: Access 6 PWMCNTx registers in an array */
    #define PWMCNT_ARR                  ((volatile byte *) &PWMCNT0)
    

    /*** PWMCNT1 - PWM Channel Counter 1 Register; 0x000000AD ***/
    union {
      byte Byte;
    } PWMCNT1STR;
    #define PWMCNT1                     _PWMCNT01.Overlap_STR.PWMCNT1STR.Byte
    
  } Overlap_STR;

} PWMCNT01STR;
extern volatile PWMCNT01STR _PWMCNT01 @(REG_BASE + 0x000000ACUL);
#define PWMCNT01                        _PWMCNT01.Word


/*** PWMCNT23 - PWM Channel Counter 23 Register; 0x000000AE ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** PWMCNT2 - PWM Channel Counter 2 Register; 0x000000AE ***/
    union {
      byte Byte;
    } PWMCNT2STR;
    #define PWMCNT2                     _PWMCNT23.Overlap_STR.PWMCNT2STR.Byte
    

    /*** PWMCNT3 - PWM Channel Counter 3 Register; 0x000000AF ***/
    union {
      byte Byte;
    } PWMCNT3STR;
    #define PWMCNT3                     _PWMCNT23.Overlap_STR.PWMCNT3STR.Byte
    
  } Overlap_STR;

} PWMCNT23STR;
extern volatile PWMCNT23STR _PWMCNT23 @(REG_BASE + 0x000000AEUL);
#define PWMCNT23                        _PWMCNT23.Word


/*** PWMCNT45 - PWM Channel Counter 45 Register; 0x000000B0 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** PWMCNT4 - PWM Channel Counter 4 Register; 0x000000B0 ***/
    union {
      byte Byte;
    } PWMCNT4STR;
    #define PWMCNT4                     _PWMCNT45.Overlap_STR.PWMCNT4STR.Byte
    

    /*** PWMCNT5 - PWM Channel Counter 5 Register; 0x000000B1 ***/
    union {
      byte Byte;
    } PWMCNT5STR;
    #define PWMCNT5                     _PWMCNT45.Overlap_STR.PWMCNT5STR.Byte
    
  } Overlap_STR;

} PWMCNT45STR;
extern volatile PWMCNT45STR _PWMCNT45 @(REG_BASE + 0x000000B0UL);
#define PWMCNT45                        _PWMCNT45.Word

/*** PWMCNT67 - PWM Channel Counter 67 Register; 0x000000B2 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** PWMCNT6 - PWM Channel Counter 6 Register; 0x000000B2 ***/
    union {
      byte Byte;
    } PWMCNT6STR;
    #define PWMCNT6                     _PWMCNT67.Overlap_STR.PWMCNT6STR.Byte 

    /*** PWMCNT7 - PWM Channel Counter 7 Register; 0x000000B3 ***/
    union {
      byte Byte;
    } PWMCNT7STR;
    #define PWMCNT7                     _PWMCNT67.Overlap_STR.PWMCNT7STR.Byte
    
  } Overlap_STR;

} PWMCNT67STR;
extern volatile PWMCNT67STR _PWMCNT67 @(REG_BASE + 0x000000B2UL);
#define PWMCNT67                        _PWMCNT67.Word

/*** PWMPER01 - PWM Channel Period 01 Register; 0x000000B4 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** PWMPER0 - PWM Channel Period 0 Register; 0x000000B4 ***/
    union {
      byte Byte;
    } PWMPER0STR;
    #define PWMPER0                     _PWMPER01.Overlap_STR.PWMPER0STR.Byte
    /* PWMPER_ARR: Access 6 PWMPERx registers in an array */
    #define PWMPER_ARR                  ((volatile byte *) &PWMPER0)
    

    /*** PWMPER1 - PWM Channel Period 1 Register; 0x000000B5 ***/
    union {
      byte Byte;
    } PWMPER1STR;
    #define PWMPER1                     _PWMPER01.Overlap_STR.PWMPER1STR.Byte
    
  } Overlap_STR;

} PWMPER01STR;
extern volatile PWMPER01STR _PWMPER01 @(REG_BASE + 0x000000B4UL);
#define PWMPER01                        _PWMPER01.Word


/*** PWMPER23 - PWM Channel Period 23 Register; 0x000000B6 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** PWMPER2 - PWM Channel Period 2 Register; 0x000000B6 ***/
    union {
      byte Byte;
    } PWMPER2STR;
    #define PWMPER2                     _PWMPER23.Overlap_STR.PWMPER2STR.Byte
    

    /*** PWMPER3 - PWM Channel Period 3 Register; 0x000000B7 ***/
    union {
      byte Byte;
    } PWMPER3STR;
    #define PWMPER3                     _PWMPER23.Overlap_STR.PWMPER3STR.Byte
    
  } Overlap_STR;

} PWMPER23STR;
extern volatile PWMPER23STR _PWMPER23 @(REG_BASE + 0x000000B6UL);
#define PWMPER23                        _PWMPER23.Word


/*** PWMPER45 - PWM Channel Period 45 Register; 0x000000B8 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** PWMPER4 - PWM Channel Period 4 Register; 0x000000B8 ***/
    union {
      byte Byte;
    } PWMPER4STR;
    #define PWMPER4                     _PWMPER45.Overlap_STR.PWMPER4STR.Byte
    

    /*** PWMPER5 - PWM Channel Period 5 Register; 0x000000B9 ***/
    union {
      byte Byte;
    } PWMPER5STR;
    #define PWMPER5                     _PWMPER45.Overlap_STR.PWMPER5STR.Byte
    
  } Overlap_STR;

} PWMPER45STR;
extern volatile PWMPER45STR _PWMPER45 @(REG_BASE + 0x000000B8UL);
#define PWMPER45                        _PWMPER45.Word

/*** PWMPER67 - PWM Channel Period 67 Register; 0x000000BA ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** PWMPER6 - PWM Channel Period 6 Register; 0x000000B8 ***/
    union {
      byte Byte;
    } PWMPER6STR;
    #define PWMPER6                     _PWMPER67.Overlap_STR.PWMPER6STR.Byte
    

    /*** PWMPER7 - PWM Channel Period 7 Register; 0x000000BA ***/
    union {
      byte Byte;
    } PWMPER7STR;
    #define PWMPER7                     _PWMPER67.Overlap_STR.PWMPER7STR.Byte
    
  } Overlap_STR;

} PWMPER67STR;
extern volatile PWMPER67STR _PWMPER67 @(REG_BASE + 0x000000BAUL);
#define PWMPER67                        _PWMPER67.Word

/*** PWMDTY01 - PWM Channel Duty 01 Register; 0x000000BC ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** PWMDTY0 - PWM Channel Duty 0 Register; 0x000000BC ***/
    union {
      byte Byte;
    } PWMDTY0STR;
    #define PWMDTY0                     _PWMDTY01.Overlap_STR.PWMDTY0STR.Byte
    /* PWMDTY_ARR: Access 6 PWMDTYx registers in an array */
    #define PWMDTY_ARR                  ((volatile byte *) &PWMDTY0)
    

    /*** PWMDTY1 - PWM Channel Duty 1 Register; 0x000000BD ***/
    union {
      byte Byte;
    } PWMDTY1STR;
    #define PWMDTY1                     _PWMDTY01.Overlap_STR.PWMDTY1STR.Byte
    
  } Overlap_STR;

} PWMDTY01STR;
extern volatile PWMDTY01STR _PWMDTY01 @(REG_BASE + 0x000000BCUL);
#define PWMDTY01                        _PWMDTY01.Word


/*** PWMDTY23 - PWM Channel Duty 23 Register; 0x000000BE ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** PWMDTY2 - PWM Channel Duty 2 Register; 0x000000BE ***/
    union {
      byte Byte;
    } PWMDTY2STR;
    #define PWMDTY2                     _PWMDTY23.Overlap_STR.PWMDTY2STR.Byte
    

    /*** PWMDTY3 - PWM Channel Duty 3 Register; 0x000000BF ***/
    union {
      byte Byte;
    } PWMDTY3STR;
    #define PWMDTY3                     _PWMDTY23.Overlap_STR.PWMDTY3STR.Byte
    
  } Overlap_STR;

} PWMDTY23STR;
extern volatile PWMDTY23STR _PWMDTY23 @(REG_BASE + 0x000000BEUL);
#define PWMDTY23                        _PWMDTY23.Word


/*** PWMDTY45 - PWM Channel Duty 45 Register; 0x000000C0 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** PWMDTY4 - PWM Channel Duty 4 Register; 0x000000C0 ***/
    union {
      byte Byte;
    } PWMDTY4STR;
    #define PWMDTY4                     _PWMDTY45.Overlap_STR.PWMDTY4STR.Byte
    

    /*** PWMDTY5 - PWM Channel Duty 5 Register; 0x000000C1 ***/
    union {
      byte Byte;
    } PWMDTY5STR;
    #define PWMDTY5                     _PWMDTY45.Overlap_STR.PWMDTY5STR.Byte
    
  } Overlap_STR;

} PWMDTY45STR;
extern volatile PWMDTY45STR _PWMDTY45 @(REG_BASE + 0x000000C0UL);
#define PWMDTY45                        _PWMDTY45.Word

/*** PWMDTY67 - PWM Channel Duty 67 Register; 0x000000C2 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** PWMDTY6 - PWM Channel Duty 6 Register; 0x000000C2 ***/
    union {
      byte Byte;
    } PWMDTY6STR;
    #define PWMDTY6                     _PWMDTY67.Overlap_STR.PWMDTY6STR.Byte
    

    /*** PWMDTY7 - PWM Channel Duty 7 Register; 0x000000C3 ***/
    union {
      byte Byte;
    } PWMDTY7STR;
    #define PWMDTY7                     _PWMDTY67.Overlap_STR.PWMDTY7STR.Byte
    
  } Overlap_STR;

} PWMDTY67STR;
extern volatile PWMDTY67STR _PWMDTY67 @(REG_BASE + 0x000000C2UL);
#define PWMDTY67                        _PWMDTY67.Word


/*** PWMSDN - PWM Shutdown Register; 0x000000C4 ***/
typedef union {
  byte Byte;
  struct {
    byte PWM5ENA     :1;                                       /* PWM emergency shutdown Enable */
    byte PWM5INL     :1;                                       /* PWM shutdown active input level for ch. 5 */
    byte PWM5IN      :1;                                       /* PWM channel 5 input status */
    byte             :1; 
    byte PWMLVL      :1;                                       /* PWM shutdown output Level */
    byte PWMRSTRT    :1;                                       /* PWM Restart */
    byte PWMIE       :1;                                       /* PWM Interrupt Enable */
    byte PWMIF       :1;                                       /* PWM Interrupt Flag */
  } Bits;
} PWMSDNSTR;
extern volatile PWMSDNSTR _PWMSDN @(REG_BASE + 0x000000C4UL);
#define PWMSDN                          _PWMSDN.Byte
#define PWMSDN_PWM5ENA                  _PWMSDN.Bits.PWM5ENA
#define PWMSDN_PWM5INL                  _PWMSDN.Bits.PWM5INL
#define PWMSDN_PWM5IN                   _PWMSDN.Bits.PWM5IN
#define PWMSDN_PWMLVL                   _PWMSDN.Bits.PWMLVL
#define PWMSDN_PWMRSTRT                 _PWMSDN.Bits.PWMRSTRT
#define PWMSDN_PWMIE                    _PWMSDN.Bits.PWMIE
#define PWMSDN_PWMIF                    _PWMSDN.Bits.PWMIF

#define PWMSDN_PWM5ENA_MASK             1U
#define PWMSDN_PWM5INL_MASK             2U
#define PWMSDN_PWM5IN_MASK              4U
#define PWMSDN_PWMLVL_MASK              16U
#define PWMSDN_PWMRSTRT_MASK            32U
#define PWMSDN_PWMIE_MASK               64U
#define PWMSDN_PWMIF_MASK               128U

/*** sPTT - Port T I/O Register; 0x000000E0 ***/
typedef union {
  byte Byte;
  struct {
    byte sPTT0        :1;                                       /* Port T Bit 0 */
    byte sPTT1        :1;                                       /* Port T Bit 1 */
    byte sPTT2        :1;                                       /* Port T Bit 2 */
    byte sPTT3        :1;                                       /* Port T Bit 3 */
    byte sPTT4        :1;                                       /* Port T Bit 4 */
    byte sPTT5        :1;                                       /* Port T Bit 5 */
    byte sPTT6        :1;                                       /* Port T Bit 6 */
    byte sPTT7        :1;                                       /* Port T Bit 7 */
  } Bits;
  struct {
    byte grpsPTT  :8;
  } MergedBits;
} sPTTSTR;
extern volatile sPTTSTR _sPTT @(REG_BASE + 0x000000E0);
#define sPTT _sPTT.Byte
#define sPTT_sPTT0 _sPTT.Bits.sPTT0
#define sPTT_sPTT1 _sPTT.Bits.sPTT1
#define sPTT_sPTT2 _sPTT.Bits.sPTT2
#define sPTT_sPTT3 _sPTT.Bits.sPTT3
#define sPTT_sPTT4 _sPTT.Bits.sPTT4
#define sPTT_sPTT5 _sPTT.Bits.sPTT5
#define sPTT_sPTT6 _sPTT.Bits.sPTT6
#define sPTT_sPTT7 _sPTT.Bits.sPTT7
#define sPTT_sPTT _sPTT.MergedBits.grpsPTT


/*** sPTIT - Port T Input; 0x000000E1 ***/
typedef union {
  byte Byte;
  struct {
    byte sPTIT0       :1;                                       /* Port T Bit 0 */
    byte sPTIT1       :1;                                       /* Port T Bit 1 */
    byte sPTIT2       :1;                                       /* Port T Bit 2 */
    byte sPTIT3       :1;                                       /* Port T Bit 3 */
    byte sPTIT4       :1;                                       /* Port T Bit 4 */
    byte sPTIT5       :1;                                       /* Port T Bit 5 */
    byte sPTIT6       :1;                                       /* Port T Bit 6 */
    byte sPTIT7       :1;                                       /* Port T Bit 7 */
  } Bits;
  struct {
    byte grpsPTIT :8;
  } MergedBits;
} sPTITSTR;
extern volatile sPTITSTR _sPTIT @(REG_BASE + 0x000000E1);
#define sPTIT _sPTIT.Byte
#define sPTIT_sPTIT0 _sPTIT.Bits.sPTIT0
#define sPTIT_sPTIT1 _sPTIT.Bits.sPTIT1
#define sPTIT_sPTIT2 _sPTIT.Bits.sPTIT2
#define sPTIT_sPTIT3 _sPTIT.Bits.sPTIT3
#define sPTIT_sPTIT4 _sPTIT.Bits.sPTIT4
#define sPTIT_sPTIT5 _sPTIT.Bits.sPTIT5
#define sPTIT_sPTIT6 _sPTIT.Bits.sPTIT6
#define sPTIT_sPTIT7 _sPTIT.Bits.sPTIT7
#define sPTIT_sPTIT _sPTIT.MergedBits.grpsPTIT


/*** sDDRT - Port T Data Direction Register; 0x000000E2 ***/
typedef union {
  byte Byte;
  struct {
    byte sDDRT0       :1;                                       /* Data Direction Port T Bit 0 */
    byte sDDRT1       :1;                                       /* Data Direction Port T Bit 1 */
    byte sDDRT2       :1;                                       /* Data Direction Port T Bit 2 */
    byte sDDRT3       :1;                                       /* Data Direction Port T Bit 3 */
    byte sDDRT4       :1;                                       /* Data Direction Port T Bit 4 */
    byte sDDRT5       :1;                                       /* Data Direction Port T Bit 5 */
    byte sDDRT6       :1;                                       /* Data Direction Port T Bit 6 */
    byte sDDRT7       :1;                                       /* Data Direction Port T Bit 7 */
  } Bits;
  struct {
    byte grpsDDRT :8;
  } MergedBits;
} sDDRTSTR;
extern volatile sDDRTSTR _sDDRT @(REG_BASE + 0x000000E2);
#define sDDRT _sDDRT.Byte
#define sDDRT_sDDRT0 _sDDRT.Bits.sDDRT0
#define sDDRT_sDDRT1 _sDDRT.Bits.sDDRT1
#define sDDRT_sDDRT2 _sDDRT.Bits.sDDRT2
#define sDDRT_sDDRT3 _sDDRT.Bits.sDDRT3
#define sDDRT_sDDRT4 _sDDRT.Bits.sDDRT4
#define sDDRT_sDDRT5 _sDDRT.Bits.sDDRT5
#define sDDRT_sDDRT6 _sDDRT.Bits.sDDRT6
#define sDDRT_sDDRT7 _sDDRT.Bits.sDDRT7
#define sDDRT_sDDRT _sDDRT.MergedBits.grpsDDRT


/*** sRDRT - Port T Reduced Drive Register; 0x000000E3 ***/
typedef union {
  byte Byte;
  struct {
    byte sRDRT0       :1;                                       /* Reduced Drive Port T Bit 0 */
    byte sRDRT1       :1;                                       /* Reduced Drive Port T Bit 1 */
    byte sRDRT2       :1;                                       /* Reduced Drive Port T Bit 2 */
    byte sRDRT3       :1;                                       /* Reduced Drive Port T Bit 3 */
    byte sRDRT4       :1;                                       /* Reduced Drive Port T Bit 4 */
    byte sRDRT5       :1;                                       /* Reduced Drive Port T Bit 5 */
    byte sRDRT6       :1;                                       /* Reduced Drive Port T Bit 6 */
    byte sRDRT7       :1;                                       /* Reduced Drive Port T Bit 7 */
  } Bits;
  struct {
    byte grpsRDRT :8;
  } MergedBits;
} sRDRTSTR;
extern volatile sRDRTSTR _sRDRT @(REG_BASE + 0x000000E3);
#define sRDRT _sRDRT.Byte
#define sRDRT_sRDRT0 _sRDRT.Bits.sRDRT0
#define sRDRT_sRDRT1 _sRDRT.Bits.sRDRT1
#define sRDRT_sRDRT2 _sRDRT.Bits.sRDRT2
#define sRDRT_sRDRT3 _sRDRT.Bits.sRDRT3
#define sRDRT_sRDRT4 _sRDRT.Bits.sRDRT4
#define sRDRT_sRDRT5 _sRDRT.Bits.sRDRT5
#define sRDRT_sRDRT6 _sRDRT.Bits.sRDRT6
#define sRDRT_sRDRT7 _sRDRT.Bits.sRDRT7
#define sRDRT_sRDRT _sRDRT.MergedBits.grpsRDRT


/*** sPERT - Port T Pull Device Enable Register; 0x000000E4 ***/
typedef union {
  byte Byte;
  struct {
    byte sPERT0       :1;                                       /* Pull Device Enable Port T Bit 0 */
    byte sPERT1       :1;                                       /* Pull Device Enable Port T Bit 1 */
    byte sPERT2       :1;                                       /* Pull Device Enable Port T Bit 2 */
    byte sPERT3       :1;                                       /* Pull Device Enable Port T Bit 3 */
    byte sPERT4       :1;                                       /* Pull Device Enable Port T Bit 4 */
    byte sPERT5       :1;                                       /* Pull Device Enable Port T Bit 5 */
    byte sPERT6       :1;                                       /* Pull Device Enable Port T Bit 6 */
    byte sPERT7       :1;                                       /* Pull Device Enable Port T Bit 7 */
  } Bits;
  struct {
    byte grpsPERT :8;
  } MergedBits;
} sPERTSTR;
extern volatile sPERTSTR _sPERT @(REG_BASE + 0x000000E4);
#define sPERT _sPERT.Byte
#define sPERT_sPERT0 _sPERT.Bits.sPERT0
#define sPERT_sPERT1 _sPERT.Bits.sPERT1
#define sPERT_sPERT2 _sPERT.Bits.sPERT2
#define sPERT_sPERT3 _sPERT.Bits.sPERT3
#define sPERT_sPERT4 _sPERT.Bits.sPERT4
#define sPERT_sPERT5 _sPERT.Bits.sPERT5
#define sPERT_sPERT6 _sPERT.Bits.sPERT6
#define sPERT_sPERT7 _sPERT.Bits.sPERT7
#define sPERT_sPERT _sPERT.MergedBits.grpsPERT


/*** sPPST - Port T Polarity Select Register; 0x000000E5 ***/
typedef union {
  byte Byte;
  struct {
    byte sPPST0       :1;                                       /* Pull Select Port T Bit 0 */
    byte sPPST1       :1;                                       /* Pull Select Port T Bit 1 */
    byte sPPST2       :1;                                       /* Pull Select Port T Bit 2 */
    byte sPPST3       :1;                                       /* Pull Select Port T Bit 3 */
    byte sPPST4       :1;                                       /* Pull Select Port T Bit 4 */
    byte sPPST5       :1;                                       /* Pull Select Port T Bit 5 */
    byte sPPST6       :1;                                       /* Pull Select Port T Bit 6 */
    byte sPPST7       :1;                                       /* Pull Select Port T Bit 7 */
  } Bits;
  struct {
    byte grpsPPST :8;
  } MergedBits;
} sPPSTSTR;
extern volatile sPPSTSTR _sPPST @(REG_BASE + 0x000000E5);
#define sPPST _sPPST.Byte
#define sPPST_sPPST0 _sPPST.Bits.sPPST0
#define sPPST_sPPST1 _sPPST.Bits.sPPST1
#define sPPST_sPPST2 _sPPST.Bits.sPPST2
#define sPPST_sPPST3 _sPPST.Bits.sPPST3
#define sPPST_sPPST4 _sPPST.Bits.sPPST4
#define sPPST_sPPST5 _sPPST.Bits.sPPST5
#define sPPST_sPPST6 _sPPST.Bits.sPPST6
#define sPPST_sPPST7 _sPPST.Bits.sPPST7
#define sPPST_sPPST _sPPST.MergedBits.grpsPPST

/*** sPTP - Port P I/O Register; 0x000000F0 ***/
typedef union {
  byte Byte;
  struct {
    byte sPTP0        :1;                                       /* Port P Bit 0 */
    byte sPTP1        :1;                                       /* Port P Bit 1 */
    byte sPTP2        :1;                                       /* Port P Bit 2 */
    byte sPTP3        :1;                                       /* Port P Bit 3 */
    byte sPTP4        :1;                                       /* Port P Bit 4 */
    byte sPTP5        :1;                                       /* Port P Bit 5 */
    byte sPTP6        :1;                                       /* Port P Bit 6 */
    byte sPTP7        :1;                                       /* Port P Bit 7 */
  } Bits;
  struct {
    byte grpsPTP  :8;
  } MergedBits;
} sPTPSTR;
extern volatile sPTPSTR _sPTP @(REG_BASE + 0x000000F0);
#define sPTP _sPTP.Byte
#define sPTP_PTP0 _sPTP.Bits.sPTP0
#define sPTP_PTP1 _sPTP.Bits.sPTP1
#define sPTP_PTP2 _sPTP.Bits.sPTP2
#define sPTP_PTP3 _sPTP.Bits.sPTP3
#define sPTP_PTP4 _sPTP.Bits.sPTP4
#define sPTP_PTP5 _sPTP.Bits.sPTP5
#define sPTP_PTP6 _sPTP.Bits.sPTP6
#define sPTP_PTP7 _sPTP.Bits.sPTP7
#define sPTP_PTP _sPTP.MergedBits.grpsPTP


/*** sPTIP - Port P Input; 0x000000F1 ***/
typedef union {
  byte Byte;
  struct {
    byte sPTIP0       :1;                                       /* Port P Bit 0 */
    byte sPTIP1       :1;                                       /* Port P Bit 1 */
    byte sPTIP2       :1;                                       /* Port P Bit 2 */
    byte sPTIP3       :1;                                       /* Port P Bit 3 */
    byte sPTIP4       :1;                                       /* Port P Bit 4 */
    byte sPTIP5       :1;                                       /* Port P Bit 5 */
    byte sPTIP6       :1;                                       /* Port P Bit 6 */
    byte sPTIP7       :1;                                       /* Port P Bit 7 */
  } Bits;
  struct {
    byte grpsPTIP :8;
  } MergedBits;
} sPTIPSTR;
extern volatile sPTIPSTR _sPTIP @(REG_BASE + 0x000000F1);
#define sPTIP _sPTIP.Byte
#define sPTIP_sPTIP0 _sPTIP.Bits.sPTIP0
#define sPTIP_sPTIP1 _sPTIP.Bits.sPTIP1
#define sPTIP_sPTIP2 _sPTIP.Bits.sPTIP2
#define sPTIP_sPTIP3 _sPTIP.Bits.sPTIP3
#define sPTIP_sPTIP4 _sPTIP.Bits.sPTIP4
#define sPTIP_sPTIP5 _sPTIP.Bits.sPTIP5
#define sPTIP_sPTIP6 _sPTIP.Bits.sPTIP6
#define sPTIP_sPTIP7 _sPTIP.Bits.sPTIP7
#define sPTIP_sPTIP _sPTIP.MergedBits.grpsPTIP


/*** sDDRP - Port P Data Direction Register; 0x000000F2 ***/
typedef union {
  byte Byte;
  struct {
    byte sDDRP0       :1;                                       /* Data Direction Port P Bit 0 */
    byte sDDRP1       :1;                                       /* Data Direction Port P Bit 1 */
    byte sDDRP2       :1;                                       /* Data Direction Port P Bit 2 */
    byte sDDRP3       :1;                                       /* Data Direction Port P Bit 3 */
    byte sDDRP4       :1;                                       /* Data Direction Port P Bit 4 */
    byte sDDRP5       :1;                                       /* Data Direction Port P Bit 5 */
    byte sDDRP6       :1;                                       /* Data Direction Port P Bit 6 */
    byte sDDRP7       :1;                                       /* Data Direction Port P Bit 7 */
  } Bits;
  struct {
    byte grpsDDRP :8;
  } MergedBits;
} sDDRPSTR;
extern volatile sDDRPSTR _sDDRP @(REG_BASE + 0x000000F2);
#define sDDRP _sDDRP.Byte
#define sDDRP_sDDRP0 _sDDRP.Bits.sDDRP0
#define sDDRP_sDDRP1 _sDDRP.Bits.sDDRP1
#define sDDRP_sDDRP2 _sDDRP.Bits.sDDRP2
#define sDDRP_sDDRP3 _sDDRP.Bits.sDDRP3
#define sDDRP_sDDRP4 _sDDRP.Bits.sDDRP4
#define sDDRP_sDDRP5 _sDDRP.Bits.sDDRP5
#define sDDRP_sDDRP6 _sDDRP.Bits.sDDRP6
#define sDDRP_sDDRP7 _sDDRP.Bits.sDDRP7
#define sDDRP_sDDRP _sDDRP.MergedBits.grpsDDRP


/*** sRDRP - Port P Reduced Drive Register; 0x000000F3 ***/
typedef union {
  byte Byte;
  struct {
    byte sRDRP0       :1;                                       /* Reduced Drive Port P Bit 0 */
    byte sRDRP1       :1;                                       /* Reduced Drive Port P Bit 1 */
    byte sRDRP2       :1;                                       /* Reduced Drive Port P Bit 2 */
    byte sRDRP3       :1;                                       /* Reduced Drive Port P Bit 3 */
    byte sRDRP4       :1;                                       /* Reduced Drive Port P Bit 4 */
    byte sRDRP5       :1;                                       /* Reduced Drive Port P Bit 5 */
    byte sRDRP6       :1;                                       /* Reduced Drive Port P Bit 6 */
    byte sRDRP7       :1;                                       /* Reduced Drive Port P Bit 7 */
  } Bits;
  struct {
    byte grpsRDRP :8;
  } MergedBits;
} sRDRPSTR;
extern volatile sRDRPSTR _sRDRP @(REG_BASE + 0x000000F3);
#define sRDRP _sRDRP.Byte
#define sRDRP_sRDRP0 _sRDRP.Bits.sRDRP0
#define sRDRP_sRDRP1 _sRDRP.Bits.sRDRP1
#define sRDRP_sRDRP2 _sRDRP.Bits.sRDRP2
#define sRDRP_sRDRP3 _sRDRP.Bits.sRDRP3
#define sRDRP_sRDRP4 _sRDRP.Bits.sRDRP4
#define sRDRP_sRDRP5 _sRDRP.Bits.sRDRP5
#define sRDRP_sRDRP6 _sRDRP.Bits.sRDRP6
#define sRDRP_sRDRP7 _sRDRP.Bits.sRDRP7
#define sRDRP_sRDRP _sRDRP.MergedBits.grpsRDRP


/*** sPERP - Port P Pull Device Enable Register; 0x000000F4 ***/
typedef union {
  byte Byte;
  struct {
    byte sPERP0       :1;                                       /* Pull Device Enable Port P Bit 0 */
    byte sPERP1       :1;                                       /* Pull Device Enable Port P Bit 1 */
    byte sPERP2       :1;                                       /* Pull Device Enable Port P Bit 2 */
    byte sPERP3       :1;                                       /* Pull Device Enable Port P Bit 3 */
    byte sPERP4       :1;                                       /* Pull Device Enable Port P Bit 4 */
    byte sPERP5       :1;                                       /* Pull Device Enable Port P Bit 5 */
    byte sPERP6       :1;                                       /* Pull Device Enable Port P Bit 6 */
    byte sPERP7       :1;                                       /* Pull Device Enable Port P Bit 7 */
  } Bits;
  struct {
    byte grpsPERP :8;
  } MergedBits;
} sPERPSTR;
extern volatile sPERPSTR _sPERP @(REG_BASE + 0x000000F4);
#define sPERP _sPERP.Byte
#define sPERP_sPERP0 _sPERP.Bits.sPERP0
#define sPERP_sPERP1 _sPERP.Bits.sPERP1
#define sPERP_sPERP2 _sPERP.Bits.sPERP2
#define sPERP_sPERP3 _sPERP.Bits.sPERP3
#define sPERP_sPERP4 _sPERP.Bits.sPERP4
#define sPERP_sPERP5 _sPERP.Bits.sPERP5
#define sPERP_sPERP6 _sPERP.Bits.sPERP6
#define sPERP_sPERP7 _sPERP.Bits.sPERP7
#define sPERP_sPERP _sPERP.MergedBits.grpsPERP


/*** sPPSP - Port P Polarity Select Register; 0x000000F5 ***/
typedef union {
  byte Byte;
  struct {
    byte sPPSP0       :1;                                       /* Pull Select Port P Bit 0 */
    byte sPPSP1       :1;                                       /* Pull Select Port P Bit 1 */
    byte sPPSP2       :1;                                       /* Pull Select Port P Bit 2 */
    byte sPPSP3       :1;                                       /* Pull Select Port P Bit 3 */
    byte sPPSP4       :1;                                       /* Pull Select Port P Bit 4 */
    byte sPPSP5       :1;                                       /* Pull Select Port P Bit 5 */
    byte sPPSP6       :1;                                       /* Pull Select Port P Bit 6 */
    byte sPPSP7       :1;                                       /* Pull Select Port P Bit 7 */
  } Bits;
  struct {
    byte grpsPPSP :8;
  } MergedBits;
} sPPSPSTR;
extern volatile sPPSPSTR _sPPSP @(REG_BASE + 0x000000F5);
#define sPPSP _sPPSP.Byte
#define sPPSP_sPPSP0 _sPPSP.Bits.sPPSP0
#define sPPSP_sPPSP1 _sPPSP.Bits.sPPSP1
#define sPPSP_sPPSP2 _sPPSP.Bits.sPPSP2
#define sPPSP_sPPSP3 _sPPSP.Bits.sPPSP3
#define sPPSP_sPPSP4 _sPPSP.Bits.sPPSP4
#define sPPSP_sPPSP5 _sPPSP.Bits.sPPSP5
#define sPPSP_sPPSP6 _sPPSP.Bits.sPPSP6
#define sPPSP_sPPSP7 _sPPSP.Bits.sPPSP7
#define sPPSP_sPPSP _sPPSP.MergedBits.grpsPPSP

#endif