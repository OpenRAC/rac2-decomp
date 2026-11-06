#include "include_asm.h"
#include "common.h"

typedef struct {
    u8 pad00[0x34];
    u16 flags;
    u8 pad36[0x68 - 0x36];
    u32 p68;
    u8 pad6C[0xAA - 0x6C];
    s16 type;
} Mob_L14_00304588;

typedef struct {
    u8 pad00[0x30];
    s32 mode;
    u8 pad34[0x44 - 0x34];
    s16 count;
    u8 pad46[0x18C - 0x46];
    Mob_L14_00304588 *mobs[1];
} MobList_L14_00304588;

extern MobList_L14_00304588 ref_L14_00304588_00;

/* sda in this -G0 unit gives the bare-symbol load: retail has it as `lui`/`lw` in the loop and after
   it and, as the filler of the first branch's delay slot, as the one-instruction `$gp` form gas
   makes of it there. */
extern int D_001A79F0 __attribute__((sda));

extern void func_L00_002FC980(void);

extern void func_002E64A0(void *);

extern void func_L00_00326048(void *, void *, int, int, float);

extern void func_L08_0037E6D8(void);

extern void func_L03_00326458(int);

/* func_PAL_L14_00306108, the PAL copy of func_L14_00304588: the same C, where the 0xFA0 mobs' call
   is skipped in game state 0x33 and its float argument scales by 6/5. As in func_PAL_L02_00302948,
   the mob pointer is read as base + i * 4 + 0x18C rather than ref_L14_00304588_00.mobs[i]. */
void func_PAL_L14_00306108(void) {
    int i;

    func_L00_002FC980();
    for (i = 0; i < ref_L14_00304588_00.count; i++) {
        Mob_L14_00304588 *mob = ((MobList_L14_00304588 *)((u8 *)&ref_L14_00304588_00 + i * 4))->mobs[0];

        if (mob != 0 && mob->type == 0xE29)
            mob->flags |= 0x800;
        if (mob->type == 0xD54)
            func_002E64A0(mob);
        if (mob != 0 && mob->type == 0xFA0 && D_001A79F0 != 0x33 && mob->p68 != 0)
            func_L00_00326048(mob, (u8 *)mob->p68 + 0xC, 0x80AAAAD2, 0x80396464, 0.07330384f);
    }
    if (D_001A79F0 == 0xE && ref_L14_00304588_00.mode == 0) {
        func_L08_0037E6D8();
        func_L03_00326458(*(int *)((char *)&ref_L14_00304588_00 + 0x194));
    }
}
