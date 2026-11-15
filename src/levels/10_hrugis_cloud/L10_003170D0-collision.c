#include "common.h"

/* A colour flash: func_002AB800 starts it, func_002AB8C0 plays it. */
typedef struct {
    u8 pad00[0x04];
    u8 baseColor[3];            /* 0x04: the moby's own colour */
    u8 flashColor[3];           /* 0x07: 0 leaves a channel alone */
} ColorFlash;

/* The instance data of the mobies this callback serves. */
typedef struct {
    f32 *health;                /* 0x00 */
    u8 pad04[0x10 - 0x04];
    ColorFlash *flash;          /* 0x10: 0 when it has none */
} TargetVars;

/* The moby, as far as func_L10_00423788 reads it. */
typedef struct {
    u8 pad00[0x10];
    f32 position[4];            /* 0x10 */
    u8 pad20[0x68 - 0x20];
    TargetVars *vars;           /* 0x68 */
    u8 pad6C[0xA8 - 0x6C];
    u8 hitSlot;                 /* 0xA8 */
    u8 padA9;
    s16 oClass;                 /* 0xAA */
} Moby;

/* The hit func_002A9640 reports for a moby. */
typedef struct {
    u8 pad00[0x20];
    Moby *source;               /* 0x20: the moby that hit it */
    u8 pad24[0x2C - 0x24];
    f32 damage;                 /* 0x2C */
} MobyHit;

extern MobyHit *func_002A9640(Moby *moby, u32 flags, s32 clear);
extern void func_002AB8C0(Moby *moby, ColorFlash *flash);
extern void func_002AB800(Moby *moby, ColorFlash *flash);
extern s32 func_00282948(s32 *timer);
extern f32 func_002A7878(f32 min, f32 max);
extern s32 func_00283CF0(f32 value);
extern void func_L05_00424990(f32 *position, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5,
                              s32 a6, s32 a7, s32 a8, s32 a9, s32 a10, f32 scale);
/* Defined with (object, bonus) in L10_00424028-reward-g8.c; this call also passes 10. */
extern void func_L10_00425508(Moby *moby, s32 bonus, s32 a2);
extern s32 func_L05_0037BBB8(Moby *moby);
extern void func_L05_0037BE98(Moby *moby);
extern void func_L05_0037AE40(Moby *moby);
extern s32 func_002E5DA0(s32 index, s32 value, Moby *moby, s32 kind);

/* Counted down by func_00282948 on each hit: class 0xF8E plays its hit sound when it has
   run out, and sets it to 10 to 20 again. */
extern s32 D_L10_001B354C __attribute__((sda));

/* Hit callback of the Hrugis controller: plays the moby's colour flash, takes the damage
   of the hit it took off its health (class 0xCBE only from a class 0xF93 moby) with a
   sound, and at zero health blows it up and drops a reward; the moby is then retired
   unless keep is set. Returns 1 when the hit destroyed it. */
s32 func_L10_00423788(Moby *moby, s32 keep)
{
    ColorFlash *flash;
    f32 *health;
    MobyHit *hit;
    s32 destroyed = 0;

    hit = func_002A9640(moby, 0x230000, 0);
    moby->hitSlot = 0xFF;
    flash = moby->vars->flash;
    health = moby->vars->health;
    if (flash != 0)
        func_002AB8C0(moby, flash);
    if (*health <= 0.0f)
        return 0;

    if (hit != 0) {
        if (moby->oClass == 0xCBE) {
            if (hit->source == 0 || hit->source->oClass != 0xF93)
                return 0;
        }
        if (flash != 0) {
            flash->flashColor[0] = 0xFF;
            func_002AB800(moby, flash);
        }
        *health -= hit->damage;
        if (moby->oClass != 0xB73 && moby->oClass != 0xF8E)
            func_002E5DA0(0xD, 0, moby, 0xFBF);
        if (func_00282948(&D_L10_001B354C) != 0 && moby->oClass == 0xF8E) {
            func_002E5DA0(3, 0, moby, 0xF8E);
            D_L10_001B354C = FloatToInt(func_002A7878(10.0f, 20.0f));
        }
        if (*health <= 0.0f) {
            *health = 0.0f;
            func_L05_00424990(moby->position, 0, 0x32, 0x1E, 0x1E, 0x1E, 0x28, 1, 1, 0, 0, 0.5f);
            func_L10_00425508(moby, 0, 0xA);
            if (func_L05_0037BBB8(moby) != 0)
                func_L05_0037BE98(moby);
            if (keep == 0)
                func_L05_0037AE40(moby);
            destroyed = 1;
        }
    }
    return destroyed;
}
