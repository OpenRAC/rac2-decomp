#include "include_asm.h"
#include "common.h"
extern s32 D_001B2748;

/* Scales the level's shared word by the object's own signed halfword, takes it modulo
   sixty and paints the object with 0x80FFFFFF when the remainder is under fifteen and
   with 0x80404040 otherwise; then it sets the sub-object's two flag words. */
void func_PAL_L17_003C0758(s32 a0)
{
    s32 v1 = D_001B2748;
    s32 d = 50;
    s32 v0 = *(short *)(a0 + 0xB2);
    s32 c1 = 0x80404040;
    s32 t0 = 0x80FFFFFF;
    s32 a1;
    s32 a3;

    v1 = v1 + v0;
    v0 = v1 % d;
    if (v0 >= 12)
        a1 = c1;
    else
        a1 = t0;
    *(s32 *)(a0 + 0x78) = a1;
    a3 = *(s32 *)(a0 + 0x68);
    *(u32 *)(a3 + 0x8C) |= 1;
    *(u16 *)(a3 + 0x3E) |= 8;
    *(u8 *)(a0 + 0x30) = 0;
}

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
extern void *func_PAL_002C0FF0(void *, void *, int, void *, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void snd_stop_voice(int);

void func_PAL_L17_003A4A28(unsigned char *obj)
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
        velocity.f[0] = *(float *)state * (D_L17_001AF320 * 3.0f) * 0.020000001f;
        FastVecScale(&jitter, &jitter, velocity.f[0] * D_L17_001AF324);
        transform_vector(&velocity, &velocity, matrix);
        add_vectors(&random, &velocity, &jitter);
        if (*(int *)(state + 0xC) >= 8 || math_random_int_below(8 - *(int *)(state + 0xC)) == 0) {
            FastVecScale(&step, &velocity, 0.33f);
            func_PAL_002C0FF0(&position, &velocity, 0x40, obj, 0x80, 0x1FF);
        }
        if (*(int *)(state + 0xC) >= 8 || math_random_int_below(8 - *(int *)(state + 0xC)) == 0) {
            FastVecAdd(&position, &position, &step);
            func_PAL_002C0FF0(&position, &velocity, 0x40, obj, 0x80, 0x1FF);
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
