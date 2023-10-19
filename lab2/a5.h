#ifndef __A5__
#define __A5__


typedef unsigned char byte;
typedef unsigned long my_word;
typedef my_word bit;


void run_key_gen(byte AtoBkeystream[], byte BtoAkeystream[]);
void key_setup(byte key[8], my_word frame);

#endif