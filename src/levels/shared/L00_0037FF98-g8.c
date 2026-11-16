#include "common.h"

extern unsigned char *g_moby_array_base;
/* This mutable end pointer has absolute reads and GP-relative delay-slot reads. */
extern unsigned char *g_moby_array_last MACRO_ADDR;
extern unsigned char *g_collected_objects[] __attribute__((sda));

/* Collect up to sixteen objects of class 0x135F and clear unused table slots. */
void CollectClass135FObjects(void)
{
    unsigned char *cursor = g_moby_array_base;
    int count = 0;

    while ((unsigned int)cursor <= (unsigned int)g_moby_array_last) {
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
