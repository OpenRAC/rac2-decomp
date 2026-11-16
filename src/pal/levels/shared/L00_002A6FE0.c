#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct {
    u8 pad0[0x18];
    float z;
    u8 pad1c[0x34 - 0x1c];
    unsigned short flags;
    u8 pad36[0x78 - 0x36];
    unsigned int color;
    u8 pad7c[0xaa - 0x7c];
    short kind;
} GlowMoby;
typedef struct {
    u8 pad0;
    u8 initialized;
    u8 pad2[0x20 - 2];
    float scale[3];
} GlowManipulator;
typedef struct { u8 pad0[0x1868]; float phase; } GlowResident;
extern GlowResident g_hero_state;
typedef struct { u8 pad0[0x30]; int state; int timer; } SceneGlow;
extern int g_frame_l00_counter[] __attribute__((sda));
extern int g_current_map_index MACRO_ADDR;
extern SceneGlow g_tutorial_probe_context;
extern GlowManipulator g_pulsing_glow_record_default MACRO_ADDR;
extern GlowManipulator g_pulsing_glow_record_alt MACRO_ADDR;
extern unsigned char g_unlocked_item_flags[] __attribute__((sda));
extern float g_glow_scale __attribute__((sda));
extern float D_L00_001A7CF8_gp SDATA(D_L00_001A7CF8);
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);
extern void moby_transform_joint_to_world(char *, int, char *);
extern float math_fabs(float);
extern void hero_queue_glow_point(Vector *, unsigned int, float, float);
extern float FastAddRotations(float, float);
extern void AttachManipulator(GlowMoby *, unsigned int, GlowManipulator *);

/* Animate the object's glow and bind the appropriate auxiliary joint record. */
void update_moby_pulsing_glow_effects_pal(GlowMoby *object) {
    Vector position;
    GlowManipulator *record;
    int red, green, blue, alpha;
    int color;
    int middle;
    int period = 83;
    int kind, emit;
    float wave, denominator, pulse;
    object->flags |= 0x10;
    denominator = IntToFloat(83);
    wave = math_fast_sin_or_cos_b((((float)(g_frame_l00_counter[0] % period) / denominator) * 2.0f) * 3.1415927410125732f + -3.1415927410125732f);
    red = FloatToInt(wave * 24.0f);
    green = FloatToInt(wave * 52.0f);
    blue = FloatToInt(wave * 24.0f);
    middle = (green + 0xA2) << 8;
    color = (blue + 0x4C) << 16;
    color |= 0x80000000U;
    color |= middle;
    color |= red + 0x44;
    object->color = color;
    if (object->kind == 0x1159) {
        moby_transform_joint_to_world((char *)object, 6, (char *)&position);
        if (math_fabs(object->z - position.f[2]) > 2.0f)
            hero_queue_glow_point(&position, 0x200000C0U, 0.25f, 0.15f);
    } else if (object->kind == 0x57) {
        emit = 1;
        if (g_current_map_index == 3 && g_tutorial_probe_context.state == 7 && g_tutorial_probe_context.timer > 0x3B2)
            emit = 0;
        else if (g_current_map_index == 3 && g_tutorial_probe_context.state == 0)
            emit = 0;
        if (emit) {
            moby_transform_joint_to_world((char *)object, 7, (char *)&position);
            g_hero_state.phase = FastAddRotations(g_hero_state.phase, 0.08028516f);
            pulse = math_fast_sin_or_cos_b(g_hero_state.phase);
            alpha = (unsigned int)FloatToInt((pulse * 0.5f + 0.5f) * 13.0f) + 23U;
            alpha <<= 24;
            hero_queue_glow_point(&position, alpha | 0xC0U, 0.04f, 0.07f);
        } else object->color = 0x80505050U;
    } else if (!(g_current_map_index == 3 && g_tutorial_probe_context.state == 7 && g_tutorial_probe_context.timer > 0x3B2)) {
        moby_transform_joint_to_world((char *)object, 1, (char *)&position);
        g_hero_state.phase = FastAddRotations(g_hero_state.phase, 0.08028516f);
        pulse = math_fast_sin_or_cos_b(g_hero_state.phase);
        alpha = (unsigned int)FloatToInt((pulse * 0.5f + 0.5f) * 13.0f) + 23U;
        alpha <<= 24;
        hero_queue_glow_point(&position, alpha | 0xC0U, 0.04f, 0.07f);
    }
    kind = object->kind;
    record = &g_pulsing_glow_record_default;
    if (kind == 0x27D) record = &g_pulsing_glow_record_alt;
    if (g_unlocked_item_flags[3] != 0) {
        if (record->initialized == 0) {
            float scale;
            if (kind == 0x27D) {
                AttachManipulator(object, 1, record);
                scale = g_glow_scale;
            } else {
                AttachManipulator(object, kind == 0x57 ? 5 : 2, record);
                scale = D_L00_001A7CF8_gp;
            }
            record->scale[0] = scale;
            record->scale[1] = scale;
            record->scale[2] = scale;
        }
    }
}




