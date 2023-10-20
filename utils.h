typedef unsigned long long int uint64_t;

uint64_t reverseBits(uint64_t n) {
    uint64_t result = 0;
    for (int i = 0; i < 32; i++) {
        result = (result << 1) | (n & 1);
        n >>= 1;
    }
    return result;
}

void print_bin(uint64_t v) {
    for (uint64_t m = (uint64_t) 1 << 63; m; m >>= 1)
        putchar('0' + !!(v & m));
    putchar('\n');
}