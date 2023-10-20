#include "a5.h"

// TESTING THERE
void setup() {}

void loop() {
    uint64_t reg = 0;
    uint64_t key = 0xCADFBFCAAEDDBFCA;
    uint64_t frame = 0xABADADDD;

    byte_t dl[4] = {0, 0, 0, 0};
    byte_t ul[4] = {0, 0, 0, 0};

    a5_key_setup(&reg, key, frame);
    a5_key_gen(&reg, dl, ul);

    // for (int i = 0; i < 15; i++) {
    //     encryptedData[i] = stream_cipher_key[i] ^ message[i];
    // }
}