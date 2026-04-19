#define Buzzer_Pin (12)

int freqs[8] = {262, 294, 330, 349, 392, 440, 494, 523};

void setup() {
  pinMode(Buzzer_Pin, OUTPUT);

  delay(100);
  
  for (int i = 0; i < 8; i++)
  {
    tone(Buzzer_Pin, freqs[i], 500);
    delay(500);
  }
  for (int i = 0; i < 8; i++)
  {
    tone(Buzzer_Pin, freqs[7-i], 500);
    delay(500);
  }
}

void loop() {
}
