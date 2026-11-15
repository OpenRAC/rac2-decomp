#include "include_asm.h"
#include "common.h"

typedef struct { char pad[0x34]; unsigned short flags; char pad2[0x68 - 0x36]; float **health; char pad3[0x100 - 0x6C]; } Moby;
extern unsigned short *D_L10_001FB1E0[];
extern Moby *D_L10_001B251C MACRO_ADDR;

/* Counts how many mobys in the same group are still alive. */
int func_L10_0037D200(u8 *self) {
    unsigned short *list = D_L10_001FB1E0[self[0x21]];
    unsigned short *entry;
    Moby *object;
    float *health;
    int count = 0;
    if (!list) return 0;
    entry = list;
    do {
        object = (Moby *)((*entry & 0x7FFF) * 0x100 + (int)D_L10_001B251C);
        if (object->flags & 0x20) {
            health = *object->health;
            if (health && *health > 0.0f) count++;
        }
    } while (*(short *)(entry++) >= 0);
    return count;
}
