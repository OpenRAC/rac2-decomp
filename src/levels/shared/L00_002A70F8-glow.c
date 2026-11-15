/* func_L00_002A70F8 in its own unit (-O2 -G0 -ffunction-sections).
 * Counterpart of RAC1's update_moby_pulsing_glow_effects
 * (src/overlays/shared/hero_idle_and_animation.c, GPL-3.0). As there, the two
 * attachment arms read the same scale through two spellings of one address
 * (RAC1: sound_volume_10 and sound_volume + 0x28), which keeps their calls apart;
 * here the canonical sda name and its SDATA view, both $gp-relative. */
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
extern SceneGlow D_L00_001BCAC0;
extern GlowManipulator D_L00_001B1710 MACRO_ADDR;
extern GlowManipulator D_L00_001B1750 MACRO_ADDR;
extern unsigned char D_001A7A40[] __attribute__((sda));
extern float D_L00_001A7CF8 __attribute__((sda));
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
void update_moby_pulsing_glow_effects(GlowMoby *object) {
    Vector position;
    GlowManipulator *record;
    int red, green, blue, alpha;
    int color;
    int middle;
    int period = 100;
    int kind, emit;
    float wave, denominator, pulse;
    object->flags |= 0x10;
    denominator = IntToFloat(100);
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
    if (object->kind == 0x1159 /* moby class 4441 */) {
        moby_transform_joint_to_world((char *)object, 6, (char *)&position);
        if (math_fabs(object->z - position.f[2]) > 2.0f)
            hero_queue_glow_point(&position, 0x200000C0U, 0.25f, 0.15f);
    } else if (object->kind == 0x57 /* Clank */) {
        emit = 1;
        if (g_current_map_index == 3 && D_L00_001BCAC0.state == 7 && D_L00_001BCAC0.timer > 0x470)
            emit = 0;
        else if (g_current_map_index == 3 && D_L00_001BCAC0.state == 0)
            emit = 0;
        if (emit) {
            moby_transform_joint_to_world((char *)object, 7, (char *)&position);
            g_hero_state.phase = FastAddRotations(g_hero_state.phase, 0.06690429896116257f);
            pulse = math_fast_sin_or_cos_b(g_hero_state.phase);
            alpha = (unsigned int)FloatToInt((pulse * 0.5f + 0.5f) * 13.0f) + 23U;
            alpha <<= 24;
            hero_queue_glow_point(&position, alpha | 0xC0U, 0.04f, 0.07f);
        } else object->color = 0x80505050U;
    } else if (!(g_current_map_index == 3 && D_L00_001BCAC0.state == 7 && D_L00_001BCAC0.timer > 0x470)) {
        moby_transform_joint_to_world((char *)object, 1, (char *)&position);
        g_hero_state.phase = FastAddRotations(g_hero_state.phase, 0.06690429896116257f);
        pulse = math_fast_sin_or_cos_b(g_hero_state.phase);
        alpha = (unsigned int)FloatToInt((pulse * 0.5f + 0.5f) * 13.0f) + 23U;
        alpha <<= 24;
        hero_queue_glow_point(&position, alpha | 0xC0U, 0.04f, 0.07f);
    }
    kind = object->kind;
    record = &D_L00_001B1710;
    if (kind == 0x27D) record = &D_L00_001B1750;
    if (D_001A7A40[3] != 0) {
        if (record->initialized == 0) {
            float scale;
            if (kind == 0x27D) {
                AttachManipulator(object, 1, record);
                scale = D_L00_001A7CF8;
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
