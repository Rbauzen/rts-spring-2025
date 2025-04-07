struct Pulse {
  byte pin;
  unsigned long interval;
  unsigned long lastToggle;
  bool state;
  bool useMicros;
};

Pulse pulses[] = {
  {3, 10, 0, LOW, false}, // 10 мс
  {5, 1, 0, LOW, false},  // 1 мс
  {6, 500, 0, LOW, true},    // 500 мкс
  {9, 100, 0, LOW, true},    // 100 мкс
  {10, 50, 0, LOW, true}     // 50 мкс
};

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(pulses[i].pin, OUTPUT);
  }
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long currentMicros = micros();

  for (int i = 0; i < 5; i++) {
    unsigned long now = pulses[i].useMicros ? currentMicros : currentMillis;

    if (now - pulses[i].lastToggle >= pulses[i].interval) {
      pulses[i].lastToggle = now;
      pulses[i].state = !pulses[i].state;
      digitalWrite(pulses[i].pin, pulses[i].state);
    }
  }
}
