/* Spawn setup; the cached class-0xFBF moby is accessed through $gp. */
#include "common.h"

/* The parts of a moby this unit touches. */
typedef struct Moby_L05_00426568 {
    /* 0x00 */ char pad00[0x10];
    /* 0x10 */ float position[4];
    /* 0x20 */ char pad20[4];
    /* 0x24 */ char *pClass;
    /* 0x28 */ struct Moby_L05_00426568 *pChain;
    /* 0x2C */ float scale;
    /* 0x30 */ unsigned char updateDist;
    /* 0x31 */ unsigned char drawn;
    /* 0x32 */ short drawDist;
    /* 0x34 */ char pad34[0xAA - 0x34];
    /* 0xAA */ short oClass;
    /* 0xAC */ char padAC[0xF0 - 0xAC];
    /* 0xF0 */ float rot[4];
} Moby_L05_00426568;

/* The moby of class 0xFBF, found once (D_L05_001B1500 in the USA release; PAL places it elsewhere). */
extern Moby_L05_00426568 *ref_L05_00426568_0 __attribute__((sda));
/* The head of the moby list. */
extern Moby_L05_00426568 *D_L05_001B2528;

extern Moby_L05_00426568 *func_0029EFD0(int);
extern void func_00282C88(float *);
extern float func_002A7940(void);
extern void func_L05_00426810(Moby_L05_00426568 *);

Moby_L05_00426568 *func_L05_00426568(Moby_L05_00426568 *object)
{
    Moby_L05_00426568 *moby;
    Moby_L05_00426568 *m;

    moby = func_0029EFD0(0x117D);
    if (moby != 0) {
        moby->updateDist = 0xFF;
        moby->drawDist = 0xFF;
        moby->drawn = 1;
        qcopy(moby->position, object->position);
        func_00282C88(moby->rot);
        moby->rot[2] = func_002A7940();
        moby->scale = moby->scale * 0.5f;
        if (ref_L05_00426568_0 == 0) {
            for (m = D_L05_001B2528; m != 0; m = m->pChain) {
                if (m->oClass == 0xFBF)
                    ref_L05_00426568_0 = m;
            }
        }
        func_L05_00426810(moby);
        moby->scale = *(float *)(moby->pClass + 0x24);
        return moby;
    }
    return 0;
}
