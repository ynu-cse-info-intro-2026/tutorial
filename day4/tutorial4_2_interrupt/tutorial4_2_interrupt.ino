const int BUTTON_PIN = 3;
const int LED_PIN = 10;
volatile bool ledState = false; // ISRで扱う変数にはvolatileをつける

volatile unsigned long lastInterruptTime = 0; //最後に割込み処理が実行された時間

// 割込みサービスルーチン(ISR)
void isr_button() {
  // 現在の時刻を取得 (ミリ秒)
  unsigned long currentTime = millis();

  // 前回の割込みから50ミリ秒以上経過している場合のみ有効
  if (currentTime - lastInterruptTime > 50) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);

    // 最後に処理した時刻を更新
    lastInterruptTime = currentTime;
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // ボタンが押された(HIGH->LOW)瞬間にisr_buttonを実行するよう登録
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), isr_button, FALLING);

  Serial.begin(115200);
}

void loop() {
  // CPUはボタン監視から解放され，別の処理に専念できる
  Serial.println("CPUは別の計算を実行中...");
  delay(1000); 
}
