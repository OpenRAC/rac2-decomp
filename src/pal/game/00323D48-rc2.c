#include "include_asm.h"

#include "common.h"
struct Vec3 { f32 x; f32 y; f32 z; };
struct Vec4 { f32 x; f32 y; f32 z; f32 w; };
extern void *cam_moby_create_pal(void *, s32, s16, s32, void *, void *, void *, s32, f32, f32);
extern void FastVecAdd(struct Vec3 *, struct Vec3 *, struct Vec4 *);
extern void vec_scale_to_length(struct Vec4 *, void *, f32);
extern void matrix_mul_vec3(struct Vec3 *, struct Vec3 *, void *);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 math_random_float_range(f32, f32);
extern f32 math_random_angle(void);
extern void func_PAL_003242C8(void);
extern s32 g_ground_check_inhibit;

void func_PAL_003240E8(void *arg0) {
    struct Vec4 loc0;
    struct Vec3 sp10;
    void *obj;
    void *v1;
    f32 t20;
    f32 t21;
    f32 t;
    f32 t22;
    s32 i;

    obj = (*(void **)((s8 *)(arg0) + (0x68)));
    vec_scale_to_length(&loc0, (s8 *)obj + 0xE0, 0.060000002f);
    for (i = 0; i < 0xF; i++) {
        if (!(((0x7F8 >> i) ^ 1) & 1)) {
            t20 = math_random_angle();
            t21 = math_random_float_range(3.0f, 5.0f) * 0.020000001f;
            sp10.x = math_fast_sin_or_cos_a(t20) * t21;
            t = math_fast_sin_or_cos_b(t20) * t21;
            sp10.z = 0.0f;
            sp10.y = t;
            sp10.z = math_random_float_range(3.0f, 5.0f) * 0.020000001f;
            if (g_ground_check_inhibit != 0) {
                matrix_mul_vec3(&sp10, &sp10, (s8 *)arg0 + 0xC0);
            }
            FastVecAdd(&sp10, &sp10, &loc0);
            t22 = math_random_float_range(90.0f, 270.0f);
            t = math_random_float_range(10.0f, 20.0f);
            v1 = cam_moby_create_pal(arg0, 2, (*(s16 *)((s8 *)(arg0) + (0xAA))), i, (s8 *)arg0 + 0x10, (s8 *)arg0 + 0xF0, &sp10, 0xFF, t22, t);
            if ((*(s32 *)((s8 *)(obj) + (0x2B4))) != 0 && v1 != 0) {
                (*(s32 *)((s8 *)(v1) + (0x64))) = (s32)func_PAL_003242C8;
            }
        }
    }
}
