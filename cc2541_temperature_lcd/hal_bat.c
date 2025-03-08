
#include "hal_bat.h"
#include<ioCC2540.h>
#include "comdef.h"

/* Resolution */
#define HAL_ADC_RESOLUTION_8       0x01
#define HAL_ADC_RESOLUTION_10      0x02
#define HAL_ADC_RESOLUTION_12      0x03
#define HAL_ADC_RESOLUTION_14      0x04

/* Channels */
#define HAL_ADC_CHANNEL_0          0x00
#define HAL_ADC_CHANNEL_1          0x01
#define HAL_ADC_CHANNEL_2          0x02
#define HAL_ADC_CHANNEL_3          0x03
#define HAL_ADC_CHANNEL_4          0x04
#define HAL_ADC_CHANNEL_5          0x05
#define HAL_ADC_CHANNEL_6          0x06
#define HAL_ADC_CHANNEL_7          0x07

#define HAL_ADC_CHN_AIN0    0x00    /* AIN0 */
#define HAL_ADC_CHN_AIN1    0x01    /* AIN1 */
#define HAL_ADC_CHN_AIN2    0x02    /* AIN2 */
#define HAL_ADC_CHN_AIN3    0x03    /* AIN3 */
#define HAL_ADC_CHN_AIN4    0x04    /* AIN4 */
#define HAL_ADC_CHN_AIN5    0x05    /* AIN5 */
#define HAL_ADC_CHN_AIN6    0x06    /* AIN6 */
#define HAL_ADC_CHN_AIN7    0x07    /* AIN7 */
#define HAL_ADC_CHN_A0A1    0x08    /* AIN0,AIN1 */
#define HAL_ADC_CHN_A2A3    0x09    /* AIN2,AIN3 */
#define HAL_ADC_CHN_A4A5    0x0a    /* AIN4,AIN5 */
#define HAL_ADC_CHN_A6A7    0x0b    /* AIN6,AIN7 */
#define HAL_ADC_CHN_GND     0x0c    /* GND */
#define HAL_ADC_CHN_VREF    0x0d    /* Positive voltage reference */
#define HAL_ADC_CHN_TEMP    0x0e    /* Temperature sensor */
#define HAL_ADC_CHN_VDD3    0x0f    /* VDD/3 */
#define HAL_ADC_CHN_BITS    0x0f    /* Bits [3:0] */

#define HAL_ADC_CHANNEL_TEMP       HAL_ADC_CHN_TEMP
#define HAL_ADC_CHANNEL_VDD        HAL_ADC_CHN_VDD3   /* channel VDD divided by 3 */

/* Vdd Limits */
#define HAL_ADC_VDD_LIMIT_0        0x00
#define HAL_ADC_VDD_LIMIT_1        0x01
#define HAL_ADC_VDD_LIMIT_2        0x02
#define HAL_ADC_VDD_LIMIT_3        0x03
#define HAL_ADC_VDD_LIMIT_4        0x04
#define HAL_ADC_VDD_LIMIT_5        0x05
#define HAL_ADC_VDD_LIMIT_6        0x06
#define HAL_ADC_VDD_LIMIT_7        0x07

/* Reference Voltages */
#define HAL_ADC_REF_125V          0x00    /* Internal Reference (1.25V-CC2430)(1.15V-CC2540) */
#define HAL_ADC_REF_AIN7          0x40    /* AIN7 Reference */
#define HAL_ADC_REF_AVDD          0x80    /* AVDD_SOC Pin Reference */
#define HAL_ADC_REF_DIFF          0xc0    /* AIN7,AIN6 Differential Reference */
#define HAL_ADC_REF_BITS          0xc0    /* Bits [7:6] */


#define HAL_ADC_EOC         0x80    /* End of Conversion bit */
#define HAL_ADC_START       0x40    /* Starts Conversion */

#define HAL_ADC_STSEL_EXT   0x00    /* External Trigger */
#define HAL_ADC_STSEL_FULL  0x10    /* Full Speed, No Trigger */
#define HAL_ADC_STSEL_T1C0  0x20    /* Timer1, Channel 0 Compare Event Trigger */
#define HAL_ADC_STSEL_ST    0x30    /* ADCCON1.ST =1 Trigger */

#define HAL_ADC_RAND_NORM   0x00    /* Normal Operation */
#define HAL_ADC_RAND_LFSR   0x04    /* Clock LFSR */
#define HAL_ADC_RAND_SEED   0x08    /* Seed Modulator */
#define HAL_ADC_RAND_STOP   0x0c    /* Stop Random Generator */
#define HAL_ADC_RAND_BITS   0x0c    /* Bits [3:2] */

#define HAL_ADC_DEC_064     0x00    /* Decimate by 64 : 8-bit resolution */
#define HAL_ADC_DEC_128     0x10    /* Decimate by 128 : 10-bit resolution */
#define HAL_ADC_DEC_256     0x20    /* Decimate by 256 : 12-bit resolution */
#define HAL_ADC_DEC_512     0x30    /* Decimate by 512 : 14-bit resolution */
#define HAL_ADC_DEC_BITS    0x30    /* Bits [5:4] */

