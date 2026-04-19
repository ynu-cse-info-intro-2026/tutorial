const int LED_PIN = LED_BUILTIN;
bool ledState = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); 
}

void loop() {
  if (BOOTSEL) { 
    // トグル動作
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
}