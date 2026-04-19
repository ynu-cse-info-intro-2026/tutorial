#define VOL_AOUT_Pin (27)

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  float adc_voltage = 0;
  uint16_t adc_read_raw = analogRead(VOL_AOUT_Pin);
  adc_voltage = adc_read_raw * 3.3 / 1024.0;
  Serial.printf("/***********************************/ \r\n");
  Serial.printf("VOL ADC TEST \r\n");
  Serial.printf("VOL_AOUT_Pin Raw Data = %d ,Voltage = %.2fV\r\n", adc_read_raw, adc_voltage);
  delay(250);
}
