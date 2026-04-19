#define LED_Pin (10)

void setup() {
  Serial.begin(115200);
}

void loop() {
  uint16_t cnt;
  for (cnt = 0; cnt < 128; cnt++) {
    analogWrite(LED_Pin, 255 - (cnt << 1));
    delay(10);
  }
  for (cnt = 128; cnt > 0; cnt--) {
    analogWrite(LED_Pin, 255 - (cnt << 1));
    delay(10);
  }
}
