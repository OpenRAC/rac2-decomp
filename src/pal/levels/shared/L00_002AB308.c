#include "include_asm.h"


extern unsigned char D_00189E20[];
extern unsigned char D_L00_0025BE10[];
extern int func_00282948(int *);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);

/* Adapted from RAC1's hero_idle_and_animation.c (GPL-3.0).
 * Refreshes four idle rotation targets and copies them to their manipulators.
 */
void func_PAL_L00_002AB830(void) {
    char *base = (char *)D_00189E20;
    int *q;
    char *g;
    int i, j;
    char *tbl;

    if (*(int *)(base + 0x2294) != 0) return;
    if (*(unsigned char *)(*(int *)(base + 0x2290) + 0x43) != 0) return;
    q = (int *)(base + 0x11F0);
    g = base;
    tbl = D_L00_0025BE10;
    for (i = 0; i < 4; i++) {
        char *f;
        if (func_00282948(&q[i])) {
            if (i == 0) {
                int *s;
                *(float *)(g + 0x11B8) = func_002A78D8(0.174532949924469f, 0.523598849773407f);
                s = (int *)(D_00189E20 + 0x11F0);
                *s = func_002A7820(0x3A, 0x7D);
            } else if (i == 1) {
                *(float *)((char *)q - 0x28) = func_002A78D8(0.174532949924469f, 0.523598849773407f);
                q[1] = func_002A7820(0x21, 0x4B);
            } else if (i == 2) {
                *(float *)((char *)q - 0x18) = func_002A78D8(0.2617994248867035f, 0.8726646900177002f);
                q[2] = func_002A7820(0x21, 0x4B);
            } else {
                float old, nw;
                *(float *)(g + i * 0x10 + 0x11B4) = func_002A7878(-0.0872664749622345f, 0.523598849773407f);
                old = *(float *)(g + i * 0x10 + 0x11B8);
                nw = func_002A78D8(0.349065899848938f, 0.9599311947822571f);
                *(float *)(g + i * 0x10 + 0x11B8) = nw;
                if ((old <= 0 && nw <= 0) || (old >= 0 && nw >= 0))
                    *(float *)(g + i * 0x10 + 0x11B8) = -*(float *)(g + i * 0x10 + 0x11B8);
                q[i] = func_002A7820(0x1D, 0x3A);
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




