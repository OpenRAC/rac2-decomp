#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F413108;

extern s32 D_L12_001B29C8[];

extern float func_002A7878(char *, float, float);
extern s32 func_002A7820(s32, s32);
extern void func_00282CC0(void *, void *, char *);
extern void func_0029FCC0(char *, s32, void *);
extern void func_002BAE50(void *, void *, s32, s32, s32, s32, s32, s32);

/* Sprays the flame sprites of the object's grabbed target: while the target is the live flame moby it draws two bursts at each of its two hand points. */
void func_L12_00413108(char *moby)
{
    V4_F413108 handA, handB, origin, offset;
    char *vars = *(char **)(moby + 0x68);
    char *partner = *(char **)(vars + 0x2F8);
    s32 bigSize, smallSize, partnerState;

    if (partner != 0 && *(short *)(partner + 0xAA) == 0x114B /* moby class 4427 */) {
        partnerState = *(u8 *)(partner + 0x20);
        if (partnerState != 0xFE) {
            if (partnerState != 0xFD) {
                offset.q = 0;
                offset.f[2] = -(RandomFloatRange(partner, 1.7f, 3.0f) * 0.016666668f);
                origin.q = offset.q;
                FastVecAdd(&origin, &origin, vars + 0x1A0);
                TransformMobyJointToWorld(*(char **)(vars + 0x2F8), 5, &handA);
                TransformMobyJointToWorld(*(char **)(vars + 0x2F8), 6, &handB);
                if (D_L12_001B29C8[0] & 1) {
                    SpawnScalingParticle(&handA, &origin, 0xCF0000FF, 0xCF, RandomIntRange(0x12, 0x16), 0x28, -10, 1);
                    SpawnScalingParticle(&handB, &origin, 0xCF0000FF, 0xCF, RandomIntRange(0x12, 0x16), 0x28, -10, 1);
                } else {
                    SpawnScalingParticle(&handA, &origin, 0x6000FFFF, 0x80, RandomIntRange(0x14, 0x18), 0x50, -10, 1);
                    SpawnScalingParticle(&handB, &origin, 0x6000FFFF, 0x80, RandomIntRange(0x14, 0x18), 0x50, -10, 1);
                }
                bigSize = RandomIntRange(10, 0x19);
                smallSize = RandomIntRange(10, 15);
                SpawnScalingParticle(&handA, &origin, 0xEFFF7F4F, 0xFF0000, smallSize, bigSize, -bigSize, 1);
                bigSize = RandomIntRange(10, 0x19);
                smallSize = RandomIntRange(10, 15);
                SpawnScalingParticle(&handB, &origin, 0xEFFF7F4F, 0xFF0000, smallSize, bigSize, -bigSize, 1);
            }
        }
    }
}
