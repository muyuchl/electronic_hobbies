#include "user_epd_service.h"

#include "app_api.h"
#include "arch_console.h"
//#include "EPD_2in9.h"
#include "EPD_2in13_V2.h"
#include "DEV_Config.h"
#include "user_custs1_def.h"
#include "user_custs1_impl.h"

#define EPD_DEFER_DELAY 1     // in 10ms slot, can not be 0, though 0 is ok in da14580 5.x sdk

#define MAX_EPD_REQUEST DEF_SVC1_LED_STATE_CHAR_LEN


ke_msg_id_t timer_epd_defer;
uint8_t request_buf[MAX_EPD_REQUEST];
uint16_t request_len = 0;

void epd_defer_timer_cb_handler(void);


void handle_cmd_epd_prepare(void);
void handle_cmd_clear(void);
void handle_cmd_send_command(uint8_t reg);

void handle_cmd_epd_write_data(const uint8_t *data, int len);
void handle_cmd_epd_display(void);


void handle_cmd_epd_sleep(void);
//void handle_cmd_epd_poweroff(void);

void user_epd_handle_ble_request(const uint8_t *data, uint16_t length)
{
    if (length > MAX_EPD_REQUEST) {
        // error, truncate, or report error
        length = MAX_EPD_REQUEST;
    }
        
//    arch_printf("got cmd %d :", length);
//    for (int i = 0; i < length; i++) {
//        arch_printf("%02X, ", data[i]);
//    }
//    arch_printf("\r\n");
    
    if (length == 0) {
        arch_printf("epd request invalid len 0\r\n");
        return;
    }
    
    switch (data[0]) {
        case EPD_CMD_SET_PINS:
            arch_printf("unsupported cmd set pin\r\n");
            break;
        case EPD_CMD_INIT:
            handle_cmd_epd_prepare();
            break;
        case EPD_CMD_CLEAR:
            handle_cmd_clear();
            break;
        case EPD_CMD_SEND_COMMAND:
            if (length> 1) {
                handle_cmd_send_command(data[1]);
            }
            break;
        case EPD_CMD_SEND_DATA:
            handle_cmd_epd_write_data(&(data[1]), length-1);
            break;
        case EPD_CMD_DISPLAY:
            handle_cmd_epd_display();
            break;
        case EPD_CMD_SLEEP:
            handle_cmd_epd_sleep();
            break;
        case EPD_CMD_SET_TIME:
            arch_printf("unsupported cmd set time\r\n");
            break;
        case EPD_CMD_SET_CONFIG:
            arch_printf("unsupported cmd set config\r\n");
            break;
        case EPD_CMD_SYS_RESET:
            arch_printf("unsupported cmd reset\r\n");
            break;
        case EPD_CMD_SYS_SLEEP:
            arch_printf("unsupported cmd sleep\r\n");
            break;
        case EPD_CMD_CFG_ERASE:
            arch_printf("unsupported cmd erase\r\n");
            break;
        default:
            arch_printf("unknown cmd %02X\r\n", data[0]);
            break;
    }
    
//    request_len = length;
//    memcpy(request_buf, data, length);
//    
//    timer_epd_defer = app_easy_timer(EPD_DEFER_DELAY, epd_defer_timer_cb_handler);

}



void handle_cmd_epd_prepare(void)
{
    arch_printf("%s\r\n", __func__);
        //  prepare epd
        DEV_Module_Init();
        
     //   DEV_Delay_ms(100);
        
        EPD_2IN13_V2_Init(EPD_2IN13_V2_FULL);

    //   EPD_2IN9_SetWindows(0, 0, EPD_2IN9_WIDTH, EPD_2IN9_HEIGHT);
    
    arch_printf("%s return\r\n", __func__);
}

void handle_cmd_clear(void)
{
    arch_printf("%s\r\n", __func__);
    EPD_2IN13_V2_Clear();
}

void handle_cmd_send_command(uint8_t reg)
{
    arch_printf("%s 0x %02X\r\n", __func__, reg);
    EPD_2IN13_V2_SendCommand(reg);
}

void handle_cmd_epd_write_data(const uint8_t *data, int len)
{
    arch_printf("%s len %d\r\n", __func__, len);
    // not efficient, can optimize
    for (int i = 0; i < len; i++) {
        EPD_2IN13_V2_SendData(data[i]);
    }
}


void handle_cmd_epd_display(void)
{
     EPD_2IN13_V2_TurnOnDisplay_NoWait();    
}

void handle_cmd_epd_sleep(void)
{
    EPD_2IN13_V2_Sleep();
}

void handle_cmd_epd_poweroff(void)
{
    uint8_t response_buf[2] = {0x00};
    uint16_t response_len = 2;
    
    DEV_Module_Exit();
}
