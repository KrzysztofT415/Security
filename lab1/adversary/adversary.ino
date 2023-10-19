// Adversary duplicates every signal

#include <IRremote.h>

#define IR_LED_PIN 3
#define IR_RECEIVER_PIN 2

IRsend irsend;
IRrecv irrecv(IR_RECEIVER_PIN);

decode_results results;

void setup() {
  irsend.begin(IR_LED_PIN);
  irrecv.enableIRIn();

  Serial.begin(9600);
}

void loop() {
    if (irrecv.decode(&results)) {
        Serial.print("Received IR Data: 0x");
        Serial.println(results.value, HEX);

        irsend.sendNEC(results.value, 32);

        irrecv.resume();
    }
}