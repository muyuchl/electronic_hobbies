/**************************************************************************************************
  
**************************************************************************************************/
#include "hal_lcd.h"
#include "hal_i2c.h"


#define LCD_I2C_ADDR 0x3E

extern void DelayMS(uint16 msec);

void HalLcdInit(void)
{
  uint8 init_command[3] = {0xC8, 0xB4, 0xF0 };
      
  HalI2CInit(LCD_I2C_ADDR, i2cClock_267KHZ);    // the clock is for 32MHz osc
  
  DelayMS(100);
  
  uint8 ret = HalI2CWrite(3, init_command);
}

void HalLcdAllOn(void)
{
  uint8 buf[9] = {0x00,   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
  
  uint8 ret = HalI2CWrite(9, buf);
}

void HalLcdAllOff(void)
{
  uint8 buf[9] = {0x00,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  
  uint8 ret = HalI2CWrite(9, buf);
}
