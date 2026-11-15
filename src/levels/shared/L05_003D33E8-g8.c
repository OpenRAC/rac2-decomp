#include "common.h"
#include "include_asm.h"

extern int D_L05_001B0F50 __attribute__((sda));

/* Resets the object's counters and a global flag to zero. */
void func_L05_00417730(char *object)
{
    char *state = *(char **)(object + 0x68);

    D_L05_001B0F50 = 0;
    *(int *)(state + 0x1BC) = 0;
    *(int *)(state + 0x1B8) = 0;
}

extern void vec_clear_128(void *target);

extern void matrix_mul_vec3(void *a, void *b, void *c);

extern void FastVecAdd(void *a, void *b, void *c);

extern int part_l00_alloc_effect_slot_2(void *p, float, float, float, float, float);

extern int D_L05_001B0FA4 __attribute__((sda));

/* Starts a light effect a few units in front of the object. */
void func_L05_00418200(char *object)
{
    float local[4];
    float one = 1.0f;

    vec_clear_128(local);
    local[0] = 4.0f;
    local[2] = one;
    matrix_mul_vec3(local, local, object + 0xC0);
    FastVecAdd(local, local, object + 0x10);
    D_L05_001B0FA4 = part_l00_alloc_effect_slot_2(local, 0.0f, 0.0f, 0.0f, one, 0.0f);
}

typedef int TI128 __attribute__((mode(TI)));

extern int func_328508(int);

extern void func_3065F8(int);

extern float func_332C18(void);

extern int D_L05_001D1348 __attribute__((sda));

extern int D_L05_001B14FC __attribute__((sda));

extern int D_L05_001B1504 __attribute__((sda));

extern int D_L05_001B2528 __attribute__((nosda));

extern void func_41D728(int);

extern void func_426270(int);

extern void func_426D98(int);

extern int g_current_map_index;

extern float fast_vec_dist(void *, void *);

extern float vec_spring_to_target(void *, void *, void *, float, float, float);

extern float FastAddRotations(float, float);

extern void slot_add_value_clamped(int, int);

extern void func_0029CC50(int, int, int);

extern int snd_play_from_class_bank(int, int, char *, int);

extern void moby_mark_spawned(void *);

extern void glow_ring_draw_sprites(char *);

