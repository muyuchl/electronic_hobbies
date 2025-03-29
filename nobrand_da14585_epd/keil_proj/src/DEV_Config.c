/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master
*                and enhance portability
*----------------
* |	This version:   V2.0
* | Date        :   2018-10-30
* | Info        :
# ******************************************************************************
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "DEV_Config.h"

// refer https://oshwhub.com/article/ru-he-kuai-su-shang-shou-yi-kuan-xin-xin-pian

void DEV_Delay_ms(int __xms)
{
	volatile uint16_t i, j;
	for (i = 0; i < __xms; i++) {
		for (j = 0; j < 2700; j++) {
			;
		}
	}	
}

void DEV_SPI_WriteByte(UBYTE value)
{
    uint8_t i = 0;
    for (i = 0; i < 8; i++) {
        EPD_SCLK_L;
        if (value & 0x80) {
            EPD_SDI_H;
        } else {
            EPD_SDI_L;
        }
        
        value <<= 1;
        EPD_SCLK_H;
    }
    
    EPD_SCLK_H;
}

int DEV_Module_Init(void)
{
	// config pins
	
	// power
	GPIO_ConfigurePin(EPD_POWER_PIN, OUTPUT, PID_GPIO, true);	
	EPD_POWER_ON();
	DEV_Delay_ms(10);
	
	// busy, input
	GPIO_ConfigurePin(EPD_BUSY_PIN, INPUT, PID_GPIO, false);	
	
	// rst
	GPIO_ConfigurePin(EPD_RST_PIN, OUTPUT, PID_GPIO, true);	
	DEV_Digital_Write(EPD_RST_PIN, 1);
	
	// dc
	GPIO_ConfigurePin(EPD_DC_PIN, OUTPUT, PID_GPIO, false);	

	// cs
	GPIO_ConfigurePin(EPD_CS_PIN, OUTPUT, PID_GPIO, false);	
	
	// spi
	GPIO_ConfigurePin(EPD_CLK_PIN, OUTPUT, PID_GPIO, false);	
	GPIO_ConfigurePin(EPD_SDI_PIN, OUTPUT, PID_GPIO, false);	
	
	
	DEV_Digital_Write(EPD_SDI_PIN, 0);
	DEV_Digital_Write(EPD_CLK_PIN, 0);
	
	DEV_Digital_Write(EPD_DC_PIN, 1);	// wave share set to 0
	DEV_Digital_Write(EPD_CS_PIN, 0);

	return 0;
}

void DEV_Module_Exit(void)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);

    //close 
    DEV_Digital_Write(EPD_RST_PIN, 0);
	
	EPD_POWER_OFF();
}

