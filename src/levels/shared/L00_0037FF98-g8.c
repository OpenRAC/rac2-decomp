#include "common.h"

extern unsigned char *D_L00_001B1E9C;
/* This mutable end pointer has absolute reads and GP-relative delay-slot reads. */
extern unsigned char *D_L00_001B1EA4 MACRO_ADDR;
extern unsigned char *g_collected_objects[] __attribute__((sda));

/* Collect up to sixteen objects of class 0x135F and clear unused table slots. */
void CollectClass135FObjects(void)
{
    unsigned char *cursor = D_L00_001B1E9C;
    int count = 0;

    while ((unsigned int)cursor <= (unsigned int)D_L00_001B1EA4) {
        if (*(short *)(cursor + 0xAA) == 0x135F /* moby class 4959 */) {
            g_collected_objects[count++] = cursor;
            if (count >= 16)
                break;
        }
        cursor += 0x100;
    }
    while (count < 16)
        g_collected_objects[count++] = 0;
}
