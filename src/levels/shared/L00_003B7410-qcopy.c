#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

/* The record the level allocates: the first quadword copy lands at +0x10, the
   second in the sub-object the +0x68 field points to. */
typedef struct NODE {
    char pad0[0x8];
    int f08;
    int f0C;
    char pad1[0x24 - 0x10];
    int f24;
    int f28;
    int f2C;
    unsigned char f30;
    char pad2[0x40 - 0x31];
    int f40;
    char pad3[0x68 - 0x44];
    void *f68;
    char pad4[0xB8 - 0x6C];
    int fB8;
    unsigned char fBC;
} NODE;

/* The quadword copy profile (-frac2-qcopy -frac2-qcopy-barrier) keeps both
   addresses in registers and groups the lq/sq pairs, as the retail does. */
typedef int TI128 __attribute__((mode(TI)));

extern NODE *CreateMoby(int);

extern void moby_set_state(NODE *, unsigned char, int);

/* Allocates the record, copies the two sixteen-byte blocks into it (the first at
   +0x10, the second in the sub-object its +0x68 field points to), fills its
   three fields and calls the level's helper. */
void *pair_game_spawn_shot(char *owner, void *position, void *velocity, void *player)
{
    NODE *record = CreateMoby(0x88D /* moby class 2189 */);

    if (record != 0) {
        TI128 *dest = (TI128 *)((char *)record + 0x10);
        TI128 *src = (TI128 *)record->f68;

        record->fB8 = (int)owner;
        record->f30 = 0xFF;
        record->fBC = (unsigned char)player;
        *dest = *(TI128 *)position;
        *src = *(TI128 *)velocity;
        moby_set_state(record, 2, -1);
    }
    return record;
}
