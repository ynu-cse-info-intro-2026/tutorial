#include "hardware/dma.h" // RP2040のDMAハードウェアAPIを使用

#define DATA_SIZE 10000 // 1万個のデータ(40KB)を転送する

uint32_t src_data[DATA_SIZE];     // 転送元データ
uint32_t dst_cpu[DATA_SIZE];      // CPUコピー用の転送先
uint32_t dst_dma[DATA_SIZE];      // DMA転送用の転送先

uint32_t cpu_time;  // CPU転送時間
uint32_t dma_time;  // DMA転送時間

void setup() {
  Serial.begin(115200);
  delay(3000); // シリアルモニタを開くまでの猶予時間

  // 転送元データの初期化
  for (int i = 0; i < DATA_SIZE; i++) {
    src_data[i] = i;
  }

  Serial.println("--- 転送速度の比較テスト ---");

  // ==========================================
  // 1. CPU (forループ) によるデータ転送
  // ==========================================
  noInterrupts(); // 割込みに邪魔されないよう割込み禁止にする
  uint32_t start_time = micros(); // 開始時間(マイクロ秒)
  for (int i = 0; i < DATA_SIZE; i++) {
    dst_cpu[i] = src_data[i];
  }
  cpu_time = micros() - start_time;
  interrupts(); // 割込み禁止を解除する

  // ==========================================
  // 2. DMA によるデータ転送
  // ==========================================
  // 空いているDMAチャンネルを取得
  int dma_chan = dma_claim_unused_channel(true);
  dma_channel_config c = dma_channel_get_default_config(dma_chan);
  
  // DMAの設定（32ビット単位で転送，読み書きのアドレスを自動増加）
  channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
  channel_config_set_read_increment(&c, true);
  channel_config_set_write_increment(&c, true);

  noInterrupts(); // 割込みに邪魔されないよう割込み禁止にする
  start_time = micros(); // 開始時間(マイクロ秒)
  dma_channel_configure(
    dma_chan,          // チャンネル
    &c,                // 設定
    dst_dma,           // 書き込み先アドレス
    src_data,          // 読み込み元アドレス
    DATA_SIZE,         // 転送する要素数
    true               // 設定後，すぐに転送開始
  );

  // 本来はここでCPUは別の処理ができるが，今回は時間計測のため転送完了を待つ
  dma_channel_wait_for_finish_blocking(dma_chan); 
  dma_time = micros() - start_time;
  interrupts(); // 割込み禁止を解除する
  
  // リソースの解放
  dma_channel_unclaim(dma_chan);
}

void loop() {// メインループは何もしない
  Serial.printf("CPU: %lu [us] DMA: %lu [us]\n", cpu_time, dma_time);
  delay(1000);
}
