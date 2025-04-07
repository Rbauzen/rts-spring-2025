volatile unsigned long lastTime = 0;
volatile unsigned long sumIntervals = 0;
volatile unsigned long sumSquares = 0;
volatile uint16_t count = 0;

const uint16_t totalSamples = 100;

void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT); // INT0
  attachInterrupt(digitalPinToInterrupt(3), capturePulse, CHANGE);
}

void loop() {
  if (count >= totalSamples) {
    noInterrupts();
    unsigned long total = sumIntervals;
    unsigned long totalSq = sumSquares;
    uint16_t samples = count;
    sumIntervals = 0;
    sumSquares = 0;
    count = 0;
    interrupts();

    float mean = total / float(samples);
    float variance = (totalSq / float(samples)) - (mean * mean);
    float stddev = sqrt(variance);

    Serial.print("Mean: ");
    Serial.print(mean, 3);
    Serial.print(" us, StdDev: ");
    Serial.print(stddev, 3);
    Serial.println(" us");
    Serial.println("-----------");
  }
}

void capturePulse() {
  unsigned long current = micros();
  if (lastTime != 0) {
    unsigned long interval = current - lastTime;
    sumIntervals += interval;
    sumSquares += (unsigned long)interval * (unsigned long)interval;
    count++;
  }
  lastTime = current;
}
