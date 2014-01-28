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
  UINT8 temp4 = 0;
  
  // Disable interrupts before init
  DisableInterrupts;
 
  /* PLL initialization, 16 MHz Bus Clock @ 32MHz core */
  vfnClock_Init();
     
  /* Other CPU initalization parameters */
  vfnCpu_init();

  /* SCI initialization */
  vfnSCI_Init();

	EnableInterrupts;
	
  // Send 49 = 1 in ANSI showing that we have reached this point
  temp3 = u8SCI_WriteTx(49);
  
  // Disable PWM
  //PWME = 0x00;
  // Set Port P as output
  //sDDRP = 0xFF;
  
  // secure that input capture is enbled
  //TIOS = 0x00;
  // set port T as output except pt0, pt1 and pt2 
  //sDDRT = 0xF8;
  
  

  // Main loop
  for(;;) {
    _FEED_COP(); /* feeds the dog */


    // Check if there is data in the recive buffer
    if (u8SCI_CheckRx() > 0) {
      // We have new input
      temp2 = 1;
      
      // Check input
      switch (u8SCI_ReadRx()) {
        case 'A': // Select port A
          temp = 4;
          temp1 = 0;
          break;

        case 'B': // Select port B
          temp = 1;
          temp1 = 0;
          break;

        case 'E': // Select port E
          temp = 5;
          temp1 = 0;
          break;

        case 'T': // Select port T
          temp = 2;
          temp1 = 0;
          break;
          
        case 'P': // Select port P
          temp = 3;
          temp1 = 0;
          break;
         
        case 'R': //Reset ports to low
          PORTB = 0x00;
          //PTIT = 0x00;
          temp3 = u8SCI_WriteTx('R');
          break;
        
        case '0':
          temp1 = 0x02;
          break;
 
        case '1':
          temp1 = 0x03;
          break;

        case '2':
          temp1 = 0x05;
          break;
                   
        case '3':
          temp1 = 0x09;
          break;

        case '4':
          temp1 = 0x11;
          break;

        case '5':
          temp1 = 0x21;
          break;
 
        case '6':
          temp1 = 0x41;
          break;

        case '7':
          temp1 = 0x81;
          break;
                            
        default:
          // No valid input recived
          temp = 0;
          temp1 = 0;
          temp2 = 0;
          DDRA = 0x00;
          DDRB = 0x00;
          DDRE = 0x00;
          //DDRP = 0x00;  
          //DDRT = 0x00; 
          temp3 = u8SCI_WriteTx('-');
          break;
      }
      
      //Check if we have valid input data
      if (temp != 0 && temp1 > 0x01 && temp1 < 0x82 && temp2 == 1){
        
        //Extract 1 from temp1
        --temp1;

        if (temp == 4) {
          //DDRA = 0xFF;
          //PORTA = temp1;
          temp4 = PORTA;
          temp3 = u8SCI_WriteTx('A');
          //Send PIN number
          temp3 = u8SCI_WriteTx(temp4);
        }
             
        if (temp == 1) {
          //DDRB = 0xFF;
          //PORTB = temp1;
          temp4 = PORTB;
          temp3 = u8SCI_WriteTx('B'); 
          //Send PIN number
          temp3 = u8SCI_WriteTx(temp4);
        }

        if (temp == 5) {
          //DDRE = 0xFF;
          //PORTE = temp1;
          temp4 = PORTE;
          temp3 = u8SCI_WriteTx('E');
          //Send PIN number
          temp3 = u8SCI_WriteTx(temp4);
        }

        
        if (temp == 2) {
          //DDRT = 0xFF;
          //sPTT = temp1;
          temp4 = sPTT;
          temp3 = u8SCI_WriteTx('T');
          //Send PIN number
          temp3 = u8SCI_WriteTx(temp4);
        }
        
        if (temp == 3) {
          //DDRP = 0xFF;
          //sPTP = temp1;
          temp4 = sPTP;
          temp3 = u8SCI_WriteTx('P');
          //Send PIN number
          temp3 = u8SCI_WriteTx(temp4);
        }
                   
        //reset input
        temp1 = 0;
        temp2 = 0;    
      }
      
     // Read one byte from buffer     
//     temp = u8SCI_ReadRx() + 10;
     
     // Send the byte - test
//     temp3 = u8SCI_WriteTx(temp);    
    }
    
    
       
  } /* loop forever */
  /* please make sure that you never leave main */
}
