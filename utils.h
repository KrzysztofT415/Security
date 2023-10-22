typedef unsigned long long int uint64_t;
typedef unsigned long int uint32_t;
typedef unsigned char byte_t;

uint32_t reverseBits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        result = (result << 1) | (n & 1);
        n >>= 1;
    }
    return result;
}

void printBinary64(uint64_t v) {
    for (uint64_t m = (uint64_t) 1 << 63; m; m >>= 1)
        Serial.print(char('0' + !!(v & m)));
    Serial.println();
}

void printBinary32(uint32_t v) {
    for (uint32_t m = (uint32_t) 1 << 31; m; m >>= 1)
        Serial.print(char('0' + !!(v & m)));
    Serial.println();
}

uint64_t bytesToUint64(char* bytes) {
    uint64_t result = 0;
    for (int i = 7; i >= 0; i--)
        result |= (static_cast<uint64_t>(bytes[7 - i]) << (i * 8));
    return result;
}

uint32_t bytesToUint32(char* bytes) {
    uint32_t result = 0;
    for (int i = 3; i >= 0; i--)
        result |= (static_cast<uint32_t>(bytes[3 - i]) << (i * 8));
    return result;
}

uint32_t bytesToUint32const(const char* bytes) {
    uint32_t result = 0;
    for (int i = 3; i >= 0; i--)
        result |= (static_cast<uint32_t>(bytes[3 - i]) << (i * 8));
    return result;
}

String codeToUtf8(uint32_t code) {
    char utf8[5];
    utf8[0] = char((code & 0xFF000000) >> 24);
    utf8[1] = char((code & 0x00FF0000) >> 16);
    utf8[2] = char((code & 0x0000FF00) >> 8);
    utf8[3] = char(code & 0x000000FF);
    utf8[4] = '\0';
    return String(utf8);
}