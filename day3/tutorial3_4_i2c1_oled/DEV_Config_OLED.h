#ifndef _DEV_CONFIG_OLED_H_
#define _DEV_CONFIG_OLED_H_

//#include "Arduino.h"
#include "Wire.h"
#include "Debug_OLED.h"

//
// 6DoF Interfaces
//

#define DEV_SPI 0
#define DEV_I2C 1

/**
 * I2C config
**/
#define OLED_I2C_PORT (1)
#define OLED_SDA_PIN  (6)   
#define OLED_SCL_PIN  (7)

#define SENSOR_I2C_PORT (0)
#define SENSOR_SDA_PIN  (8)
#define SENSOR_SCL_PIN  (9)

void DEV_Delay_ms(uint32_t xms);

void DEV_I2C_Write_Byte(uint8_t i2c_num,uint8_t addr, uint8_t value);
void DEV_I2C_Write_nByte(uint8_t i2c_num,uint8_t addr, uint8_t *pData, uint32_t len);

void DEV_I2C_Write_Reg_Byte(uint8_t i2c_num,uint8_t addr,uint8_t reg, uint8_t value);
void DEV_I2C_Write_Reg_nByte(uint8_t i2c_num,uint8_t addr,uint8_t reg, uint8_t *pData, uint32_t len);

uint8_t DEV_I2C_Read_Byte(uint8_t i2c_num,uint8_t addr);
void DEV_I2C_Read_nByte(uint8_t i2c_num,uint8_t addr, uint8_t *pData, uint32_t len);

uint8_t DEV_I2C_Read_Reg_Byte(uint8_t i2c_num,uint8_t addr,uint8_t reg);
void DEV_I2C_Read_Reg_nByte(uint8_t i2c_num,uint8_t addr,uint8_t reg, uint8_t *pData, uint32_t len);

uint8_t DEV_ModuleInit(void);
void  DEV_ModuleExit(void);

//
// OLED Interfaces
//
/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t
#define USE_IIC     1

#define IIC_CMD        0X00
#define IIC_RAM        0X40

uint8_t System_Init(void);

void I2C1_Write_Byte(uint8_t value, uint8_t Cmd);
void I2C1_Write_nByte_data(uint8_t Cmd,const uint8_t* pdata,uint16_t len);
void Driver_Delay_ms(unsigned long xms);
void Driver_Delay_us(int xus);

#endif
