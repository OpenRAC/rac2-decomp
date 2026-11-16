#include "include_asm.h"

#include "common.h"
extern u8 g_hero_position[];
extern u32 g_current_map_index MACRO_ADDR;
extern s32 g_bolt_amount_by_level[];
extern f32 fast_vec_dist(u8 *, u8 *);
extern void part_spawn_bolt_pickups_pal(u8 *, s32, s32, s32, s32, s32, f32);

/* Spawns bolt pickups scaled by the level's bolt amount; the hero standing close gives mode 3. */
void part_spawn_scaled_bolts_pal(u8 *object, s32 multiplier, f32 height) {
    s32 mode = 1;
    u32 i;
    s32 v;

    if (fast_vec_dist(object + 0x10, g_hero_position) < 7.0f)
        mode = 3;
    i = g_current_map_index;
    if (i > 25)
        i = 25;
    v = g_bolt_amount_by_level[i] * multiplier - 1;
    part_spawn_bolt_pickups_pal(object, v, v, mode, -1, 0, height);
}


extern void func_0029CC50(void);

/* Resets the particle effects (PAL). */
void part_reset_effects_pal(void)
{
    func_0029CC50();
}

typedef int TI __attribute__((mode(TI)));
typedef union { TI q; float f[4]; } Vector;
extern void vec_random_direction(void *, float, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_angle(void);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern char *cam_moby_create_pal(char *, int, int, int, void *, void *, void *, unsigned char, float, float);
extern void glow_fade_update_pal(char *);
extern void set_moby_color(char *, unsigned long, unsigned long, unsigned long);

/* Spawn count effects around origin, tinted by color (0xAABBGGRR). */
void part_spawn_glow_fade_effects_pal(char *owner, void *origin, int count, int mode,
                       void *velocity_origin, int color, Vector *fixed_rotation,
                       float radius, float speed, float low_scale, float high_scale)
{
    Vector velocity, position, rotation, random_rotation;
    char *effect, *payload;
    int kind, variant;
    int r, g, b, t;
    u32 packed;
    int i;
    float life;
    for (i = 0; i < count; i++) {
        vec_random_direction(&velocity, 0.0f, speed * 0.020000001f);
        FastVecAdd(&velocity, &velocity, velocity_origin);
        vec_random_direction(&position, 0.0f, radius);
        FastVecAdd(&position, &position, origin);
        random_rotation.q = 0;
        random_rotation.f[0] = math_random_angle();
        random_rotation.f[2] = math_random_angle();
        rotation.q = random_rotation.q;
        if (fixed_rotation != 0)
            qcopy(&rotation, fixed_rotation);
        kind = mode ? 2 : 1;
        variant = math_random_int_below(4);
        life = math_random_float_range(10.0f, 20.0f);
        effect = cam_moby_create_pal(owner, kind, 0x43e, variant, &position, &rotation, &velocity,
                               0xff, 180.0f, life);
        if (effect != 0) {
            *(void (**)(char *))(effect + 0x64) = glow_fade_update_pal;
            r = color & 0xff;
            t = (unsigned int)color >> 24;
            *(float *)(effect + 0x2c) = *(float *)(*(char **)(effect + 0x24) + 0x24)
                                        * math_random_float_range(low_scale, high_scale);
            b = (color >> 16) & 0xff;
            g = (color >> 8) & 0xff;
            payload = *(char **)(effect + 0x68);
            set_moby_color(effect, r, g, b);
            ((unsigned char *)effect)[0x23] = t;
            if (r != g || r != b)
                t = 1;
            else
                t = 0;
            packed = t << 24;
            packed |= b << 16;
            packed |= g << 8;
            packed |= r;
            *(u32 *)(payload + 0x50) = packed;
        }
    }
}

