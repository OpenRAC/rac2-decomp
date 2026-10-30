/* Complete C near miss; not linked and no matching credit.
 * 2026-10-30: game -O2 -G8 -ffunction-sections -frac2-zero-ti-por -g.
 * us: 0/4; us2: 0/4; pal: absent.
 * 780/772 bytes; frame 0xC0. Five full aligned vectors, real owner formal, three FP and seven
 * integer-bank particle arguments, random spin and actual pointer returns are retained. Constant
 * roles, outgoing arguments and loop allocation differ.
 * Reopen: Independent particle-vector/constant lifetime witness.
 */
#include "common.h"

typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
extern float D_L05_001B105C[] SDATA(D_L05_001B105C);
extern char D_L05_001B96C0[];
extern char D_L05_001FF240[];
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern void func_002ACEC0(void *, void *, void *, float);
extern u8 *func_002C2210(void *, int, u32, int, int, void *, int,
                       float, float, float);

void func_L05_00419F10(float *position, int count, u32 color, char *owner)
{
    Vector velocity, endpoint, direction, axis, normalized;
    int n;
    axis.q = 0;
    axis.f[3] = 1.0f;
    axis.f[2] = 1.0f;
    if (*(int *)(*(char **)(owner + 0x68) + 0x30) != 0) {
        D_L05_001B105C[0] = 0.1f;
        D_L05_001B105C[1] = 6.0f;
        D_L05_001B105C[2] = 2.0f;
        D_L05_001B105C[3] = 10.0f;
    }
    func_00282CF0(&direction, D_L05_001B96C0, position);
    func_00282F20(&normalized, &direction, 0.5f);
    direction.f[2] = 0.0f;
    if (count > 0) {
        n = count;
        do {
            float size = func_002A7878(D_L05_001B105C[5], D_L05_001B105C[6]);
            int spin = func_002A77E0(2);
            u8 *particle;
            if (spin == 0)
                spin--;
            func_002ACEC0(&velocity, &direction, &axis,
                          func_002A7878(-1.0471977f, 1.0471977f));
            func_00282F20(&velocity, &velocity,
                          func_002A7878(D_L05_001B105C[0], D_L05_001B105C[1]) * 0.016666668f);
            velocity.f[2] = func_002A7878(D_L05_001B105C[2], D_L05_001B105C[3]) * 0.016666668f;
            func_00282CC0(&endpoint, position, &normalized);
            position[0] += func_002A78D8(0.0f, 0.15f);
            position[1] += func_002A78D8(0.0f, 0.15f);
            position[2] += func_002A78D8(0.0f, 0.15f);
            particle = func_002C2210(position, 60, color, 0, spin, &velocity, 0,
                                    size * 0.1f, size, D_L05_001B105C[4]);
            if (particle != 0) {
                particle[2] = (*(u8 **)(D_L05_001FF240 + 0x184))[6];
                particle[9] = func_00283CF0(4.0f) + 0x70;
            }
            particle = func_002C2210(position, 60, 0x7F7F7F7F, 1, -spin, &velocity, 0,
                                    size * 0.07f, size * 0.7f, D_L05_001B105C[4]);
            if (particle != 0) {
                particle[2] = (*(u8 **)(D_L05_001FF240 + 0x184))[6];
                particle[9] = func_00283CF0(4.0f) + 0x70;
            }
        } while (--n != 0);
    }
}
