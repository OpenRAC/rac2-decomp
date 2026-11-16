#include "common.h"

/* func_PAL_L11_0044CC18, the PAL copy of func_L11_004471A8: the same C, where the timer's reload
   value is scaled to 50 Hz and 1.0f / 60.0f becomes 0.020000001f. D_L11_001B19A8 is a word: USA's
   halfword load is its narrowing to the u16 timer, which the scale here no longer allows. */

typedef int TI128 __attribute__((mode(TI)));

extern float math_random_float_range(float, float);
extern s32 math_random_int_below(s32);
extern s32 FastDecTimer(void *);
extern float *arena_get_center_point(void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern char *joba_swirl_effect_create_pal(void *, void *, void *, float, float, float, float);
extern TI128 g_hero_position;
extern s32 g_timed_effect_duration __attribute__((sda));
extern s32 g_timed_effect_chance __attribute__((sda));
extern float g_timed_effect_gravity __attribute__((sda));
extern float g_timed_effect_radius __attribute__((sda));

typedef struct JobObject JobObject;

/* The record behind an object's +0x68 pointer for the kind handled by this function. */
typedef struct {
    u8 pad00[0x20];
    float health;           /* +0x20 */
    u8 pad24[0x34 - 0x24];
    u8 f34;
    u8 pad35[0x1FC - 0x35];
    u16 spawnTimer;         /* +0x1FC */
} JobState;

struct JobObject {
    u8 pad00[0x68];
    JobState *state;        /* +0x68 */
};

/* Spawns the effect at a random point around the object's anchor when its timer runs out. */
void func_PAL_L11_0044CC18(JobObject *object)
{
    float position[4], velocity[4], acceleration[4];
    JobState *state = object->state;
    float angle;
    float *base;
    int chance;
    u16 timer;

    if (FastDecTimer(&state->spawnTimer)) {
        timer = (g_timed_effect_duration * 5 + 2) / 6;
        chance = g_timed_effect_chance;
        state->spawnTimer = timer;
        if (!math_random_int_below(chance)) {
            qcopy(position, &g_hero_position);
            FastVecSub(velocity, position, arena_get_center_point(object));
            velocity[2] = 0;
            vec_scale_to_length(velocity, velocity, g_timed_effect_radius);
            FastVecAdd(position, velocity, arena_get_center_point(object));
            position[2] += 5.0f;
        } else {
            angle = math_random_float_range(-3.1415927410125732f, 3.1415927410125732f);
            base = arena_get_center_point(object);
            position[0] = base[0] + g_timed_effect_radius * math_fast_sin_or_cos_a(angle);
            base = arena_get_center_point(object);
            position[1] = base[1] + g_timed_effect_radius * math_fast_sin_or_cos_b(angle);
            position[2] = arena_get_center_point(object)[2] + 5.0f;
        }
        *(TI128 *)acceleration = 0;
        acceleration[2] = g_timed_effect_gravity * 0.020000001f;
        *(TI128 *)velocity = *(TI128 *)acceleration;
        joba_swirl_effect_create_pal(object, velocity, position, state->health, (float)state->f34, 1.0f,
                          550.0f);
    }
}
