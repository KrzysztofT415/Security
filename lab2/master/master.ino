int LED_PIN = 13;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.write('1');
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  Serial.write('0');
  delay(1000);
}
