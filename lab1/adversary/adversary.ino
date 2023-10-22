// Adversary duplicates every signal

#include <IRremote.h>
#include "utils.h"

#define IR_LED_PIN 3
#define IR_RECEIVER_PIN 2

IRsend irsend;
IRrecv irrecv(IR_RECEIVER_PIN);

void setup() {
    irsend.begin(IR_LED_PIN);
    irrecv.enableIRIn();

    Serial.begin(9600);
}

void loop() {
    if (irrecv.decode()) {
        Serial.print("Received IR Data: 0x");
        uint32_t data = reverseBits(irrecv.decodedIRData.decodedRawData);
        Serial.println(data, HEX);

        irsend.sendNEC(data, 32);

        irrecv.resume();
    }
}