#define HAL_ADC_STSEL       HAL_ADC_STSEL_ST
#define HAL_ADC_RAND_GEN    HAL_ADC_RAND_STOP
#define HAL_ADC_REF_VOLT    HAL_ADC_REF_AVDD
#define HAL_ADC_DEC_RATE    HAL_ADC_DEC_064
#define HAL_ADC_SCHN        HAL_ADC_CHN_VDD3
#define HAL_ADC_ECHN        HAL_ADC_CHN_GND


static uint8 adcRef;

static void HalAdcInit (void)
{
  /*设置ad转换的参考电压
  这里使用了宏定义，其实最终设置的是
  ADCCON3.EREF  ADCCON3寄存器的高两位：擦考电压选择
  00:选择内部参考电压
  01:AIN7脚的电压作为参考电压
  10:AVDD5脚的电压作为参考电压
  11:AIN6、7的差分电压作为参考电压
  */
  adcRef = HAL_ADC_REF_125V;

}

uint16 HalAdcRead (uint8 channel, uint8 resolution)
{
  int16  reading = 0;


  uint8   i, resbits;
  uint8  adcChannel = 1;

  if (channel < 8)
  {
    for (i=0; i < channel; i++)
    {
      adcChannel <<= 1;
    }
  }

  /* Enable channel */
  /*
  配置相应通道所用到的模拟引脚，使能该引脚为模拟引脚，注意，该操作并不是必须的。
  TI的datasheet中是找不到ADCCFG这个寄存器，其实它是个别名，
  真正的名字叫：APCFG，Analog peripheral I/O configuration
  */
  ADCCFG |= adcChannel;

  /* Convert resolution to decimation rate */
  /*采样率设置，这里要注意了
  注意这里：采样率的设置影响最后adc值的处理，
  ADCH/L中的值最后要截取有效的MSBs，就是高多少位！
  比如设置的64位采样率，即8位分辨率，ADC最中的结果就要舍弃ADCL，只保留ADCH（即整个ADC右移8位）
  如果是最高512采样率，最终的ADC值要舍弃ADCL的低两位（即整个ADC值右移2位）
  */
  switch (resolution)
  {
    case HAL_ADC_RESOLUTION_8:
      resbits = HAL_ADC_DEC_064;
      break;
    case HAL_ADC_RESOLUTION_10:
      resbits = HAL_ADC_DEC_128;
      break;
    case HAL_ADC_RESOLUTION_12:
      resbits = HAL_ADC_DEC_256;
      break;
    case HAL_ADC_RESOLUTION_14:
    default:
      resbits = HAL_ADC_DEC_512;
      break;
  }

  /* writing to this register starts the extra conversion */
  /*参见上述说明，设置采样通道，采样率以及基准电压*/
  ADCCON3 = channel | resbits | adcRef;

  /* Wait for the conversion to be done */
  /*等待采样结束，标志位为ADCCON1的最高位EOC
  当转换结束后EOC置1，while跳出循环
  */
  while (!(ADCCON1 & HAL_ADC_EOC));

  /* Disable channel after done conversion */
  /*转换后取消采样通道的模拟输入设置*/
  ADCCFG &= (adcChannel ^ 0xFF);

  /* Read the result */
  /*保存ADC值，ADCH左移8+ADCL*/
  reading = (int16) (ADCL);
  reading |= (int16) (ADCH << 8);

  /* Treat small negative as 0 */
  if (reading < 0)
    reading = 0;

  /*参见上述说明*/
  switch (resolution)
  {
    case HAL_ADC_RESOLUTION_8:
    /*64位采样率，ADC的高8位为有效值，因此reading右移8位*/
      reading >>= 8;
      break;
    case HAL_ADC_RESOLUTION_10:
    /*128位采样率，ADC的高10位为有效值，因此reading右移6位*/
      reading >>= 6;
      break;
    case HAL_ADC_RESOLUTION_12:
    /*256位采样率，ADC的高12位为有效值，因此reading右移4位*/
      reading >>= 4;
      break;
    case HAL_ADC_RESOLUTION_14:
    default:
    /*512位采样率，ADC的高14位为有效值，因此reading右移2位*/
      reading >>= 2;
    break;
  }

  return ((uint16)reading);
}

void HalAdcSetReference ( uint8 reference )
{

  adcRef = reference;
}

/*采样电压，判断供电是否已稳定*/
bool HalAdcCheckVdd(uint8 vdd)
{
  ADCCON3 = 0x0F;
  while (!(ADCCON1 & 0x80));
  return (ADCH > vdd);
}

int hal_bat_read_level()
{
  HalAdcInit();
  uint16 adc=HalAdcRead(HAL_ADC_CHN_VDD3, HAL_ADC_RESOLUTION_8);
  
  // the internal ref voltage is 1.24V for cc2541
  // don't know why it is not accurate, here we just use the experiment result
  // 3.3V =>  adc result 117
  // 
  // 3V => deduced adc : 106
  
  // 2.69V 97
  // 2.48V 89
  // 2v => 71
  
  // original fw, 2.6V show two segs
  
  
  int level = BAT_LEVEL_EMPTY;
  if (level > 85) {
    level = BAT_LEVEL_1;
  } else if (level > 93) {
    level = BAT_LEVEL_2;
  } else if (level > 98) {
    level = BAT_LEVEL_3;    
  } else {
    level = BAT_LEVEL_4;
  }
  
  return level;
}