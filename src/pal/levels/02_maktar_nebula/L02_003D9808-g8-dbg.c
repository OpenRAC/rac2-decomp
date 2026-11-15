#include "names.h"
/* func_PAL_L02_003D9808, the PAL copy of func_L02_003D5748: the same C, where outbound and inbound
   take 0.7142857f and 0.5555555f, the 50 Hz scale (x * 5.0f + 2.0f) * 0.16666667f is applied to outbound
   and outbound + 5.0f in the phase tests and terms, 0.2916667f becomes 0.058333337f, 1.1666667f becomes
   1.4000001f and 1.5000001f becomes 1.8000001f. */
#include "common.h"

typedef int Vector __attribute__((mode(TI)));
/* The trajectory table has at least the five observed entries; full extent unknown. */
extern float D_L02_001B0190[] SDATA(D_L02_001B0190);
extern float D_L02_001B01E4 __attribute__((sda));
extern float D_L02_001B01E8 __attribute__((sda));
extern float D_L02_001B01B8;
extern void moby_transform_joint_to_world(char *, int, char *);
extern void moby_transform_joint_point(char *, int, char *);
extern void copy_matrix3x4(void *, void *);
extern void mat_normalize_columns(void *);
extern float math_fast_sin_or_cos_a(float);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void moby_copy_joint_transform_to_object(char *, char *, int, int);
extern void func_002A10E8(char *);
extern void chainblade_free_effect_trail(char *);
extern char *chainblade_spawn_effect_trail(void *, void *, float);
extern int FloatToInt(float);
/* NOTE REVIEW: typed int/FP interleaving (AGENTS.md): each bank's order, the stack arguments and the return
 * match 0032C700-explosion.c. Floats-first is the order the matched callers L16_0041EE90-g8.c,
 * shared/L00_003AB388-hit.c, shared/L00_003F5390-g8.c and shared/L04_00402D90.c use; it puts the
 * size move ahead of the integer arguments, as retail schedules it. */
extern char *func_PAL_L00_003FB330(void *, float, float, int, int, int, int, int, int, int, int, int, int, char *);
extern int coll_sweep_from_object(void *, void *, int, int, int, int, float, float, float);

int func_PAL_L02_003D9808(char *self, int joint) {
    float origin[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float impact[4] __attribute__((aligned(16)));
    float rotation[12] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    char *state = *(char **)(self + 0x68);
    char **slots;
    float travel;
    float outbound;
    float inbound;
    float phase;
    float time;
    int i;
    int trajectoryOffset;
    int rounded;
    int timer;
    int elapsed;
    moby_transform_joint_to_world(self, joint, (char *)origin);
    moby_transform_joint_point(self, joint, (char *)matrix);
    copy_matrix3x4(rotation, matrix);
    mat_normalize_columns(rotation);
    qcopy(direction, rotation);
    travel = (origin[2] - D_L02_001B01B8) / math_fast_sin_or_cos_a(1.15f);
    FastVecScale(impact, direction, travel);
    FastVecAdd(impact, impact, origin);
    travel -= 5.3f;
    outbound = travel * 0.7142857f;
    inbound = travel * 0.5555555f;
    for (i = 0, slots = (char **)(state + 0x2A0), trajectoryOffset = 0; i < 5; i++, slots++, trajectoryOffset += sizeof(float)) {
        if (*slots) {
            moby_copy_joint_transform_to_object(self, *slots, joint, joint != 1 ? 0 : 6);
            time = (float)*(short *)(state + 0x31E);
            if (time < (outbound * 5.0f + 2.0f) * 0.16666667f) {
                phase = (time - (outbound * 5.0f + 2.0f) * ((4.0f - (float)i) * 0.16666667f) * 0.25f) * 1.4000001f;
                if (phase < 0.0f) phase = 0.0f;
            } else if (time < ((outbound + 5.0f) * 5.0f + 2.0f) * 0.16666667f) {
                phase = (outbound * 5.0f + 2.0f) * ((float)i * 0.058333337f);
                if (phase < 0.0f) phase = 0.0f;
            } else {
                phase = (outbound * 5.0f + 2.0f) * ((float)i * 0.058333337f) - (time - ((outbound + 5.0f) * 5.0f + 2.0f) * 0.16666667f) * 1.8000001f;
                if (phase < 0.0f) phase = 0.0f;
            }
            vec_scale_to_length(delta, direction, phase + *(float *)((char *)D_L02_001B0190 + trajectoryOffset));
            FastVecAdd(*slots + 0x10, origin, delta);
            func_002A10E8(*slots);
            if (*(char **)(state + 0x300)) chainblade_free_effect_trail(*(char **)(state + 0x300));
            vec_scale_to_length(offset, rotation + 8, D_L02_001B01E8);
            FastVecAdd(origin, *(char **)(state + 0x2A0) + 0x10, offset);
            qcopy(end, *(char **)(state + 0x2B0) + 0x10);
            vec_scale_to_length(offset, rotation + 4, D_L02_001B01E4);
            FastVecAdd(origin, origin, offset);
            *(char **)(state + 0x300) = chainblade_spawn_effect_trail(origin, end, 0.2f);
        }
    }
    timer = ++*(short *)(state + 0x31E);
    rounded = FloatToInt(outbound);
    if (timer > FloatToInt(inbound) + rounded + 7) return 2;
    elapsed = *(short *)(state + 0x31E);
    if (elapsed > FloatToInt(outbound) + 6) return 1;
    elapsed = *(short *)(state + 0x31E);
    if (elapsed > FloatToInt(outbound) + 1 && *(short *)(state + 0x320) == 0) {
        func_PAL_L00_003FB330(impact, 0.5f, 20.0f, 0, 25, 20, 20, 20, 45, 0, 1, 0, 0, 0);
        coll_sweep_from_object(self, impact, 0x10001, 0, 1, 0, 0.5f, (float)*(unsigned char *)(state + 0x35), 1.0f);
        *(short *)(state + 0x320) = 1;
    }
    return 0;
}
