const int PICO_LED = 25; //GP25

void setup() {
  //内蔵LEDのピンを出力モードにする
  pinMode(PICO_LED, OUTPUT);
}

void loop() {
  //LEDを点灯する（電圧をHIGHにする）
  digitalWrite(PICO_LED, HIGH);
  //1秒（1000ミリ秒）待機
  delay(1000);

  //LEDを消灯する（電圧をLOWにる）
  digitalWrite(PICO_LED, LOW);      
  //1秒（1000ミリ秒）待機
  delay(1000);
}
