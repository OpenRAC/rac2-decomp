#include "common.h"

/* func_L23_0041AFE8 is a unit of its own: it reads $gp data and needs -fno-sched-interblock
   (config/cflags.txt), which keeps the effect call's argument setup behind the handle test.
   Every transfer is the qcopy helper: the inline parameters keep the loop's two names for the
   next point apart, which is what spills obj to the 0xD0 frame. The effect call is typed with
   its FP arguments ahead of the last integer register, as retail sets them up; the EE assigns
   the two banks independently, so this is the same call as func_L23_004256F0's definition. */

typedef int TI128 __attribute__((mode(TI)));

extern float D_L23_001B157C __attribute__((sda));
extern float D_L23_001B378C;
extern char D_L23_001B37A0[] __attribute__((sda));
extern int D_L23_001B1534 __attribute__((sda));
extern unsigned char D_L23_001B1510 __attribute__((sda));
extern unsigned char D_L23_001B1514 __attribute__((sda));
extern float D_L23_001B1518 __attribute__((sda));
extern float D_L23_001B151C __attribute__((sda));
extern float D_L23_001B1520 __attribute__((sda));
extern float D_L23_001B1524 __attribute__((sda));
extern short D_L23_001B1528 __attribute__((sda));
extern short D_L23_001B152C __attribute__((sda));
extern int D_L23_001B1530 __attribute__((sda));

extern void func_L23_00418650(char *, float);
extern void func_00282CC0(float *, float *, float *);
extern void func_00282CF0(float *, float *, float *);
extern void func_00282F20(float *, float *, float);
extern void *func_L23_004256F0(u8 *, u8 *, u8 *, u8, u8, short, short, float, float, float, float, int, int, int, int, int);

/* Lays three beam segments between two points around the planet, creating each beam effect only once. */
void func_L23_0041AFE8(char *obj, TI128 *p1, TI128 *p2, TI128 *out, int *handles) {
    TI128 loc[5];
    char *prev = D_L23_001B37A0;
    int k;

    qcopy(&loc[0], p2);
    ProjectPointOntoPlanetSurface((char *)&loc[0], D_L23_001B157C);
    FastVecSub((float *)&loc[1], (float *)&loc[0], (float *)p1);
    vec_scale_to_length((float *)&loc[1], (float *)&loc[1], D_L23_001B378C);
    qcopy(&loc[4], p1);
    qcopy(&loc[2], p1);
    ProjectPointOntoPlanetSurface((char *)&loc[2], D_L23_001B157C);
    for (k = 0; k < 3; k++) {
        FastVecAdd((float *)&loc[3], (float *)&loc[4], (float *)&loc[1]);
        ProjectPointOntoPlanetSurface((char *)&loc[3], D_L23_001B157C);
        qcopy(out, &loc[3]);
        if (*handles == 0) {
            *handles = (int)CreateRibbonTrail(prev, obj, (char *)out, D_L23_001B1510, D_L23_001B1514, D_L23_001B1528, D_L23_001B152C, D_L23_001B1518, D_L23_001B151C, D_L23_001B1520, D_L23_001B1524, D_L23_001B1530, D_L23_001B1534, 1, -1, 1);
        }
        handles++;
        qcopy(&loc[2], &loc[3]);
        prev = (char *)out;
        FastVecAdd((float *)&loc[4], (float *)&loc[4], (float *)&loc[1]);
        out++;
    }
}
