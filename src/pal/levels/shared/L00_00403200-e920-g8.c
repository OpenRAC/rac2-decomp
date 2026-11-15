#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad00[0x50];
    float scale;
    u8 pad54[0xE0 - 0x54];
} TableEntry_L00_003FE920;
typedef struct {
    u8 pad000[0x750];
    float vec750[4];
    float vec760[4];
    u8 pad770[0xBF8 - 0x770];
    void *effect;
    u8 padBFC[0x1500 - 0xBFC];
    int optional;
    u8 pad1504[0x24EC - 0x1504];
    s16 state;
} Hero_L00_003FE920;
extern u8 D_00139581[];
extern TableEntry_L00_003FE920 g_weapon_l00_table[];
extern Hero_L00_003FE920 g_hero_state;
extern u8 D_L00_001B9010[];
extern int D_L00_001B0C0C __attribute__((sda));
extern float D_L00_001B0C10 __attribute__((sda));
extern void vec_scale_to_length(void *, void *, float);
extern void math_compute_aim_direction(void *, void *, float, float, float);
extern void vec_compute_object_to_target(void *, void *, void *, float);
extern float IntToFloat(int);
extern float FastAddRotations(float, float);
extern void math_build_axis_angle_quat(float, void *, void *);
extern void vec_rotate_by_quaternion(void *, void *, void *);

/* Build a per-frame step vector in out from the hero or object, rotated by a mode-dependent spread. */
void func_PAL_L00_00403200(u8 *obj, u8 *out, int mode, u8 *flag)
{
    float factor;
    float angle;
    float denom;
    float spread;
    float axis[4] __attribute__((aligned(16)));
    float rotation[4] __attribute__((aligned(16)));
    Hero_L00_003FE920 *h = &g_hero_state;

    {
        int index = D_00139581[0];
        TableEntry_L00_003FE920 *entry = g_weapon_l00_table + index;

        factor = entry->scale * 0.020000001f;
    }

    if (h->state == 1) {
        vec_scale_to_length(out, obj + 0xD0, -factor);
        qcopy(axis, obj + 0xC0);
    } else {
        vec_scale_to_length(out, h->vec760, factor);
        qcopy(axis, h->vec750);
        if (h->optional != 0) {
            math_compute_aim_direction(out, flag, factor, 32.0f, 0.6981318f);
            qcopy(axis, D_L00_001B9010);
        }
    }

    if (g_hero_state.effect != 0)
        vec_compute_object_to_target(g_hero_state.effect, flag, out, factor);

    factor = IntToFloat(mode);
    denom = IntToFloat(D_L00_001B0C0C - 1);
    factor = factor / denom;
    spread = ((D_L00_001B0C10 * 0.017453294f) * 2.0f) * factor;
    if (mode != 2) {
        float *rot = rotation;

        angle = FastAddRotations(-(D_L00_001B0C10 * 0.017453294f), spread);
        math_build_axis_angle_quat(angle, rot, axis);
        vec_rotate_by_quaternion(out, out, rot);
    }
}
