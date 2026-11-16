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
extern void part_update_fading_debris_pal(void);
extern s32 g_ground_check_inhibit;

/* Throws out eight pieces of debris in random directions when the robot enemy is destroyed. */
void robot_spawn_death_debris_pal(void *moby) {
    struct Vec4 back_dir;
    struct Vec3 velocity;
    void *data;
    void *piece;
    f32 angle;
    f32 speed;
    f32 value;
    f32 spin;
    s32 i;

    data = (*(void **)((s8 *)(moby) + (0x68)));
    vec_scale_to_length(&back_dir, (s8 *)data + 0xE0, 0.060000002f);
    for (i = 0; i < 0xF; i++) {
        if (!(((0x7F8 >> i) ^ 1) & 1)) {
            angle = math_random_angle();
            speed = math_random_float_range(3.0f, 5.0f) * 0.020000001f;
            velocity.x = math_fast_sin_or_cos_a(angle) * speed;
            value = math_fast_sin_or_cos_b(angle) * speed;
            velocity.z = 0.0f;
            velocity.y = value;
            velocity.z = math_random_float_range(3.0f, 5.0f) * 0.020000001f;
            if (g_ground_check_inhibit != 0) {
                matrix_mul_vec3(&velocity, &velocity, (s8 *)moby + 0xC0);
            }
            FastVecAdd(&velocity, &velocity, &back_dir);
            spin = math_random_float_range(90.0f, 270.0f);
            value = math_random_float_range(10.0f, 20.0f);
            piece = cam_moby_create_pal(moby, 2, (*(s16 *)((s8 *)(moby) + (0xAA))), i, (s8 *)moby + 0x10, (s8 *)moby + 0xF0, &velocity, 0xFF, spin, value);
            if ((*(s32 *)((s8 *)(data) + (0x2B4))) != 0 && piece != 0) {
                (*(s32 *)((s8 *)(piece) + (0x64))) = (s32)part_update_fading_debris_pal;
            }
        }
    }
}
