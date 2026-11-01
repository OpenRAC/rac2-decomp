#include "include_asm.h"

extern float D_L22_001AF3C8 __attribute__((sda));
extern float D_L22_001AF3CC __attribute__((sda));
extern float D_L22_001AF3D0 __attribute__((sda));
extern float D_L22_001AF3D4 __attribute__((sda));
extern float D_L22_001AF3D8 __attribute__((sda));
extern float D_L22_001AF3DC __attribute__((sda));
extern void ref_L22_003A45F0_00(void *, float, float, float, float);
extern void ref_L22_003A45F0_01(void *, int, int, int);

               /* func_002A7470 */

/* One turn of the orbit: the first flag bit runs the object's own update, the
 * second one hands the result over to the child object. */
void func_PAL_L22_003A7930(char *a0, int a1, int a2, int a3, int a4, float a5) {
    char *obj = a0;
    char *sub = *(char **)(a0 + 0x68);
    char *child;
    float f;
    float p0;
    float p1;
    float p2;
    float p3;
    float g0;
    float g1;

    if (a4 & 1) {
        if (*(short *)(sub + 0x34E) == 0) {
            *(int *)(sub + 0x3EC) = *(unsigned char *)(obj + 0x43);
            if (a1 == 11) {
                p0 = D_L22_001AF3D0 * 0.00040000002f;
                p1 = D_L22_001AF3D4 * 0.020000001f;
                p2 = D_L22_001AF3D8 * 6.981318e-06f;
                p3 = D_L22_001AF3DC * 0.0003490659f;
                ref_L22_003A45F0_00(obj, p0, p1, p2, p3);
                *(float *)(obj + 0x48) = 1.5f;
                *(float *)(sub + 0x138) = 0.6f;
            } else {
                p0 = D_L22_001AF3C8 * 0.00040000002f;
                p1 = D_L22_001AF3CC * 0.020000001f;
                p2 = D_L22_001AF3D8 * 6.981318e-06f;
                p3 = D_L22_001AF3DC * 0.0003490659f;
                ref_L22_003A45F0_00(obj, p0, p1, p2, p3);
                *(float *)(obj + 0x48) = 1.3f;
                *(float *)(sub + 0x138) = 0.40000004f;
            }

            g0 = *(float *)(sub + 0x128);
            g1 = *(float *)(sub + 0x134);
            g0 = g0 + g0;
            g1 = g1 * 8.0f;
            *(float *)(sub + 0x128) = g0;
            *(float *)(sub + 0x134) = g1;
            if (*(unsigned char *)(obj + 0x43) != a1) {
                ref_L22_003A45F0_01(obj, a1, a2, a3);
            }
        }
    }
    if (*(short *)(sub + 0x34C) != 0) {
        return;
    }
    if (*(unsigned char *)(obj + 0x43) < 11 || *(unsigned char *)(obj + 0x43) > 12) {
        *(float *)(obj + 0x48) = a5;
    }
    f = *(float *)(obj + 0x48);
    *(float *)(*(char **)(sub + 0x440) + 0x48) = f;
    if (a4 & 2) {
        child = *(char **)(sub + 0x440);
        if (child != 0) {
            ref_L22_003A45F0_01(child, a1, a2, a3);
        }
    }
}
