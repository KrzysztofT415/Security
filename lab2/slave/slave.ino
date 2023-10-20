int LED_PIN = 13;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
    if (Serial.available()) {
        char data_rcvd = Serial.read();
        if (data_rcvd == '1') digitalWrite(LED_PIN, HIGH);
        if (data_rcvd == '0') digitalWrite(LED_PIN, LOW);
    }
}

