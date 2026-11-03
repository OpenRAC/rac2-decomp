#include "include_asm.h"

/* One-shot trigger: on the first update it marks the object initialised; once the level's
   counter reaches 14 while the current level (0x1A79F0) is 16, it sets the resident flag at
   0x1A7A6B, makes the two calls RAC2's other copies of this one-shot make, and sets 0x1A903C.
   Built with -mno-split-addresses: retail keeps the absolute loads and stores as assembler
   macros (stores through $at). The counter is small data, so the copy reorg places in the
   first branch's delay slot is gp-relative while the fall-through load stays absolute. */

extern int D_L02_001A9048 __attribute__((sda));
extern int D_001A79F0 __attribute__((sda));
extern unsigned char D_001A7A6B __attribute__((nosda));
extern int D_L02_001A903C __attribute__((sda));

extern int func_002E5E58(int, int, void *);
extern void func_002B0A18(int, int);

struct TriggerState {
    unsigned char pad00[0x20];
    unsigned char initialized;
    unsigned char pad21[15];
    unsigned char state;
};

void func_L02_00389F70(struct TriggerState *self) {
    if (self->initialized == 0) {
        self->state = 0xFF;
        self->initialized = 1;
    }
    if (D_L02_001A9048 < 14)
        return;
    if (D_001A79F0 != 16)
        return;
    if (D_001A7A6B != 0)
        return;
    D_001A7A6B = 1;
    func_002E5E58(1, 0, 0);
    func_002B0A18(0x1233, -1);
    D_L02_001A903C = 1;
}
