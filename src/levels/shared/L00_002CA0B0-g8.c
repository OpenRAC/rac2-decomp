#include "common.h"
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

typedef struct { float start, end, reserved0, reserved1; } AnimationRange;
/* The same table from its first end field; retail reaches these through an absolute address. */
extern float D_L00_001A7DAC[][4] MACRO_ADDR;
extern AnimationRange animation_ranges[2] SDATA(D_L00_001A7DA8);
extern int D_L00_001A7DC8[2][2] SDATA(D_L00_001A7DC8);
extern void func_L00_002D2168(int, int, float);

/* Sets the animation scale. Mode 1 scales from field_170. With both 0x1454 flags set it plays
 * animation 20 and clamps a scale from the time. Otherwise it moves frame to the range holding the
 * time, restarts the animation at the matching frame when frame changes (the table gives an
 * offset per old and new frame), and clamps a scale chosen by frame. */
void func_L00_002CA0B0(void)
{
    float limit;
    int old;
    if (gHeroState.mode_22b4 == 1) {
        gHeroState.animation_scale = gHeroState.field_170 * 90.0f;
        if (gHeroState.animation_scale < 0.5f) gHeroState.animation_scale = 0.5f;
        return;
    }
    if (gHeroState.flag_1454 != 0 && gHeroState.flag_1456 != 0) {
        if (((unsigned char *)gHeroState.object)[0x43] != 20)
            set_hero_animation(20, 0, 11.0f);
        gHeroState.animation_scale = gHeroState.animation_time * 25.0f;
        if (gHeroState.animation_scale < 0.7f) gHeroState.animation_scale = 0.7f;
        if (2.2f < gHeroState.animation_scale) gHeroState.animation_scale = 2.2f;
        return;
    }
    if (((unsigned char *)gHeroState.object)[0x43] == 20) {
        set_hero_animation(gHeroState.frame + 3, 0, 7.0f);
    } else if (gHeroState.count_1c0 > 4 && gHeroState.flag_40e == 0) {
        float time = gHeroState.animation_time;
        float start;
        int before_range;
        old = gHeroState.frame;
        start = animation_ranges[old].start * 0.01666666753590107f;
        before_range = time < start;
        if (before_range || D_L00_001A7DAC[old][0] * 0.01666666753590107f < time) {
            if (before_range) {
                if (time < start) {
                    do {
                        --gHeroState.frame;
                    } while (time < animation_ranges[gHeroState.frame].start * 0.01666666753590107f);
                }
            } else {
                while (D_L00_001A7DAC[gHeroState.frame][0] * 0.01666666753590107f < time) gHeroState.frame++;
            }
            if (gHeroState.frame < 0) gHeroState.frame = 0;
            if (gHeroState.frame > 1) gHeroState.frame = 1;
            if (old != gHeroState.frame) {
                char *object = gHeroState.object;
                struct { char pad[0x48]; unsigned char *entry[1]; } *frames = *(void **)(object + 0x24);
                int before = frames->entry[old + 3][0x10];
                int after = frames->entry[gHeroState.frame + 3][0x10];
                int offset = D_L00_001A7DC8[old][gHeroState.frame];
                set_hero_animation(gHeroState.frame + 3, ((unsigned char)object[0x41] * after / before + offset) % after, 8.0f);
            }
        }
    }
    switch (gHeroState.frame) {
    case 0:
        gHeroState.animation_scale = gHeroState.animation_time * 157.0f;
        if (gHeroState.animation_scale < 0.6f) gHeroState.animation_scale = 0.6f;
        if (4.0f < gHeroState.animation_scale) gHeroState.animation_scale = 4.0f;
        break;
    case 1:
        gHeroState.animation_scale = gHeroState.animation_time * 14.0f;
        if (gHeroState.animation_scale < 0.6f) gHeroState.animation_scale = 0.6f;
        if (2.2f < gHeroState.animation_scale) gHeroState.animation_scale = 2.2f;
        break;
    }
}
