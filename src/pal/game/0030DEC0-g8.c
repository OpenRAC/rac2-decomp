/* func_PAL_0030DEC0, the PAL copy of func_0030CAD0: the same C, where the D_001AF040 copy is scaled for 50 Hz
   after the two stores of zero, and D_001B24A0 and D_001B24A4 trade sda and absolute access. */
#include "common.h"
extern short D_001B2494[] MACRO_ADDR;
extern short D_001B2496[] MACRO_ADDR;
extern short D_001B249E[] MACRO_ADDR;
extern short D_001B2490[] MACRO_ADDR;
extern short D_001B2498[] MACRO_ADDR;
extern short D_001B2492[] MACRO_ADDR;
extern short D_001B249A[] MACRO_ADDR;
extern short D_001B249C[] MACRO_ADDR;
typedef struct { float f[4]; } __attribute__((aligned(16))) Vec;
extern void FastVecSub(void *, void *, void *), FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float), vec_clear_128(void *);
extern int g_current_map_index, g_current_game_mode;
extern Vec D_001C1490[], D_001C14E0[];
extern int D_001AEFA0 __attribute__((sda));
extern float D_001AEFA4 __attribute__((sda));
extern int D_001AF040 __attribute__((sda));
extern int D_001AEFBC __attribute__((sda));
extern int D_001AEFC4 __attribute__((sda));
extern int D_001AEFD8 __attribute__((sda));
extern int D_001B24A0 __attribute__((sda));
extern int D_001B24A4;
extern short D_001B2480[4];
extern Vec D_00229710[];
extern Vec D_002299E0[];
extern int D_00229990[];
extern int D_00229B20[];
/* Same family as func_0030A188 (RAC1 initialize_electric_water_bolt_effect). */
void func_PAL_0030DEC0(char *obj) {
    Vec delta, step;
    Vec *state = *(Vec **)(obj + 0x68);
    int i;
    Vec *points;
    if (g_current_map_index == 1 && g_current_game_mode == 2) state = D_001C1490;
    if (g_current_map_index == 20 && g_current_game_mode == 2) state = D_001C14E0;
    if (D_001AEFA0) {
        D_001AEFA0 = 0;
        D_001B24A4 = 0;
        D_001B24A0 = ((s32)(D_001AF040) * 5 + 2) / 6;
        FastVecSub(&delta, state + 1, state);
        vec_scale_to_length(&step, &delta, D_001AEFA4 * 0.05f);
        points = D_00229710;
        qcopy(points, state);
        for (i = 1; i < 20; i++) {
            FastVecAdd(&points[i], &points[i - 1], &step);
            D_00229990[i] = 0;
            vec_clear_128(&D_002299E0[i]);
            D_00229B20[i] = 0;
        }
        { short empty = -1; int j; for (j = 3; j >= 0; j--) D_001B2480[j] = empty; }
        D_001B2490[0] = 8;
        D_001B2498[0] = 4;
        D_001B2492[0] = 4;
        D_001B249A[0] = 2;
        D_001B249C[0] = 4;
        D_001B2494[0] = 8;
        D_001B2496[0] = 4;
        D_001B249E[0] = 2;
        D_001AEFBC = 0;
        D_001AEFC4 = 0;
        D_001AEFD8 = 0;
    }
}
