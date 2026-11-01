#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
extern float D_L02_001B0518 __attribute__((sda));
extern float D_L02_001B051C __attribute__((sda));
extern float D_L02_001B0520 __attribute__((sda));
extern float D_L02_001B0524 __attribute__((sda));
extern float D_L02_001B0528 __attribute__((sda));
extern char D_L02_001B0500[4] __attribute__((sda));
extern char D_L02_001BA500[];
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACB48(float *, float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void *func_L02_003449D8(void *, void *, void *, void *, int);

/* Spawns arg1 particles at the point arg0 raised by D_L02_001B0524 and pushed along the vector
   from D_L02_001BA500, each with a random upward speed (a sixtieth of the range D_L02_001B051C ..
   D_L02_001B0520) and the particle kind that func_002A77E0 picks for 2. */
void func_PAL_L02_003DFC18(char *arg0, int arg1) {
    float vel[4];
    float pos[4];
    float tmp[4];
    int i;

    *(TI128 *)vel = 0;
    *(TI128 *)pos = *(TI128 *)arg0;
    pos[2] += D_L02_001B0524;
    pos[3] = 0;
    func_00282CF0(tmp, D_L02_001BA500, pos);
    tmp[2] = 0;
    func_00282F20(tmp, tmp, D_L02_001B0528);
    func_00282CC0(pos, pos, tmp);
    for (i = 0; i < arg1; i++) {
        func_002ACB48(pos, D_L02_001B0518);
        vel[2] = func_002A7878(D_L02_001B051C, D_L02_001B0520) * 0.020000001f;
        func_L02_003449D8(pos, vel, D_L02_001B0500, (void *)func_002A77E0(2), 1);
    }
}
