#include <ioCC2541.h>	 

#include "hal_lcd.h"
#include "hal_sht20.h"
#include "hal_bat.h"

int16 teTenth = 0;
int16 rhTenth = 0;

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


void SysClkSet_32M(void)//设置系统时钟为32MHz
{
  CLKCONCMD &= ~0x40;
  while(CLKCONSTA & 0x40);    
  CLKCONCMD &= ~0x47;  
}

void main(void)
{     
 // InitGPIO();                   //
  
  SysClkSet_32M();
  DelayMS(200); // orig is 115ms
  
  //
  
  HalLcdInit();
 // HalSHT20Init();

  while(1)                     //
  {
    /*
    if (0 == HalSHT20ReadTE(&teTenth)) {
      setTE(teTenth);
    } else {
      // read error
    }
    
    if (0 == HalSHT20ReadRH(&rhTenth)) {
      setRH(rhTenth);
    } else {
      // read error
    }
    */
    int level = hal_bat_read_level();
    setTE(level);
    
    DelayMS(2000);
   
   
  }    
}
