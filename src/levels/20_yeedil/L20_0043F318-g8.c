#include "names.h"
/* Nonmatching: 332/328 bytes.
 * Profile: -O2 -G8 -ffunction-sections.
 * Placement checks: US: 0/1; US2: 0/1; PAL: 0/1.
 * 332/328 bytes. The complete prefix and count-up copy loop agree until an additional NOP at +0x10c shifts the back edge and epilogue. The reviewed qcopy emits two words but is counted as one instruction by post-DBR loop padding (MATCHING-BLOCKERS section30). The subtraction scratch now reserves the full16 bytes written by the callee.
 * Reopen with an independently qualified loop-padding/compiler profile or meaningful loop source change. Indexed helpers and the grouped TI/barrier profile retain this extra NOP; no dummy padding is added.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void *CreateMoby(int);
extern void moby_init_child_from_parent(void *, void *);
extern void FastVecSub(float *, void *, void *);
extern float vec_length_xy(float *);
extern float mat_fast_helper_a(float, float);
extern float math_random_float_range(float, float);
extern float g_yeedil_shot_base_timer __attribute__((sda));


/* Spawns a projectile next to its owner and points it at the hero. It also sets the speed, the delay before it moves, its lifetime and its damage. */
char *yeedil_enemy_spawn_shot(char *owner, char *spawn_pos, int lifetime, int side, int counter_ptr, float damage) {
    char *obj = (char *)CreateMoby(0x119D /* moby class 4509 */);
    char *state;
    float v[4] __attribute__((aligned(16)));
    float random_value;
    float timer;
    int i;

    if (obj == 0) {
        goto out;
    }
    moby_init_child_from_parent(obj, owner);
    qcopy(obj + 0x10, spawn_pos);
    FastVecSub(v, (void *)(obj + 0x10), owner + 0x10);
    state = *(char **)(obj + 0x68);
    *(float *)(state + 0x40) = vec_length_xy(v);
    *(float *)(state + 0x44) = mat_fast_helper_a(v[0], v[1]);
    *(float *)(state + 0x5C) = *(float *)(owner + 0x18);
    random_value = math_random_float_range(1.0f, 4.0f);
    *(float *)(state + 0x4C) = *(float *)(state + 0x5C) + random_value;
    random_value = math_random_float_range(0.0f, 1.0f);
    timer = g_yeedil_shot_base_timer + random_value;
    *(int *)(state + 0x64) = lifetime;
    *(int *)(state + 0x68) = side;
    *(int *)(state + 0x6C) = counter_ptr;
    *(float *)(state + 0x70) = damage;
    *(float *)(state + 0x48) = timer;
    for (i = 0; i < 3; i++) {
        qcopy(state + 0x10 + i * 0x10, spawn_pos);
    }
out:
    return obj;
}
