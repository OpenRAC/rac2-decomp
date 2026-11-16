#include "common.h"

typedef int Q16_F398378 __attribute__((mode(TI)));
typedef union { Q16_F398378 q; float f[4]; } V4_F398378;

extern float math_random_float_range(float low, float high);
extern float math_random_signed_float_range(float low, float high);
extern void vec_clear_128(void *p);
extern char g_effect_records[];

/* Claims the first free record of the twenty-four 0xB0-byte records at D_L05_00233560 for the
   owner, starts it at the owner and fills it with eighteen drawn values. */
/* Takes a free debris slot and fills it with random spin and size values so a piece of debris
   tumbles away from the owner. */
void func_L05_00398378(char *owner, char *vel, int life)
{
    char *base = g_effect_records;
    char *origin = owner + 0x10;
    char *slot;
    int i;

    for (i = 0; i < 24; i++) {
        slot = base + i * 0xB0;
        if (*(int *)(slot + 0x9C) != 0)
            continue;
        *(char **)(slot + 0x9C) = owner;
        *(Q16_F398378 *)(slot + 0x20) = *(Q16_F398378 *)origin;
        *(Q16_F398378 *)(slot + 0x40) = *(Q16_F398378 *)vel;
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
        *(int *)(slot + 0x98) = 20;
        *(int *)(slot + 0xA8) = 0;
        *(int *)(slot + 0xA0) = life;
        *(int *)(slot + 0xA4) = life;
        break;
    }
}
