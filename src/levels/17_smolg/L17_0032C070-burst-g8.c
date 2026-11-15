#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern float D_L17_001AF320 __attribute__((sda)), D_L17_001AF324 __attribute__((sda));
extern char g_sound_state[];
extern int math_fast_float_d(void *);
extern float math_random_float_range(float, float);
extern void euler_to_matrix(void *, void *);
extern void vec_clear_128(void *);
extern void FastVecScale(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern void add_vectors(void *, void *, void *);
extern int math_random_int_below(int);
extern void *part_spawn_scaled_smoke(void *, void *, int, void *, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void snd_stop_voice(int);
/* Updates the moby that sprays a burst of randomly scattered particles: it waits, sprays for a
   while, then stops its sound and starts over. */
void part_burst_update(unsigned char *obj)
{
    float matrix[16];
    Vec position, velocity, step, jitter, random;
    char *state = *(char **)(obj + 0x68);
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(int *)(state + 0xC) = *(int *)(state + 0x14);
        obj[0x30] = 255;
        obj[0x20] = 1;
        *(float *)(obj + 0x18) -= 3.0f;
        break;
    case 1:
        *(int *)(state + 0x10) = -1;
        if (math_fast_float_d(state + 0xC)) {
            *(int *)(state + 0xC) = *(int *)(state + 4);
            obj[0x20] = 2;
        }
        break;
    case 2:
        random.q = 0;
        random.f[0] = math_random_float_range(-1.0f, 1.0f);
        random.f[1] = math_random_float_range(-1.0f, 1.0f);
        random.f[2] = math_random_float_range(-1.0f, 1.0f);
        jitter.q = random.q;
        qcopy(&position, obj + 0x10);
        euler_to_matrix(matrix, obj + 0xF0);
        vec_clear_128(&velocity);
        velocity.f[0] = *(float *)state * (D_L17_001AF320 * 3.0f) * 0.016666668f;
        FastVecScale(&jitter, &jitter, velocity.f[0] * D_L17_001AF324);
        transform_vector(&velocity, &velocity, matrix);
        add_vectors(&random, &velocity, &jitter);
        if (*(int *)(state + 0xC) >= 10 || math_random_int_below(10 - *(int *)(state + 0xC)) == 0) {
            FastVecScale(&step, &velocity, 0.33f);
            part_spawn_scaled_smoke(&position, &velocity, 0x40, obj, 0x80, 0x1FF);
        }
        if (*(int *)(state + 0xC) >= 10 || math_random_int_below(10 - *(int *)(state + 0xC)) == 0) {
            FastVecAdd(&position, &position, &step);
            part_spawn_scaled_smoke(&position, &velocity, 0x40, obj, 0x80, 0x1FF);
        }
        if (math_fast_float_d(state + 0xC)) {
            int index;
            *(int *)(state + 0xC) = *(int *)(state + 8);
            obj[0x20] = 1;
            index = *(int *)(state + 0x10);
            if (index != -1) {
                char *slot = g_sound_state + index * 0x70;
                if (*(char **)(slot + 0x88) == obj && *(unsigned char *)(slot + 0x74))
                    snd_stop_voice(index);
            }
            *(int *)(state + 0x10) = -1;
        }
        break;
    }
}
