#include <ioCC2541.h>	 

#include "hal_lcd.h"
#include "hal_sht20.h"
#include "hal_bat.h"
#include "hal_sleep.h"

int16 teTenth = 0;
bool teOk;
int16 rhTenth = 0;
bool rhOk;
int batLevel = 0;

// sleep time, unit is second
#define SLEEP_INTERVAL 10

// SET OVR bit, so in sleep mode, prevent scl pin glitch, pullup enabled
#define I2C_WRAPPER_ENABLE() st( I2CWC    =     0x8C;      )

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

  InitSleepTimer(); 
  DelayMS(200); // orig is 115ms
  
  //
  
  HalLcdInit();
  HalSHT20Init();

  while(1)                     //
  {    
    HalSHT20I2CSelect();
    
    if (0 == HalSHT20ReadTE(&teTenth)) {
      teOk = TRUE;
    } else {
      // read error
      teOk = FALSE;
    }
    
    if (0 == HalSHT20ReadRH(&rhTenth)) {
      rhOk = TRUE;
    } else {
      // read error
      rhOk = FALSE;
    }
    
    batLevel = hal_bat_read_level();
    
    HalLcdUpdate(teTenth, teOk, rhTenth, rhOk, batLevel);
    
    SetSleepTime(SLEEP_INTERVAL);   
    // so no scl glich during sleep
    I2C_WRAPPER_ENABLE();
    PowerMode(2);    //进入睡眠模式PM2
   
  }    
}
