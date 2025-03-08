/**************************************************************************************************
  
**************************************************************************************************/
#include "hal_lcd.h"
#include "hal_i2c.h"



extern void DelayMS(uint16 msec);

#define LCD_BUF_SIZE 8

// the first byte is ram address, 0
unsigned char buf_with_ramaddr[1+LCD_BUF_SIZE]; 

unsigned char *plcdbuf = buf_with_ramaddr+1;

static void reset_buf();
static void update_segs(uint8 seg_data, const uint8 *digit_position);

// xGFEDCBA 0b01101101 = 0x6D = 109 = show "5", from '0' to '9'
const unsigned char DIGIT_FONT[10] = {
  0x3F,  0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

// bit position of segs, from seg A to seg G
const unsigned char DIGIT_1_SEGS[7] = {
    3,
    2,
    1,
    0,
    4,
    6,
    5
};

const unsigned char DIGIT_2_SEGS[7] = {
    11, // 2A
    10,
    9,
    8,
    12,
    14,
    13
};

const unsigned char DIGIT_3_SEGS[7] = {
    3 + 16,
    2 + 16,
    1 + 16,
    0 + 16,
    4 + 16,  // 3E
    6 + 16,
    5 + 16
};

const unsigned char DIGIT_4_SEGS[7] = {
    3 + 24,
    2 + 24,
    1 + 24,
    0 + 24,
    4 + 24,
    6 + 24,
    5 + 24
};

const unsigned char DIGIT_5_SEGS[7] = {
    3 + 48,
    2 + 48,
    1 + 48,
    0 + 48,
    5 + 56,      // 5E
    7 + 56,
    6 + 56
};

const unsigned char DIGIT_6_SEGS[7] = {
    3 + 40,
    2 + 40,
    1 + 40,
    0 + 40,
    5 + 48, // 6E
    7 + 48,
    6 + 48
};

const unsigned char DIGIT_7_SEGS[7] = {
    3 + 32,
    2 + 32,
    1 + 32,
    0 + 32,
    5 + 40,      // 7E
    7 + 40,
    6 + 40
};

void HalLcdInit(void)
{
  uint8 init_command[3] = {0xC8, 0xB4, 0xF0 };
      
  HalI2CInit(LCD_I2C_ADDR, i2cClock_267KHZ);    // the clock is for 32MHz osc
  
  DelayMS(100);
  
  buf_with_ramaddr[0] = 0;  // ram addr 0
  reset_buf();
  
  // this is not required when when woken from sleep
  uint8 ret = HalI2CWrite(3, init_command);
  
  HalLcdAllOn();
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

void setTE(int16 valueTenthDegC)
{
  reset_buf();

    unsigned char minus = 0;
    if (valueTenthDegC < 0) {
        minus = 1;
        valueTenthDegC = -valueTenthDegC;
    }

    unsigned char segs = 0;

    unsigned char d1 = (valueTenthDegC/1000) % 10;
    if (d1 != 0) {
        // only update when d1 is not zero,
        segs = DIGIT_FONT[d1];
        update_segs(segs, DIGIT_1_SEGS);
    }

    unsigned char d2 = (valueTenthDegC/100) % 10;
    if (d1 == 0 && d2 == 0) {
        // not show
    } else {
        segs = DIGIT_FONT[d2];
        update_segs(segs, DIGIT_2_SEGS);
    }

    unsigned char d3 = (valueTenthDegC/10) % 10;
    segs = DIGIT_FONT[d3];
    update_segs(segs, DIGIT_3_SEGS);


    unsigned char d4 = valueTenthDegC % 10;
    segs = DIGIT_FONT[d4];
    update_segs(segs, DIGIT_4_SEGS);


    if (minus) {
        // set 1G
        int byteOffset = 0;
        int bitOffset = 5;
        plcdbuf[byteOffset] |= (1 << bitOffset);
    }

    
    // todo: call in main when all data is set
    writeBufToLcd();
}


void writeBufToLcd(void)
{
//  uint8 local_buf[9];
  
//  for (int i = 0; i < 1 + LCD_BUF_SIZE; i++) {
//    local_buf[i] = buf_with_ramaddr[i];
//  }
  
  uint8 ret = HalI2CWrite(9, buf_with_ramaddr);
  if (ret != 9) {
    // write error
  }
  
}

static void reset_buf()
{
  for (int i = 0; i < LCD_BUF_SIZE; i++) {
        plcdbuf[i] = 0;
    }

#if 0
    // set deciaml point and battery frame
    int byteOffset = 2;
    int bitOffset = 7;

    buf[byteOffset] |= (1 << bitOffset);

    // set degree celsius
    byteOffset = 5;
    bitOffset = 4;
    buf[byteOffset] |= (1 << bitOffset);
#endif
}

static void update_segs(uint8 seg_data, const uint8 *digit_position)
{
  for (int i = 0; i < 7; i++) {
        unsigned char segPosition = digit_position[i];
        int byteOffset = segPosition / 8;
        int bitOffset = segPosition % 8;

        if (seg_data & (1 << i)) {
            // set bit
            plcdbuf[byteOffset] |= (1 << bitOffset);
        } else {
            // clear bit
            plcdbuf[byteOffset] &= ~(1 << bitOffset);
        }
    }
}