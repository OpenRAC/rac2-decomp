#include "include_asm.h"

#include "common.h"
extern void part_spawn_masked_debris_pal(void *, int, void *, int, float, float, float, float);
extern void moby_mark_spawned(void *);
typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} Quad __attribute__((aligned(16)));

/* Waits for a trigger and then bursts out a small puff of debris and removes the object. */
void puff_update_pal(unsigned char *moby) {
    int state = moby[0x20];
    Quad puff;

    switch (state) {
    case 0:
        moby[0x20] = 1;
        break;
    case 1:
        if (moby[0xBC] != 0)
            moby[0x20] = 2;
        break;
    case 2:
        qzero(&puff);
        puff.f[2] = 0.18f;
        part_spawn_masked_debris_pal(moby, 0x7F, &puff, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        moby_mark_spawned(moby);
        break;
    }
}

