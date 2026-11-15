#include "include_asm.h"
#include "names.h"

typedef unsigned int u32;

/* The slot: sixteen bytes of state, then the callback the level installs. */
typedef struct Slot_r002F6B90 {
    char pad_00[0x10];
    void (*f10)(struct Slot_r002F6B90 *);
    char pad_14[0x7C];
} Slot_r002F6B90;

extern Slot_r002F6B90 D_L00_0027DD00[];

/* Runs the callback the slot at D_L00_0027DD00[a0 & 0xF] holds, and answers whether it
   had one: the callback takes the slot itself, so the pointer stays live across the
   call, as the retail keeps it in $a0 while the callback sits in $v0. */
int level_run_slot_callback(u32 slot_index)
{
    Slot_r002F6B90 *p = &D_L00_0027DD00[slot_index & 0xF];
    int r = 0;

    if (p != 0 && p->f10 != 0) {
        p->f10(p);
        r = 1;
    }
    return r;
}
