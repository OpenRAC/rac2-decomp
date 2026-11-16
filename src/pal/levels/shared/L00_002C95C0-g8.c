#include "include_asm.h"

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
extern HeroActionState g_hero_state;
typedef struct { float start, end, reserved0, reserved1; } AnimationRange;
extern float g_hero_anim_range_table[][4] MACRO_ADDR;
extern AnimationRange animation_ranges[2] SDATA(D_L00_001A7DA8);
extern int g_hero_anim_offset_table[2][2] SDATA(D_L00_001A7DC8);
extern void set_hero_animation_pal(int, int, float);

/* Sets the animation scale. Mode 1 scales from field_170. With both 0x1454 flags set it plays
 * animation 20 and clamps a scale from the time. Otherwise it moves frame to the range holding the
 * time, restarts the animation at the matching frame when frame changes (the table gives an
 * offset per old and new frame), and clamps a scale chosen by frame. */
void hero_update_anim_scale_pal(void)
{
    float limit;
    int old;
    if (g_hero_state.mode_22b4 == 1) {
        g_hero_state.animation_scale = g_hero_state.field_170 * 75.0f;
        if (g_hero_state.animation_scale < 0.5f) g_hero_state.animation_scale = 0.5f;
        return;
    }
    if (g_hero_state.flag_1454 != 0 && g_hero_state.flag_1456 != 0) {
        if (((unsigned char *)g_hero_state.object)[0x43] != 20)
            set_hero_animation_pal(20, 0, 9.0f);
        g_hero_state.animation_scale = g_hero_state.animation_time * 20.833334f;
        if (g_hero_state.animation_scale < 0.7f) g_hero_state.animation_scale = 0.7f;
        if (2.2f < g_hero_state.animation_scale) g_hero_state.animation_scale = 2.2f;
        return;
    }
    if (((unsigned char *)g_hero_state.object)[0x43] == 20) {
        set_hero_animation_pal(g_hero_state.frame + 3, 0, 6.0f);
    } else if (g_hero_state.count_1c0 > 3 && g_hero_state.flag_40e == 0) {
        float time = g_hero_state.animation_time;
        float start;
        int before_range;
        old = g_hero_state.frame;
        start = animation_ranges[old].start * 0.020000001f;
        before_range = time < start;
        if (before_range || g_hero_anim_range_table[old][0] * 0.020000001f < time) {
            if (before_range) {
                if (time < start) {
                    do {
                        --g_hero_state.frame;
                    } while (time < animation_ranges[g_hero_state.frame].start * 0.020000001f);
                }
            } else {
                while (g_hero_anim_range_table[g_hero_state.frame][0] * 0.020000001f < time) g_hero_state.frame++;
            }
            if (g_hero_state.frame < 0) g_hero_state.frame = 0;
            if (g_hero_state.frame > 1) g_hero_state.frame = 1;
            if (old != g_hero_state.frame) {
                char *object = g_hero_state.object;
                struct { char pad[0x48]; unsigned char *entry[1]; } *frames = *(void **)(object + 0x24);
                int before = frames->entry[old + 3][0x10];
                int after = frames->entry[g_hero_state.frame + 3][0x10];
                int offset = g_hero_anim_offset_table[old][g_hero_state.frame];
                set_hero_animation_pal(g_hero_state.frame + 3, ((unsigned char)object[0x41] * after / before + offset) % after, 7.0f);
            }
        }
    }
    switch (g_hero_state.frame) {
    case 0:
        g_hero_state.animation_scale = g_hero_state.animation_time * 130.83334f;
        if (g_hero_state.animation_scale < 0.6f) g_hero_state.animation_scale = 0.6f;
        if (4.0f < g_hero_state.animation_scale) g_hero_state.animation_scale = 4.0f;
        break;
    case 1:
        g_hero_state.animation_scale = g_hero_state.animation_time * 11.666667f;
        if (g_hero_state.animation_scale < 0.6f) g_hero_state.animation_scale = 0.6f;
        if (2.2f < g_hero_state.animation_scale) g_hero_state.animation_scale = 2.2f;
        break;
    }
}
