const int BUTTON_PIN = 3;  // スイッチは GP3
const int LED_PIN = 10;    // LEDは GP10

void setup() {
  pinMode(LED_PIN, OUTPUT); // LEDを繋いだGP10ピンを「出力モード」に
  pinMode(BUTTON_PIN, INPUT_PULLUP); // スイッチを繋いだGP3ピンを「入力モード（内部プルアップ有効）」に設定
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN); // スイッチの状態
  if (buttonState == HIGH) {               // スイッチが「押されていない」
    digitalWrite(LED_PIN, HIGH);           // LEDを消灯
  } else {                                 // スイッチが「押された」
    digitalWrite(LED_PIN, LOW);            // LEDを点灯
  }
}

