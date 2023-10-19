// Transmitter is sending signal, the part where he reads signals is addition to check if it is working

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

long prev = 0;
long timeout = 1000;
void loop() {
    // READ SIGNALS
    if (irrecv.decode()) {
        Serial.print("Received IR Data: 0x");
        uint32_t data = reverseBits(irrecv.decodedIRData.decodedRawData);
        Serial.println(data, HEX);
        irrecv.resume();
    }

    // TRANSMIT SIGNAL EVERY SECOND
    if ((long) (millis() - prev) > timeout) {
        prev = millis();
        unsigned long irCode = 0x4CB343BC;
        irsend.sendNEC(irCode, 32);
        Serial.print("Sent IR Code: 0x");
        Serial.println(irCode, HEX);
    }
}