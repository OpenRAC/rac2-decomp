#include "include_asm.h"
#include "common.h"

typedef struct {
    u8 pad00[0x34];
    u16 flags;
    u8 pad36[0x68 - 0x36];
    u32 p68;
    u8 pad6C[0xAA - 0x6C];
    s16 type;
} Mob_L11_0030F060;

typedef struct {
    u8 pad00[0x30];
    s32 mode;
    u8 pad34[0x44 - 0x34];
    s16 count;
    u8 pad46[0x18C - 0x46];
    Mob_L11_0030F060 *mobs[1];
} MobList_L11_0030F060;

extern MobList_L11_0030F060 ref_L11_0030F060_00;

/* sda in this -G0 unit gives the bare-symbol load, as in func_US2_L14_00305238. */
extern int D_001A79F0 __attribute__((sda));

extern void func_L00_002FC980(void);

extern void func_US2_002E72D8(void *);

extern void func_L00_00326048(void *, void *, int, int, float);

extern void func_L00_002E6CF0(void *, void *);

extern void func_L11_0030ED58(void *);

/* func_US2_L11_0030FC28, the USA v2.00 copy of func_L11_0030F060: the same C, where the 0xFA0 mobs' call
   is skipped in game state 0x33, func_002E64A0 becomes func_US2_002E72D8, and the mob pointer is read as
   base + i * 4 + 0x18C rather than ref_L11_0030F060_00.mobs[i], as in func_US2_L14_00305238. */
void func_US2_L11_0030FC28(void) {
    int i;

    func_L00_002FC980();
    for (i = 0; i < ref_L11_0030F060_00.count; i++) {
        Mob_L11_0030F060 *mob = ((MobList_L11_0030F060 *)((u8 *)&ref_L11_0030F060_00 + i * 4))->mobs[0];

        if (mob != 0 && mob->type == 0xE29)
            mob->flags |= 0x800;
        if (mob->type == 0xD54)
            func_US2_002E72D8(mob);
        if (mob != 0 && mob->type == 0xFA0 && D_001A79F0 != 0x33 && mob->p68 != 0)
            func_L00_00326048(mob, (u8 *)mob->p68 + 0xC, 0x80AAAAD2, 0x80396464, 0.061086535f);
    }
    if (D_001A79F0 == 0xB && ref_L11_0030F060_00.mode == 2)
        func_L00_002E6CF0(func_L11_0030ED58, 0);
}
