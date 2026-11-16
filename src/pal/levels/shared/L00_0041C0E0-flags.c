#include "include_asm.h"

#include "common.h"
typedef int Q16_F417A40 __attribute__((mode(TI)));
typedef union { Q16_F417A40 q; float f[4]; } V4_F417A40;
extern float math_random_float_range(float low, float high);
extern float math_random_signed_float_range(float low, float high);
extern void vec_clear_128(void *p);
extern void matrix_mul_vec3(void *out, void *in, void *matrix);
extern void FastVecAdd(void *out, void *a, void *b);
extern char g_spark_l00_records[];

/* Claims the first free record of the twenty-four 0xB0-byte records at D_L00_0025A920 for the
   owner, starts it at the owner (or at an offset from the owner's parent) and fills it with
   eighteen drawn values. */
void spark_record_claim_pal(char *owner, char *vel, int life)
{
    char *base = g_spark_l00_records;
    char *info = *(char **)(owner + 0x68);
    char *origin = owner + 0x10;
    char *slot;
    V4_F417A40 pos, offset;
    int i;

    for (i = 0; i < 24; i++) {
        slot = base + i * 0xB0;
        if (*(int *)(slot + 0x9C) != 0)
            continue;
        *(char **)(slot + 0x9C) = owner;
        if (*(int *)(info + 4) == 0) {
            *(Q16_F417A40 *)(slot + 0x20) = *(Q16_F417A40 *)origin;
        } else {
            offset.q = 0;
            offset.f[0] = -0.15f;
            offset.f[1] = -0.8f;
            offset.f[3] = 1.0f;
            matrix_mul_vec3(&pos, &offset, *(char **)(info + 8) + 0xC0);
            FastVecAdd(&pos, &pos, *(char **)(info + 8) + 0x10);
            *(Q16_F417A40 *)(slot + 0x20) = pos.q;
        }
        *(Q16_F417A40 *)(slot + 0x40) = *(Q16_F417A40 *)vel;
        *(float *)(slot + 0x20) += math_random_float_range(-0.1f, 0.1f);
        *(float *)(slot + 0x24) += math_random_float_range(-0.1f, 0.1f);
        *(float *)(slot + 0x28) += math_random_float_range(-0.1f, 0.1f);
        *(float *)(slot + 0x50) = math_random_float_range(-3.14159274f, 3.14159274f);
        *(float *)(slot + 0x54) = math_random_float_range(-3.14159274f, 3.14159274f);
        *(float *)(slot + 0x58) = math_random_float_range(-3.14159274f, 3.14159274f);
        *(float *)(slot + 0x74) = math_random_float_range(-3.14159274f, 3.14159274f);
        *(float *)(slot + 0x78) = math_random_float_range(-3.14159274f, 3.14159274f);
        *(float *)(slot + 0x7C) = math_random_float_range(-3.14159274f, 3.14159274f);
        *(float *)(slot + 0x5C) = math_random_signed_float_range(0.001f, 0.005f);
        *(float *)(slot + 0x60) = math_random_signed_float_range(0.001f, 0.005f);
        *(float *)(slot + 0x64) = math_random_signed_float_range(0.001f, 0.005f);
        *(float *)(slot + 0x80) = math_random_signed_float_range(0.001f, 0.005f);
        *(float *)(slot + 0x84) = math_random_signed_float_range(0.001f, 0.005f);
        *(float *)(slot + 0x88) = math_random_signed_float_range(0.001f, 0.005f);
        *(float *)(slot + 0x68) = math_random_float_range(3.25f, 4.75f);
        *(float *)(slot + 0x6C) = math_random_float_range(3.25f, 4.75f);
        *(float *)(slot + 0x70) = math_random_float_range(3.25f, 4.75f);
        *(float *)(slot + 0x8C) = math_random_float_range(3.25f, 4.75f);
        *(float *)(slot + 0x90) = math_random_float_range(3.25f, 4.75f);
        *(float *)(slot + 0x94) = math_random_float_range(3.25f, 4.75f);
        vec_clear_128(slot);
        vec_clear_128(slot + 0x10);
        *(int *)(slot + 0x98) = 17;
        *(int *)(slot + 0xA8) = 0;
        *(int *)(slot + 0xA0) = life;
        *(int *)(slot + 0xA4) = life;
        break;
    }
}
