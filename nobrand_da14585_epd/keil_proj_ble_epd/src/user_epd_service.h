#ifndef USER_EPD_SERVICE_H
#define USER_EPD_SERVICE_H

//enum {
//    EPD_CMD_RESULT_OK = 0,
//    EPD_CMD_RESULT_ERROR
//};

enum {
EPD_CMD_SET_PINS,                                 /**< set EPD pin mapping. */
    EPD_CMD_INIT,                                     /**< init EPD display driver */
    EPD_CMD_CLEAR,                                    /**< clear EPD screen */
    EPD_CMD_SEND_COMMAND,                             /**< send command to EPD */
    EPD_CMD_SEND_DATA,                                /**< send data to EPD */
    EPD_CMD_DISPLAY,                                  /**< diaplay EPD ram on screen */
    EPD_CMD_SLEEP,                                    /**< EPD enter sleep mode */
	
	EPD_CMD_SET_TIME = 0x20,                          /** < set time with unix timestamp */

    EPD_CMD_SET_CONFIG = 0x90,                        /**< set full EPD config */
    EPD_CMD_SYS_RESET  = 0x91,                        /**< MCU reset */
    EPD_CMD_SYS_SLEEP  = 0x92,                        /**< MCU enter sleep mode */
    EPD_CMD_CFG_ERASE  = 0x99,                        /**< Erase config and reset */
};


void user_epd_handle_ble_request(const uint8_t *data, uint16_t length);

#endif
