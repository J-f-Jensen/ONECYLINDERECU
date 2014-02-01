#include "MC9S12T64.H"

volatile PWMESTR _PWME;                                    /* PWM Enable Register; 0x000000E0 */
volatile PWMCNT01STR _PWMCNT01;                            /* PWM Channel Counter 01 Register; 0x000000EC */
volatile PWMCNT23STR _PWMCNT23;                            /* PWM Channel Counter 23 Register; 0x000000EE */
volatile PWMCNT45STR _PWMCNT45;                            /* PWM Channel Counter 45 Register; 0x000000F0 */
volatile PWMPER01STR _PWMPER01;                            /* PWM Channel Period 01 Register; 0x000000F2 */
volatile PWMPER23STR _PWMPER23;                            /* PWM Channel Period 23 Register; 0x000000F4 */
volatile PWMPER45STR _PWMPER45;                            /* PWM Channel Period 45 Register; 0x000000F6 */
volatile PWMDTY01STR _PWMDTY01;                            /* PWM Channel Duty 01 Register; 0x000000F8 */
volatile PWMDTY23STR _PWMDTY23;                            /* PWM Channel Duty 23 Register; 0x000000FA */
volatile PWMDTY45STR _PWMDTY45;                            /* PWM Channel Duty 45 Register; 0x000000FC */

volatile TIOSSTR _TIOS;                                    /* Timer Input Capture/Output Compare Select; 0x00000040 */
volatile CFORCSTR _CFORC;                                  /* Timer Compare Force Register; 0x00000041 */
volatile TCTL1STR _TCTL1;                                  /* Timer Control Register 1; 0x00000048 */
volatile TCTL2STR _TCTL2;                                  /* Timer Control Register 2; 0x00000049 */
volatile TCTL3STR _TCTL3;                                  /* Timer Control Register 3; 0x0000004A */
volatile TCTL4STR _TCTL4;                                  /* Timer Control Register 4; 0x0000004B */
volatile TIESTR _TIE;                                      /* Timer Interrupt Enable Register; 0x0000004C */
volatile TSCR1STR _TSCR1;                                  /* Timer System Control Register 1; 0x000000 */
volatile TSCR2STR _TSCR2;                                  /* Timer System Control Register 2; 0x0000004D */
volatile TFLG1STR _TFLG1;                                  /* Main Timer Interrupt Flag 1; 0x0000004E */
volatile TFLG2STR _TFLG2;                                  /* Main Timer Interrupt Flag 2; 0x0000004F */
volatile PACTLSTR _PACTL;                                  /* 16-Bit Pulse Accumulator A Control Register; 0x00000060 */
//volatile PAFLGSTR _PAFLG;                                  /* Pulse Accumulator A Flag Register; 0x00000061 */
volatile TCNTSTR _TCNT;                                    /* Timer Count Register; 0x00000044 */
volatile TC0STR _TC0;                                      /* Timer Input Capture/Output Compare Register 0; 0x00000050 */
volatile TC1STR _TC1;                                      /* Timer Input Capture/Output Compare Register 1; 0x00000052 */
volatile TC2STR _TC2;                                      /* Timer Input Capture/Output Compare Register 2; 0x00000054 */
volatile TC3STR _TC3;                                      /* Timer Input Capture/Output Compare Register 3; 0x00000056 */
volatile TC4STR _TC4;                                      /* Timer Input Capture/Output Compare Register 4; 0x00000058 */
volatile TC5STR _TC5;                                      /* Timer Input Capture/Output Compare Register 5; 0x0000005A */
volatile TC6STR _TC6;                                      /* Timer Input Capture/Output Compare Register 6; 0x0000005C */
volatile TC7STR _TC7;                                      /* Timer Input Capture/Output Compare Register 7; 0x0000005E */


volatile sPTTSTR _sPTT;                                      /* Port T I/O Register; 0x000000E0 */
volatile sPTITSTR _sPTIT;                                    /* Port T Input Register; 0x000000E1 */
volatile sDDRTSTR _sDDRT;                                    /* Port T Data Direction Register; 0x000000E2 */
volatile sRDRTSTR _sRDRT;                                    /* Port T Reduced Drive Register; 0x000000E3 */
volatile sPERTSTR _sPERT;                                    /* Port T Pull Device Enable Register; 0x000000E4 */
volatile sPPSTSTR _sPPST;                                    /* Port T Polarity Select Register; 0x000000E5 */

volatile sPTPSTR _sPTP;                                      /* Port P I/O Register; 0x000000F0 */
volatile sPTIPSTR _sPTIP;                                    /* Port P Input Register; 0x000000F1 */
volatile sDDRPSTR _sDDRP;                                    /* Port P Data Direction Register; 0x000000F2 */
volatile sRDRPSTR _sRDRP;                                    /* Port P Reduced Drive Register; 0x000000F3 */
volatile sPERPSTR _sPERP;                                    /* Port P Pull Device Enable Register; 0x000000F4 */
volatile sPPSPSTR _sPPSP;                                    /* Port P Polarity Select Register; 0x000000F5 */


