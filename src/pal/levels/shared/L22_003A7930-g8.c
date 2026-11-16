#include "include_asm.h"
#include "names.h"

extern float g_orbit_param_a __attribute__((sda));
extern float g_orbit_param_b __attribute__((sda));
extern float g_orbit_param_c __attribute__((sda));
extern float g_orbit_param_d __attribute__((sda));
extern float g_orbit_param_e __attribute__((sda));
extern float g_orbit_param_f __attribute__((sda));
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
                p0 = g_orbit_param_c * 0.00040000002f;
                p1 = g_orbit_param_d * 0.020000001f;
                p2 = g_orbit_param_e * 6.981318e-06f;
                p3 = g_orbit_param_f * 0.0003490659f;
                ref_L22_003A45F0_00(obj, p0, p1, p2, p3);
                *(float *)(obj + 0x48) = 1.5f;
                *(float *)(sub + 0x138) = 0.6f;
            } else {
                p0 = g_orbit_param_a * 0.00040000002f;
                p1 = g_orbit_param_b * 0.020000001f;
                p2 = g_orbit_param_e * 6.981318e-06f;
                p3 = g_orbit_param_f * 0.0003490659f;
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
