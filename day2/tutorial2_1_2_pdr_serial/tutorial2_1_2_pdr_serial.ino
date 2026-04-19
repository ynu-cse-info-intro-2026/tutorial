#define LDR_AOUT_Pin (26)

void setup() {  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  uint16_t adc_read_raw = analogRead(LDR_AOUT_Pin);

  // シリアルプロッタ向けの出力形式：「ラベル名:数値」
  Serial.print("Light:");
  Serial.println(adc_read_raw);

  delay(50);
}
