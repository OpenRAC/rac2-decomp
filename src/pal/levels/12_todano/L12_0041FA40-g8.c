#include "include_asm.h"

#include "common.h"
typedef struct {
    f32 x, y, z, w;
} V __attribute__((aligned(16)));
typedef struct {
    u8 pad00[0x34];
    u8 damage;
    u8 pad35[0x1b];
    V origin;
    f32 heightSpeed;
    f32 angularSpeed;
    s32 timer;
    f32 radius;
    f32 age;
} Vars;
extern u8 *g_tracked_object_ptr;
extern u8 *g_second_tracked_object MACRO_ADDR;
extern V g_hero_position;
extern V g_zero_l12_vec MACRO_ADDR;
extern f32 g_ring_blast_start_radius __attribute__((sda));
extern f32 g_ring_blast_hero_range __attribute__((sda));
extern f32 g_ring_blast_max_radius __attribute__((sda));
extern f32 g_ring_blast_duration_seconds __attribute__((sda));
extern f32 g_ring_blast_expand_speed __attribute__((sda));
extern s32 g_ring_blast_spark_color_a __attribute__((sda));
extern s32 g_ring_blast_spark_color_b __attribute__((sda));
extern f32 g_ring_blast_spark_size_min __attribute__((sda));
extern f32 g_ring_blast_spark_size_max __attribute__((sda));
extern f32 g_ring_blast_spark_angle_range __attribute__((sda));
extern s32 g_ring_blast_spark_count __attribute__((sda));
extern s32 g_ring_blast_spark_enabled __attribute__((sda));
extern void DrawAnimatedRings(void *);
extern s32 tracked_object_is_open(void);
extern void tracked_moby_set_state_pal(s32, s32);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void FastVecAdd(void *, void *, void *);
extern s32 CollLine(void *, void *, s32, void *, void *);
extern void make_hit_descriptor(void *, void *, s32, f32, void *);
extern s32 second_tracked_object_is_open(void), flag_set_first_pending(void *), math_fast_float_d(s32 *);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern f32 fast_vec_dist(void *, void *), vec_distance_xy(void *, void *), FastAddRotations(f32, f32);
extern f32 math_random_float_range(f32, f32), math_fast_sin_or_cos_b(f32), math_fast_sin_or_cos_a(f32), math_random_angle(void);
extern s32 FloatToInt(f32), FastTweenColor(s32, s32, f32), math_random_int_below(s32);
extern f32 ApproachValue(f32 *, f32, f32);
extern int PlayMobySound(s32, s32, void *);
extern float math_step_value_toward_target(f32 *, f32 *, f32, f32, f32, f32);
extern void vec_scale_to_length(void *, void *, f32), vec_random_direction(void *, f32, f32);
extern void *part_spawn_hero_relative(void *, void *, s32, f32, u8, u8, s32);
extern char *part_spawn_flying_fragment_pal(void *, s32, void *, void *, s32, s32, void *, void *, void *, f32);
extern void global_object_start_pal(s32, s32);
typedef struct {
    u8 pad00[0x10];
    V position;
    u8 state;
    u8 pad21[3];
    u8 *classData;
    u8 pad28[0xc];
    u16 flags;
    u8 pad36[0x32];
    Vars *vars;
    u8 pad6c[0x2c];
    s32 collision;
    u8 pad9c[0x54];
    f32 rotation[4];
} Obj;

