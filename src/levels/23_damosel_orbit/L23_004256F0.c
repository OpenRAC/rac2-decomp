#include "include_asm.h"
#include "names.h"

/* func_L23_004256F0 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef unsigned char u8;

typedef int s32;

typedef int TI16 __attribute__((mode(TI)));

extern void *CreateMoby(int size);

extern float math_random_angle(void);

/* allocates the record, fills its sub-record from the arguments, then draws three samples into it */
/* Creates a ribbon trail object that follows a start point and aims at a target point. */
void *ribbon_trail_create(u8 *startPos, u8 *owner, u8 *targetPos, u8 alpha, u8 outerAlpha, short randRange, short angleShift, s32 baseColor, float coreWidth, float width,
                        float extend, float curveScale, s32 outerColor, s32 drawTwice, s32 lifetime, s32 useOverride) {
    u8 *ribbon;
    u8 *vars;

    ribbon = CreateMoby(0x11AC /* moby class 4524 */);
    if (ribbon != 0) {
        vars = *(u8 **)(ribbon + 0x68);
        vars[0x28] = alpha;
        vars[0x29] = outerAlpha;
        *(float *)(vars + 0x10) = coreWidth;
        *(float *)(vars + 0x14) = width;
        *(float *)(vars + 0x18) = extend;
        *(float *)(vars + 0x1C) = curveScale;
        *(short *)(vars + 0xC) = randRange;
        *(short *)(vars + 0xE) = angleShift;
        *(s32 *)vars = baseColor;
        *(s32 *)(vars + 4) = outerColor;
        vars[0x2A] = drawTwice;
        *(s32 *)(vars + 0x2C) = lifetime;
        vars[0x2B] = useOverride;
        ribbon[0x30] = 0xFF;
        *(u8 **)(ribbon + 0xB8) = owner;
        ribbon[0x20] = 0;
        *(u8 **)(vars + 0x20) = targetPos;
        *(u8 **)(vars + 0x24) = startPos;
        *(TI16 *)(ribbon + 0x10) = *(TI16 *)startPos;
        *(float *)(ribbon + 0xF0) = math_random_angle();
        *(float *)(ribbon + 0xF4) = math_random_angle();
        *(float *)(ribbon + 0xF8) = math_random_angle();
        ribbon[0x20] = 0;
    }
    return ribbon;
}
