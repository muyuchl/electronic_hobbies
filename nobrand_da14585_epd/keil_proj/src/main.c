/**
 ****************************************************************************************
 *
 * @file main.c
 * @brief dong fu epaper price tag on da14585
 ****************************************************************************************
 */
#include <stdio.h>
#include "arch_system.h"
#include "uart.h"
#include "uart_utils.h"
#include "user_periph_setup.h"
#include "gpio.h"
#include "epd_2in13_test.h"

//#include "DEV_Config.h"

int fputc(int ch, FILE *f)
{  
  uart_write_byte(UART, ch);   
  return ch;
}

/**
 ****************************************************************************************
 * @brief Main routine of the epaper dongfu example
 ****************************************************************************************
 */
int main (void)
{
    system_init();
    
    printf_string(UART, "epaper test\r\n");

    GPIO_SetInactive(LED_PORT, LED_PIN);
	EPD_2in13_V2_test();
    GPIO_SetActive(LED_PORT, LED_PIN);    
    
	
    while(1);

        
}

