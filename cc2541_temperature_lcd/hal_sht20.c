#include "hal_i2c.h"
#include "hal_sht20.h"


// Internal commands
#define SHT20_CMD_TEMP_T_H         0xE3 // command trig. temp meas. hold master
#define SHT20_CMD_HUMI_T_H         0xE5 // command trig. humidity meas. hold master
#define SHT20_CMD_TEMP_T_NH        0xF3 // command trig. temp meas. no hold master
#define SHT20_CMD_HUMI_T_NH        0xF5 // command trig. humidity meas. no hold master
#define SHT20_CMD_WRITE_U_R        0xE6 // command write user register
#define SHT20_CMD_READ_U_R         0xE7 // command read user register
#define SHT20_CMD_SOFT_RST         0xFE // command soft reset

#define HUMIDITY				   0x00
#define TEMPERATURE			        0x01

#define USR_REG_MASK               0x38  // Mask off reserved bits (3,4,5)
#define USR_REG_DEFAULT            0x02  // Disable OTP reload
#define USR_REG_RES_MASK           0x7E  // Only change bits 0 and 7 (meas. res.)
#define USR_REG_11BITRES           0x81  // 11-bit resolution  

extern void DelayMS(uint16 msec);

void HalSHT20Init(void)
{
  
  
  // todo: set precision
}

// return 0 for ok, -1 fail
int HalSHT20ReadTE(int16 *teTenth)
{
  // todo: move this elsewhere
  HalI2CInit(SHT20_I2C_ADDR, i2cClock_267KHZ);
  
  uint8 cmd = SHT20_CMD_TEMP_T_H;
  
  uint8 data_read[3] = {0};
  
  HalI2CWrite(1,&cmd);
  
  DelayMS(50);
  
  if (3 == HalI2CRead(3, data_read)) {
    // you can calc crc
    
    // convert
    uint16 rawT = ((uint16)(data_read[0]) << 8) | (data_read[1]);
    double v = -46.85 + 175.72/65536 *(double)(int16)rawT;
    *teTenth = (int16)(v * 10);
    return 0;
  } else {
    // read fail
    return -1;
  }
  
}

int HalSHT20ReadRH(int16 *rhTenth)
{
  // todo: move this elsewhere
  HalI2CInit(SHT20_I2C_ADDR, i2cClock_267KHZ);
  
  uint8 cmd = SHT20_CMD_HUMI_T_H;
  
  uint8 data_read[3] = {0};
  
  HalI2CWrite(1,&cmd);
  
  DelayMS(20);
  
  if (3 == HalI2CRead(3, data_read)) {
    // you can calc crc
    
    // convert
    uint16 rawH = ((uint16)(data_read[0]) << 8) | (data_read[1]);
    rawH &= ~0x0003; // clear bits [1..0] (status bits)
    
    double v = -6.0 + 125.0/65536 * (double)rawH; // RH= -6 + 125 * SRH/2^16
    *rhTenth = (int16)(v * 10);
    return 0;
  } else {
    // read fail
    return -1;
  }
}