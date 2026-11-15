/* func_L20_00442890: own unit (-O2 -G8). The parent state block is read into its own block
 * local (st) and p is formed from it before the hero distance call: that extra pseudo copy
 * gives sched1 the retail order (the parent load before the hero-pos loads, base still live). */
#include "common.h"

extern char D_L20_001B9E80[];

typedef struct { char pad[0x80]; float pos[4]; } HeroView;
extern HeroView D_00189E20;

extern float D_L20_001B2150 __attribute__((sda));
extern float D_L20_001B2154 __attribute__((sda));
extern float D_L20_001B2158 __attribute__((sda));
extern float D_L20_001B215C __attribute__((sda));
extern float D_L20_001B2160 __attribute__((sda));

extern void func_L00_00424A08(int, float, float);
extern void func_L00_00424A50(float, float);
extern void func_L00_00424A88(int, float, float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_002AAA00(void *, float, float, float, float, void *, int);

void func_L20_00442890(char *arg0)
{
    char *s0 = arg0;
    char *base = D_L20_001B9E80;
    char *s1;
    float *p;
    float r, q, w, x;

    if (*(short *)(*(char **)(base + 0x190) + 0x86) != 0) {
        return;
    }
    follow_camera_set_distance(0, D_L20_001B2158, 0.003f);
    follow_camera_set_height(D_L20_001B215C, 0.003f);
    func_L00_00424A88(0, D_L20_001B2160, 0.005f);
    if (*(unsigned char *)(s0 + 0x95) == 4 ||
        *(unsigned char *)(s0 + 0x95) == 2) {
        return;
    }
    s1 = *(char **)(s0 + 0x68);
    {
        char *st = *(char **)(*(char **)(base + 0x190) + 0x70);
        s0 = st;
        p = (float *)(st + 0x160);
    }
    r = func_00283248(*(float *)(arg0 + 0x10) - D_00189E20.pos[0],
                      *(float *)(arg0 + 0x14) - D_00189E20.pos[1]);
    x = p[0];
    s0 += 0x1C0;
    q = func_00283248(x, p[1]);
    q = FastAddRotations(q, 3.1415927f);
    w = fast_subtract_rotations(r, q);
    func_002AAA00((char *)&w, 0.0f,
                   D_L20_001B2150 * 4.84813745e-06f,
                   D_L20_001B2150 * 4.84813745e-06f,
                   D_L20_001B2154 * 0.000290888245f, s1 + 0x17F0, 0);
    *(float *)(s0 + 0x1C) = 1.0f;
    *(float *)(s0 + 0x14) = -*(float *)(s1 + 0x17F0);
}
