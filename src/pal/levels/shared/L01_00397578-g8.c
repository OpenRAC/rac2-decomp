#include "include_asm.h"

#include "common.h"
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float), fast_subtract_rotations(float, float);
extern void FastVecAdd(void *, void *, void *), vec_clear_128(void *);
extern void FadeToBlack(int), hero_reset_for_area_start(int), hero_reset_position_and_direction_pal(void *, void *, int, int);
extern int PlayMobySound(int, int, void *);
extern void SetCamera5Pose(void *, void *, int, int, int), object_copy_vector_to_selected(void *), cam_set_state_rotation(void *);
extern void func_PAL_002A7E68(void *, int, int, int), set_hero_animation_pal(int, int, float);
extern unsigned char g_state_flag_c;
extern int g_camera_lock_flag;
typedef struct {
    char pad[0x80];
    float pos[4];
    float rot[4];
    char pad2[0x2214];
    unsigned char state;
    char pad3[10];
    unsigned char flag;
} TransitionPlayerState;
extern TransitionPlayerState g_hero_state;

void func_PAL_L01_0039A520(unsigned char *m) {
    float a[4], b[4], c[4], d[4];
    char *p = *(char **)(m + 0x68);
    a[0] = math_fast_sin_or_cos_a(*(float *)(p + 0x1C))*2.5f;
    a[1] = math_fast_sin_or_cos_b(*(float *)(p + 0x1C))*2.5f;
    a[2] = 0;
    FastVecAdd(a, a, p + 0x10);
    vec_clear_128(b);
    b[2] = FastAddRotations(*(float *)(p + 0x1C), 3.1415929794311523f);
    FadeToBlack(8);
    if (g_hero_state.state == 3) hero_reset_for_area_start(0);
    hero_reset_position_and_direction_pal(a, b, 0x6F, 0);
    PlayMobySound(0, 0, m);
    c[0] = math_fast_sin_or_cos_a(*(float *)(p + 0x1C))*1.25f;
    c[1] = math_fast_sin_or_cos_b(*(float *)(p + 0x1C))*1.25f;
    c[2] = 0;
    c[0] += math_fast_sin_or_cos_a(FastAddRotations(*(float *)(p + 0x1C), 1.5707964897155762f))*4.0f;
    c[1] += math_fast_sin_or_cos_b(FastAddRotations(*(float *)(p + 0x1C), 1.5707964897155762f))*4.0f;
    FastVecAdd(c, c, p + 0x10);
    c[2] += 1;
    vec_clear_128(d);
    d[2] = fast_subtract_rotations(*(float *)(p + 0x1C), 1.5707964897155762f);
    SetCamera5Pose(c, d, 1, 0, 0);
    object_copy_vector_to_selected(c);
    cam_set_state_rotation(d);
    qcopy_nc(m + 0x10, g_hero_state.pos);
    qcopy_nc(m + 0xF0, g_hero_state.rot);
    if (m[0x43] != 1) func_PAL_002A7E68(m, 1, 0, 0);
    set_hero_animation_pal(0x7B, 0, 0.0f);
    if (g_state_flag_c) *(unsigned short *)(m + 0x34) |= 0x8000;
    g_hero_state.flag = 1;
    g_camera_lock_flag = 1;
    m[0x20] = 2;
    *(int *)(p + 0x6C) = 50;
}

typedef struct {
    u8 pad0[0x18];
    f32 f18;
    u8 pad1[0x60 - 0x1C];
    f32 f60;
    f32 f64;
    f32 f68;
} State_397870;
typedef struct {
    u8 pad0[0x24];
    f32 f24;
} Class_397870;
typedef struct {
    u8 pad0[0x18];
    f32 f18;
    u8 pad1[0x20 - 0x1C];
    u8 b20;
    u8 pad2[0x24 - 0x21];
    Class_397870 *cls;
    u8 pad3[0x2C - 0x28];
    f32 f2C;
    u8 pad4[0x68 - 0x30];
    State_397870 *st;
    u8 pad5[0xF0 - 0x6C];
    f32 fF0;
    f32 fF4;
    f32 fF8;
    f32 fFC;
} Obj_397870;
extern void part_spawn_sparkle_trail_above_ground_pal(Obj_397870 *a0);
extern float g_collectible_height_scale __attribute__((sda));
extern float g_bob_base_height __attribute__((sda));
extern float g_bob_l01_amplitude __attribute__((sda));
extern float g_bolt_bob_spin_speed __attribute__((sda));
extern int g_sparkle_chance __attribute__((sda));
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern int math_random_int_below(int);
extern void func_PAL_L01_0039AE48(Obj_397870 *);

void func_PAL_L01_0039AC80(Obj_397870 *a0)
{
    State_397870 *s1 = a0->st;
    float f;

    a0->f2C = a0->cls->f24 * g_collectible_height_scale;

    if (a0->b20 == 1) {
        f = math_fast_sin_or_cos_b(a0->fFC);
        a0->f18 = s1->f18 + g_bob_base_height + g_bob_l01_amplitude * f;
        a0->fF0 = FastAddRotations(a0->fF0, s1->f68);
        a0->fF4 = FastAddRotations(a0->fF4, s1->f64);
        a0->fF8 = FastAddRotations(a0->fF8, s1->f60);
        a0->fFC = FastAddRotations(a0->fFC, 0.0003490659f * g_bolt_bob_spin_speed);
    }

    func_PAL_L01_0039AE48(a0);
    if (math_random_int_below(g_sparkle_chance) == 0)
        part_spawn_sparkle_trail_above_ground_pal(a0);
}
