#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad00[0x04];
    u8 baseColor[3];             
    u8 flashColor[3];            
} ColorFlash;
typedef struct {
    f32 *health;                 
    u8 pad04[0x10 - 0x04];
    ColorFlash *flash;           
} TargetVars;
typedef struct {
    u8 pad00[0x10];
    f32 position[4];             
    u8 pad20[0x68 - 0x20];
    TargetVars *vars;            
    u8 pad6C[0xA8 - 0x6C];
    u8 hitSlot;                  
    u8 padA9;
    s16 oClass;                  
} Moby;
typedef struct {
    u8 pad00[0x20];
    Moby *source;                
    u8 pad24[0x2C - 0x24];
    f32 damage;                  
} MobyHit;
extern MobyHit *func_002A9640(Moby *moby, u32 flags, s32 clear);
extern void func_PAL_002AC3C0(Moby *moby, ColorFlash *flash);
extern void func_PAL_002AC290(Moby *moby, ColorFlash *flash);
extern s32 func_00282948(s32 *timer);
extern f32 func_002A7878(f32 min, f32 max);
extern s32 func_00283CF0(f32 value);
extern void func_PAL_L05_0042A240(f32 *position, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5,
                              s32 a6, s32 a7, s32 a8, s32 a9, s32 a10, f32 scale);
extern void func_L10_00425508(Moby *moby, s32 bonus, s32 a2);
extern s32 func_L05_0037BBB8(Moby *moby);
extern void func_L05_0037BE98(Moby *moby);
extern void func_L05_0037AE40(Moby *moby);
extern s32 func_002E5DA0(s32 index, s32 value, Moby *moby, s32 kind);
extern s32 D_L10_001B354C __attribute__((sda));

/* Hit callback of the Hrugis controller: plays the moby's colour flash, takes the damage
   of the hit it took off its health (class 0xCBE only from a class 0xF93 moby) with a
   sound, and at zero health blows it up and drops a reward; the moby is then retired
   unless keep is set. Returns 1 when the hit destroyed it. */
s32 func_PAL_L10_00428E38(Moby *moby, s32 keep)
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
        func_PAL_002AC3C0(moby, flash);
    if (*health <= 0.0f)
        return 0;

    if (hit != 0) {
        if (moby->oClass == 0xCBE) {
            if (hit->source == 0 || hit->source->oClass != 0xF93)
                return 0;
        }
        if (flash != 0) {
            flash->flashColor[0] = 0xFF;
            func_PAL_002AC290(moby, flash);
        }
        *health -= hit->damage;
        if (moby->oClass != 0xB73 && moby->oClass != 0xF8E)
            func_002E5DA0(0xD, 0, moby, 0xFBF);
        if (func_00282948(&D_L10_001B354C) != 0 && moby->oClass == 0xF8E) {
            func_002E5DA0(3, 0, moby, 0xF8E);
            D_L10_001B354C = ((s32)(func_00283CF0(func_002A7878(10.0f, 20.0f))) * 5 + 2) / 6;
        }
        if (*health <= 0.0f) {
            *health = 0.0f;
            func_PAL_L05_0042A240(moby->position, 0, 0x32, 0x1E, 0x1E, 0x1E, 0x28, 1, 1, 0, 0, 0.5f);
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


INCLUDE_ASM("asm/pal/levels", func_PAL_L10_00429070);


INCLUDE_ASM("asm/pal/levels", func_PAL_L10_00429880);

INCLUDE_ASM("asm/pal/levels", func_PAL_L10_00429B20);

INCLUDE_ASM("asm/pal/levels", func_PAL_L10_00429D08);


INCLUDE_ASM("asm/pal/levels", func_PAL_L10_0042A5C8);
