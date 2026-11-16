#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef float Vec[4] __attribute__((aligned(16)));
typedef struct { char pad[0x80]; Vec position; char pad90[0x40]; Vec top; } PlayerView;
typedef struct {
    Vec velocity;
    Vec trail[3];
    float radius, angle, targetRadius, targetZ, radiusSpeed, spin, zSpeed, baseZ, pad60;
    int timer;
    int reverse;
    int *clock;
    float scale;
} ShardState;
extern PlayerView g_hero_state;
typedef struct { char pad[0xF0]; float rot[3]; } Moby;
extern int g_hero_vehicle_mode, g_hit_l20_result[];
extern int g_frame_l20_counter;
extern float g_shard_radius_speed __attribute__((sda)), g_shard_radius_param __attribute__((sda));
extern float g_shard_spin_target __attribute__((sda)), g_shard_spin_rate __attribute__((sda));
extern float g_shard_z_speed __attribute__((sda)), g_shard_z_rate __attribute__((sda));
extern float g_shard_delta_length __attribute__((sda)), g_shard_length_rate __attribute__((sda));
extern char g_camera_l20_position[];
extern void moby_mark_spawned(void *);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern float ApproachValue(float *, float, float);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float), math_fabs(float);
extern void FastVecAdd(void *, void *, void *), FastVecSub(void *, void *, void *), vec_scale_to_length(void *, void *, float);
extern float FastAddRotations(float, float), mat_fast_helper_a(float, float), FastDiffRots(float, float);
extern float math_random_float_range(float, float), vec_length_xy(void *), FastVecLength(void *);
extern int math_fast_float_d(void *), subtract_integer_with_clamp(int);
extern void moby_set_state(void *, int, int);
extern int CollLine(void *, void *, int, void *, int);
extern int coll_sweep_from_object(void *, void *, float, float, int, float, int, int, int);
extern char *part_spawn_blast_effect_moby(void *, void *, void *, float);
extern char *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern int PlayMobySound(int, int, void *);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void part_spawn_shard(char *), part_add_moby_glow_trail(void *);

