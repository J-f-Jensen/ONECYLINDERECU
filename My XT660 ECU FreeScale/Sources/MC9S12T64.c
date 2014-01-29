#include "MC9S12T64.H"

volatile PWMESTR _PWME;                                    /* PWM Enable Register; 0x000000E0 */
volatile TIOSSTR _TIOS;                                    /* Timer Input Capture/Output Compare Select; 0x00000040 */

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

