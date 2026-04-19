#include "Wire.h"
#include "QMI8658.h"

void setup() {
  Serial.begin(115200);

  Wire.setClock(100000);
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.begin();

  QMI8658_init();
}

void loop() {
  float acc[3], gyro[3];
  unsigned int tim_count = 0;

  QMI8658_read_xyz(acc, gyro, &tim_count);

  Serial.printf("\r\n\r\n/**************************************************/\r\n", tim_count);
  Serial.printf("acc_x   = %4.3fmg , acc_y  = %4.3fmg , acc_z  = %4.3fmg\r\n", acc[0], acc[1], acc[2]);
  Serial.printf("gyro_x  = %4.3fdps, gyro_y = %4.3fdps, gyro_z = %4.3fdps\r\n", gyro[0], gyro[1], gyro[2]);
  Serial.printf("tim_count = %d\r\n", tim_count);

  delay(100);
}
