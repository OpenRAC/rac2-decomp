#include "include_asm.h"

#include "common.h"
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
extern int D_L20_001A8F00, D_L20_001C0418[];
extern int D_L20_001B2AC8;
extern float D_L20_001B1F9C __attribute__((sda)), D_L20_001B1FA0 __attribute__((sda));
extern float D_L20_001B1FA4 __attribute__((sda)), D_L20_001B1FA8 __attribute__((sda));
extern float D_L20_001B1FAC __attribute__((sda)), D_L20_001B1FB0 __attribute__((sda));
extern float D_L20_001B1FB4 __attribute__((sda)), D_L20_001B1FB8 __attribute__((sda));
extern char D_L20_001B9FC0[];
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
extern char *func_PAL_0032F3B8(void *, void *, void *, float);
extern char *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern int PlayMobySound(int, int, void *);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void func_PAL_L20_00444E38(char *), part_add_moby_glow_trail(void *);

void func_PAL_L20_00444688(unsigned char *obj)
{
    Vec old, delta, target;
    float speed;
    ShardState *s = *(ShardState **)(obj + 0x68);

    if (D_L20_001A8F00 == 2) {
        moby_mark_spawned(obj);
        return;
    }
    qcopy(old, obj + 0x10);
    switch (obj[0x20]) {
    case 0:
        math_step_value_toward_target(&s->radius, &s->radiusSpeed, s->targetRadius, D_L20_001B1F9C * 0.00040000002f, D_L20_001B1F9C * 0.00040000002f, D_L20_001B1FA0 * 0.020000001f);
        ((float *)(obj + 0x10))[0] = math_fast_sin_or_cos_a(s->angle) * s->radius;
        ((float *)(obj + 0x10))[1] = math_fast_sin_or_cos_b(s->angle) * s->radius;
        ((float *)(obj + 0x10))[2] = 0.0f;
        FastVecAdd(obj + 0x10, obj + 0x10, *(char **)(obj + 0xB8) + 0x10);
        ((float *)(obj + 0x10))[2] = old[2];
        if (math_fabs(s->radius - s->targetRadius) < 0.5f) {
            speed = D_L20_001B1FA4 * 0.0003490659f;
            if (s->reverse == 0)
                speed = -speed;
            ApproachValue(&s->spin, speed, D_L20_001B1FA8 * 6.981318e-06f);
            s->angle = FastAddRotations(s->angle, s->spin);
            math_step_value_toward_target((float *)(obj + 0x18), &s->zSpeed, s->targetZ, D_L20_001B1FAC * 0.00040000002f, D_L20_001B1FAC * 0.00040000002f, D_L20_001B1FB0 * 0.020000001f);
            if (math_fabs(((float *)(obj + 0x10))[2] - s->targetZ) < 0.1f)
                s->targetZ = s->baseZ + math_random_float_range(3.0f, 8.0f);
        }
        if (math_fast_float_d(&s->timer)
            && FastDiffRots(((Moby *)obj)->rot[2], mat_fast_helper_a(g_hero_state.position[0] - ((float *)(obj + 0x10))[0], g_hero_state.position[1] - ((float *)(obj + 0x10))[1])) < 0.62831855f) {
            FastVecSub(s->velocity, obj + 0x10, old);
            s->velocity[2] = 0.0f;
            moby_set_state(obj, 1, -1);
        } else if (subtract_integer_with_clamp(*s->clock - D_L20_001B2AC8) >= 6) {
            FastVecSub(s->velocity, obj + 0x10, old);
            s->velocity[2] = 0.0f;
            moby_set_state(obj, 2, -1);
        }
        break;
    case 1:
        {
            float rate;

            { float b = D_L20_001B1FB0 * 0.020000001f; math_step_value_toward_target((float *)(obj + 0x18), &s->zSpeed, s->baseZ + 1.0f, D_L20_001B1FAC * 0.00040000002f, D_L20_001B1FAC * 0.00040000002f, b); }
            rate = D_L20_001B1FB8 * 0.020000001f;
            FastVecSub(target, g_hero_state.top, obj + 0x10);
            target[2] = 0.0f;
            vec_scale_to_length(target, target, rate);
            FastVecSub(delta, target, s->velocity);
            vec_scale_to_length(delta, delta, D_L20_001B1FB4 * 0.00040000002f);
            FastVecAdd(s->velocity, s->velocity, delta);
            vec_scale_to_length(s->velocity, s->velocity, rate);
            FastVecAdd(obj + 0x10, obj + 0x10, s->velocity);
            if (FastDiffRots(((Moby *)obj)->rot[2], mat_fast_helper_a(g_hero_state.position[0] - ((float *)(obj + 0x10))[0], g_hero_state.position[1] - ((float *)(obj + 0x10))[1])) > 1.5707964f)
                moby_set_state(obj, 2, -1);
        }
        break;
    case 2:
        {
            float length = FastVecLength(s->velocity);

            ApproachValue(&length, D_L20_001B1FB8 * 0.020000001f, 0.004f);
            vec_scale_to_length(s->velocity, s->velocity, length);
            FastVecAdd(obj + 0x10, obj + 0x10, s->velocity);
            if (obj[0x31] == 0) {
                moby_mark_spawned(obj);
                return;
            }
        }
        break;
    }
    FastVecSub(delta, obj + 0x10, old);
    ((Moby *)obj)->rot[2] = mat_fast_helper_a(delta[0], delta[1]);
    ((Moby *)obj)->rot[1] = -mat_fast_helper_a(vec_length_xy(delta), delta[2]);
    ((Moby *)obj)->rot[0] = FastAddRotations(((Moby *)obj)->rot[0], 0.062831864f);
    if ((D_L20_001B2AC8 & 3) == (((int)obj >> 8) & 3)) {
        int i;

        for (i = 2; i > 0; i--)
            qcopy(s->trail[i], s->trail[i - 1]);
        qcopy(s->trail[0], obj + 0x10);
    }
    if (CollLine(old, obj + 0x10, 0, *(void **)(obj + 0xB8), 0)) {
        if (D_L20_001C0418[0]) {
            FastVecSub(target, D_L20_001B9FC0, obj + 0x10);
            vec_scale_to_length(target, target, 1.0f);
            coll_sweep_from_object(*(void **)(obj + 0xB8), obj + 0x10, 2.0f, s->scale, 0x10001, 1.0f, 0, 1, 0);
            func_PAL_0032F3B8(obj, obj + 0x10, target, 0.0f);
        } else {
            func_PAL_L00_003FB330(obj + 0x10, 0, 10, 20, 20, 20, 45, 0, 0.75f, 20.0f, 1, 0, 0, 0);
        }
        PlayMobySound(0, 0, obj);
        moby_mark_spawned(obj);
        return;
    }
    if (obj[0x31])
        func_PAL_L20_00444E38(obj);
    gfx_add_draw_callback_third(part_add_moby_glow_trail, obj);
}
