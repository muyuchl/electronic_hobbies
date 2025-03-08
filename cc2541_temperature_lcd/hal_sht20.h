#ifndef HAL_SHT20_H
#define HAL_SHT20_H

#define SHT20_I2C_ADDR 0x40

void HalSHT20Init(void);

void HalSHT20I2CSelect(void);

int HalSHT20ReadTE(int16 *teTenth);
int HalSHT20ReadRH(int16 *rhTenth);


#endif // HAL_SHT20_H