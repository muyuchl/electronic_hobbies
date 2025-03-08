#include <ioCC2541.h>	 

#include "hal_lcd.h"



/****************************************************************************
DelayMS()
osc: 16M
max delay 65536ms

****************************************************************************/
void DelayMS(uint16 msec)
{ 
    uint16 i,j;
    
    for (i=0; i<msec; i++)
        for (j=0; j<536; j++);
}

/****************************************************************************

****************************************************************************/

/*
void InitGPIO(void)
{
  P1DIR |= 0x02; //P1.1  output
  P1SEL &= ~0x02;	//P1.1 gpio
}
*/


void main(void)
{     
 // InitGPIO();                   //
  
  DelayMS(800); // orig is 115ms
  
  //
  
  HalLcdInit();

  while(1)                     //
  {
   
    HalLcdAllOn();
    DelayMS(5000);           //
    HalLcdAllOff();
    DelayMS(5000);   
  }    
}
