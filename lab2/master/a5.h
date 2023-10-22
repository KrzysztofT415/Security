#include <stdbool.h>

#define R1_MASK (((uint64_t) 1 << 19) - 1)
#define R2_MASK ((((uint64_t) 1 << 22 << 19) - 1) - R1_MASK)
#define R3_MASK (~(((uint64_t) 1 << 22 << 19) - 1))

#define R1_PAR ((uint64_t) 1 << 8)
#define R2_PAR ((uint64_t) 1 << 10 << 19)
#define R3_PAR ((uint64_t) 1 << 10 << 22 << 19)

#define R1_TAP ((uint64_t) 0b111001 << 13)
#define R2_TAP ((uint64_t) 0b11 << 20 << 19)
#define R3_TAP (((uint64_t) 0b111 << 13) + 1 << 7 << 22 << 19)

#define INPUT ((((uint64_t) 1 << 22) + 1 << 19) + 1)
#define OUTPUT ((((uint64_t) 1 << 23) + 1 << 22) + 1 << 18)

typedef bool bit_t;
typedef uint64_t A5register; 

bit_t parity(uint64_t x) {
    for (int s = 1 << 5; s; s >>= 1) x ^= x >> s;
    return x & 1;
}

bit_t getBit(uint64_t* reg) {
	return parity(*reg & OUTPUT);
}

void clockWhole(uint64_t* reg) {
    uint64_t tap = parity(*reg & R1_TAP);
    tap |= ((uint64_t) parity(*reg & R2_TAP) << 19);
    tap |= ((uint64_t) parity(*reg & R3_TAP) << 41);
	*reg = ((*reg << 1) & ~INPUT) | tap;
}

void clockMod(uint64_t* reg, uint64_t mask) {
	uint64_t save = *reg & mask;
    clockWhole(reg);
    *reg = (*reg & ~mask) | save;
}

void clock(uint64_t* reg) {
    int sum = (!!(*reg & R1_PAR) + !!(*reg & R2_PAR) + !!(*reg & R3_PAR));
	bit_t par = sum > 1;
    if (!sum || sum == 3) return clockWhole(reg);
	if (!!(*reg & R1_PAR) != par) return clockMod(reg, R1_MASK);
	if (!!(*reg & R2_PAR) != par) return clockMod(reg, R2_MASK);
	if (!!(*reg & R3_PAR) != par) return clockMod(reg, R3_MASK);
}

void a5_key_setup(uint64_t* reg, uint64_t key, uint64_t frame) {
	*reg = 0;

    for (int i = 0; i < 64; i++) {
		clockWhole(reg);
        if ((key >> i) & 1) *reg ^= INPUT;
	}

	for (int i = 0; i < 22; i++) {
		clockWhole(reg);
        if ((frame >> i) & 1) *reg ^= INPUT;
	}

	for (int i = 0; i < 100; i++) clock(reg);
}

uint32_t a5_key_gen(uint64_t* reg) {
    uint32_t key = 0;
	for (int i = 0; i < 32; i++) {
        clock(reg);
        key |= static_cast<uint32_t>(getBit(reg)) << i;
    }
    return key;
}

