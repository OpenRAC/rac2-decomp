/* Retained complete C reconstruction, 30 October 2026. NOT MATCHING.
 * Profile: -O2 -G8 -ffunction-sections.
 * us: 11_joba: 892 bytes, expected 880; us2: 11_joba: 892 bytes, expected 880; pal: ABSENT.
 * Complete paired-particle burst with five full vectors. The particle helper has its real
 * pointer return and seven integer-register/three FP arguments. The random rotation constant
 * uses the exact measured encoding; countdown and branch lifetimes remain different, with an
 * extra saved GPR.
 * Reopen: Independent loop-local vector pointer lifetime witness.
 * Local placement checks only; no strict linked or native-runtime claim.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } EffectVector;
extern char D_L11_001BA8C0[];
extern float D_L11_001B0654 __attribute__((sda)),D_L11_001B0658 __attribute__((sda));
extern float D_L11_001B065C __attribute__((sda)),D_L11_001B0660 __attribute__((sda));
extern float D_L11_001B0664 __attribute__((sda)),D_L11_001B0668 __attribute__((sda)),D_L11_001B066C __attribute__((sda));
extern float func_002A7878(float,float),func_002A78D8(float,float);
extern int func_002A77E0(int),func_001163B0(void),func_00283CF0(float);
extern void func_00282CF0(void *,void *,void *),func_00282CC0(void *,void *,void *);
extern void func_00282F20(void *,void *,float),func_00282D30(void *,void *,float);
extern void func_002ACEC0(void *,void *,void *,float);
extern u8 *func_002C2210(void *,int,u32,int,int,void *,int,float,float,float);

/* Emits paired particles around a complete input position vector. */
void func_L11_003F4A58(float *position, int count)
{
    EffectVector velocity, point, delta, up, toward;
    int sign;
    u8 *particle;
    float size, speed;
    int remaining;
    up.q = 0;
    up.f[2] = 1.0f;
    func_00282CF0(delta.f, D_L11_001BA8C0, position);
    delta.f[2] = 0.0f;
    if (count <= 0) return;
    remaining = count;
    do {
        size = func_002A7878(D_L11_001B0668, D_L11_001B066C);
        sign = func_002A77E0(2);
        if (sign == 0) sign--;
        func_002ACEC0(velocity.f, delta.f, up.f, func_002A7878(-1.047197699546814f, 1.047197699546814f));
        speed = func_002A7878(D_L11_001B0654, D_L11_001B0658) * 0.016666668f;
        func_00282F20(velocity.f, velocity.f, speed);
        velocity.f[2] = func_002A7878(D_L11_001B065C, D_L11_001B0660) * 0.016666668f;
        qcopy(point.f, position);
        point.f[0] += func_002A78D8(0.0f, 0.15f);
        point.f[1] += func_002A78D8(0.0f, 0.15f);
        point.f[2] += func_002A78D8(0.0f, 0.15f);
        if (!(func_001163B0() & 1)) {
            func_00282D30(velocity.f, velocity.f, 1.5f);
            particle = func_002C2210(point.f, 60, 0x7F800000, 0, sign,
                                     velocity.f, 0, size * 0.35f, size, D_L11_001B0664);
            if (particle) particle[9] = func_00283CF0(4.0f) + 112;
            particle = func_002C2210(point.f, 60, 0x7F7F7F7F, 1, -sign,
                                     velocity.f, 0, size * 0.245f, size * 0.7f, D_L11_001B0664);
        } else {
            func_00282CF0(toward.f, D_L11_001BA8C0, position);
            func_00282F20(toward.f, toward.f, speed);
            func_00282CC0(velocity.f, velocity.f, toward.f);
            particle = func_002C2210(point.f, 40, 0x7F800000, 0, sign,
                                     velocity.f, 0, size * 2.05f, size, D_L11_001B0664);
            if (particle) particle[9] = func_00283CF0(4.0f) + 112;
            particle = func_002C2210(point.f, 40, 0x7F7F7F7F, 1, -sign,
                                     velocity.f, 0, size * 1.435f, size * 0.7f, D_L11_001B0664);
        }
        if (particle) particle[9] = func_00283CF0(4.0f) + 112;
    } while (--remaining);
}
