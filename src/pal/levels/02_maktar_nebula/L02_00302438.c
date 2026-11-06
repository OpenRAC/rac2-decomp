#include "include_asm.h"
#include "common.h"

typedef struct {
    u8 pad00[0x34];
    u16 flags;
    u8 pad36[0x68 - 0x36];
    u32 p68;
    u8 pad6C[0xAA - 0x6C];
    s16 type;
} L02_Mob;

typedef struct {
    u8 pad00[0x30];
    s32 mode;
    u8 pad34[0x44 - 0x34];
    s16 count;
    u8 pad46[0x18C - 0x46];
    L02_Mob *mobs[1];
} L02_MobList;

extern L02_MobList D_L02_001BE200;

/* sda in this -G0 unit gives the bare-symbol load: retail has it as `lui`/`lw` after the loop and,
   as the filler of the first branch's delay slot, as the one-instruction `$gp` form gas makes of
   it there. */
extern int D_001A79F0 __attribute__((sda));

extern void func_L00_002FC980(void);

extern void func_002E64A0(void *);

extern void func_L00_00326048(void *, void *, int, int, float);

extern void func_L00_002E6CF0(void *, void *);

extern void func_PAL_L02_00302438(void *);

/* func_PAL_L02_00302948, the PAL copy of func_L02_00300CE8: the same C, where the 0xFA0 mobs' call
   is skipped in game state 0x33 and its float argument scales by 6/5. The mob pointer is read as
   base + i * 4 + 0x18C rather than D_L02_001BE200.mobs[i]: without a separate base + 0x18C in the
   loop, loop.c's first pass still hoists 0xFA0 (ahead of the pointer's giv) and leaves 0x33 to the
   second pass, the order retail has. */
void func_PAL_L02_00302948(void) {
    int i;

    func_L00_002FC980();
    for (i = 0; i < D_L02_001BE200.count; i++) {
        L02_Mob *mob = ((L02_MobList *)((u8 *)&D_L02_001BE200 + i * 4))->mobs[0];

        if (mob != 0 && mob->type == 0xE29)
            mob->flags |= 0x800;
        if (mob->type == 0xD54)
            func_002E64A0(mob);
        if (mob != 0 && mob->type == 0xFA0 && D_001A79F0 != 0x33 && mob->p68 != 0)
            func_L00_00326048(mob, (u8 *)mob->p68 + 0xC, 0x80AAAAD2, 0x80396464, 0.07330384f);
    }
    if (D_001A79F0 == 2 && D_L02_001BE200.mode == 2)
        func_L00_002E6CF0(func_PAL_L02_00302438, 0);
}
