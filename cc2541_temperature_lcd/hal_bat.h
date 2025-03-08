#ifndef HAL_BAT_H
#define HAL_BAT_H

enum {
  BAT_LEVEL_EMPTY = 0,
  BAT_LEVEL_1,
  BAT_LEVEL_2,
  BAT_LEVEL_3,
  BAT_LEVEL_4   // full
  
};

int hal_bat_read_level();

#endif // HAL_BAT_H