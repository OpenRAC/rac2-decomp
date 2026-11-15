#include "include_asm.h"

#include "common.h"
extern void moby_set_state(void *, int, int);
extern int IsPointInCuboid(void *, int);
extern u8 g_hero_position[];
extern u8 *protopet_count_group(int, int *);
extern int flag_set_first_pending(void *);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern int PlayMobySound(int, int, void *);
extern void vec_clear_128(void *);
extern void vec_add_random_offset(void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void protopet_launch_shot(void *, void *, void *);
extern char *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern int projectile_compute_flight_time(float, float, float, float);
extern int math_random_int_below(int);
extern float IntToFloat(int);
extern float math_fast_float_g(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float D_L18_001B1530 __attribute__((sda));
extern float D_L18_001B1534 __attribute__((sda));
extern float D_L18_001B1538 __attribute__((sda));
extern float D_L18_001B153C __attribute__((sda));
extern float D_L18_001B1540 __attribute__((sda));
extern float D_L18_001B1544 __attribute__((sda));
extern float D_L18_001B1548 __attribute__((sda));
extern int D_L18_001B154C __attribute__((sda));
extern float D_L18_001B1550 __attribute__((sda));
extern int D_L18_001B1554 __attribute__((sda));
extern float D_L18_001B1558 __attribute__((sda));
extern float D_L18_001B155C __attribute__((sda));
extern u8 D_L18_001B1560[16] __attribute__((sda));
typedef struct {
    float angles[4];
    int firstId,  secondId,  group;
    float restHeight,  verticalSpeed,  period,  amplitude;
    int spawnCount;
} LauncherState;
typedef struct {
    u8 pad00[0x10];
    float position[4];
    u8 state;
    u8 pad21[0x47];
    LauncherState *vars;
    u8 pad6c[0x2A];
    u16 timer;
    u8 pad98[0x58];
    float rotation[4];
} LauncherObject;

void func_PAL_L18_00434BE0(u8 *a)
{
    float velocity[4], position[4];
    int count1, count2, count, i;
    u8 *p;
    LauncherObject *object = (LauncherObject *)a;
    LauncherState *s = object->vars;
    float zero, duration;

    switch (object->state) {
    case 0:
        s->restHeight = object->position[2];
        moby_set_state(a, 1, -1);
        break;
    case 1:
        if (s->firstId != -1 && IsPointInCuboid(g_hero_position, s->firstId)) {
            protopet_count_group(s->group, &count1);
            if (count1 >= 4)
                moby_set_state(a, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(a)) {
            object->rotation[0] = 0;
            object->rotation[1] = 0;
            zero = object->rotation[0];
            object->position[2] = s->restHeight;
            s->verticalSpeed += math_random_float_range(zero, D_L18_001B1530 * 0.020000001f);
            s->angles[0] = math_random_float_range(zero, D_L18_001B1534 * 0.0003490659f);
            s->angles[1] = math_random_float_range(zero, D_L18_001B1538 * 0.0003490659f);
            object->position[2] = s->restHeight;
            PlayMobySound(0, 0, a);
        }
        if (object->position[2] >= s->restHeight) {
            object->position[2] += s->verticalSpeed;
            s->verticalSpeed -= D_L18_001B155C * 0.00040000002f;
            if (s->verticalSpeed > 0) {
                object->rotation[0] = FastAddRotations(s->angles[0], object->rotation[0]);
                object->rotation[1] = FastAddRotations(s->angles[1], object->rotation[1]);
            } else {
                object->rotation[0] = FastAddRotations(-s->angles[0], object->rotation[0]);
                object->rotation[1] = FastAddRotations(-s->angles[1], object->rotation[1]);
            }
        } else {
            moby_set_state(a, 2, -1);
        }
        if (s->secondId != -1 && IsPointInCuboid(g_hero_position, s->secondId)) {
            protopet_count_group(s->group, &count2);
            if (count2 >= 4)
                moby_set_state(a, 3, -1);
        }
        break;
    case 3:
        if (flag_set_first_pending(a)) {
            object->rotation[0] = 0;
            object->rotation[1] = 0;
            object->position[2] = s->restHeight;
            count = 50;
            for (i = 0; i < s->spawnCount && count > 0; i++) {
                p = protopet_count_group(s->group, &count);
                if (p) {
                    vec_clear_128(velocity);
                    velocity[2] = D_L18_001B153C * 0.020000001f;
                    vec_add_random_offset(velocity, D_L18_001B1540 * 0.020000001f);
                    FastVecAdd(position, a + 0x10, D_L18_001B1560);
                    protopet_launch_shot(p, position, velocity);
                    *(u8 **)(p + 0xB8) = a;
                }
            }
            if (i) {
                func_PAL_L00_003FB330(a + 0x10, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1,
                              1.0f, 20.0f, 1, 1, 0, 0);
                PlayMobySound(0, 0, a);
                s->verticalSpeed += math_random_float_range(D_L18_001B1544, D_L18_001B1548) * 0.020000001f;
                duration = (float)projectile_compute_flight_time(object->position[2], s->restHeight,
                                                   s->verticalSpeed, D_L18_001B155C * 0.00040000002f);
                s->angles[0] = (float)math_random_int_below(D_L18_001B154C) * 6.28318548f / duration;
                s->angles[1] = (float)math_random_int_below(D_L18_001B154C) * 6.28318548f / duration;
                s->angles[2] = (float)math_random_int_below(D_L18_001B154C) * 6.28318548f / duration;
            }
        }
        if (object->position[2] >= s->restHeight) {
            object->position[2] += s->verticalSpeed;
            s->verticalSpeed -= D_L18_001B155C * 0.00040000002f;
            object->rotation[0] = FastAddRotations(s->angles[0], object->rotation[0]);
            object->rotation[1] = FastAddRotations(s->angles[1], object->rotation[1]);
            object->rotation[2] = FastAddRotations(s->angles[2], object->rotation[2]);
        } else {
            moby_set_state(a, 4, -1);
        }
        break;
    case 4:
        if (flag_set_first_pending(a)) {
            vec_clear_128(s);
            vec_clear_128(a + 0xF0);
            object->position[2] = s->restHeight;
            s->period = IntToFloat(D_L18_001B1554);
            s->amplitude = D_L18_001B1558;
            PlayMobySound(0, 0, a);
        }
        if (s->amplitude >= 0.1f) {
            object->rotation[0] = s->amplitude * math_fast_sin_or_cos_b(math_fast_float_g(
                IntToFloat(object->timer) * 6.28318548f / s->period));
            object->rotation[1] = s->amplitude * math_fast_sin_or_cos_a(math_fast_float_g(
                IntToFloat(object->timer) * 6.28318548f / s->period));
            s->amplitude *= D_L18_001B1550;
            s->period *= D_L18_001B1550;
        } else {
            object->rotation[0] = object->rotation[1] = object->rotation[2] = 0.0f;
            moby_set_state(a, 5, -1);
        }
    }
    if (object->timer <= 0xFFFE)
        ++object->timer;
}
