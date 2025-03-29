#include "epd_2in9_test.h"
#include "EPD_2in9.h"
#include "DEV_Config.h"
#include "image_data.h"
#include <stdio.h>

void epd_2in9_test()
{
	
	printf("EPD_2IN9_test Demo\r\n");
    DEV_Module_Init();

    printf("e-Paper Init and Clear...\r\n");
    EPD_2IN9_Init(EPD_2IN9_FULL);
    EPD_2IN9_Clear();
    DEV_Delay_ms(500);
	
#if 1   //show image for array    
    printf("show image for array\r\n");
  
    EPD_2IN9_Display((UBYTE *)gImage_2in9);
    DEV_Delay_ms(10000);
#endif

	printf("Clear...\r\n");
    EPD_2IN9_Init(EPD_2IN9_FULL);
    EPD_2IN9_Clear();

    printf("Goto Sleep...\r\n");
    EPD_2IN9_Sleep();

    DEV_Module_Exit();
}