const int PICO_LED = 25; //GP25

void setup() {
  //内蔵LEDのピンを出力モードに設定
  pinMode(PICO_LED, OUTPUT);

  //※GPIOであれば，ここにボタンを入力と
  //して使うための設定（pinMode）が必要
}

void loop() {
  if (BOOTSEL) { //押されている場合
    // LEDを点灯
    digitalWrite(PICO_LED, HIGH);
  }
  else { //押されていない場合
    // LEDを消灯
    digitalWrite(PICO_LED, LOW); 
  }
}