/* Raises the object, emits particles, and expands a damaging ring before reset. */
void expanding_ring_blast_update_pal(Obj *self)
{
    V spark_dir;
    u8 damage[0x30] __attribute__((aligned(16)));
    V next;
    Vars *vars = self->vars;

    switch (self->state) {
    case 0:
        qcopy(&vars->origin, &self->position);
        self->state = 1;
        break;
    case 1: {
        f32 distance;
        distance = 100000;
        if (tracked_object_is_open())
            distance = fast_vec_dist(&self->position, g_tracked_object_ptr + 0x10);
        else if (second_tracked_object_is_open())
            distance = fast_vec_dist(&self->position, g_second_tracked_object + 0x10);
        if (vec_distance_xy(&self->position, &g_hero_position) < g_ring_blast_hero_range ||
           part_find_owned_effect_slot(self, 0x30000, 0) || distance < g_ring_blast_hero_range * 0.5f) {
            self->state = 2;
            vars->timer = ((s32)(FloatToInt(g_ring_blast_duration_seconds * 60)) * 5 + 2) / 6;
            vars->radius = g_ring_blast_start_radius;
            vars->age = 0;
        }
        break;
    }
    case 2: {
        f32 step, ratio, angle, cosine, sine, size;
        s32 color, i;
        u8 life, alpha;
        if (flag_set_first_pending(self))
            PlayMobySound(0, 0, self);
        gfx_add_draw_callback_first(DrawAnimatedRings, self);
        vars->age += g_ring_blast_expand_speed * 0.020000001f;
        math_step_value_toward_target(&self->position.z, &vars->heightSpeed, vars->origin.z + 0.5f, 1, 0.012f, 1);
        ApproachValue(&vars->angularSpeed, 0.5026549f, 0.14400001f);
        self->rotation[2] = FastAddRotations(self->rotation[2], vars->angularSpeed);
        step = g_ring_blast_expand_speed * 0.020000001f;
        ratio = g_ring_blast_max_radius / step;
        angle = math_random_float_range(-15, 15) * 0.017453294f;
        sine = math_fast_sin_or_cos_b(angle);
        cosine = math_fast_sin_or_cos_a(angle);
        angle = math_random_angle();
        spark_dir.x = math_fast_sin_or_cos_a(angle) * cosine;
        spark_dir.y = math_fast_sin_or_cos_b(angle) * cosine;
        spark_dir.z = sine;
        vec_scale_to_length(&spark_dir, &spark_dir, step);
        color = FastTweenColor(g_ring_blast_spark_color_a, g_ring_blast_spark_color_b, math_random_float_range(0, 1));
        size = math_random_float_range(g_ring_blast_spark_size_min, g_ring_blast_spark_size_max);
        life = FloatToInt(math_random_float_range(1, 1.5f) * 7) & 255;
        alpha = math_random_int_below(255) & 255;
        part_spawn_hero_relative(&self->position, &spark_dir, color, size, life, alpha, 0);
        if (math_fast_float_d(&vars->timer)) {
            self->state = 3;
            vars->timer = 17;
            for (i = 0; i < g_ring_blast_spark_count; i++) {
                f32 angle, sine, cosine, size;
                s32 color;
                u8 life, alpha;
                angle = math_random_float_range(-g_ring_blast_spark_angle_range, g_ring_blast_spark_angle_range) * 0.017453294f;
                sine = math_fast_sin_or_cos_b(angle);
                cosine = math_fast_sin_or_cos_a(angle);
                angle = math_random_angle();
                spark_dir.x = math_fast_sin_or_cos_a(angle) * cosine;
                spark_dir.y = math_fast_sin_or_cos_b(angle) * cosine;
                spark_dir.z = sine;
                vec_scale_to_length(&spark_dir, &spark_dir, step);
                color = FastTweenColor(g_ring_blast_spark_color_a, g_ring_blast_spark_color_b, math_random_float_range(0, 1));
                size = math_random_float_range(g_ring_blast_spark_size_min, g_ring_blast_spark_size_max);
                life = FloatToInt(ratio * math_random_float_range(1, 1.5f)) & 255;
                alpha = math_random_int_below(255) & 255;
                part_spawn_hero_relative(&self->position, &spark_dir, color, size, life, alpha, 0);
            }
            vec_random_direction(&spark_dir, 0.020000001f, 0.040000003f);
            spark_dir.z = math_random_float_range(5, 8) * 0.020000001f;
            part_spawn_flying_fragment_pal(self, 0xFF6, &self->position, self->rotation, 0, 0, &spark_dir, &g_zero_l12_vec, &g_zero_l12_vec, 0);
        }
        break;
    }
    case 3: {
        f32 step, angle;
        s32 i;
        self->flags = (self->flags | 0x41) & 0xEFFF;
        self->collision = 0;
        if (g_ring_blast_max_radius < vars->radius) {
            if (g_ring_blast_spark_enabled) {
                self->flags = (self->flags & 0xEFBE) | 0x1000;
                self->collision = *(s32 *)(self->classData + 0x10);
                qcopy(&self->position, &vars->origin);
                self->state = 1;
                vars->angularSpeed = 0;
                vars->radius = 0;
            }
            break;
        }
        gfx_add_draw_callback_first(DrawAnimatedRings, self);
        step = g_ring_blast_expand_speed * 0.020000001f;
        vars->radius += step;
        vars->age += step;
        make_hit_descriptor(damage, self, 0x10001, (f32)vars->damage, &g_zero_l12_vec);
        angle = 0;
        spark_dir.x = math_fast_sin_or_cos_a(angle) * vars->radius;
        spark_dir.y = math_fast_sin_or_cos_b(angle) * vars->radius;
        spark_dir.z = 0;
        FastVecAdd(&spark_dir, &spark_dir, &self->position);
        angle = 0.52359885f;
        for (i = 11; i >= 0; i--) {
            next.x = math_fast_sin_or_cos_a(angle) * vars->radius;
            next.y = math_fast_sin_or_cos_b(angle) * vars->radius;
            next.z = 0;
            FastVecAdd(&next, &next, &self->position);
            CollLine(&next, &spark_dir, 9, self, damage);
            angle = FastAddRotations(angle, 0.52359885f);
            qcopy(&spark_dir, &next);
        }
        if (tracked_object_is_open() && fast_vec_dist(&self->position, g_tracked_object_ptr + 0x10) < vars->radius)
            tracked_moby_set_state_pal(1, 0);
        if (second_tracked_object_is_open() && fast_vec_dist(&self->position, g_second_tracked_object + 0x10) < vars->radius)
            global_object_start_pal(1, 0);
        break;
    }
    }
}
