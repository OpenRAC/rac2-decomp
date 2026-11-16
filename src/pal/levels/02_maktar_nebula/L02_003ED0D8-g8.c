#include "include_asm.h"
#include "names.h"

/* func_PAL_L02_003ED0D8, the PAL copy of func_L02_003E8CE8: the same C and the same unit flags,
   where the spring's 1/3600 becomes 1/2500 and the damping divisor takes PAL's 50 Hz scale,
   (x * 5 + 2) / 6, in floats. */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    unsigned char pad000[0xE0];
    float vec_e0[4];
    unsigned char pad0F0[0x5C0 - 0xF0];
    char *target_5c0;
} Player003ED0D8;

extern char *g_moby_l02_pool[3] __attribute__((sda));
extern float g_tether_pull_height __attribute__((sda));
extern float g_tether_pull_step_limit __attribute__((sda));
extern float g_tether_spring_stiffness __attribute__((sda));
extern float g_tether_pull_damping __attribute__((sda));
extern Player003ED0D8 g_hero_state;

extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float ApproachValue(float *, float, float);

/* Pulls the tethered entity toward the actor with a spring and damping (PAL timings). */
void tether_pull_entity_pal(char *moby) {
    char *state = *(char **)(moby + 0x68);
    char *target = g_moby_l02_pool[0] + (*(int *)state << 8);
    float point[4];
    float hero_dir[4];
    float diff[4];
    float spring[4];
    float damp[4];
    float step;
    float *aim_point;
    float spring_len;
    float damp_len;

    *(TI128 *)point = *(TI128 *)(moby + 0x10);
    point[2] += g_tether_pull_height;
    if (g_hero_state.target_5c0 == target) {
        FastVecSub(hero_dir, g_hero_state.vec_e0, point);
        step = FastVecLength(hero_dir);
        ApproachValue(&step, 0.1f, g_tether_pull_step_limit);
        vec_scale_to_length(hero_dir, hero_dir, step);
        FastVecAdd(hero_dir, hero_dir, point);
    } else {
        *(TI128 *)hero_dir = *(TI128 *)point;
    }
    aim_point = hero_dir;
    FastVecSub(diff, target + 0x10, aim_point);
    spring_len = FastVecLength(diff);
    damp_len = FastVecLength(state + 0x10);
    spring_len = spring_len * 0.00040000002f;
    damp_len = damp_len / ((g_tether_pull_damping * 5.0f + 2.0f) * 0.16666667f);
    vec_scale_to_length(spring, diff, -(g_tether_spring_stiffness * spring_len));
    vec_scale_to_length(damp, state + 0x10, -damp_len);
    FastVecAdd(state + 0x10, state + 0x10, spring);
    FastVecAdd(state + 0x10, state + 0x10, damp);
    FastVecAdd(target + 0x10, target + 0x10, state + 0x10);
}
