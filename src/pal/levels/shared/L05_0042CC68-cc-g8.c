#include "names.h"
/* func_PAL_L05_0042CC68, the PAL copy of func_L05_00427238: the same C, where rename func_L05_004276E8 becomes func_PAL_L05_0042D118; rename func_L05_00424990 becomes func_PAL_L05_0042A240; lit 10 becomes 8. */
#include "common.h"

extern void FastVecAdd(void *a, void *b, void *c);

extern int snd_play_from_class_bank(int, int, char *, int);

extern void moby_mark_spawned(void *);

/* Same shape as func_L05_004260B8, on its own data slot and with its own tail. */
/* Turns the object towards the global target and clamps its aim cone; a target within
   half a unit takes the fast path, the rest the slow one (an angle step and an update). */
extern int math_fast_float_d(void *);
extern int CollLine(void *, void *, int, void *, void *);
extern int GetCollHitMaterial(void);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern int coll_test_point(void *, int, void *, float);
extern void func_PAL_L05_0042D118(void *, void *, void *);
extern void *func_PAL_L05_0042A240(void *, int, int, int, int, int, int, int, int, int, int, float);
extern unsigned char *func_L05_003D1E60(void *, int, int);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *, float, float, float);
extern char *part_spawn_trailing_spark(void *, void *, int, int, int, int, float);
extern float g_projectile_hit_radius_alt __attribute__((sda));
extern float g_projectile_hit_radius_normal __attribute__((sda));
extern char g_projectile_pos_scratch[], g_collision_l05_result[];
extern u8 *g_particle_params_table[] NOT_SDA;

typedef struct { char pad[0x18]; char *hit; int count; int point[4]; } Collision;

/* End of a shot's flight: the optional burst, then the object is removed. */
static __inline__ void ShotEndFlight(char *object, char *state)
{
    if (*(int *)(state + 0x2C)) {
        if (*(int *)(state + 0x24))
            func_PAL_L05_0042A240(object + 0x10, 0, 50, 30, 30, 30, 40, 1, 1, 1, 1, 2.0f);
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
void func_PAL_L05_0042CC68(char *object)
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
        radius = *(int *)(state + 0x24) ? g_projectile_hit_radius_alt : g_projectile_hit_radius_normal;
        if (coll_test_point(object + 0x10, 16, *(void **)(state + 0x20), radius)) {
            hit = 1;
            qcopy(object + 0x10, g_projectile_pos_scratch);
        }
        if (hit || CollLine(old, object + 0x10, 16, *(void **)(state + 0x20), 0)) {
            collision = (Collision *)g_collision_l05_result;
            if (collision->hit) {
                snd_play_from_class_bank(7, 0, object, 0xFBF);
                qcopy(object + 0x10, &collision->point);
                func_PAL_L05_0042D118(object, state, object + 0x10);
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
            qcopy(object + 0x10, g_projectile_pos_scratch);
        }
        if (hit || CollLine(old, object + 0x10, 16, *(void **)(state + 0x20), 0)) {
            snd_play_from_class_bank(7, 0, object, 0xFBF);
            qcopy(object + 0x10, &((Collision *)g_collision_l05_result)->point);
            func_PAL_L05_0042D118(object, state, object + 0x10);
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
        vec_build_spherical_offset(random, 0.015000001f, value, angle);
        if (*(int *)(state + 0x24)) {
            particle = part_spawn_trailing_spark(pos, random, 0x4FFF0040, 0x1FFF0040, 8, 1, 30000.0f);
            if (particle)
                particle[2] = g_particle_params_table[97][7];
            particle = part_spawn_trailing_spark(pos, random, 0x4FFF2040, 0x1FFF2040, 8, 1, 15000.0f);
        } else {
            particle = part_spawn_trailing_spark(pos, random, 0x4F00FF20, 0x1F00FF20, 8, 1, 30000.0f);
            if (particle)
                particle[2] = g_particle_params_table[97][7];
            particle = part_spawn_trailing_spark(pos, random, 0x4F20FF20, 0x1F20FF20, 8, 1, 15000.0f);
        }
        if (particle)
            particle[2] = g_particle_params_table[97][7];
    }
}
