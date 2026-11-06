#include "include_asm.h"
#include "common.h"

/* func_US2_L04_0031E208, the USA v2.00 copy of func_L04_0031D630: the same C, where the mobs of
   type 0xFA0 are also skipped while D_001A79F0 is 0x33. The extra test lengthens the loop, so
   `type` holds 0xFA0 inside the null check: loop.c then finds that constant worth hoisting on
   its first pass, ahead of the base-pointer giv, and 0x33 only on its second. */
typedef struct {
    u8 pad00[0x34];
    u16 flags;
    u8 pad36[0x68 - 0x36];
    u32 p68;
    u8 pad6C[0xAA - 0x6C];
    s16 type;
} MobStruct;

typedef struct {
    u8 pad00[0x44];
    s16 count;
    u8 pad46[0x18C - 0x46];
    u32 mobs[1];          /* the array the count field bounds */
} MobListStruct;

/* the list of mobs: level 04 has it at 0x001BD3C0, every level at its own address */
extern MobListStruct ref_L04_0031D630_00;

extern s32 D_001A79F0 MACRO_ADDR;

/* shared callees, named by their catalogue rows */
extern void func_L00_002FC980(void);
extern void func_US2_002E72D8(void *mob);
extern void func_L00_00326048(void *mob, void *p, s32 a2, s32 a3, f32 alpha);

void func_US2_L04_0031E208(void) {
    s32 i;

    func_L00_002FC980();
    for (i = 0; i < ref_L04_0031D630_00.count; i++) {
        MobStruct *mob = (MobStruct *)ref_L04_0031D630_00.mobs[i];

        if (mob != 0 && mob->type == 0xE29) {
            mob->flags |= 0x800;
        }
        if (mob->type == 0xD54) {
            func_US2_002E72D8(mob);
        }
        if (mob != 0) {
            s32 type = 0xFA0;

            if (mob->type == type && D_001A79F0 != 0x33 && mob->p68 != 0) {
                func_L00_00326048(mob, (void *)((u8 *)mob->p68 + 0xC), 0x80AAAAD2, 0x80396464, 0.0610865355f);
            }
        }
    }
}
