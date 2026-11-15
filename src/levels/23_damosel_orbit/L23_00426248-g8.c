#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* number of live effects of this kind, and the five slots they occupy */
extern float D_L23_001B19FC __attribute__((sda));
extern s32 D_L23_001B3918[5] MACRO_ADDR;
extern u8 D_L23_001BA500[];

extern void *func_0029EFD0(s32);
extern float func_002A78D8(float, float);
extern s32 func_00283DB8(void *, float);
extern float func_00282E48(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern void func_L05_00428AC8(void *);

/* spawns object 0x11DF at pos with parent's orientation, when one of the five slots is free:
   fills its vars from the arguments and, if it is in view, grades it against the reference
   point at D_L23_001BA500 + 0x140 */
/* Creates an effect object in one of five free slots, if any is free. It also shakes the
   camera when the hero is close. */
void *func_L23_00426248(u8 *pos, u8 *parent, s32 shakeCamera, float scale, s32 a3, s32 a4, s32 a5,
                        s32 a6, s32 a7, s32 aimCheck, s32 a9, s32 a10, s32 a11, s32 a12) {
    TI128 sphere;
    TI128 dir;
    s32 i;
    u8 *obj;
    u8 *vars;
    float angle;

    if (gActiveSlotEffectCount == -1.0f) {
        for (i = 0; i < 5; i++) {
            gSlotEffectInUse[i] = 0;
        }
        gActiveSlotEffectCount = 0.0f;
    }
    if (gActiveSlotEffectCount >= 5.0f) {
        return 0;
    }
    for (i = 0; i < 5; i++) {
        if (gSlotEffectInUse[i] == 0) {
            break;
        }
    }
    gActiveSlotEffectCount += 1.0f;
    gSlotEffectInUse[i] = 1;
    obj = CreateMoby(0x11DF /* moby class 4575 */);
    if (obj != 0) {
        vars = *(u8 **)(obj + 0x68);
        obj[0x30] = 0xFF;
        *(s16 *)(obj + 0x32) = 0xFF;
        obj[0x20] = 0;
        *(s32 *)(vars + 0x3C) = i;
        qcopy(obj + 0x10, pos);
        *(float *)(obj + 0x1C) = 1.0f;
        qcopy(obj + 0xC0, parent + 0xC0);
        qcopy(obj + 0xD0, parent + 0xD0);
        qcopy(obj + 0xE0, parent + 0xE0);
        *(float *)(obj + 0xCC) = *(float *)(obj + 0xDC) = *(float *)(obj + 0xEC) = 0.0f;
        *(s32 *)(vars + 0x20) = a3;
        *(s32 *)(vars + 0x24) = a4;
        *(s32 *)(vars + 0x28) = a5;
        *(s32 *)(vars + 0x2C) = a6;
        *(float *)(vars + 0x14) = scale;
        *(s32 *)(vars + 0x30) = a7;
        *(s32 *)(vars + 0x34) = a9;
        *(s32 *)(vars + 0x48) = a12;
        *(s16 *)vars = 0x3C;
        *(s16 *)(vars + 2) = 0x3C;
        *(float *)(vars + 8) = scale + scale;
        *(float *)(vars + 0xC) = scale * 4.0f;
        *(s32 *)(vars + 0x1C) = a10;
        *(s32 *)(vars + 0x38) = a11;
        *(s32 *)(vars + 0x18) = aimCheck;
        *(float *)(vars + 0x44) = RandomSignedFloatRange(65.0f, 80.0f);
        qcopy(&sphere, obj + 0x10);
        ((float *)&sphere)[3] = scale * 3.0f;
        if (FastMathHelperA(&sphere, 128.0f) == 1) {
            *(s16 *)(vars + 4) = 0x19;
            *(float *)(vars + 0x10) = 0.04f;
            if (fast_vec_dist(pos, D_L23_001BA500 + 0x140) < 48.0f && shakeCamera != 0) {
                u8 *ref = D_L23_001BA500;
                *(s32 *)(ref + 0x16C) = 0;
                *(s32 *)(ref + 0x168) = 0x28;
                *(float *)(ref + 0x160) = 0.075f;
            }
            if (*(s32 *)(vars + 0x18) != 0) {
                FastVecSub(&dir, obj + 0x10, D_L23_001BA500 + 0x140);
                vec_scale_to_length(&dir, &dir, 1.0f);
                angle = FastAngleHelper(FastVecDot(&dir, D_L23_001BA500 + 0x370));
                if (1.5707964f - angle < 0.45378566f) {
                    *(s32 *)(vars + 0x18) = 1;
                } else {
                    *(s32 *)(vars + 0x18) = 0;
                }
            }
        } else {
            *(s16 *)(vars + 4) = 0;
            *(s32 *)(vars + 0x18) = 0;
        }
        SpawnFireExplosionEffect(obj);
    }
    return obj;
}
