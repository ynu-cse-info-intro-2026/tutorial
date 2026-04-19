#define SOUND_AOUT_Pin (28)

void setup() {
  Serial.begin(115200);
}

void loop() {
  float adc_voltage = 0;
  uint16_t adc_read_raw = analogRead(SOUND_AOUT_Pin);

  // シリアルプロッタ向けの出力形式：「ラベル名:数値」
  Serial.print("Light:");
  Serial.println(adc_read_raw);

  delay(30);
}
