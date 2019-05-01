


void tdc7200_start_meas(uint16_t s)
{  uint8_t Data_Byte_Low    = s;
   uint8_t Data_Byte_High  = s>>8;
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	uint8_t address[2] = {Data_Byte_High, Data_Byte_Low };
  HAL_SPI_Transmit(&hspi1, address, 2, 1);
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
}

void tdc1000_wr_config_reg (uint16_t config_reg_data)
{
   uint8_t Data_Byte_Low    = config_reg_data;
   uint8_t Data_Byte_High  = config_reg_data>>8;
  

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

      
uint8_t address[2] = {Data_Byte_High, Data_Byte_Low };
 

HAL_SPI_Transmit(&hspi1, address, 2, 1);
     
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	
}
void tdc7200_wr_config_reg (uint16_t config_reg_data)
{
   uint8_t Data_Byte_Low    = config_reg_data;
   uint8_t Data_Byte_High  = config_reg_data>>8;
  

  
     HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);

      
uint8_t address[2] = {Data_Byte_High, Data_Byte_Low };
 

HAL_SPI_Transmit(&hspi1, address, 2, 1);
      
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);

}

double tdc7200_read_n_bytes(uint8_t n, uint8_t read_opcode)
{
  uint16_t    Result_read = 0;

  double      Result = 0;
  
      HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	
       HAL_SPI_Transmit(&hspi1, &read_opcode, 1, 1);
       
       HAL_SPI_Receive(&hspi1, spiData, n, 1);
	

        
     if (n==1){
				Result_read = (spiData[0]);
				}
		 if (n==3){
			 	Result_read = (spiData[0] << 16) |  (spiData[1] << 8) | (spiData[2] << 0);
		}
			
    if (read_opcode==0x11 ||read_opcode==0x19 ||  read_opcode==0x13 || read_opcode==0x15 || read_opcode==0x17){
		 Result_read =Result_read >>6;
		 }
				 Result=Result_read;

      HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
  return Result;
}            