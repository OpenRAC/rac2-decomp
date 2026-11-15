#include "include_asm.h"
#include "names.h"

/* func_L02_003D47B0 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern float func_002A7878(float, float);

extern void func_002A7750(char *, int, int);

extern void func_002A0488(char *, int, int, int);

extern void func_L02_003D4AF0(char *, int);

extern void func_L02_003D5570(char *);

extern float func_00283248(float, float);

typedef struct {
    char pad0[0x80];
    float x;
    float y;
} L02_003D7900_Hero;

extern L02_003D7900_Hero D_00189E20;

extern int D_L02_001B01C0 __attribute__((sda));

/* Puts the Chainblade back at its start spot facing the hero and resets its timers and phase. */
void func_L02_003D47B0(char *self, int hitCooldown) {
    char *state = *(char **)(self + 0x68);
    float randomAngle;
    L02_003D7900_Hero *hero;

    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    randomAngle = RandomFloatRange(0.0f, 1.5707965f);
    *(float *)(state + 0x304) = 0.0f;
    *(short *)(state + 0x32C) = 0;
    *(int *)(state + 0x300) = 0;
    *(short *)(state + 0x32A) = 0;
    *(short *)(state + 0x98) = 0;
    *(float *)(state + 0x2F4) = randomAngle;
    SetMobyState(self, 2, 1);
    PickChainbladeIdleAnimation(self, 1);
    *(unsigned char *)(state + 0x7A) = 0;
    *(unsigned char *)(state + 0x2E) = 1;
    *(unsigned char *)(self + 0x31) = 1;
    *(unsigned short *)(self + 0x34) = *(unsigned short *)(self + 0x34) & 0xFFFE;
    *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
    *(unsigned short *)(self + 0x34) = (*(unsigned short *)(self + 0x34) | 0x1000) & 0xFFFD;
    *(unsigned char *)(self + 0x7F) = 0;
    /* The destination is named so that its address is formed first, as in retail: written
       inline, the source's small-data address goes into a register while the right-hand side
       is expanded, before the destination's, and the two address registers swap. */
    {
        TI128 *dst = (TI128 *)(self + 0x10);

        *dst = *(TI128 *)&D_L02_001B01C0;
    }
    hero = &gHeroState;
    *(float *)(self + 0xF8) = FastMatrixHelperA(hero->x - *(float *)(self + 0x10),
                                            hero->y - *(float *)(self + 0x14));
    *(int *)(state + 0x310) = 0;
    *(short *)(state + 0x318) = 0;
    *(short *)(state + 0x31A) = 0;
    SpawnChainLinks(self);
    if (*(short *)(state + 0x60) != 0) {
        *(short *)(state + 0x60) = 0;
        set_moby_color(self, *(unsigned char *)(state + 0x64),
                      *(unsigned char *)(state + 0x65),
                      *(unsigned char *)(state + 0x66));
        *(short *)(state + 0x62) = 1;
    }
    *(short *)(state + 0x330) = hitCooldown;
}
