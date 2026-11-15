#include "common.h"

extern unsigned char *D_L00_001B1E9C;
/* This mutable end pointer has absolute reads and GP-relative delay-slot reads. */
extern unsigned char *D_L00_001B1EA4 MACRO_ADDR;
extern unsigned char *D_L00_001B26B8[] __attribute__((sda));

/* Collect up to sixteen objects of class 0x135F and clear unused table slots. */
void func_L00_0037FF98(void)
{
    unsigned char *cursor = D_L00_001B1E9C;
    int count = 0;

    while ((unsigned int)cursor <= (unsigned int)D_L00_001B1EA4) {
        if (*(short *)(cursor + 0xAA) == 0x135F /* moby class 4959 */) {
            gClass135FObjects[count++] = cursor;
            if (count >= 16)
                break;
        }
        cursor += 0x100;
    }
    while (count < 16)
        gClass135FObjects[count++] = 0;
}
