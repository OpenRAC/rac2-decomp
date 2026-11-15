#include "include_asm.h"

#include "common.h"
extern float math_random_angle(void);
extern float math_random_float_range(float a, float b);
extern float math_fast_sin_or_cos_a(float a);
extern float math_fast_sin_or_cos_b(float a);
extern int math_random_int_range(int a, int b);
extern int math_random_int_below(int a);
extern void *func_PAL_002C0838(char *p, float *q, int a, int b);

/* func_00329768 uses small data in 00329768-g8.c. */



/* Per frame: scales the value one helper returns by the factor another helper returns, stores both scaled samples and a third sample into a three-float record, and hands the record to a setter with two selector results. */
void func_PAL_0032B650(char *a0)
{
    float v[3];
    float a;
    float b;
    int i;
    int m;
    int n;

    for (i = 47; i >= 0; i--) {
        a = math_random_angle();
        b = math_random_float_range(0.0f, 0.060000002f);
        v[0] = math_fast_sin_or_cos_a(a) * b;
        v[1] = math_fast_sin_or_cos_b(a) * b;
        v[2] = math_random_float_range(0.060000002f, 0.13000001f);
        m = math_random_int_range(90, 120);
        n = math_random_int_below(2);
        func_PAL_002C0838(a0 + 16, v, n, m);
    }
}


extern unsigned char *D_001BAF98[];
extern char g_music_state[];
extern int snd_resume_music_stream(void);
extern void moby_set_byte_on_group(int, int);
extern void STUB_printf(const char *, ...);
extern char D_001B0238[];
extern int g_surface_height_tiles[] __attribute__((sda));
extern int D_001B22D8[] __attribute__((sda));
extern int SampleSurfaceHeightMap(float *, float *, float, float, float);
extern void RippleDisturb(int, int, int, float, float, float, float);
extern int func_PAL_0026F670(void);

void func_PAL_0032B730(char *self)
{
    unsigned char *target = D_001BAF98[0];
    char *state = *(char **)(self + 0x68);
    unsigned char *object;
    unsigned char *obj_state;
    char *probe;
    float aux[4];
    float result[4];
    char *context;
    int mode;

    if (target == 0) {
        if (*(int *)(state + 0x38) != 2)
            return;
    }
    mode = *(int *)(state + 0x38);
    object = target;
    if (mode == 2)
        object = *(unsigned char **)(state + 0x48);
    if (*(short *)(*(char **)(object + 0x24) + 0x46) == 18) {
        obj_state = *(unsigned char **)(object + 0x68);
        if (obj_state != 0) {
            if (*(short *)(obj_state + 0x16) == 0) {
                *(int *)&result[0] = 0;
                if (mode != 2)
                    SampleSurfaceHeightMap(result, aux, *(float *)(self + 0x10), *(float *)(self + 0x14), *(float *)(self + 0x18));
                else
                    SampleSurfaceHeightMap(result, aux, *(float *)(state + 0x20), *(float *)(state + 0x24), *(float *)(state + 0x28));
                probe = *(char **)(object + 0x68);
                if (*(float *)(self + 0x18) > result[0] && *(float *)(probe + 0xC) == 0.0f) {
                    *(unsigned char **)(state + 0x48) = object;
                    *(int *)(state + 0x38) = 2;
                    return;
                }
                if (obj_state[0x14] == 0) {
                    RippleDisturb(g_surface_height_tiles[0], D_001B22D8[0], 1, *(float *)(self + 0x10), *(float *)(self + 0x14), 0.5f, -0.03f);
                    if (func_PAL_0026F670() == 0) {
                        object[0xBC] += 1;
                        if (object[0xBC] >= 25) {
                            context = g_music_state;
                            if (*(short *)(context + 0x72) == 3 && *(short *)(context + 0x6C) < 6000)
                                snd_resume_music_stream();
                        }
                        if (object[0x21] != 255)
                            moby_set_byte_on_group(object[0x21], object[0xBC]);
                    }
                }
                *(int *)(state + 0x44) = 0;
            } else {
                *(int *)(state + 0x44) = 1;
            }
        } else {
            STUB_printf(D_001B0238, *(short *)(object + 0xAA));
        }
        *(int *)(state + 0x38) = 1;
    } else {
        *(int *)(state + 0x38) = 0;
    }
}


void func_PAL_0032B920(void)
{
}
