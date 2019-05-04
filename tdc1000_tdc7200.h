
#ifndef tdc1000
#define tdc1000

#include "stm32f10x.h"

// TDC1000 registers definitions
#define CONFIG_0               0x00
#define CONFIG_1               0x01
#define CONFIG_2               0x02
#define CONFIG_3               0x03
#define CONFIG_4               0x04
#define TOF_1                  0x05
#define TOF_0                  0x06
#define ERROR_FLAGS            0x07
#define TIMEOUT                0x08
#define CLOCK_RATE             0x09


// TDC7200 registers definitions
#define CONFIG1                0x00
#define CONFIG2                0x01
#define INT_STATUS             0x02
#define INT_MASK               0x03
#define COARSE_CNTR_OVF_H      0x04
#define COARSE_CNTR_OVF_L      0x05
#define CLOCK_CNTR_OVF_H       0x06
#define CLOCK_CNTR_OVF_L       0x07
#define CLOCK_CNTR_STOP_MASK_H 0x08
#define CLOCK_CNTR_STOP_MASK_L 0x09
#define TIME1                  0x10
#define CLOCK_COUNT1           0x11
#define TIME2                  0x12
#define CLOCK_COUNT2           0x13
#define TIME3                  0x14
#define CLOCK_COUNT3           0x15
#define TIME4                  0x16
#define CLOCK_COUNT4           0x17
#define TIME5                  0x18
#define CLOCK_COUNT5           0x19
#define TIME6                  0x1A
#define CALIBRATION1           0x1B
#define CALIBRATION2           0x1C


void tdc7200_start_meas();

void tdc7200_wr_config_reg (uint8_t  rw,  uint8_t reg, uint8_t config_reg_data);

double tdc7200_read_n_bytes(uint8_t n, uint8_t read_opcode);

void tdc1000_wr_config_reg (uint8_t  rw,  uint8_t reg, uint8_t config_reg_data);

void RST_TDC1000(void);

int tdc1000_error_check();







#endif




