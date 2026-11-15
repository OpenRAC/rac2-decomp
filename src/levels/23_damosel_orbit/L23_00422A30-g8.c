#include "common.h"

typedef int TI16 __attribute__((mode(TI)));

typedef struct View_00422A30 {
    u8 pad0[0x188C];
    u8 *f188C;
    u8 pad1[0x2290 - 0x1890];
    u8 *f2290;
    s32 f2294;
} View_00422A30;

extern View_00422A30 D_00189E20;

extern float D_L23_001B1910 __attribute__((sda));

extern float D_L23_001B1928 __attribute__((sda));

extern u8 *D_L23_001B1484 __attribute__((sda));

extern s32 D_L23_001B36E0;

/* A 16-byte global vector: retain the unsplit address form, as in retail. */
extern TI16 D_L23_001B1FB0 MACRO_ADDR;

extern u8 *func_0029EFD0(s32);

extern void func_002B37E8(u8 *, u8 *);

extern void func_L23_00418650(void *, float);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(void *, void *, float);

extern float func_002B0360(void *);

extern float func_00282E48(void *, void *);

extern float func_00282C48(float);

extern float func_00282DB0(void *, void *);

extern void func_00282D30(void *, void *, float);

extern s32 func_L23_0041B948(void);

extern s32 func_002E5CF8(s32, s32, u8 *);

/* Creates the follower object for `src` (the effect that tracks `target`, or the hero, or nothing): copies
   the pose rows, fills the state, and when it has a live target works out the direction, the distance and
   the aim test, dropping the target when the aim, the range or the helper says so. */
/* Creates a homing shot. It chooses a target (given, the hero, or none), points the shot
   at it, and drops the target if it is too far, off to the side or blocked. */
u8 *func_L23_00422A30(u8 *src, TI16 *pos, u8 *target, s32 trackMoby, s32 trackPoint) {
    u8 *obj;
    u8 *vars;
    TI16 loc[4];
    float targetValue;
    float sourceValue;
    float distance;
    float aimDot;
    s32 tooFarOff;
    u8 *hero;
    TI16 row0;
    TI16 row1;
    TI16 row2;
    TI16 *backDir;

    obj = CreateMoby(0x118F /* moby class 4495 */);
    if (obj != 0) {
        vars = *(u8 **)(obj + 0x68);
        InitChildObjectFromParent(obj, src);
        *(float *)(obj + 0x2C) = *(float *)(obj + 0x2C) * D_L23_001B1910;
        *(u16 *)(obj + 0x34) = *(u16 *)(obj + 0x34) | 0x100;
        *(float *)(vars + 0x1C) = 0.33333334f;
        row0 = *(TI16 *)(src + 0xC0);
        *(TI16 *)(obj + 0xC0) = row0;
        row1 = *(TI16 *)(src + 0xD0);
        *(TI16 *)(obj + 0xD0) = row1;
        row2 = *(TI16 *)(src + 0xE0);
        *(TI16 *)(obj + 0xE0) = row2;
        *(u8 **)(vars + 0x10) = src;
        qcopy(obj + 0x10, pos);
        *(s32 *)(vars + 0x14) = 0x96;
        *(float *)(obj + 0x2C) = *(float *)(obj + 0x2C) + *(float *)(obj + 0x2C);
        vars[0x28] = trackMoby;
        vars[0x29] = trackPoint;
        hero = gMothershipBossMoby;
        if (target != 0) {
            *(u8 **)(vars + 0x18) = target;
            *(s32 *)(vars + 0x24) = 0x890000;
        } else {
            if (hero != 0) {
                *(u8 **)(vars + 0x18) = hero;
                if (*(s16 *)(hero + 0xAA) == 0xF7F /* Mothership Boss Part */) {
                    *(s32 **)(vars + 0x2C) = &D_L23_001B36E0;
                } else {
                    *(u8 **)(vars + 0x2C) = hero + 0x10;
                }
                *(s32 *)(vars + 0x24) = 0x890000;
            } else {
                *(s32 *)(vars + 0x18) = 0;
                *(s32 *)(vars + 0x24) = 0x890000;
                vars[0x29] = 0;
                vars[0x28] = 0;
            }
        }
        if (src == gHeroState.f2290) {
            vars[0x29] = 1;
        }
        if (vars[0x28] == 0 && *(s32 *)(vars + 0x18) != 0) {
            qcopy(&loc[0], *(void **)(vars + 0x2C));
            ProjectPointOntoPlanetSurface(&loc[0], 0.0f);
            FastVecSub(vars + 0x30, *(u8 **)(vars + 0x2C), obj + 0x10);
            qcopy(&loc[1], obj + 0x10);
            ProjectPointOntoPlanetSurface(&loc[1], 0.0f);
            FastVecSub(&loc[2], &loc[0], &loc[1]);
            tooFarOff = 0;
            vec_scale_to_length(&loc[2], &loc[2], 1.0f);
            vec_scale_to_length(vars + 0x30, vars + 0x30, 1.0f);
            sourceValue = GetDistanceFromGravityCenter(src + 0x10);
            targetValue = GetDistanceFromGravityCenter(*(u8 **)(vars + 0x2C));
            distance = fast_vec_dist(&loc[0], &loc[1]);
            if (distance < 5.0f) {
                if (FloatAbs(sourceValue - targetValue) > 10.0f) {
                    tooFarOff = 1;
                }
            }
            qcopy(&loc[3], obj + 0xC0);
            aimDot = FastVecDot(&loc[2], &loc[3]);
            if ((src == gHeroState.f2290 && *(*(u8 **)(vars + 0x18) + 0x31) == 0) ||
                aimDot < D_L23_001B1928 || 50.0f < distance || tooFarOff != 0 || IsBossHeldFlagSet() != 0) {
                *(s32 *)(vars + 0x18) = 0;
            }
            if (src == gHeroState.f2290) {
                if (*(s32 *)(vars + 0x18) != 0) {
                    gHeroState.f188C = vars + 0x30;
                } else if (gHeroState.f2294 == 0x5B) {
                    backDir = (TI16 *)(src + 0xE0);
                    qcopy(&D_L23_001B1FB0, backDir);
                    FastVecScale(&D_L23_001B1FB0, &D_L23_001B1FB0, -1.0f);
                    gHeroState.f188C = (u8 *)&D_L23_001B1FB0;
                    qcopy(vars + 0x30, &D_L23_001B1FB0);
                    vars[0x28] = 0;
                    *(s32 *)(vars + 0x18) = 1;
                    vars[0x29] = 0;
                }
            }
        }
        *(s32 *)(vars + 0x20) = 0;
        PlayMobySound(1, 0, obj);
        *(u16 *)(obj + 0x34) = *(u16 *)(obj + 0x34) | 0x41;
        obj[0xBC] = 0;
    }
    return obj;
}
