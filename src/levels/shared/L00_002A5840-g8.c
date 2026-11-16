#include "common.h"

typedef int Vector __attribute__((mode(TI)));
/* Four additional hero manipulators, each with a 0x40-byte record. */
typedef struct {
    unsigned char type, attached, pad2, absolute;
    unsigned char pad4[8];
    float blend;
    Vector quat, scale, translation;
} Manip5840;
typedef struct {
    unsigned char pad[0x1080];
    Manip5840 effects[4];
    unsigned char pad1180[0xC];
    short delay, timer;
    unsigned char pad1190[0x24FC - 0x1190];
    short disabled;
} Hero5840;
extern Hero5840 g_hero_state;
extern unsigned char g_state_flag_b;
extern float g_glow_scale SDATA(D_L00_001A7CF8);
extern int g_frame_l00_counter;
extern Vector g_hero_effect_quat_table[4] SDATA(D_L00_001A7E60);
extern Vector g_hero_effect_scale_table[4] SDATA(D_L00_001A7EA0);
extern Vector g_hero_effect_translation_table[4] SDATA(D_L00_001A7EE0);
extern int g_hero_effect_manipulator_ids[4] SDATA(D_L00_001A7F20);
extern float g_hero_effect_blend_table[22];
extern float ApproachValue(float *, float, float);
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);
extern int FastDecTimer(short *);
extern int math_random_int_range(int, int);
extern void moby_detach_manipulator(char *, char *);
extern void AttachManipulator(unsigned char *, unsigned int, unsigned char *);
extern void FastVecScale(void *, void *, float);

/* Update the hero glow and initialize, fade or detach four extra manipulators.
 * Adapted from RAC1's update_hero_glow_and_extra_manipulators
 * (src/overlays/shared/hero_idle_and_animation.c, GPL-3.0).
 */
void UpdateHeroGlowAndExtraManipulators(void) {
    unsigned char *hero0, *hero1, *hero2;
    unsigned char *object;
    int alpha, green_base, red_wave, red, blue, green, green_offset, red_offset, blue_offset, period;
    float normalized, wave, amplitude;
    if (g_state_flag_b)
        ApproachValue(&g_glow_scale, 1.8f, 0.05f);
    else
        ApproachValue(&g_glow_scale, 1.0f, 0.05f);
    hero0 = (unsigned char *)&g_hero_state;
    if ((unsigned int)(hero0[0x22B4] - 1) < 2)
        object = *(unsigned char **)(hero0 + 0x2290);
    else {
        if (*(short *)(hero0 + 0x24FC)) return;
        object = *(unsigned char **)(hero0 + 0x1314);
    }
    if (object == 0) return;
    hero1 = (unsigned char *)&g_hero_state;
    *(unsigned short *)(object + 0x34) |= 0x10;
    alpha = 128;
    green = 136;
    blue = 56;
    if (*(int *)(hero1 + 0x24CC) == 1) blue = green;
    period = 110;
    normalized = IntToFloat(period);
    normalized = (float)(g_frame_l00_counter % period) / normalized;
    normalized = normalized + normalized;
    normalized = normalized * 3.1415927f;
    wave = math_fast_sin_or_cos_b(normalized + -3.1415927f);
    amplitude = wave * 24.0f;
    blue_offset = FloatToInt(amplitude) + 12;
    blue += blue_offset;
    green_base = FloatToInt(wave * 48.0f);
    green_offset = green_base + 24;
    red_wave = FloatToInt(amplitude);
    green = green_base + 160;
    red_offset = red_wave + 12;
    red = red_wave + 76;
    if (*(short *)(hero1 + 0x20E) != 0) {
        float blend = 1.0f;
        int max = 40;
        int age = *(short *)(hero1 + 0x20E);
        if (max < age)
            blend = IntToFloat(45 - *(short *)(hero1 + 0x20E)) / IntToFloat(5);
        if (*(short *)(hero1 + 0x20E) < 20)
            blend = IntToFloat(*(short *)(hero1 + 0x20E)) / IntToFloat(20);
        blue -= FloatToInt((float)blue_offset * blend);
        green -= FloatToInt((float)green_offset * blend);
        red -= FloatToInt((float)red_offset * blend);
        blue += FloatToInt(blend * 112.0f);
        green -= FloatToInt(blend * 72.0f);
    }
    {
        int color = (alpha << 24) | (red << 16);
        color |= green << 8;
        color |= blue;
        *(int *)(object + 0x78) = color;
    }
    hero2 = (unsigned char *)&g_hero_state;
    if (hero2[0x22B4] != 0 || *(int *)(hero2 + 0x2294) == 124) return;
    if (FastDecTimer((short *)(hero2 + 0x118C)) && object[0x43] == 1) {
        *(short *)(hero2 + 0x118C) = math_random_int_range(50, 200);
        *(short *)(hero2 + 0x118E) = 1;
    }
    if (g_hero_state.timer == 0) return;
    g_hero_state.timer++;
    if (g_hero_state.timer > 21) g_hero_state.timer = 0;
    if (g_hero_state.timer == 0) {
        int i;
        for (i = 0; i < 4; i++)
            if (g_hero_state.effects[i].attached)
                moby_detach_manipulator((char *)object, (char *)&g_hero_state.effects[i]);
    } else {
        int i, j;
        const Vector *scale = g_hero_effect_scale_table;
        for (i = 0; i < 4; scale++, i++) {
            if (!g_hero_state.effects[i].attached) {
                AttachManipulator(object, g_hero_effect_manipulator_ids[i], (unsigned char *)&g_hero_state.effects[i]);
                g_hero_state.effects[i].absolute = 1;
                qcopy(&g_hero_state.effects[i].quat, &g_hero_effect_quat_table[i]);
                qcopy(&g_hero_state.effects[i].scale, scale);
                qcopy(&g_hero_state.effects[i].translation, &g_hero_effect_translation_table[i]);
                FastVecScale(&g_hero_state.effects[i].translation, &g_hero_state.effects[i].translation, *(float *)(object + 0x2C));
            }
        }
        for (j = 0; j < 4; j++)
            g_hero_state.effects[j].blend = g_hero_effect_blend_table[g_hero_state.timer];
    }
}
