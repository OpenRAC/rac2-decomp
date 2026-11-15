#include "include_asm.h"
#include "common.h"

extern float D_L02_001B1720 __attribute__((sda));

extern float D_L02_001B1724;

extern int D_L02_001B1710 __attribute__((sda));

extern int D_L02_001B1714 __attribute__((nosda));

extern int D_L02_001B1718 __attribute__((nosda));

extern int D_L02_001B171C __attribute__((nosda));

extern char D_L02_001A8F20[];

extern float func_002A7878(float, float);

extern int func_002A7820(int, int);

/* The EE ABI preserves the integer and FP argument banks independently. */
extern void func_002BDBC0(void *, void *, float, u32, s32, s32);

/* Spawns a puff of effect at the object with a random speed and count. */
void func_L02_004013C0(void *mobyArg)
{
    void *moby = mobyArg;
    void *vars;
    int local[2];
    float speed;
    float randomValue;
    int count;

    vars = *(void **)(moby + 0x68);
    randomValue = RandomFloatRange(D_L02_001B1720, D_L02_001B1724);
    speed = randomValue * 210000.0f;
    count = RandomIntRange(*(unsigned char *)(vars + 0x75), *(unsigned char *)(vars + 0x76));
    if (*(short *)(moby + 0xAA) == 0xB5A /* moby class 2906 */) {
        local[0] = D_L02_001B1710;
        local[1] = D_L02_001B1714;
    } else {
        local[0] = D_L02_001B1718;
        local[1] = D_L02_001B171C;
    }
    SpawnGrowingPuffParticle(moby + 0x10, D_L02_001A8F20, speed, D_L02_001B1710, D_L02_001B1714, count);
}


