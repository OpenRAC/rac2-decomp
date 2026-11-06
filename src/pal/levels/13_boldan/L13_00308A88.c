#include "include_asm.h"

/* func_PAL_L13_00308A88, the PAL copy of func_L13_00306F38: the same C, where the 0xFA0 mobs
   are also skipped when the game state is 0x33 and the float argument is scaled 6/5 for 50 Hz.
   The new test adds three insns to the loop. The count read through `list` takes two back, so
   loop.c still hoists 0xFA0 on its first pass and 0x33 on its second, as retail does. */
typedef struct {
    unsigned char pad00[0x34];
    unsigned short flags;
    unsigned char pad36[0x68 - 0x36];
    unsigned int p68;
    unsigned char pad6C[0xAA - 0x6C];
    short type;
} Mob_L13_00306F38;

typedef struct {
    unsigned char pad00[0x30];
    int mode;
    unsigned char pad34[0x44 - 0x34];
    short count;
    unsigned char pad46[0x18C - 0x46];
    Mob_L13_00306F38 *mobs[1];
} MobList_L13_00306F38;

extern MobList_L13_00306F38 ref_L13_00306F38_00;
extern int D_001A79F0 __attribute__((sda));
extern void func_L00_002FC980(void);
extern void func_002E64A0(void *);
extern void func_L00_00326048(void *, void *, int, int, float);
typedef struct { unsigned char pad[0x7C]; short f7C; } Obj_L13_00306F38;

void func_PAL_L13_00308A88(void) {
    int i;

    func_L00_002FC980();
    i = 0;
    if (i < ref_L13_00306F38_00.count) {
        MobList_L13_00306F38 *list;

        do {
            Mob_L13_00306F38 *mob;

            list = &ref_L13_00306F38_00;
            mob = list->mobs[i];

            if (mob != 0 && mob->type == 0xE29)
                mob->flags |= 0x800;
            if (mob->type == 0xD54)
                func_002E64A0(mob);
            if (mob != 0 && mob->type == 0xFA0 && D_001A79F0 != 0x33 && mob->p68 != 0)
                func_L00_00326048(mob, (unsigned char *)mob->p68 + 0xC, 0x80AAAAD2, 0x80396464, 0.07330384f);
            i++;
        } while (i < list->count);
    }
    if (D_001A79F0 == 0xD) {
        switch (ref_L13_00306F38_00.mode) {
        case 0:
            (*(Obj_L13_00306F38 **)((char *)&ref_L13_00306F38_00 + 0x1A0))->f7C = 7;
            (*(Obj_L13_00306F38 **)((char *)&ref_L13_00306F38_00 + 0x1A4))->f7C = 7;
            break;
        case 1:
            (*(Obj_L13_00306F38 **)((char *)&ref_L13_00306F38_00 + 0x19C))->f7C = 7;
            (*(Obj_L13_00306F38 **)((char *)&ref_L13_00306F38_00 + 0x1A0))->f7C = 7;
            break;
        }
    }
}
