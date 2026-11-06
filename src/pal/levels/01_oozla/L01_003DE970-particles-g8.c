/* func_PAL_L01_003DE970, the PAL copy of func_L01_003DA3F0: the same C at 50 Hz, with the frame
 * constants rescaled and the particle lifetimes passed through the 5/6 scale. */
#include "common.h"
extern int D_L01_001B0844 __attribute__((sda));
extern int D_L01_001B0848 __attribute__((sda));
extern int D_L01_001B0888 __attribute__((sda));
extern int D_L01_001B088C __attribute__((sda));
extern int D_L01_001B0874 __attribute__((sda));
extern int D_L01_001B0878 __attribute__((sda));
extern int D_L01_001B087C __attribute__((sda));
extern int D_L01_001B0880 __attribute__((sda));
extern int D_L01_001B0884 __attribute__((sda));
extern float D_L01_001B084C __attribute__((sda));
extern float D_L01_001B0850 __attribute__((sda));
extern float D_L01_001B0854 __attribute__((sda));
extern float D_L01_001B0858 __attribute__((sda));
extern float D_L01_001B085C __attribute__((sda));
extern float D_L01_001B0860 __attribute__((sda));
extern float D_L01_001B0864 __attribute__((sda));
extern float D_L01_001B0868 __attribute__((sda));
extern float D_L01_001B086C __attribute__((sda));
extern float D_L01_001B0870 __attribute__((sda));
extern float D_L01_001B0890 __attribute__((sda));
extern float D_L01_001B083C __attribute__((sda));
extern void func_002ACB48(void *, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern void func_00282D30(void *,void *, float);
extern float func_00283180(float), func_00283198(float);
extern int func_00283D38(int, int, float);
extern int func_00283CF0(float);
extern void *func_002BAA28(void *,void *,void *,int,int,int,int,int,int);
extern void func_002ABBB8(void *,void *,int,int,int,int,int,int,int,int,int, int, float, float,float, float,float, float,float);
/* Emits randomized particle trails, then the owner's explosion effect. */
void func_PAL_L01_003DE970(u8 *a0, void *a1)
{
    float pos[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    float acc[4] __attribute__((aligned(16)));
    u8 *p = *(u8 **)(a0 + 0x68);
    int i, j, c1, c2, n;
    float angle, speed, z, r, scale, lifetime, maximum;
    u8 *position;

    for (i = 0; i < D_L01_001B0844; i++) {
        position = a0 + 0x10;
        qcopy(pos, position);
        func_002ACB48(pos, D_L01_001B084C);
        pos[2] += 0.25f;
        angle = func_002A7940();
        speed = func_002A7878(D_L01_001B0858, D_L01_001B085C);
        z = func_002A7878(D_L01_001B0860, D_L01_001B0864);
        r = func_002A7878(0.0f, D_L01_001B0890);
        func_00282D30(vel, a1, r * 0.020000001f);
        vel[0] += func_00283180(angle) * 0.020000001f * speed;
        vel[1] += func_00283198(angle) * 0.020000001f * speed;
        vel[2] += z * 0.020000001f;
        qcopy(acc, vel);
        acc[2] -= D_L01_001B0868 * ((float)(((s32)D_L01_001B0888 * 5 + 2) / 6) * 0.00040000002f);
        for (j = 0; j < D_L01_001B0848; j++) {
            scale = func_002A7878(0.5f, 1.5f);
            vel[3] = scale * D_L01_001B086C;
            acc[3] = scale * D_L01_001B0870;
            func_002ACB48(pos, D_L01_001B0850);
            func_002ACB48(acc, D_L01_001B0854 * 0.020000001f);
            c1 = func_00283D38(D_L01_001B0874, D_L01_001B087C,
                              func_002A7878(0.0f, 1.0f));
            c2 = func_00283D38(D_L01_001B0878, D_L01_001B0880,
                              func_002A7878(0.0f, 1.0f));
            lifetime = (float)D_L01_001B088C;
            maximum = lifetime * 2.5f;
            n = func_00283CF0((func_002A7878(lifetime * 0.5f, maximum) * 5.0f + 2.0f) * 0.16666667f);
            func_002BAA28(pos, vel, acc, c1, c2, ((s32)D_L01_001B0884 * 5 + 2) / 6,
                          ((s32)D_L01_001B0888 * 5 + 2) / 6, n, -1);
        }
    }
    func_002ABBB8(a0, p, 0, 4, 0, 0, -1, 0, 0, -1, 1, 0x810001,
                  D_L01_001B083C, *(float *)(p + 0x18), 4.0f, 2.0f,
                  9.0f, 1.2f, 0.0f);
}
