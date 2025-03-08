/**************************************************************************************************
  
**************************************************************************************************/
#ifndef HAL_LCD_H
#define HAL_LCD_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "hal_types.h"

/*********************************************************************
 * CONSTANTS
 */
#define LCD_I2C_ADDR 0x3E

/*********************************************************************
 * FUNCTIONS
 */
void HalLcdInit(void);
void HalLcdAllOn(void);
void HalLcdAllOff(void);

void setTE(int16 valueTenthDegC);
void setRH(int16 valueTenth);
void setBattery(int level);

void writeBufToLcd(void);

/*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* HAL_LCD_H */