/* Flies the pickup toward the player and gives a reward when it arrives. */
void func_L05_004260B8(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scale;

    if (D_L05_001B14FC != 0) {
        scale = fast_vec_dist((void *)(D_L05_001B14FC + 0x10), object + 0x10);

        if (g_current_map_index == 0x14) {
            vec_spring_to_target(object + 0x10, (void *)(D_L05_001B14FC + 0x10), state + 0x40,
                         0.008888889104127884f, 0.0033333334140479565f, 1.0666667222976685f);
            goto check_scale;
        }
        if (scale < 60.0f) {
            float *p = *(float **)(object + 0x24);
            float v = p[9] * 0.02222222276031971f * scale;

            *(float *)(object + 0x2C) = v;
            {
                float cap = p[9] * 0.30000001192092896f;

                if (v < cap)
                    *(float *)(object + 0x2C) = cap;
            }
            vec_spring_to_target(object + 0x10, (void *)(D_L05_001B14FC + 0x10), state + 0x40,
                         0.0055555556900799274f, 0.0016666667070239782f, 0.5f);
        }
check_scale:
        if (scale < 0.5f) {
            slot_add_value_clamped(2, 10);
            func_0029CC50(0x1288, 10, -1);
            snd_play_from_class_bank(0xC, 0, object, 0xFBF);
            moby_mark_spawned(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), 0.04f);
    glow_ring_draw_sprites(object);
}

extern int D_L05_001B1500 __attribute__((sda));

extern void glow_l05_ring_draw(char *);

extern int D_L05_001B1348 __attribute__((sda));

extern void glow_l05_ring_draw_3(char *);

/* Flies the pickup toward the player and gives a reward when it arrives. */
void func_L05_0041D570(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scale;

    if (D_L05_001B1348 != 0) {
        scale = fast_vec_dist((void *)(D_L05_001B1348 + 0x10), object + 0x10);

        if (g_current_map_index == 0x14) {
            vec_spring_to_target(object + 0x10, (void *)(D_L05_001B1348 + 0x10), state + 0x40,
                         0.008888889104127884f, 0.0033333334140479565f, 1.0666667222976685f);
            goto check_scale;
        }
        if (scale < 60.0f) {
            float *p = *(float **)(object + 0x24);
            float v = p[9] * 0.02222222276031971f * scale;

            *(float *)(object + 0x2C) = v;
            {
                float cap = p[9] * 0.30000001192092896f;

                if (v < cap)
                    *(float *)(object + 0x2C) = cap;
            }
            vec_spring_to_target(object + 0x10, (void *)(D_L05_001B1348 + 0x10), state + 0x40,
                         0.0055555556900799274f, 0.0016666667070239782f, 0.5f);
        }
    check_scale:
        if (scale < 0.5f) {
            snd_play_from_class_bank(0xC, 0, object, 0xFBF);
            slot_add_value_clamped(1, 10);
            func_0029CC50(0x1286, 10, -1);
            moby_mark_spawned(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), 0.04f);
    glow_l05_ring_draw_3(object);
}

/* Same shape as func_L05_004260B8, on its own data slot and with its own tail. */
/* Flies the pickup toward the player and gives a reward when it arrives. */
void func_L05_00426658(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scale;

    if (D_L05_001B1500 != 0) {
        scale = fast_vec_dist((void *)(D_L05_001B1500 + 0x10), object + 0x10);

        if (g_current_map_index == 0x14) {
            vec_spring_to_target(object + 0x10, (void *)(D_L05_001B1500 + 0x10), state + 0x40,
                         0.008888889104127884f, 0.0033333334140479565f, 1.0666667222976685f);
            goto check_scale;
        }
        if (scale < 60.0f) {
            float *p = *(float **)(object + 0x24);
            float v = p[9] * 0.02222222276031971f * scale;

            *(float *)(object + 0x2C) = v;
            {
                float cap = p[9] * 0.30000001192092896f;

                if (v < cap)
                    *(float *)(object + 0x2C) = cap;
            }
            vec_spring_to_target(object + 0x10, (void *)(D_L05_001B1500 + 0x10), state + 0x40,
                         0.0055555556900799274f, 0.0016666667070239782f, 0.5f);
        }
check_scale:
        if (scale < 0.5f) {
            slot_add_value_clamped(3, 10);
            func_0029CC50(0x1287, 10, -1);
            snd_play_from_class_bank(0xC, 0, object, 0xFBF);
            moby_mark_spawned(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), 0.04f);
    glow_l05_ring_draw(object);
}

extern void glow_l05_ring_draw_4(void *);

/* Turns the object towards the global target and clamps its aim cone; a target within
   half a unit takes the fast path, the rest the slow one (an angle step and an update). */
/* Flies the pickup toward the player and gives a reward when it arrives. */
void func_L05_00426BE0(char *object)
{
    char *state = *(char **)(object + 0x68);
    float distance;

    if (D_L05_001B1504 != 0) {
        char *pos = object + 0x10;
        char *aim;
        float scaled;
        float capped;

        distance = fast_vec_dist((char *)D_L05_001B1504 + 0x10, pos);
        if (g_current_map_index == 0x14) {
            vec_spring_to_target(pos, (char *)D_L05_001B1504 + 0x10, state + 0x40,
                          0.008888889f, 0.0033333333f, 1.0666667f);
        } else {
            if (distance < 60.0f) {
                aim = *(char **)(object + 0x24);
                scaled = *(float *)(aim + 0x24) * 0.022222222f * distance;
                *(float *)(object + 0x2C) = scaled;
                capped = *(float *)(aim + 0x24) * 0.3f;
                if (capped > scaled)
                    *(float *)(object + 0x2C) = capped;
                vec_spring_to_target(pos, (char *)D_L05_001B1504 + 0x10, state + 0x40,
                              0.0055555556f, 0.0016666667f, 0.5f);
            }
        }
        if (distance < 0.5f) {
            slot_add_value_clamped(4, 1);
            func_0029CC50(0x1285, 1, -1);
            snd_play_from_class_bank(0xC, 0, object, 0xFBF);
            moby_mark_spawned(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), 0.04f);
    glow_l05_ring_draw_4(object);
}

typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
typedef struct {
    float direction[4]; void *attacker; int flags; u8 kind, mode; u16 object_class;
    float damage; int enabled; float field24;
} Impact;
extern void stub_l05_empty(void *);
extern int math_fast_float_d(void *);
extern float vec_distance_xy(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern int GetCollHitMaterial(void);
extern void part_spawn_sprite_pair_burst(void *, int, u32, void *);
extern float coll_project_point_on_segment(void *, void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern int coll_process_hit(void *, int, void *, void *, float);
extern void QueueMobyImpact(void *, Impact *);
extern void light_spot_add_nearby_object(void *);
extern void gfx_add_draw_callback_third(void *, void *);
extern void gfx_draw_energy_blast(void *);
extern char D_L05_001BFB20[], D_L05_001B9580[];
extern u8 *D_L05_001C3B80[];
extern float D_L05_001B104C __attribute__((sda));

void UpdateFeltzinProjectile(u8 *actor)
{
    Vector previous;
    Impact impact __attribute__((aligned(16)));
    Vector point, delta, closest;
    u8 *state = *(u8 **)(actor + 0x68);
    int count, i;

    qcopy(&previous, actor + 0x10);
    stub_l05_empty(actor);
    FastVecAdd(actor + 0x10, actor + 0x10, state + 0x10);
    if (math_fast_float_d(state) != 0) {
        moby_mark_spawned(actor);
        return;
    }
    if (*(float *)(actor + 0x10) < 2.0f || *(float *)(actor + 0x10) > 1021.0f ||
        *(float *)(actor + 0x14) < 2.0f || *(float *)(actor + 0x14) > 1021.0f ||
        *(float *)(actor + 0x18) < 2.0f || *(float *)(actor + 0x18) > 1021.0f) {
        if (*(int *)(state + 0x38) == 0) {
            moby_mark_spawned(actor);
            return;
        }
    }
    if (*(int *)(state + 0x38) != 0) {
        if (vec_distance_xy(actor + 0x10, D_L05_001B9580 + 0x140) < 2.0f) {
            moby_mark_spawned(actor);
            return;
        }
    }
    if (*(int *)(state + 0x38) != 0)
        goto finish;
    impact.attacker = actor;
    impact.flags = 0x110000;
    if (*(int *)(state + 0x30) != 0)
        impact.damage = 3.0f;
    else
        impact.damage = 1.0f;
    impact.enabled = 1;
    qcopy(impact.direction, state + 0x10);
    vec_scale_to_length(impact.direction, impact.direction, 1.0f);
    impact.kind = 1;
    impact.mode = 1;
    impact.direction[3] = 5627.9248046875f;
    impact.object_class = *(u16 *)(actor + 0xAA);
    /* The last Impact word is read by the receiver but not initialized by retail. */
    *(float *)(state + 0x3C) += *(float *)(state + 0x40);
    if (CollLine(&previous, actor + 0x10, 0, *(void **)(state + 4), &impact) != 0 &&
        GetCollHitMaterial() != 6) {
        snd_play_from_class_bank(7, 0, (char *)actor, 0xFBF);
        part_spawn_sprite_pair_burst(D_L05_001BFB20, 20, *(u32 *)(state + 0x24), actor);
        moby_mark_spawned(actor);
        return;
    }
    if (*(s16 *)(*(u8 **)(state + 4) + 0xAA) != 0xFBF) {
        coll_project_point_on_segment(&point, &previous, actor + 0x10, D_L05_001B9580 + 0x140);
        if (fast_vec_dist(&point, D_L05_001B9580 + 0x140) < D_L05_001B104C) {
            snd_play_from_class_bank(7, 0, (char *)actor, 0xFBF);
            {
                char *camera = D_L05_001B9580;
                *(int *)(camera + 0x16C) = 0;
                *(int *)(camera + 0x168) = 30;
                *(float *)(camera + 0x160) = 0.05f;
            }
            part_spawn_sprite_pair_burst(&point, 20, *(u32 *)(state + 0x24), actor);
            moby_mark_spawned(actor);
            return;
        }
        goto finish;
destroy:
        moby_mark_spawned(actor);
        return;
    }
    lerp_vector(&point, &previous, actor + 0x10, 0.5f);
    FastVecSub(&delta, actor + 0x10, &previous);
    count = coll_process_hit(&point, 1, *(void **)(state + 4), 0, FastVecLength(&delta));
    if (count != 0) {
        for (i = 0; i < count; i++) {
            coll_project_point_on_segment(&closest, &previous, actor + 0x10, D_L05_001C3B80[i] + 0x10);
            FastVecSub(&delta, D_L05_001C3B80[i] + 0x10, &closest);
            if (FastVecLength(&delta) < *(float *)(state + 0x3C)) {
                snd_play_from_class_bank(7, 0, (char *)actor, 0xFBF);
                part_spawn_sprite_pair_burst(&closest, 20, *(u32 *)(state + 0x24), actor);
                QueueMobyImpact(D_L05_001C3B80[i], &impact);
                goto destroy;
            }
        }
    }
finish:
    light_spot_add_nearby_object(actor);
    gfx_add_draw_callback_third(gfx_draw_energy_blast, actor);
}

extern void FastVecScale(void *, void *, float);
extern int coll_test_point(void *, int, void *, float);
extern void projectile_apply_impact_sparks(void *, void *, void *);
extern void *part_spawn_shockwave_burst(void *, int, int, int, int, int, int, int, int, int, int, float);
extern void func_L05_003D1E60(void *, int, int);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *, float, float, float);
extern char *part_spawn_trailing_spark(void *, void *, int, int, int, int, float);
extern float D_L05_001B1534 __attribute__((sda));
extern float D_L05_001B1530 __attribute__((sda));
extern char D_L05_001BFB30[], D_L05_001BFB00[];
extern u8 *D_L05_001FF240[] NOT_SDA;

typedef struct { char pad[0x18]; char *hit; int count; int point[4]; } Collision;

/* End of a shot's flight: the optional burst, then the object is removed. */
static __inline__ void ShotEndFlight(char *object, char *state)
{
    if (*(int *)(state + 0x2C)) {
        if (*(int *)(state + 0x24))
            part_spawn_shockwave_burst(object + 0x10, 0, 50, 30, 30, 30, 40, 1, 1, 1, 1, 2.0f);
        func_L05_003D1E60(object + 0x10, 0, 0);
    }
    moby_mark_spawned(object);
}

/* Per-frame update of a shot: moves it, removes it when it leaves the 2..1021 world box or expires
 * (with a last collision test), and otherwise tests for a hit and leaves a three-step trail.
 * The end-of-flight code is expanded once per exit and jump2 cross-jumps the copies. The two
 * collision.point loads merge through their shared REG_EQUIV constant, which leaves a dead lui
 * before the impact code, so one shared label does not reproduce it.
 */
void UpdateProjectile(char *object)
{
    float old[4], pos[4], step[4], random[4];
    char *state = *(char **)(object + 0x68);
    int hit;
    int i;
    char *particle;
    float value;
    float angle;
    float radius;
    float x;
    Collision *collision;

    qcopy(old, object + 0x10);
    FastVecAdd(object + 0x10, object + 0x10, state);
    *(float *)(object + 0x2C) += 0.07f;
    if (*(float *)(object + 0x2C) > *(float *)(*(char **)(object + 0x24) + 0x24))
        *(float *)(object + 0x2C) = *(float *)(*(char **)(object + 0x24) + 0x24);
    if (math_fast_float_d(state + 0x18)) {
        moby_mark_spawned(object);
        return;
    }
    x = *(float *)(object + 0x10);
    value = 2.0f;
    if (x < value || x > 1021.0f
        || *(float *)(object + 0x14) < value || *(float *)(object + 0x14) > 1021.0f
        || *(float *)(object + 0x18) < value || *(float *)(object + 0x18) > 1021.0f) {
        moby_mark_spawned(object);
        return;
    }
    if (math_fast_float_d(state + 0x28)) {
        hit = 0;
        radius = *(int *)(state + 0x24) ? D_L05_001B1534 : D_L05_001B1530;
        if (coll_test_point(object + 0x10, 16, *(void **)(state + 0x20), radius)) {
            hit = 1;
            qcopy(object + 0x10, D_L05_001BFB30);
        }
        if (hit || CollLine(old, object + 0x10, 16, *(void **)(state + 0x20), 0)) {
            collision = (Collision *)D_L05_001BFB00;
            if (collision->hit) {
                snd_play_from_class_bank(7, 0, object, 0xFBF);
                qcopy(object + 0x10, &collision->point);
                projectile_apply_impact_sparks(object, state, object + 0x10);
                ShotEndFlight(object, state);
                return;
            }
        }
        ShotEndFlight(object, state);
        return;
    }
    if (GetCollHitMaterial() != 6) {
        hit = 0;
        radius = 1.0f;
        if (*(int *)(state + 0x24))
            radius = 1.5f;
        if (coll_test_point(object + 0x10, 16, *(void **)(state + 0x20), radius)) {
            hit = 1;
            qcopy(object + 0x10, D_L05_001BFB30);
        }
        if (hit || CollLine(old, object + 0x10, 16, *(void **)(state + 0x20), 0)) {
            snd_play_from_class_bank(7, 0, object, 0xFBF);
            qcopy(object + 0x10, &((Collision *)D_L05_001BFB00)->point);
            projectile_apply_impact_sparks(object, state, object + 0x10);
            ShotEndFlight(object, state);
            return;
        }
    }
    qcopy(pos, old);
    FastVecSub(step, object + 0x10, old);
    FastVecScale(step, step, 0.333f);
    for (i = 2; i >= 0; i--) {
        FastVecAdd(pos, pos, step);
        value = math_random_angle();
        angle = math_random_angle();
        vec_build_spherical_offset(random, 0.012500001f, value, angle);
        if (*(int *)(state + 0x24)) {
            particle = part_spawn_trailing_spark(pos, random, 0x4FFF0040, 0x1FFF0040, 10, 1, 30000.0f);
            if (particle)
                particle[2] = D_L05_001FF240[97][7];
            particle = part_spawn_trailing_spark(pos, random, 0x4FFF2040, 0x1FFF2040, 10, 1, 15000.0f);
        } else {
            particle = part_spawn_trailing_spark(pos, random, 0x4F00FF20, 0x1F00FF20, 10, 1, 30000.0f);
            if (particle)
                particle[2] = D_L05_001FF240[97][7];
            particle = part_spawn_trailing_spark(pos, random, 0x4F20FF20, 0x1F20FF20, 10, 1, 15000.0f);
        }
        if (particle)
            particle[2] = D_L05_001FF240[97][7];
    }
}
