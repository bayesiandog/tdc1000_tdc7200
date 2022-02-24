#include "tdc1000.h"   
#include <stdint.h>


/**
  * @brief  TDC1000 reset
  */
void RST_TDC1000(void){   // TDC1000 reset
	tdc1000_wr_config_reg (w, 7, 3);
}


/**
  * @brief  Write to a configuration register of TDC1000
  * @param  Register address
  * @param  Configuration value
  */
void tdc1000_wr_config_reg (uint8_t  rw,  uint8_t reg, uint8_t config_reg_data)  // write or read configuration register
{
	uint8_t Data_Byte_Low    = config_reg_data;

	uint8_t Data_Byte_High  = 0x40|reg;  // 0b01000000 to write to a register

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	uint8_t address[2] = {Data_Byte_High, Data_Byte_Low };
	HAL_SPI_Transmit(&hspi1, address, 2, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}


/**
  * @brief  Check error status register
  * @retval error code
  */
int tdc1000_error_check()
{
	uint8_t    Result_read = 0;
	int      Result = 0;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, 0x7, 1, 1);
	HAL_SPI_Receive(&hspi1, spiData, 1, 1);
	Result_read = (spiData[0]);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

	if (Result_read==1)
		err=1;
	else if (Result_read==2)
		err=2;
	else if (Result_read==3)
		err=3;

	return err;
}                


/**
  * @brief  Start a TOF measurement
  */
void tdc7200_start_meas()
{  
	uint8_t Data_Byte_Low   = 43;
	uint8_t Data_Byte_High  = 40;
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	uint8_t address[2] = {Data_Byte_High, Data_Byte_Low };
	HAL_SPI_Transmit(&hspi1, address, 2, 1);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
}


/**
  * @brief  Write to a configuration register of TDC7200
  * @param  Register address
  * @param  Configuration value
  */
void tdc7200_wr_config_reg (uint8_t  rw,  uint8_t reg, uint8_t config_reg_data)
{
	uint8_t Data_Byte_Low    = config_reg_data;

	uint8_t Data_Byte_High  = 0x40|reg;

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	uint8_t address[2] = {Data_Byte_High, Data_Byte_Low };
	HAL_SPI_Transmit(&hspi1, address, 2, 1);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
}


/**
  * @brief  Read TDC7200 result registers
  * @param  Number of bytes to be read
  * @param  Opcode corresponding to result register
  * @retval Measurement value
  */
double tdc7200_read_n_bytes(uint8_t n, uint8_t read_opcode)
{
uint16_t    Result_read = 0;
double      Result = 0;

HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
HAL_SPI_Transmit(&hspi1, &read_opcode, 1, 1);
HAL_SPI_Receive(&hspi1, spiData, n, 1);

if (n==1)
	Result_read = (spiData[0]);
if (n==3)
	Result_read = (spiData[0] << 16) |  (spiData[1] << 8) | (spiData[2] << 0);

if (read_opcode==0x11 || read_opcode==0x19 ||  read_opcode==0x13 || read_opcode==0x15 || read_opcode==0x17)
	Result_read =Result_read >>6;
Result=Result_read;

HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
return Result;
}               

