#include "include_asm.h"

#include "common.h"
extern s32 g_explosion_particle_trim;
extern s32 g_001AFC6C __attribute__((sda));
extern f32 g_explosion_speed_a __attribute__((sda));
extern f32 g_explosion_speed_b __attribute__((sda));
extern s8 g_active_camera[];
struct Vec4 { f32 x; f32 y; f32 z; f32 w; };
struct Obj { s8 pad[0x10]; struct Vec4 pos; };
struct Tab { s8 pad[0x140]; f32 f140; f32 f144; };
f32 math_random_float_range(f32 a, f32 b);
f32 math_random_angle(void);
void vec_build_spherical_offset(struct Vec4 *p, f32 x, f32 y, f32 z);
s32 math_random_int_range(s32 a, s32 b);
void part_spawn_growing_puff_pal(struct Vec4 *a, struct Vec4 *b, u32 c, s32 d, s32 e, f32 f);
void FastVecAdd(struct Vec4 *a, struct Vec4 *b, struct Vec4 *c);
f32 mat_fast_helper_a(f32 a, f32 b);
f32 math_random_signed_float_range(f32 a, f32 b);
int FloatToInt(f32 a);
f32 FastAddRotations(f32 a, f32 b);
f32 math_fast_sin_or_cos_a(f32 a);
f32 math_fast_sin_or_cos_b(f32 a);
unsigned char *part_spawn_spinning_spark_pal_2(struct Vec4 *a, struct Vec4 *b, s32 c);
void moby_release_slot_by_id(struct Obj *a);
void moby_mark_spawned(struct Obj *a);

/* Explodes the creature: spawns a burst of particles and sparks, then frees the moby. */
void explosion_effect_update_pal(struct Obj *moby)
{
    struct Vec4 vec_b;
    struct Vec4 vec_a;
    struct Tab *camera;
    s32 i;
    s32 j;
    f32 radius;
    f32 yaw;
    f32 pitch;
    f32 z_lift;
    f32 vel_radius;
    f32 vel_yaw;
    f32 vel_pitch;
    s32 life;
    f32 cam_angle;
    f32 spark_angle;
    f32 jitter_x;
    f32 jitter_y;
    f32 jitter_z;
    f32 angle_jitter;
    f32 sin_val;
    f32 cos_val;
    f32 speed;

    i = 0;
    if (0x21 - g_explosion_particle_trim > 0) {
        do {
            i++;
            radius = math_random_float_range(0.0f, 0.3700000047683716f);
            yaw = math_random_angle();
            pitch = math_random_angle();
            vec_build_spherical_offset(&vec_a, radius, yaw, pitch);
            z_lift = math_random_float_range(0.3499999940395355f, 0.6000000238418579f);
            vec_a.z = vec_a.z + z_lift;
            FastVecAdd(&vec_a, &vec_a, &moby->pos);
            vel_radius = math_random_float_range(0.002f, 0.020000001f);
            vel_yaw = math_random_angle();
            vel_pitch = math_random_angle();
            vec_build_spherical_offset(&vec_b, vel_radius, vel_yaw, vel_pitch);
            life = math_random_int_range(0x19, 0x2F);
            part_spawn_growing_puff_pal(&vec_a, &vec_b, 0x4F20507F, 0x102F, life, 150000.0f);
        } while (i < 0x21 - g_explosion_particle_trim);
    }
    j = 0;
    if (0x32 - g_explosion_particle_trim > 0) {
        camera = (struct Tab *)g_active_camera;
        do {
            j++;
            cam_angle = mat_fast_helper_a(camera->f140 - moby->pos.x, camera->f144 - moby->pos.y);
            FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
            jitter_x = math_random_signed_float_range(0.0f, 0.15000000596046448f);
            vec_b.x = moby->pos.x + jitter_x;
            jitter_y = math_random_signed_float_range(0.0f, 0.15000000596046448f);
            vec_b.y = moby->pos.y + jitter_y;
            jitter_z = math_random_signed_float_range(0.0f, 0.15000000596046448f);
            vec_b.z = moby->pos.z + jitter_z;
            speed = g_explosion_speed_a;
            angle_jitter = math_random_signed_float_range(0.0f, -1.5707964897155762f);
            spark_angle = FastAddRotations(cam_angle, angle_jitter);
            sin_val = math_fast_sin_or_cos_a(spark_angle);
            vec_a.x = sin_val * 0.020000001f * speed;
            cos_val = math_fast_sin_or_cos_b(spark_angle);
            vec_a.y = cos_val * 0.020000001f * speed;
            speed = g_explosion_speed_b;
            vec_a.z = speed * 0.020000001f;
            part_spawn_spinning_spark_pal_2(&vec_b, &vec_a, 0xFA);
        } while (j < 0x32 - g_explosion_particle_trim);
    }
    g_001AFC6C = g_explosion_particle_trim - 1;
    moby_release_slot_by_id(moby);
    moby_mark_spawned(moby);
}
