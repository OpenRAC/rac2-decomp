/* func_L08_004207D0: the radar HUD (levels 08 and 19): three labels, an anchor sprite and one
 * sprite per nearby entity of the anchor's list. Own unit for -g and -frac2-zero-ti-por.
 * label_y/hud_coord are the dead-test HUD helpers (allowed by owner rulings of 7 and 8 November 2026). */
#include "common.h"
typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
extern u8 *D_L08_001A904C MACRO_ADDR, *D_L08_001B29DC MACRO_ADDR;
extern f32 D_L08_001B3244 MACRO_ADDR;
extern f32 D_L08_001B1B84 __attribute__((sda)), D_L08_001B1B88 __attribute__((sda));
extern f32 D_L08_001B1B8C __attribute__((sda)), D_L08_001B1B90 __attribute__((sda));
extern s32 D_L08_001B1B94 __attribute__((sda)), D_L08_001B1B98 __attribute__((sda));
extern f32 D_L08_001B1B9C __attribute__((sda));
extern s32 D_L08_001B1BA0 __attribute__((sda));
extern f32 D_L08_001B1BA4 __attribute__((sda));
extern u32 D_L08_001B1BA8 __attribute__((sda));
extern u16 *D_L08_001FB660[];
extern u8 D_L08_001B9D30[];
extern s32 hero_begin_saved_float_hold(void), hero_end_saved_float_hold(void);
extern void hero_set_saved_float_and_update(void);
extern char *table_find_by_id(void *, s32);
extern void gfx_draw_scaled_object_two_axes(char *, u32, f32, f32, f32, f32, f32);
extern u64 GetEffectTextureDescriptor(s32);
extern void AppendSubpixelTexturedScreenQuad(f32, f32, f32, f32, s32, s32, s32, s32, u64, u64);
extern f32 fast_vec_dist(void *, void *);
extern void euler_rotation_basis(void *, void *), FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32), mat_fast_helper_c(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern s32 FloatToInt(f32);

extern int D_L08_001B3240;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L08_001B3240;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = D_L08_001B3240;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == 1)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}

/* Draws the radar on screen: three text labels, a centre marker, and a fading dot for every
   nearby object, placed by its direction and distance from the hero's vehicle. */
void radar_draw(u8 *vehicle)
{
    Vector offset, euler;
    f32 rotation[12], inverse[12];
    u8 *vars, *blip, *anchor_obj;
    char *label1, *label2, *label3;
    u16 *list_start, *id_cursor;
    f32 dot_y, distance, dot_size, dot_x;
    s32 dot_alpha;
    s64 dot_color;
    u64 texture;
    f32 half;
    hero_begin_saved_float_hold();
    hero_set_saved_float_and_update();
    vars = *(u8 **)(vehicle + 0x68);
    label1 = table_find_by_id(D_L08_001A904C + 0x8710, 0xBA);
    label2 = table_find_by_id(D_L08_001A904C + 0x8710, 0xBB);
    label3 = table_find_by_id(D_L08_001A904C + 0x8710, 0xBC);
    gfx_draw_scaled_object_two_axes(label1, 0x60442D00, D_L08_001B1B84 + 4.0f, (f32)label_y(label1, D_L08_001B1B88 + 4.0f, D_L08_001B3244, 0.5f, 1), 0.8f, -0.8f, 0.0f);
    half = 0.5f;
    gfx_draw_scaled_object_two_axes(label2, 0x60241700, D_L08_001B1B84 + 4.0f, (f32)label_y(label1, D_L08_001B1B88 + 4.0f, D_L08_001B3244, 0.5f, 1), 0.8f, -0.8f, 0.0f);
    gfx_draw_scaled_object_two_axes(label3, 0x55F0C070, D_L08_001B1B84 + 4.0f, (f32)label_y(label3, D_L08_001B1B88 + 4.0f, D_L08_001B3244, half, 1), 0.8f, -0.8f, 0.0f);
    dot_y = (f32)label_y(vehicle, D_L08_001B1B88, D_L08_001B3244, 0.5f, 1);
    texture = GetEffectTextureDescriptor(D_L08_001B1BA0);
    AppendSubpixelTexturedScreenQuad(D_L08_001B1B84, dot_y, D_L08_001B1B8C, D_L08_001B1B90,
                     0, 0, D_L08_001B1B94, D_L08_001B1B98, 0x80808080UL, texture);
    hero_end_saved_float_hold();
    anchor_obj = *(u8 **)(vars + 0x1B0);
    if (!anchor_obj) return;
    list_start = D_L08_001FB660[anchor_obj[0x21]];
    if (!list_start) return;
    id_cursor = list_start;
    do {
        blip = D_L08_001B29DC + ((*id_cursor & 0x7FFF) << 8);
        if (!blip || blip[0x20] == 0xFE || blip[0x20] == 0xFD || *(s16 *)(blip + 0xAA) == MOBY_CLASS_DESERT_CRYSTAL_SHELL) continue;
        distance = fast_vec_dist(vehicle + 0x10, blip + 0x10);
        if (distance <= D_L08_001B1BA4) {
            dot_y = distance / D_L08_001B1BA4;
            dot_y *= D_L08_001B1B9C;
            euler.q = 0;
            euler.f[2] = 1.5707964f;
            euler_rotation_basis(rotation, &euler);
            FastVecSub(&offset, blip + 0x10, vehicle + 0x10);
            vec_scale_to_length(&offset, &offset, dot_y);
            mat_fast_helper_c(inverse, D_L08_001B9D30);
            matrix_mul_vec3(&offset, &offset, inverse);
            matrix_mul_vec3(&offset, &offset, rotation);
            dot_alpha = FloatToInt((1.0f - distance / D_L08_001B1BA4) * 128.0f);
            dot_size = offset.f[2] * 0.125f + D_L08_001B1B8C * 0.5f;
            if (dot_size > D_L08_001B1B8C + D_L08_001B1B8C) dot_size = D_L08_001B1B8C + D_L08_001B1B8C;
            else if (dot_size < 0.0f) dot_size = 0.0f;
            dot_x = offset.f[0] + D_L08_001B1B84;
            dot_y = (f32)hud_coord(D_L08_001B1B88 - offset.f[1], D_L08_001B3244, 0.5f);
            dot_color = (s32)(D_L08_001B1BA8 | ((u32)dot_alpha << 24));
            texture = GetEffectTextureDescriptor(D_L08_001B1BA0);
            AppendSubpixelTexturedScreenQuad(dot_x, dot_y, dot_size, dot_size, 0, 0, D_L08_001B1B94, D_L08_001B1B98, dot_color, texture);
        }
    } while ((s16)*id_cursor++ >= 0);
}
