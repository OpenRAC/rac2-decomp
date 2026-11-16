#include "names.h"
/* func_PAL_L05_0039A9A8, the PAL copy of func_L05_00397B30: the same C, where func_L05_00398378
   becomes func_PAL_L05_0039B1F0; func_L05_00424990 becomes func_PAL_L05_0042A240. */
#include "common.h"

extern float math_random_angle(void);

typedef struct {
    float f[38];
    int timer;
    char *owner;
    int active;
    int pad;
    int dying;
    int pad2;
} Record233560;

typedef struct {
    float v[4];
    char *owner;
    int flags;
    unsigned char kind;
    unsigned char mode;
    unsigned short id;
    float value;
    int one;
} HitRecord97B30;

extern Record233560 g_effect_records[24];
extern char g_projectile_target_pos[];
extern char g_projectile_pos_scratch[];
extern float g_homing_hit_value_b __attribute__((sda));
extern float g_homing_hit_value_a __attribute__((sda));
extern float g_homing_speed_alt __attribute__((sda));
extern float g_homing_speed_normal __attribute__((sda));

extern void FastVecAdd(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastAddRotations(float, float);
extern int math_fast_float_d(void *);
extern unsigned char *func_L05_003D1E60(void *, int, int);
extern void moby_mark_spawned(void *);
extern void vec_build_spherical_offset(void *, float, float, float);
extern int CollLine(void *, void *, int, void *, int);
extern void record_claim_effect_slot_pal(void *, void *, int);
extern void record_animate_owned(char *);
extern void record_update_owned_effects(char *);
extern void gfx_add_draw_callback_third(void (*)(char *), char *);
extern int coll_process_hit(void *, float, int, char *, void *);
extern int GetCollHitMaterial(void);
extern int coll_test_point(void *, float, int, void *);
extern void SubmitFlightStateHitRecord(char *, char *, char *);
extern char *moby_spawn_large_explosion_pal(char *, int, int, int, int, int, int, int, int, int, int, float);

/* Moves the projectile along its velocity, slowing it and spinning its two angles. When its life
   runs out or it leaves the 2..1021 box it releases all twenty-four records, bursts and removes
   itself. Each time its second timer expires it throws a hit record towards a random point 21
   units away. On hitting the world it submits its hit record, bursts and removes itself. */
void homing_l05_projectile_update_pal(char *obj)
{
    float old[4];
    float target[4];
    HitRecord97B30 hit;
    char *state = *(char **)(obj + 0x68);
    float speed;
    int i;
    int collided;

    qcopy(old, obj + 0x10);
    FastVecAdd(obj + 0x10, obj + 0x10, state);
    speed = FastVecLength(state);
    if (*(int *)(state + 0x24))
        speed *= 0.986f;
    else
        speed *= 0.982f;
    vec_scale_to_length(state, state, speed);
    *(float *)(obj + 0xF8) = FastAddRotations(*(float *)(obj + 0xF8), 0.05f);
    *(float *)(obj + 0xF4) = FastAddRotations(*(float *)(obj + 0xF4), 0.03f);

    if (math_fast_float_d(state + 0x18)) {
        for (i = 0; i < 24; i++)
            g_effect_records[i].owner = 0;
        func_L05_003D1E60(obj + 0x10, 0, 0);
        moby_mark_spawned(obj);
        return;
    }
    if (*(float *)(obj + 0x10) < 2.0f || *(float *)(obj + 0x10) > 1021.0f ||
        *(float *)(obj + 0x14) < 2.0f || *(float *)(obj + 0x14) > 1021.0f ||
        *(float *)(obj + 0x18) < 2.0f || *(float *)(obj + 0x18) > 1021.0f) {
        for (i = 0; i < 24; i++)
            g_effect_records[i].owner = 0;
        func_L05_003D1E60(obj + 0x10, 0, 0);
        moby_mark_spawned(obj);
        return;
    }

    if (math_fast_float_d(state + 0x28)) {
        vec_build_spherical_offset(target, 21.0f, math_random_angle(), math_random_angle());
        FastVecAdd(target, target, obj + 0x10);
        if (CollLine(obj + 0x10, target, 0, obj, 0))
            qcopy(target, g_projectile_target_pos);
        record_claim_effect_slot_pal(obj, target, 1);
        record_animate_owned(obj);
        gfx_add_draw_callback_third(record_update_owned_effects, obj);

        hit.owner = obj;
        hit.flags = 0x810000;
        if (*(int *)(state + 0x24))
            hit.value = g_homing_hit_value_b;
        else
            hit.value = g_homing_hit_value_a;
        hit.one = 1;
        qcopy(hit.v, state);
        vec_scale_to_length(hit.v, hit.v, 1.0f);
        hit.kind = 3;
        hit.v[3] = 5627.925f;
        hit.mode = 2;
        hit.id = *(unsigned short *)(obj + 0xAA);
        if (*(int *)(state + 0x24))
            speed = g_homing_speed_alt;
        else
            speed = g_homing_speed_normal;
        coll_process_hit(obj + 0x10, speed, 1, *(char **)(state + 0x20), &hit);
    }

    if (GetCollHitMaterial() != 6) {
        collided = 0;
        if (coll_test_point(obj + 0x10, 1.0f, 16, *(void **)(state + 0x20))) {
            collided = 1;
            qcopy(obj + 0x10, g_projectile_pos_scratch);
        }
        if (collided || CollLine(old, obj + 0x10, 16, *(void **)(state + 0x20), 0)) {
            qcopy(obj + 0x10, g_projectile_target_pos);
            SubmitFlightStateHitRecord(obj, state, obj + 0x10);
            if (*(int *)(state + 0x24))
                moby_spawn_large_explosion_pal(obj + 0x10, 0, 50, 30, 30, 30, 40, 1, 1, 1, 1, 2.0f);
            func_L05_003D1E60(obj + 0x10, 0, 0);
            moby_mark_spawned(obj);
        }
    }
}
