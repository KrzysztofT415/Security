#include <IRremote.h>
#include "utils.h"

#define IR_RECEIVER_PIN 2

IRrecv irrecv(IR_RECEIVER_PIN);
uint32_t key = 0;
String message = "";

void setup() {
    irrecv.enableIRIn();
    Serial.begin(9600);
    Serial1.begin(9600);

    while (!Serial);
}

void loop() {
    if (!key) {
        while (!Serial1.available());
        String key_str = Serial1.readStringUntil('\n');
        key = strtoul(key_str.c_str(), NULL, 16);
        Serial.print("Key from UART: 0x");
        Serial.println(key, HEX);
        Serial.println("Received:");
        message = "";
    }

    if (irrecv.decode()) {
        uint32_t data = reverseBits(irrecv.decodedIRData.decodedRawData);
        Serial.print("\t0x");
        Serial.print(data, HEX);

        data ^= key;
        Serial.print(" -> 0x");
        Serial.print(data, HEX);
        Serial.print(" = ");
        String chunk = codeToUtf8(data);
        Serial.println(chunk);
        message += chunk;

        if (chunk[3] == '\x1a') {
            key = 0;
            Serial.println("Decoded: " + message);
            Serial.println();
        }
        irrecv.resume();
    }
}

