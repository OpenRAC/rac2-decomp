#include "include_asm.h"
#include "names.h"

/* func_L23_00425848 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef unsigned char u8;

typedef unsigned short u16;

typedef int s32;

typedef int TI128 __attribute__((mode(TI)));

extern void func_002AFFD8(void *, void *, s32);

extern s32 func_002A77E0(s32);

extern void func_L23_00425568(u8 *);

extern void func_L00_002E6EF8(void *, void *);

extern void func_L23_004259E0(u8 *);

extern void func_0029F338(u8 *);

extern s32 func_00282948(void *);

/* keeps the object's position vector in step with its owner's, runs the state it is in (0: arm
   the object, 1: refresh and re-register), and destroys it when it leaves the 2.0..1021.0 box or
   when its payload has no timer; otherwise it counts one more frame */
/* Per-frame update of a ribbon trail. It follows its start point, redraws the ribbon, and
   removes itself when it leaves the level or runs out of time. */
void func_L23_00425848(u8 *obj) {
    TI128 loc[3];
    u8 *vars = *(u8 **)(obj + 0x68);
    TI128 *pos = (TI128 *)(obj + 0x10);

    *pos = **(TI128 **)(vars + 0x24);
    loc[0] = *pos;
    ComputeViewDirection(pos, &loc[1], 1);
    loc[2] = *pos;
    switch (obj[0x20]) {
    case 0:
        obj[0x20] = 1;
        *(u16 *)(obj + 0x34) |= 0x41;
        *(u16 *)(obj + 0x96) = RandomIntBelow(0xFFFF);
        break;
    case 1:
        BuildTrailCurvePoints(obj);
        AddDrawCallbackToList3((void *)DrawTrailRibbon_L23, obj);
        break;
    }
    if (*(float *)(obj + 0x10) < 2.0f || *(float *)(obj + 0x10) > 1021.0f
        || *(float *)(obj + 0x14) < 2.0f || *(float *)(obj + 0x14) > 1021.0f
        || *(float *)(obj + 0x18) < 2.0f || *(float *)(obj + 0x18) > 1021.0f
        || *(s32 *)(vars + 0x2C) == 0) {
        MarkMobySpawned(obj);
    } else {
        u16 *cp = (u16 *)(obj + 0x96);
        *cp = *cp + 1;
        if (*cp > 0xFFFE) {
            *cp = 0;
        }
        if (*(s32 *)(vars + 0x2C) != -1) {
            FastFloatHelperD(vars + 0x2C);
        }
    }
}
