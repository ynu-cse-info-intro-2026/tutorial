const int BUTTON_PIN = 3;
const int LED_PIN = 10;
volatile bool ledState = false; // ISRで扱う変数にはvolatileをつける

// 割込みサービスルーチン(ISR)
void isr_button() {
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
  delay(50);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  // ボタンが押された(HIGH->LOW)瞬間にisr_buttonを実行
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), isr_button, FALLING);
  Serial.begin(115200);
}

void loop() {
  // CPUはボタン監視から解放され，別の処理に専念できる
  Serial.println("CPUは別の計算を実行中...");
  delay(1000); 
}
