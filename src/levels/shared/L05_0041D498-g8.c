/* Spawn setup; the cached class-0xFBF moby is accessed through $gp. */
#include "common.h"

/* The parts of a moby this unit touches. */
typedef struct Moby_L05_0041D498 {
    /* 0x00 */ char pad00[0x10];
    /* 0x10 */ float position[4];
    /* 0x20 */ char pad20[4];
    /* 0x24 */ char *pClass;
    /* 0x28 */ struct Moby_L05_0041D498 *pChain;
    /* 0x2C */ float scale;
    /* 0x30 */ unsigned char updateDist;
    /* 0x31 */ unsigned char drawn;
    /* 0x32 */ short drawDist;
    /* 0x34 */ char pad34[0xAA - 0x34];
    /* 0xAA */ short oClass;
    /* 0xAC */ char padAC[0xF0 - 0xAC];
    /* 0xF0 */ float rot[4];
} Moby_L05_0041D498;

/* The moby of class 0xFBF, found once. */
extern Moby_L05_0041D498 *D_L05_001B1348 __attribute__((sda));
/* The head of the moby list. */
extern Moby_L05_0041D498 *D_L05_001B2528;

extern Moby_L05_0041D498 *func_0029EFD0(int);
extern void func_00282C88(float *);
extern float func_002A7940(void);
extern void func_L05_0041D728(Moby_L05_0041D498 *);

/* Spawns a moby of class 0x10F9 at the caller's position with a random turn, remembers the
   last moby of class 0xFBF in the list the first time, and sets up the new moby's state. */
Moby_L05_0041D498 *func_L05_0041D498(Moby_L05_0041D498 *caller)
{
    Moby_L05_0041D498 *moby;
    Moby_L05_0041D498 *other;

    moby = CreateMoby(0x10F9 /* moby class 4345 */);
    if (moby != 0) {
        moby->updateDist = 0xFF;
        moby->drawDist = 0xFF;
        moby->drawn = 1;
        qcopy(moby->position, caller->position);
        ClearVector128(moby->rot);
        moby->rot[2] = RandomAngle();
        if (D_L05_001B1348 == 0) {
            for (other = D_L05_001B2528; other != 0; other = other->pChain) {
                if (other->oClass == 0xFBF /* moby class 4031 */)
                    D_L05_001B1348 = other;
            }
        }
        InitGlowRingState_L05_2(moby);
        moby->scale = *(float *)(moby->pClass + 0x24);
        return moby;
    }
    return 0;
}
