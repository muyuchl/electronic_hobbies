#ifndef HAL_SLEEP_H
#define HAL_SLEEP_H
#include "comdef.h"

void PowerMode(uint8 mode);
void InitSleepTimer(void) ;
void SetSleepTime(int sec) ;

#endif//HAL_SLEEP_H
