#include "common.h"

/* func_PAL_L11_0045F298, the PAL copy of func_L11_00459640: the same C at 50 Hz, where 1.0f / 60.0f
   becomes 0.020000001f, the lifetimes 60, 40, (10, 20) and (25, 60) become 50, 33, (8, 17) and
   (21, 50), and D_L11_001B1FF0 gains a factor of 1.44f (1.2 squared). */

extern void func_00282CF0(void *, void *, void *);
extern float func_002A7940(void);
extern int func_002A7820(int a0, int a1);
extern float func_002A7878(float a, float b);
extern float func_002A78D8(float, float);
extern void func_00282F20(char *a0, void *a1, float f12);
extern void func_00282D30(char *a0, void *a1, float f12);
extern void func_00282CC0(void *a0, void *a1, void *a2);
extern int func_001163B0(void);
extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_002AF000(void *, float, float, float);
extern char *func_002C2210(void *, int, int, float, float, float, int, int, void *, int);
extern void func_L00_0033E888(void *, void *, int, int, float, float, int, int, int, int, int);
extern char D_L11_001BA8C0[];
extern float D_L11_001B1FE0 __attribute__((sda));
extern float D_L11_001B1FE4 __attribute__((sda));
extern float D_L11_001B1FE8 __attribute__((sda));
extern float D_L11_001B1FEC __attribute__((sda));
extern float D_L11_001B1FF0 __attribute__((sda));
extern float D_L11_001B1FF4 __attribute__((sda));
extern float D_L11_001B1FF8 __attribute__((sda));
extern int D_L11_001B2000 __attribute__((sda));
extern int D_L11_001B2004 __attribute__((sda));

void func_PAL_L11_0045F298(float *p, int count, int mode)
{
    float vel[4], pos[4], axis[4], up[4], a[4], b[4], out[4];
    int i, j, sign;
    char *effect;
    float size, speed, angle, r;

    func_00282CF0(axis, D_L11_001BA8C0, p);
    axis[2] = 0;
    up[0] = 0;
    up[1] = 0;
    up[2] = 1;
    up[3] = 1;
    for (i = 0; i < count; i++) {
        size = func_002A7878(D_L11_001B1FF4, D_L11_001B1FF8);
        sign = func_002A77E0(2);
        if (!sign)
            --sign;
        angle = func_002A7878(-1.0471977f, 1.0471977f);
        func_002ACEC0(vel, axis, up, angle);
        speed = func_002A7878(D_L11_001B1FE0, D_L11_001B1FE4) * 0.020000001f;
        func_00282F20((char *)vel, vel, speed);
        vel[2] = func_002A7878(D_L11_001B1FE8, D_L11_001B1FEC) * 0.020000001f;
        qcopy(pos, p);
        pos[0] += func_002A78D8(0, 0.15f);
        pos[1] += func_002A78D8(0, 0.15f);
        pos[2] += func_002A78D8(0, 0.15f);
        if (!mode) {
            if (!(func_001163B0() & 1)) {
                func_00282D30((char *)vel, vel, 1.5f);
                effect = func_002C2210(pos, 50, D_L11_001B2000, size * 0.35f, size, D_L11_001B1FF0 * 1.44f, 0, sign, vel, 0);
                if (effect)
                    effect[9] = func_00283CF0(4.0f) + 112;
                effect = func_002C2210(pos, 50, D_L11_001B2004, size * 0.245f, size * 0.7f, D_L11_001B1FF0 * 1.44f, 1, -sign, vel, 0);
            } else {
                func_00282CF0(a, D_L11_001BA8C0, pos);
                func_00282F20((char *)a, a, speed);
                func_00282CC0(vel, vel, a);
                effect = func_002C2210(pos, 33, D_L11_001B2000, size * 2.05f, size, D_L11_001B1FF0 * 1.44f, 0, sign, vel, 0);
                if (effect)
                    effect[9] = func_00283CF0(4.0f) + 112;
                effect = func_002C2210(pos, 33, D_L11_001B2004, size * 1.4350000619888306f, size * 0.7f, D_L11_001B1FF0 * 1.44f, 1, -sign, vel, 0);
            }
        } else {
            if (!(func_001163B0() & 1)) {
                func_00282D30((char *)vel, vel, 1.5f);
                effect = func_002C2210(pos, 50, D_L11_001B2000, size * 0.3f, size, D_L11_001B1FF0 * 1.44f, 0, sign, vel, 0);
                if (effect)
                    effect[9] = func_00283CF0(4.0f) + 112;
                effect = func_002C2210(pos, 50, D_L11_001B2004, size * (0.3f * 0.7f), size * 0.7f, D_L11_001B1FF0 * 1.44f, 1, -sign, vel, 0);
            } else {
                func_00282CF0(a, D_L11_001BA8C0, pos);
                func_00282F20((char *)a, a, speed);
                func_00282CC0(vel, vel, a);
                effect = func_002C2210(pos, 33, D_L11_001B2000, size * 0.25f, size, D_L11_001B1FF0 * 1.44f, 0, sign, vel, 0);
                if (effect)
                    effect[9] = func_00283CF0(4.0f) + 112;
                effect = func_002C2210(pos, 33, D_L11_001B2004, size * 0.175f, size * 0.7f, D_L11_001B1FF0 * 1.44f, 1, -sign, vel, 0);
            }
        }
        if (effect)
            effect[9] = func_00283CF0(4.0f) + 112;
    }
    for (j = 1; j >= 0; j--) {
        angle = func_002A7878(-0.9599312f, -1.3962636f);
        r = func_002A7940();
        func_002AF000(a, func_002A7878(0, 0.5f) * 0.020000001f, r, angle);
        func_00282CF0(b, D_L11_001BA8C0, p);
        func_00282F20((char *)b, b, 0.15f);
        func_00282CC0(p, p, b);
        size = func_002A7878(30000, 60000);
        out[0] = p[0] + func_002A78D8(0, 0.15f);
        out[1] = p[1] + func_002A78D8(0, 0.15f);
        out[2] = p[2] + func_002A78D8(0, 0.15f);
        if (mode)
            func_L00_0033E888(out, a, 0x4F93E5FF, 0x102434EE, size, 0.5f, func_002A7820(8, 17), 1, -1, -1, 0);
        else
            func_L00_0033E888(out, a, 0x4F93E5FF, 0x102434EE, size, 0.5f, func_002A7820(21, 50), 1, -1, -1, 0);
    }
}
