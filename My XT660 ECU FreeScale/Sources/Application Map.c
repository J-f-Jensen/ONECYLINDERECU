/*******************************************************************************/
/**
Copyright (c) 2009 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Application Map.c
\brief      Application Map files
\author     Freescale Semiconductor
\author     Jesse Beeker
\version    0.2
\date       August/ 2009
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


/** Application definitions */
#include "Application Definitions.h" 

#include "typedefs.h"


/* Spark Map Parameters */

#ifdef Spark_Data_16_bit
UINT16 Spark_Timing_Map_RAM[SPARK_RPM_POINTS][SPARK_LOAD_POINTS];
const UINT16 Spark_Timing_Map[SPARK_RPM_POINTS][SPARK_LOAD_POINTS] = 
{
13,13,13,13,
13,13,13,13,
15,20,25,27,
15,25,27,27,
15,22,27,27,
16,25,27,27,
19,25,27,27,
21,30,27,27,
23,40,27,27,
24,42,27,27,
26,45,45,45,
25,48,47,47,
50,50,48,48,
50,50,49,49,
53,53,51,51,
53,53,51,51,
53,53,51,51,
53,53,52,51,
54,54,52,54,
54,54,53,54,
54,54,53,54,
54,54,54,54,
54,54,54,55,
55,55,55,55,
55,55,55,55,
55,55,55,55,
55,55,55,55,
55,55,55,55,
55,55,55,55,
55,55,55,55,
55,55,55,55
};


#else
UINT8 Spark_Timing_Map_RAM[SPARK_LOAD_POINTS][SPARK_RPM_POINTS];
const UINT8 Spark_Timing_Map[SPARK_LOAD_POINTS][SPARK_RPM_POINTS] = 
{
/* RPM ---------------------------------------->             */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00    /* LOAD  */
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00    /*   |   */
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00    /*   |   */
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00    /*   |   */
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00    /*   |   */
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00    /*   v   */ 

}; 


#endif


UINT16 Spark_Load_Map_Values[SPARK_LOAD_POINTS] = 
{  
151,165,186,220
};


UINT16 Spark_RPM_Map_Values[SPARK_RPM_POINTS] = 
{  
2083,
1785,
1562,
1388,
1250,
1136,
1041,
961,
892,
833,
781,
735,
694,
657,
625,
595,
568,
543,
520,
500,
480,
462,
446,
431,
416,
403,
390,
378,
367,
357,
347
};


/* Fuel Map Parameters */

#ifdef Fuel_Pulse_Data_16_bit

/* Control map containing angle to start fuel pulse (16bit) */
const UINT16 Fuel_Pulse_Angle_Map[FUEL_RPM_POINTS][FUEL_LOAD_POINTS] = 
{
/* RPM -------------------------------------------------------->             */
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 
       /*   v   */ 
};

UINT16 Fuel_Pulse_Angle_Map_RAM[FUEL_RPM_POINTS][FUEL_LOAD_POINTS];


/* Control map containing fuel pulse width (16bit) */
const UINT16 Fuel_Pulse_Width_Map[FUEL_RPM_POINTS][FUEL_LOAD_POINTS] = 
{
/* RPM| LOAD -------------------------------------------------------->             */
1875,1912,1950,1989,2029,2070,2111,2153,2196,2240,2285,2331,
1912,1950,1989,2029,2070,2111,2153,2196,2240,2285,2331,2377,
1950,1989,2029,2070,2111,2153,2196,2240,2285,2331,2377,2425,
1989,2029,2070,2111,2153,2196,2240,2285,2331,2377,2425,2474,
2029,2070,2111,2153,2196,2240,2285,2331,2377,2425,2474,2523,
2070,2111,2153,2196,2240,2285,2331,2377,2425,2474,2523,2573,
2111,2153,2196,2240,2285,2331,2377,2425,2474,2523,2573,2625,
2153,2196,2240,2285,2331,2377,2425,2474,2523,2573,2625,2677,
2196,2240,2285,2331,2377,2425,2474,2523,2573,2625,2677,2731,
2240,2285,2331,2377,2425,2474,2523,2573,2625,2677,2731,2786,
2285,2331,2377,2425,2474,2523,2573,2625,2677,2731,2786,2841,
2331,2377,2425,2474,2523,2573,2625,2677,2731,2786,2841,2898,
2377,2425,2474,2523,2573,2625,2677,2731,2786,2841,2898,2956,
2425,2474,2523,2573,2625,2677,2731,2786,2841,2898,2956,3015,
2474,2523,2573,2625,2677,2731,2786,2841,2898,2956,3015,3076,
2523,2573,2625,2677,2731,2786,2841,2898,2956,3015,3076,3137,
2573,2625,2677,2731,2786,2841,2898,2956,3015,3076,3137,3200,
2625,2677,2731,2786,2841,2898,2956,3015,3076,3137,3200,3264,
2677,2731,2786,2841,2898,2956,3015,3076,3137,3200,3264,3329,
2731,2786,2841,2898,2956,3015,3076,3137,3200,3264,3329,3396,
2786,2841,2898,2956,3015,3076,3137,3200,3264,3329,3396,3464,
2841,2898,2956,3015,3076,3137,3200,3264,3329,3396,3464,3533,
2898,2956,3015,3076,3137,3200,3264,3329,3396,3464,3533,3604,
2956,3015,3076,3137,3200,3264,3329,3396,3464,3533,3604,3676,
3015,3076,3137,3200,3264,3329,3396,3464,3533,3604,3676,3749,
3076,3137,3200,3264,3329,3396,3464,3533,3604,3676,3749,3824,
3137,3200,3264,3329,3396,3464,3533,3604,3676,3749,3824,3901,
3200,3264,3329,3396,3464,3533,3604,3676,3749,3824,3901,3979,
3264,3329,3396,3464,3533,3604,3676,3749,3824,3901,3979,4058,
3329,3396,3464,3533,3604,3676,3749,3824,3901,3979,4058,4140,
3396,3464,3533,3604,3676,3749,3824,3901,3979,4058,4140,4222

};

UINT16 Fuel_Pulse_Width_Map_RAM[FUEL_LOAD_POINTS][FUEL_RPM_POINTS];


#else

/* Control map containing angle to start fuel pulse (8bit) */
const UINT8 Fuel_Pulse_Angle_Map[FUEL_LOAD_POINTS][FUEL_RPM_POINTS] = 
{
/* RPM ---------------------------------------->             */
  0, 0    /* LOAD  */
    /*   |   */
  /*   |   */
}; 

UINT8 Fuel_Pulse_Angle_Map_RAM[FUEL_LOAD_POINTS][FUEL_RPM_POINTS];


/* Control map containing fuel pulse width (8bit) */
const UINT8 Fuel_Pulse_Width_Map[FUEL_LOAD_POINTS][FUEL_RPM_POINTS] = 
{
0, 0
}; 

UINT8 Fuel_Pulse_Width_Map_RAM[FUEL_LOAD_POINTS][FUEL_RPM_POINTS];

#endif


UINT16 Fuel_Load_Map_Values[FUEL_LOAD_POINTS] = 
{  
0,81,204,409,614,819,1023,1228,1638,2457,3276,4095
};

UINT16 Fuel_RPM_Map_Values[FUEL_RPM_POINTS] = 
{  
2083,
1785,
1562,
1388,
1250,
1136,
1041,
961,
892,
833,
781,
735,
694,
657,
625,
595,
568,
543,
520,
500,
480,
462,
446,
431,
416,
403,
390,
378,
367,
357,
347
};


