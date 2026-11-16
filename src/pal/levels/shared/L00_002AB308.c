#include "include_asm.h"
#include "names.h"


extern unsigned char g_hero_state[];
extern unsigned char g_hero_item_attach_records[];
extern int math_fast_float_d(int *);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);

/* Adapted from RAC1's hero_idle_and_animation.c (GPL-3.0).
 * Refreshes four idle rotation targets and copies them to their manipulators.
 */
void UpdateHeroIdleRandomRotationTargets_pal(void) {
    char *base = (char *)g_hero_state;
    int *q;
    char *g;
    int i, j;
    char *tbl;

    if (*(int *)(base + 0x2294) != 0) return;
    if (*(unsigned char *)(*(int *)(base + 0x2290) + 0x43) != 0) return;
    q = (int *)(base + 0x11F0);
    g = base;
    tbl = g_hero_item_attach_records;
    for (i = 0; i < 4; i++) {
        char *f;
        if (math_fast_float_d(&q[i])) {
            if (i == 0) {
                int *s;
                *(float *)(g + 0x11B8) = math_random_signed_float_range(0.174532949924469f, 0.523598849773407f);
                s = (int *)(g_hero_state + 0x11F0);
                *s = math_random_int_range(0x3A, 0x7D);
            } else if (i == 1) {
                *(float *)((char *)q - 0x28) = math_random_signed_float_range(0.174532949924469f, 0.523598849773407f);
                q[1] = math_random_int_range(0x21, 0x4B);
            } else if (i == 2) {
                *(float *)((char *)q - 0x18) = math_random_signed_float_range(0.2617994248867035f, 0.8726646900177002f);
                q[2] = math_random_int_range(0x21, 0x4B);
            } else {
                float old, nw;
                *(float *)(g + i * 0x10 + 0x11B4) = math_random_float_range(-0.0872664749622345f, 0.523598849773407f);
                old = *(float *)(g + i * 0x10 + 0x11B8);
                nw = math_random_signed_float_range(0.349065899848938f, 0.9599311947822571f);
                *(float *)(g + i * 0x10 + 0x11B8) = nw;
                if ((old <= 0 && nw <= 0) || (old >= 0 && nw >= 0))
                    *(float *)(g + i * 0x10 + 0x11B8) = -*(float *)(g + i * 0x10 + 0x11B8);
                q[i] = math_random_int_range(0x1D, 0x3A);
            }
        }
        f = g + i * 0x10;
        j = i + 13;
        base = (char *)(j * 0xB0);
        {
            char *r = tbl + (int)base;
            *(float *)(r + 0x68) = *(float *)(f + 0x11B8);
            *(float *)(r + 0x64) = *(float *)(f + 0x11B4);
        }
    }
}




