#include "include_asm.h"
#include "names.h"

typedef unsigned int u32;
typedef int RecordTi16 __attribute__((mode(TI)));

extern u32 D_L04_001AC18C __attribute__((sda));

/* Claims the first free 80-byte record of the table (the one whose owner word at +0x48 is 0): copies the fields
   and the two 16-byte vectors of `source` into it and stores the owner. `tail` starts from the loaded pointer
   `base`, not from `cursor`: with `cursor + 16` the loop optimizer sees a biv that is a giv of `cursor` and drops
   its register, where retail keeps both counting by 80. The order of the four initialisations and of the three
   increments is retail's. */
/* Adds a new particle to the table by copying it into the first free slot. */
void func_002ED2B8(u32 owner, u32 source)
{
    u32 base;
    u32 cursor;
    u32 tail;
    u32 source_tail;
    int i;

    base = gEffectRecordTable;
    if (base == 0) {
        return;
    }
    i = 0;
    source_tail = source + 16;
    tail = base + 16;
    cursor = base;
    while (i < 512) {
        if (*(u32 *)(cursor + 0x48) == 0) {
            *(u32 *)(cursor + 0x38) = *(u32 *)(source + 0x38);
            *(u32 *)(cursor + 0x3C) = *(u32 *)(source + 0x3C);
            *(u32 *)(cursor + 0x30) = *(u32 *)(source + 0x30);
            *(u32 *)(cursor + 0x44) = *(u32 *)(source + 0x44);
            *(float *)(cursor + 0x24) = *(float *)(source + 0x24);
            *(float *)(cursor + 0x20) = *(float *)(source + 0x20);
            *(float *)(cursor + 0x28) = *(float *)(source + 0x28);
            *(u32 *)(cursor + 0x34) = *(u32 *)(source + 0x34);
            *(u32 *)(cursor + 0x2C) = *(u32 *)(source + 0x2C);
            *(u32 *)(cursor + 0x40) = *(u32 *)(source + 0x40);
            *(u32 *)(cursor + 0x4C) = *(u32 *)(source + 0x4C);
            *(RecordTi16 *)cursor = *(RecordTi16 *)source;
            *(RecordTi16 *)tail = *(RecordTi16 *)source_tail;
            *(u32 *)(cursor + 0x48) = owner;
            return;
        }
        i++;
        tail += 80;
        cursor += 80;
    }
}
