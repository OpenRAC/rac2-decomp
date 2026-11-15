#include "include_asm.h"
#include "names.h"
typedef struct {
    unsigned char pad0[0x160]; float velocity[4];
    float field_170, elapsed_174, speed_178;
    unsigned char pad1[0x1B4 - 0x17C]; float animation_time; int count_1b8;
    unsigned char pad2[4]; int count_1c0;
    unsigned char pad3[0x1E0 - 0x1C4]; short flag_1e0;
    unsigned char pad4[2]; short flag_1e4;
    unsigned char pad5[0x278 - 0x1E6]; float distance_278;
    unsigned char pad6[4]; float angle_280; unsigned char flag_284;
    unsigned char pad7[0x40E - 0x285]; unsigned char flag_40e;
    unsigned char pad8[0x49C - 0x40F]; unsigned char level_49c;
    unsigned char pad9[0xC20 - 0x49D]; float animation_scale;
    unsigned char pad10[4]; int flags_c28;
    unsigned char pad11[0x1454 - 0xC2C]; short flag_1454; unsigned char flag_1456;
    unsigned char pad12[0x1492 - 0x1457]; unsigned char flag_1492;
    unsigned char pad13[0x2290 - 0x1493]; void *object; int mode, frame;
    unsigned char pad14[0x22B4 - 0x229C]; unsigned char mode_22b4;
    unsigned char pad15[4]; unsigned char flag_22b9;
    unsigned char pad16[0x24A0 - 0x22BA]; int reset_24a0;
    unsigned char pad17[0x24B8 - 0x24A4]; float timer;
    unsigned char pad18[0x24FC - 0x24BC]; short flag_24fc;
} HeroActionState;
extern HeroActionState D_00189E20;

extern unsigned int D_00138320[];
extern int ref_L00_002CA898_00(int, int);

extern void func_L00_002B39F0(int, float);
extern void func_L00_002D2168(int, int, float);
extern void func_L00_002D2470(int, int);
extern int ref_L00_002CA898_01(int);
extern void func_002AC9F8(void *, float);
extern int D_L00_001A7DDC __attribute__((sda));

/* Picks what the hero does next after a landing or a stop, such as starting to run or idling. */
void func_L00_002CA898(void)
{
    gHeroState.reset_24a0 = 0;
    if (gHeroState.flag_1492 != 0 && 0.008333333767950535f < gHeroState.elapsed_174) {
        ref_L00_002CA898_00(0x2E, 1);
        return;
    }
    ResolveStickInputToDirection(0, 1.0f);
    if (D_00138320[0] & 8) {
        ref_L00_002CA898_00(4, 0);
        set_hero_animation(0xD, 2, -2.0f);
        SelectHeroAnimationFrame(3, 0x12);
        return;
    }
    if (0.3f < gHeroState.timer && gHeroState.flag_1e0 == 0) {
        if (gHeroState.flag_1492 != 0 || gHeroState.flag_22b9 != 0) {
            ref_L00_002CA898_00(2, 1);
        } else {
            int amount;
            if (!ref_L00_002CA898_00(2, 0)) return;
            amount = 8;
            if (gHeroState.level_49c > 5) amount = 14;
            gHeroState.frame = 1;
            set_hero_animation(4, D_L00_001A7DDC, (float)amount);
            gHeroState.flag_40e = 1;
        }
        return;
    }
    if ((0.050000004470348358f < gHeroState.speed_178 && gHeroState.level_49c > 3) ||
        gHeroState.mode == 0x10) {
        if (ref_L00_002CA898_00(3, 0)) {
            set_hero_animation(5, 0, -1.0f);
            ClampVectorLength(gHeroState.velocity, 0.083333335816860199f);
        }
        return;
    }
    if (gHeroState.level_49c < 13 && (gHeroState.flags_c28 & 2) == 0) return;
    if (!ref_L00_002CA898_00(0, 0)) return;
    if (ref_L00_002CA898_01(0) == 0x51) {
        set_hero_animation(ref_L00_002CA898_01(0), 0, 15.0f);
    } else if (gHeroState.flags_c28 & 2) {
        set_hero_animation(ref_L00_002CA898_01(0), 0, -2.0f);
    }
}
