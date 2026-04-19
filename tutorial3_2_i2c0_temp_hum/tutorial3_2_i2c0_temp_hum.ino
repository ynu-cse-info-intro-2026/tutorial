#include "Wire.h"

#define SHTC3_I2C_ADDR (0X70)
#define SHTC3_REG_WAKEUP                (0x3517)    // Wakeup mode
#define SHTC3_REG_NORMAL_T_F            (0x7866)    // Read T First And Clock Stretching Disabled In Normal Mode

void i2c_write_nbyte(uint8_t addr, uint8_t *pData, uint32_t len) {
  Wire.beginTransmission(addr);
  for (; len > 0; len--) {
    Wire.write(*pData++);
  }
  Wire.endTransmission();
}

void i2c_read_nbyte(uint8_t addr, uint8_t *pData, uint32_t len)
{
  while(Wire.requestFrom(addr, len) != len) {
    delay(1);
  }

  for (; len > 0; len--) {
    *pData = Wire.read();
    pData++;
  }  
}

void setup() {
  Serial.begin(115200);

  //i2c0 init
  Wire.setClock(100000);
  Wire.setSDA(8);
  Wire.setSCL(9);
	Wire.begin();

  // SHTC3 init
  uint8_t buffer[4] = { 0, 0, 0, 0 };
  i2c_write_nbyte(SHTC3_I2C_ADDR, buffer, 3); //  おまじない．不要？

  //  Wake up SHTC3
  buffer[0] = SHTC3_REG_WAKEUP >> 8;
  buffer[1] = SHTC3_REG_WAKEUP & 0xff;
  i2c_write_nbyte(SHTC3_I2C_ADDR, buffer, 2);

  delay(1);
}

void loop() {
  float temp, hum;
  uint8_t buffer[6];

  // Set read mode
  buffer[0] = SHTC3_REG_NORMAL_T_F >> 8;
  buffer[1] = SHTC3_REG_NORMAL_T_F & 0xff;
  i2c_write_nbyte(SHTC3_I2C_ADDR, buffer, 2);

  i2c_read_nbyte(SHTC3_I2C_ADDR, buffer, 6);
  temp = (((buffer[0] << 8) + buffer[1]) * 175.0) / (1 << 16) - 45;
  hum = (((buffer[3] << 8) + buffer[4]) * 100.0) / (1 << 16);

  Serial.printf("Temp=%f Hum=%f\n", temp, hum);

  delay(1000);
}
