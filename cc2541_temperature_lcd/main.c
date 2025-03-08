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
  
  DelayMS(200); // orig is 115ms
  
  //
  
  HalLcdInit();

  while(1)                     //
  {
   
    setTE(1234);    // 123.4
    DelayMS(2000);
    
    setTE(5678);    // 567.8
    DelayMS(2000);
    
    setTE(268);    // 26.8
    DelayMS(2000);
    
    setTE(45);    // 4.5
    DelayMS(2000);
    
    setTE(0);    // 0.0
    DelayMS(2000);
    
    setTE(-52);    // -5.2
    DelayMS(2000);
    
    setTE(-168);    // -16.8
    DelayMS(2000);
      
  }    
}
