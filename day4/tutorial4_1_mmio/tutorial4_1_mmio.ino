// LEDのピン番号
const int LED_PIN = 10;
const int BUTTON_PIN = 3;

// SIO_GPIO_IN レジスタのアドレス
volatile uint32_t *sio_gpio_in = (volatile uint32_t *)0xd0000004;

// SIO_GPIO_OUT レジスタのアドレス
volatile uint32_t *sio_gpio_out = (volatile uint32_t *)0xd0000010;

void setup() {
  pinMode(LED_PIN, OUTPUT);          // ピンの初期設定は標準関数を使用
  pinMode(BUTTON_PIN, INPUT_PULLUP); // ピンの初期設定は標準関数を使用
  delay(10);

  // LEDに0を書込む（点灯させる）
  *sio_gpio_out = (*sio_gpio_out) & (~(1 << LED_PIN));
}

void loop() {
  uint32_t button_status = (*sio_gpio_in) & (1 << BUTTON_PIN);
  if(!button_status) {
    // LEDの状態をトグルする
    *sio_gpio_out = (*sio_gpio_out) ^ (1 << LED_PIN);

    // チャタリング除去
    delay(50);
    while(true) {
      button_status = (*sio_gpio_in) & (1 << BUTTON_PIN);
      if(button_status)
        break;
    }
    delay(50);
  }
}
