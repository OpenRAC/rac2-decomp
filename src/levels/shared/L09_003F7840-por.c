#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F3F7840;

extern s32 D_L09_001B2388[];

extern float func_002A7878(char *, float, float);
extern s32 func_002A7820(s32, s32);
extern void func_00282CC0(void *, void *, char *);
extern void func_0029FCC0(char *, s32, void *);
extern void func_002BAE50(void *, void *, s32, s32, s32, s32, s32, s32);

/* Sprays the flame sprites of the object's grabbed target: while the target is the live flame moby it draws two bursts at each of its two hand points. */
void func_L09_003F7840(char *moby)
{
    V4_F3F7840 handA, handB, offset, temp;
    char *vars = *(char **)(moby + 0x68);
    char *target = *(char **)(vars + 0x2F8);
    s32 bigSize, smallSize, targetState;

    if (target != 0 && *(short *)(target + 0xAA) == 0xD0E /* Megacorp Trooper Torso */) {
        targetState = *(u8 *)(target + 0x20);
        if (targetState != 0xFE) {
            if (targetState != 0xFD) {
                temp.q = 0;
                temp.f[2] = -(RandomFloatRange(target, 1.7f, 3.0f) * 0.016666668f);
                offset.q = temp.q;
                FastVecAdd(&offset, &offset, vars + 0x1A0);
                TransformMobyJointToWorld(*(char **)(vars + 0x2F8), 5, &handA);
                TransformMobyJointToWorld(*(char **)(vars + 0x2F8), 6, &handB);
                if (D_L09_001B2388[0] & 1) {
                    SpawnScalingParticle(&handA, &offset, 0xCF0000FF, 0xCF, RandomIntRange(0x12, 0x16), 0x28, -10, 1);
                    SpawnScalingParticle(&handB, &offset, 0xCF0000FF, 0xCF, RandomIntRange(0x12, 0x16), 0x28, -10, 1);
                } else {
                    SpawnScalingParticle(&handA, &offset, 0x6000FFFF, 0x80, RandomIntRange(0x14, 0x18), 0x50, -10, 1);
                    SpawnScalingParticle(&handB, &offset, 0x6000FFFF, 0x80, RandomIntRange(0x14, 0x18), 0x50, -10, 1);
                }
                bigSize = RandomIntRange(10, 0x19);
                smallSize = RandomIntRange(10, 15);
                SpawnScalingParticle(&handA, &offset, 0xEFFF7F4F, 0xFF0000, smallSize, bigSize, -bigSize, 1);
                bigSize = RandomIntRange(10, 0x19);
                smallSize = RandomIntRange(10, 15);
                SpawnScalingParticle(&handB, &offset, 0xEFFF7F4F, 0xFF0000, smallSize, bigSize, -bigSize, 1);
            }
        }
    }
}
