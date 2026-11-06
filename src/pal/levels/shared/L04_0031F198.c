#include "include_asm.h"
/* func_PAL_L04_0031F198, the PAL copy of func_L04_0031D630: the same C, where the alpha becomes
   0.07330384f and the type 0xFA0 test also needs D_PAL_001A7A78 != 0x33. */
#include "common.h"

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

/* the list of mobs: every level has it at its own address */
extern MobListStruct ref_L04_0031D630_00;

extern int D_PAL_001A7A78 MACRO_ADDR;

extern void func_L00_002FC980(void);
extern void func_PAL_002E7270(void *mob);
extern void func_L00_00326048(void *mob, void *p, s32 a2, s32 a3, f32 alpha);

/* Walks the list of mobs: the ones of type 0xE29 get the 0x800 flag, the ones of type
   0xD54 are handed to func_PAL_002E7270, and the ones of type 0xFA0 with a 0x68 pointer
   get that pointer's block (from +0xC) to func_L00_00326048, unless D_PAL_001A7A78 is 0x33. */
void func_PAL_L04_0031F198(void) {
    s32 i;

    func_L00_002FC980();
    for (i = 0; i < ref_L04_0031D630_00.count; i++) {
        MobListStruct *list = &ref_L04_0031D630_00;
        MobStruct *mob = (MobStruct *)*(list->mobs + i);

        if (mob != 0 && mob->type == 0xE29) {
            mob->flags |= 0x800;
        }
        if (mob->type == 0xD54) {
            func_PAL_002E7270(mob);
        }
        if (mob != 0 && mob->type == 0xFA0 && D_PAL_001A7A78 != 0x33 && mob->p68 != 0) {
            func_L00_00326048(mob, (void *)((u8 *)mob->p68 + 0xC), 0x80AAAAD2, 0x80396464, 0.07330384f);
        }
    }
}
