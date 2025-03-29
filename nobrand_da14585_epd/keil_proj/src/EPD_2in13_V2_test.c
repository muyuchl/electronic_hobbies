#include "epd_2in13_test.h"
#include "EPD_2in13_V2.h"
#include "DEV_Config.h"
#include "image_data.h"
#include <stdio.h>

void EPD_2in13_V2_test(void)
{
 printf("EPD_2IN9_test Demo\r\n");
    DEV_Module_Init();

    printf("e-Paper Init and Clear...\r\n");
    EPD_2IN13_V2_Init(EPD_2IN13_V2_FULL);
    EPD_2IN13_V2_Clear();
    DEV_Delay_ms(500);
	
#if 1   //show image for array    
    printf("show image for array\r\n");
  
    EPD_2IN13_V2_Display((UBYTE *)gImage_2in9);
    DEV_Delay_ms(10000);
#endif

	printf("Clear...\r\n");
    EPD_2IN13_V2_Init(EPD_2IN13_V2_FULL);
    EPD_2IN13_V2_Clear();

    printf("Goto Sleep...\r\n");
    EPD_2IN13_V2_Sleep();

    DEV_Module_Exit();
    
   
}

