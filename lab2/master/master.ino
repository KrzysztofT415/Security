#include <IRremote.h>
#include <XxHash_arduino.h>
#include "a5.h"
#include "utils.h"

#define IR_LED_PIN 3

IRsend irsend;
A5register reg;
uint64_t frame = 0;
uint64_t key = 0;

void setup() {
    irsend.begin(IR_LED_PIN);
    Serial.begin(9600);
    Serial1.begin(9600);

    while (!Serial);

    // GET USER SECRET KEY
    Serial.print("Secret key: ");
    while (!Serial.available());
    String key_str = Serial.readStringUntil('\n');
    Serial.println(key_str);
    char key_hash[9];
    xxh32(key_hash, key_str.c_str());
    key = bytesToUint64(key_hash);
}

void loop() {
    // GET MESSAGE AND PAD IT
    Serial.print("\nMessage: ");
    while (!Serial.available());
    String message = Serial.readStringUntil('\n');
    Serial.println(message);
    while ((message.length() + 1) % 4) message += ' ';
    message += '\x1a';

    // PREPARE CIPHER KEY
    a5_key_setup(&reg, key, frame++);
    uint32_t cipher_key = a5_key_gen(&reg);
    Serial.print("Cipher_key: 0x");
    Serial.println(cipher_key, HEX);
    Serial1.println(cipher_key, HEX);

    // SEND ENCRYPTED MESSAGE
    Serial.println("Sending:");
    for (int i = 0; i < message.length(); i += 4) {
        uint32_t code = bytesToUint32const(message.substring(i, i + 4).c_str());
        Serial.print("\t");
        Serial.print(message.substring(i, i + 4).c_str());
        Serial.print(" = 0x");
        Serial.print(code, HEX);

        code ^= cipher_key;
        Serial.print(" -> 0x");
        Serial.println(code, HEX);
        irsend.sendNEC(code, 32);
        delay(200);
    }
}