#include <ioCC2541.h>	 

#include "hal_lcd.h"
#include "hal_sht20.h"

int16 teTenth = 0;

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
  HalSHT20Init();

  while(1)                     //
  {
    
    if (0 == HalSHT20ReadTE(&teTenth)) {
      setTE(teTenth);
    } else {
      // read error
    }
    
    DelayMS(2000);
   
   
  }    
}
