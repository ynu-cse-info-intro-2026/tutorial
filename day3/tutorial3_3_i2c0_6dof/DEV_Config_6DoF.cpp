/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V2.0
* | Date        :   2019-07-08
* | Info        :   Basic version
*
******************************************************************************/
#include "DEV_Config_6DoF.h"

//
// 6DoF Interface
//

/******************************************************************************
function:	I2C Function initialization and transfer
parameter:
Info:
******************************************************************************/
void DEV_I2C_Write_Byte(uint8_t i2c_num, uint8_t addr, uint8_t value) {
  TwoWire *i2c = 0;
  if (i2c_num == 0) {
    i2c = &Wire;
  } else if (i2c_num == 1) {
    i2c = &Wire1;
  }
  //
  i2c->beginTransmission(addr);
  i2c->write(value);
  i2c->endTransmission();
}
void DEV_I2C_Write_nByte(uint8_t i2c_num, uint8_t addr, uint8_t *pData, uint32_t len) {
  TwoWire *i2c = 0;
  if (i2c_num == 0) {
    i2c = &Wire;
  } else if (i2c_num == 1) {
    i2c = &Wire1;
  }
  //
  i2c->beginTransmission(addr);
  for (; len > 0; len--) {
    i2c->write(*pData++);
  }
  i2c->endTransmission();
}

void DEV_I2C_Write_Reg_Byte(uint8_t i2c_num, uint8_t addr, uint8_t reg, uint8_t value) {
  TwoWire *i2c = 0;
  if (i2c_num == 0) {
    i2c = &Wire;
  } else if (i2c_num == 1) {
    i2c = &Wire1;
  }
  //
  i2c->beginTransmission(addr);
  i2c->write(reg);
  i2c->write(value);
  i2c->endTransmission();
}
void DEV_I2C_Write_Reg_nByte(uint8_t i2c_num, uint8_t addr, uint8_t reg, uint8_t *pData, uint32_t len)
{
  TwoWire *i2c = 0;
  if (i2c_num == 0) {
    i2c = &Wire;
  } else if (i2c_num == 1) {
    i2c = &Wire1;
  }
  //
  i2c->beginTransmission(addr);
  i2c->write(reg);
  for (; len > 0; len--) {
    i2c->write(*pData++);
  }
  i2c->endTransmission();  
}

uint8_t DEV_I2C_Read_Byte(uint8_t i2c_num, uint8_t addr)
{
  TwoWire *i2c = 0;
  if (i2c_num == 0) {
    i2c = &Wire;
  } else if (i2c_num == 1) {
    i2c = &Wire1;
  }
  //
  i2c->requestFrom(addr, 1);
  return i2c->read();  
}
void DEV_I2C_Read_nByte(uint8_t i2c_num, uint8_t addr, uint8_t *pData, uint32_t len)
{
   TwoWire *i2c = 0;
  if (i2c_num == 0) {
    i2c = &Wire;
  } else if (i2c_num == 1) {
    i2c = &Wire1;
  }
  i2c->requestFrom(addr, len);
  for (; len > 0; len--) {
    *pData = i2c->read();
    pData++;
  }  
}

uint8_t DEV_I2C_Read_Reg_Byte(uint8_t i2c_num, uint8_t addr, uint8_t reg)
{
  TwoWire *i2c = 0;
  if (i2c_num == 0) {
    i2c = &Wire;
  } else if (i2c_num == 1) {
    i2c = &Wire1;
  }
  //
  i2c->beginTransmission(addr);
  i2c->write(reg);
  i2c->endTransmission();
  i2c->requestFrom(addr, 1);
  return i2c->read();    
}
void DEV_I2C_Read_Reg_nByte(uint8_t i2c_num, uint8_t addr, uint8_t reg, uint8_t *pData, uint32_t len)
{
  TwoWire *i2c = 0;
  if (i2c_num == 0) {
    i2c = &Wire;
  } else if (i2c_num == 1) {
    i2c = &Wire1;
  }
  //
  i2c->beginTransmission(addr);
  i2c->write(reg);
  i2c->endTransmission();
    i2c->requestFrom(addr, len);
  for (; len > 0; len--) {
    *pData = i2c->read();
    pData++;
  }   
}

/******************************************************************************
function:	Module Initialize, the library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
uint8_t DEV_ModuleInit(void) {
  //usb cdc init
  Serial.begin(115200);
  //i2c0 init
  Wire.setClock(100000);
  Wire.setSDA(8);
  Wire.setSCL(9);
	Wire.begin();
  //i2c1 init
  Wire1.setClock(1000000);
  Wire1.setSDA(6);
  Wire1.setSCL(7);
	Wire1.begin();
  
  return 0;
}

/******************************************************************************
function:	Module exits, closes SPI and BCM2835 library
parameter:
Info:
******************************************************************************/
void DEV_ModuleExit(void) {
}

//
// OLED Interface
//

/********************************************************************************
  function: System Init and exit
  note:
  Initialize the communication method
********************************************************************************/
uint8_t System_Init(void)
{

  //set Serial
  Serial.begin(115200);
  Wire1.setClock(2000000);
  Wire1.setSDA(6);
  Wire1.setSCL(7);
  Wire1.begin();


  return 0;

}

void I2C1_Write_Byte(uint8_t Cmd,uint8_t value)
{
  uint8_t Addr = 0x3d;
  Wire1.beginTransmission(Addr);
  Wire1.write(Cmd);
  Wire1.write(value);
  Wire1.endTransmission();
}

void I2C1_Write_nByte_data(uint8_t Cmd,const uint8_t* pdata,uint16_t len)
{
  uint8_t Addr = 0x3d;
  Wire1.beginTransmission(Addr);
  Wire1.write(Cmd);
  for(;len>0;len--)
  {
    Wire1.write(*pdata++);
    if(len%(0xff) == 0)
    {
      Wire1.endTransmission();
      // Driver_Delay_ms(1);
      Wire1.beginTransmission(Addr);
      Wire1.write(Cmd);
    }
            
  }
  Wire1.endTransmission();
}

/********************************************************************************
  function: Delay function
  note:
  Driver_Delay_ms(xms) : Delay x ms
  Driver_Delay_us(xus) : Delay x us
********************************************************************************/
void Driver_Delay_ms(unsigned long xms)
{
  delay(xms);
}

void Driver_Delay_us(int xus)
{
  for (int j = xus; j > 0; j--);
}
