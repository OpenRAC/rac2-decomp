#include "include_asm.h"
#include "common.h"
extern s32 g_flashing_frame;

/* Scales the level's shared word by the object's own signed halfword, takes it modulo
   sixty and paints the object with 0x80FFFFFF when the remainder is under fifteen and
   with 0x80404040 otherwise; then it sets the sub-object's two flag words. */
void flashing_update_pal(s32 moby)
{
    s32 counter = g_flashing_frame;
    s32 period = 50;
    s32 value = *(short *)(moby + 0xB2);
    s32 dark_color = 0x80404040;
    s32 bright_color = 0x80FFFFFF;
    s32 color;
    s32 sub_object;

    counter = counter + value;
    value = counter % period;
    if (value >= 12)
        color = dark_color;
    else
        color = bright_color;
    *(s32 *)(moby + 0x78) = color;
    sub_object = *(s32 *)(moby + 0x68);
    *(u32 *)(sub_object + 0x8C) |= 1;
    *(u16 *)(sub_object + 0x3E) |= 8;
    *(u8 *)(moby + 0x30) = 0;
}

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern float g_burst_l17_speed_scale __attribute__((sda)), g_burst_jitter_scale __attribute__((sda));
extern char g_sound_state[];
extern int math_fast_float_d(void *);
extern float math_random_float_range(float, float);
extern void euler_to_matrix(void *, void *);
extern void vec_clear_128(void *);
extern void FastVecScale(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern void add_vectors(void *, void *, void *);
extern int math_random_int_below(int);
extern void *part_spawn_scaled_smoke_pal(void *, void *, int, void *, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void snd_stop_voice(int);

/* Updates the moby that sprays a burst of randomly scattered smoke puffs: it waits, sprays for a
   while, then stops its sound and starts over (PAL: 50 Hz rates). */
void part_burst_update_pal(unsigned char *obj)
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
        velocity.f[0] = *(float *)state * (g_burst_l17_speed_scale * 3.0f) * 0.020000001f;
        FastVecScale(&jitter, &jitter, velocity.f[0] * g_burst_jitter_scale);
        transform_vector(&velocity, &velocity, matrix);
        add_vectors(&random, &velocity, &jitter);
        if (*(int *)(state + 0xC) >= 8 || math_random_int_below(8 - *(int *)(state + 0xC)) == 0) {
            FastVecScale(&step, &velocity, 0.33f);
            part_spawn_scaled_smoke_pal(&position, &velocity, 0x40, obj, 0x80, 0x1FF);
        }
        if (*(int *)(state + 0xC) >= 8 || math_random_int_below(8 - *(int *)(state + 0xC)) == 0) {
            FastVecAdd(&position, &position, &step);
            part_spawn_scaled_smoke_pal(&position, &velocity, 0x40, obj, 0x80, 0x1FF);
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