/* Updates moby class 4509: a glowing shard that circles in place, then flies at the player, and breaks with sparks when it hits something. */
void orbiting_shard_update(unsigned char *moby)
{
    Vec old, delta, target;
    float speed;
    ShardState *shard = *(ShardState **)(moby + 0x68);

    if (g_hero_vehicle_mode == 2) {
        moby_mark_spawned(moby);
        return;
    }
    qcopy(old, moby + 0x10);
    switch (moby[0x20]) {
    case 0:
        math_step_value_toward_target(&shard->radius, &shard->radiusSpeed, shard->targetRadius, g_shard_radius_speed * 0.00027777778f, g_shard_radius_speed * 0.00027777778f, g_shard_radius_param * 0.016666668f);
        ((float *)(moby + 0x10))[0] = math_fast_sin_or_cos_a(shard->angle) * shard->radius;
        ((float *)(moby + 0x10))[1] = math_fast_sin_or_cos_b(shard->angle) * shard->radius;
        ((float *)(moby + 0x10))[2] = 0.0f;
        FastVecAdd(moby + 0x10, moby + 0x10, *(char **)(moby + 0xB8) + 0x10);
        ((float *)(moby + 0x10))[2] = old[2];
        if (math_fabs(shard->radius - shard->targetRadius) < 0.5f) {
            speed = g_shard_spin_target * 0.00029088825f;
            if (shard->reverse == 0)
                speed = -speed;
            ApproachValue(&shard->spin, speed, g_shard_spin_rate * 4.8481376e-06f);
            shard->angle = FastAddRotations(shard->angle, shard->spin);
            math_step_value_toward_target((float *)(moby + 0x18), &shard->zSpeed, shard->targetZ, g_shard_z_speed * 0.00027777778f, g_shard_z_speed * 0.00027777778f, g_shard_z_rate * 0.016666668f);
            if (math_fabs(((float *)(moby + 0x10))[2] - shard->targetZ) < 0.1f)
                shard->targetZ = shard->baseZ + math_random_float_range(3.0f, 8.0f);
        }
        if (math_fast_float_d(&shard->timer)
            && FastDiffRots(((Moby *)moby)->rot[2], mat_fast_helper_a(g_hero_state.position[0] - ((float *)(moby + 0x10))[0], g_hero_state.position[1] - ((float *)(moby + 0x10))[1])) < 0.62831855f) {
            FastVecSub(shard->velocity, moby + 0x10, old);
            shard->velocity[2] = 0.0f;
            moby_set_state(moby, 1, -1);
        } else if (subtract_integer_with_clamp(*shard->clock - g_frame_l20_counter) >= 6) {
            FastVecSub(shard->velocity, moby + 0x10, old);
            shard->velocity[2] = 0.0f;
            moby_set_state(moby, 2, -1);
        }
        break;
    case 1:
        {
            float rate;

            { float z_rate = g_shard_z_rate * 0.016666668f; math_step_value_toward_target((float *)(moby + 0x18), &shard->zSpeed, shard->baseZ + 1.0f, g_shard_z_speed * 0.00027777778f, g_shard_z_speed * 0.00027777778f, z_rate); }
            rate = g_shard_length_rate * 0.016666668f;
            FastVecSub(target, g_hero_state.top, moby + 0x10);
            target[2] = 0.0f;
            vec_scale_to_length(target, target, rate);
            FastVecSub(delta, target, shard->velocity);
            vec_scale_to_length(delta, delta, g_shard_delta_length * 0.00027777778f);
            FastVecAdd(shard->velocity, shard->velocity, delta);
            vec_scale_to_length(shard->velocity, shard->velocity, rate);
            FastVecAdd(moby + 0x10, moby + 0x10, shard->velocity);
            if (FastDiffRots(((Moby *)moby)->rot[2], mat_fast_helper_a(g_hero_state.position[0] - ((float *)(moby + 0x10))[0], g_hero_state.position[1] - ((float *)(moby + 0x10))[1])) > 1.5707964f)
                moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        {
            float length = FastVecLength(shard->velocity);

            ApproachValue(&length, g_shard_length_rate * 0.016666668f, 0.0027777778f);
            vec_scale_to_length(shard->velocity, shard->velocity, length);
            FastVecAdd(moby + 0x10, moby + 0x10, shard->velocity);
            if (moby[0x31] == 0) {
                moby_mark_spawned(moby);
                return;
            }
        }
        break;
    }
    FastVecSub(delta, moby + 0x10, old);
    ((Moby *)moby)->rot[2] = mat_fast_helper_a(delta[0], delta[1]);
    ((Moby *)moby)->rot[1] = -mat_fast_helper_a(vec_length_xy(delta), delta[2]);
    ((Moby *)moby)->rot[0] = FastAddRotations(((Moby *)moby)->rot[0], 0.052359887f);
    if ((g_frame_l20_counter & 3) == (((int)moby >> 8) & 3)) {
        int i;

        for (i = 2; i > 0; i--)
            qcopy(shard->trail[i], shard->trail[i - 1]);
        qcopy(shard->trail[0], moby + 0x10);
    }
    if (CollLine(old, moby + 0x10, 0, *(void **)(moby + 0xB8), 0)) {
        if (g_hit_l20_result[0]) {
            FastVecSub(target, g_camera_l20_position, moby + 0x10);
            vec_scale_to_length(target, target, 1.0f);
            coll_sweep_from_object(*(void **)(moby + 0xB8), moby + 0x10, 2.0f, shard->scale, 0x10001, 1.0f, 0, 1, 0);
            part_spawn_blast_effect_moby(moby, moby + 0x10, target, 0.0f);
        } else {
            SpawnExplosion(moby + 0x10, 0, 10, 20, 20, 20, 45, 0, 0.75f, 20.0f, 1, 0, 0, 0);
        }
        PlayMobySound(0, 0, moby);
        moby_mark_spawned(moby);
        return;
    }
    if (moby[0x31])
        part_spawn_shard(moby);
    gfx_add_draw_callback_third(part_add_moby_glow_trail, moby);
}
