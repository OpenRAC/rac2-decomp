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
extern u8 *D_L12_001B090C;
extern u8 *D_L12_001B1360 MACRO_ADDR;
extern V g_hero_position;
extern V D_L12_001A8F20 MACRO_ADDR;
extern f32 D_L12_001B1C78 __attribute__((sda));
extern f32 D_L12_001B1C7C __attribute__((sda));
extern f32 D_L12_001B1C80 __attribute__((sda));
extern f32 D_L12_001B1C84 __attribute__((sda));
extern f32 D_L12_001B1C88 __attribute__((sda));
extern s32 D_L12_001B1C94 __attribute__((sda));
extern s32 D_L12_001B1C98 __attribute__((sda));
extern f32 D_L12_001B1C9C __attribute__((sda));
extern f32 D_L12_001B1CA0 __attribute__((sda));
extern f32 D_L12_001B1CA4 __attribute__((sda));
extern s32 D_L12_001B1CA8 __attribute__((sda));
extern s32 D_L12_001B1CAC __attribute__((sda));
extern void DrawAnimatedRings(void *);
extern s32 tracked_object_is_open(void);
extern void func_PAL_L00_003E38E8(s32, s32);
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
extern char *func_PAL_L02_0032D5F8(void *, s32, void *, void *, s32, s32, void *, void *, void *, f32);
extern void func_PAL_L00_004071F0(s32, s32);
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
void func_PAL_L12_0041FA40(Obj *self)
{
    V v;
    u8 damage[0x30] __attribute__((aligned(16)));
    V next;
    Vars *s = self->vars;

    switch (self->state) {
    case 0:
        qcopy(&s->origin, &self->position);
        self->state = 1;
        break;
    case 1: {
        f32 distance;
        distance = 100000;
        if (tracked_object_is_open())
            distance = fast_vec_dist(&self->position, D_L12_001B090C + 0x10);
        else if (second_tracked_object_is_open())
            distance = fast_vec_dist(&self->position, D_L12_001B1360 + 0x10);
        if (vec_distance_xy(&self->position, &g_hero_position) < D_L12_001B1C7C ||
           part_find_owned_effect_slot(self, 0x30000, 0) || distance < D_L12_001B1C7C * 0.5f) {
            self->state = 2;
            s->timer = ((s32)(FloatToInt(D_L12_001B1C84 * 60)) * 5 + 2) / 6;
            s->radius = D_L12_001B1C78;
            s->age = 0;
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
        s->age += D_L12_001B1C88 * 0.020000001f;
        math_step_value_toward_target(&self->position.z, &s->heightSpeed, s->origin.z + 0.5f, 1, 0.012f, 1);
        ApproachValue(&s->angularSpeed, 0.5026549f, 0.14400001f);
        self->rotation[2] = FastAddRotations(self->rotation[2], s->angularSpeed);
        step = D_L12_001B1C88 * 0.020000001f;
        ratio = D_L12_001B1C80 / step;
        angle = math_random_float_range(-15, 15) * 0.017453294f;
        sine = math_fast_sin_or_cos_b(angle);
        cosine = math_fast_sin_or_cos_a(angle);
        angle = math_random_angle();
        v.x = math_fast_sin_or_cos_a(angle) * cosine;
        v.y = math_fast_sin_or_cos_b(angle) * cosine;
        v.z = sine;
        vec_scale_to_length(&v, &v, step);
        color = FastTweenColor(D_L12_001B1C94, D_L12_001B1C98, math_random_float_range(0, 1));
        size = math_random_float_range(D_L12_001B1C9C, D_L12_001B1CA0);
        life = FloatToInt(math_random_float_range(1, 1.5f) * 7) & 255;
        alpha = math_random_int_below(255) & 255;
        part_spawn_hero_relative(&self->position, &v, color, size, life, alpha, 0);
        if (math_fast_float_d(&s->timer)) {
            self->state = 3;
            s->timer = 17;
            for (i = 0; i < D_L12_001B1CA8; i++) {
                f32 angle, sine, cosine, size;
                s32 color;
                u8 life, alpha;
                angle = math_random_float_range(-D_L12_001B1CA4, D_L12_001B1CA4) * 0.017453294f;
                sine = math_fast_sin_or_cos_b(angle);
                cosine = math_fast_sin_or_cos_a(angle);
                angle = math_random_angle();
                v.x = math_fast_sin_or_cos_a(angle) * cosine;
                v.y = math_fast_sin_or_cos_b(angle) * cosine;
                v.z = sine;
                vec_scale_to_length(&v, &v, step);
                color = FastTweenColor(D_L12_001B1C94, D_L12_001B1C98, math_random_float_range(0, 1));
                size = math_random_float_range(D_L12_001B1C9C, D_L12_001B1CA0);
                life = FloatToInt(ratio * math_random_float_range(1, 1.5f)) & 255;
                alpha = math_random_int_below(255) & 255;
                part_spawn_hero_relative(&self->position, &v, color, size, life, alpha, 0);
            }
            vec_random_direction(&v, 0.020000001f, 0.040000003f);
            v.z = math_random_float_range(5, 8) * 0.020000001f;
            func_PAL_L02_0032D5F8(self, 0xFF6, &self->position, self->rotation, 0, 0, &v, &D_L12_001A8F20, &D_L12_001A8F20, 0);
        }
        break;
    }
    case 3: {
        f32 step, angle;
        s32 i;
        self->flags = (self->flags | 0x41) & 0xEFFF;
        self->collision = 0;
        if (D_L12_001B1C80 < s->radius) {
            if (D_L12_001B1CAC) {
                self->flags = (self->flags & 0xEFBE) | 0x1000;
                self->collision = *(s32 *)(self->classData + 0x10);
                qcopy(&self->position, &s->origin);
                self->state = 1;
                s->angularSpeed = 0;
                s->radius = 0;
            }
            break;
        }
        gfx_add_draw_callback_first(DrawAnimatedRings, self);
        step = D_L12_001B1C88 * 0.020000001f;
        s->radius += step;
        s->age += step;
        make_hit_descriptor(damage, self, 0x10001, (f32)s->damage, &D_L12_001A8F20);
        angle = 0;
        v.x = math_fast_sin_or_cos_a(angle) * s->radius;
        v.y = math_fast_sin_or_cos_b(angle) * s->radius;
        v.z = 0;
        FastVecAdd(&v, &v, &self->position);
        angle = 0.52359885f;
        for (i = 11; i >= 0; i--) {
            next.x = math_fast_sin_or_cos_a(angle) * s->radius;
            next.y = math_fast_sin_or_cos_b(angle) * s->radius;
            next.z = 0;
            FastVecAdd(&next, &next, &self->position);
            CollLine(&next, &v, 9, self, damage);
            angle = FastAddRotations(angle, 0.52359885f);
            qcopy(&v, &next);
        }
        if (tracked_object_is_open() && fast_vec_dist(&self->position, D_L12_001B090C + 0x10) < s->radius)
            func_PAL_L00_003E38E8(1, 0);
        if (second_tracked_object_is_open() && fast_vec_dist(&self->position, D_L12_001B1360 + 0x10) < s->radius)
            func_PAL_L00_004071F0(1, 0);
        break;
    }
    }
}
