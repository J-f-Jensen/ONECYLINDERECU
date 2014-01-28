/** Seabreeze Emulator Compilation Options */
#include "Seabreeze_Emulator.h"

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

/** Variable types and common definitions */
#include "typedefs.h"

#include "Cpu.h"

#include "SCI.h"


void main(void) {

  UINT8 temp = 0;
  UINT8 temp1 = 0;
  UINT8 temp2 = 0;
  UINT8 temp3 = 0;
  
  // Disable interrupts before init
  DisableInterrupts;
   
  /* PLL initialization, 16 MHz Bus Clock @ 32MHz core */
  vfnClock_Init();
     
  /* Other CPU initalization parameters */
  vfnCpu_init();

  /* SCI initialization */
  vfnSCI_Init();

	EnableInterrupts;
	
  // Send 100 showing that we have reached this point
  temp3 = u8SCI_WriteTx(100);

  // Main loop
  for(;;) {
    _FEED_COP(); /* feeds the dog */


    // Check if there is data in the recive buffer
    if (u8SCI_CheckRx() > 0) {

     // Read one byte from buffer     
     temp = u8SCI_ReadRx() + 10;
     
     // Send the byte - test
     temp3 = u8SCI_WriteTx(temp);    
    
    }
    
/*    
    if (SCI0SR1_RDRF == 1) {
    
      temp = SCI0DRL + 10;
      if (temp1 == 1) {
         //This is the echo just discard it
         temp1 = 0;
      } else{
        //Echo back
        temp3 = u8SCI_WriteTx(temp);
        temp3 = u8SCI_WriteTx(u8SCI_CheckRx());
        temp1 = 1;
      }
      
    }
 */   

  
//Debug  
/*
     // We only run this one time
     if (temp2 == 0) {
       
       temp1 = 0;
       temp3 = 0;
       
       while(temp1 < 10){
         // Send temp1
         temp3 = u8SCI_WriteTx(temp1);
         
         //Increment temp1 if buffer is not full
         if (temp3 != SCI_COMM_TX_BUFFER_FULL) {
            temp1++;
         }
         
         temp3 = 0;
       }
       
       temp2 = 1;
     }
*/
//End debug


     
    
  } /* loop forever */
  /* please make sure that you never leave main */
}
