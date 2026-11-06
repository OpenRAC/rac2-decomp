#include "include_asm.h"
#include "common.h"

/* func_PAL_L00_003EEF94, the PAL copy of func_L00_003EACC0: the same C, where the frame counts
 * scale to 50 Hz (20 becomes 17, 300 becomes 250, and both func_002A7820 draws take
 * ((s32)(x) * 5 + 2) / 6) and the speed 0.41666669f becomes 0.50000006f. */

extern int func_00282948(int *);
extern int func_002A7820(int, int);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
/* EE integer and floating-point argument banks retain their independent order. */
extern void func_L00_00338E90(void *, void *, int, float, int, int);

void func_PAL_L00_003EEF94(unsigned char *p) {
    float v[4], pos[4];
    float radius, secondRadius, z;
    int *s = *(int **)(p + 0x68);
    unsigned char *base;

    if (p[0x20] == 0) {
        p[0x30] = 0x80;
        p[0x20] = 1;
        s[1] = 17;
        s[0] = 0;
    }
    if (p[0x20] == 1) {
        if (func_00282948(s)) {
            p[0x20] = 2;
            s[0] = ((s32)func_002A7820(50, 120) * 5 + 2) / 6;
        }
    }
    if (p[0x20] == 2) {
        if (func_00282948(s + 1)) {
            p[0x20] = 1;
            s[1] = ((s32)func_002A7820(10, 25) * 5 + 2) / 6;
        } else {
            v[0] = func_00283180(*(float *)(p + 0xf8) - 1.570796489715576171875f)
                   * 0.50000006f;
            v[1] = func_00283198(*(float *)(p + 0xf8) - 1.570796489715576171875f)
                   * 0.50000006f;
            v[2] = 0.0f;
            base = p + 0x10;
            qcopy(pos, base);
            z = v[2];
            pos[2] += func_002A78D8(z, 0.5f);
            radius = func_002A7878(0.1f, 3.0f);
            func_L00_00338E90(pos, v, 250, radius,
                             func_00283CF0(func_002A78D8(1.0f, 4.0f)), 0x40808080);
            qcopy(pos, base);
            pos[2] += func_002A78D8(z, 0.5f);
            secondRadius = func_002A7878(0.1f, 3.0f);
            func_L00_00338E90(pos, v, 250, secondRadius,
                             func_00283CF0(func_002A78D8(1.0f, 4.0f)), 0x40808080);
        }
    }
}
