#include "common.h"

typedef struct {
    unsigned char pad00[0x34];
    unsigned short flags;
    unsigned char pad36[0x68 - 0x36];
    unsigned int p68;
    unsigned char pad6C[0xAA - 0x6C];
    short type;
} Mob_PAL_L09_002FAA98;

typedef struct {
    unsigned char pad00[0x30];
    int mode;
    unsigned char pad34[0x44 - 0x34];
    short count;
    unsigned char pad46[0x18C - 0x46];
    Mob_PAL_L09_002FAA98 *mobs[1];
} MobList_PAL_L09_002FAA98;

extern MobList_PAL_L09_002FAA98 ref_L09_002F8FD8_00;
extern int D_001A79F0 __attribute__((sda));
extern void func_L00_002FC980(void);
extern void func_PAL_002E7270(void *);
extern void func_L00_00326048(void *, void *, int, int, float);
extern void func_L00_002E6CF0(void *, void *);
extern void func_PAL_L09_002FA660(void *);

/* func_PAL_L09_002FAA98, the PAL copy of func_L09_002F8FD8: the same C, with a game-state
   test before the 0xFA0 mob's call and its angle 0.0610865355f becoming 0.07330384f. */
void func_PAL_L09_002FAA98(void) {
    int i;

    func_L00_002FC980();
    for (i = 0; i < ref_L09_002F8FD8_00.count; i++) {
        Mob_PAL_L09_002FAA98 *mob = ref_L09_002F8FD8_00.mobs[i];

        if (mob != 0 && mob->type == 0xE29)
            mob->flags |= 0x800;
        if (mob->type == 0xD54)
            func_PAL_002E7270(mob);
        if (mob != 0) {
            int class_id = 0xFA0;

            if (mob->type == class_id && D_001A79F0 != 0x33 && mob->p68 != 0)
                func_L00_00326048(mob, (unsigned char *)mob->p68 + 0xC, 0x80AAAAD2, 0x80396464, 0.07330384f);
        }
    }
    if (D_001A79F0 == 9 && ref_L09_002F8FD8_00.mode == 1)
        func_L00_002E6CF0(func_PAL_L09_002FA660, *(void **)((char *)&ref_L09_002F8FD8_00 + 0x194));
}
