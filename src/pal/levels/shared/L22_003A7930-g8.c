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
void orbit_update_pal(char *moby, int new_state, int state_arg1, int state_arg2, int flags, float default_scale) {
    char *obj = moby;
    char *vars = *(char **)(moby + 0x68);
    char *child;
    float scale;
    float p0;
    float p1;
    float p2;
    float p3;
    float value_a;
    float value_b;

    if (flags & 1) {
        if (*(short *)(vars + 0x34E) == 0) {
            *(int *)(vars + 0x3EC) = *(unsigned char *)(obj + 0x43);
            if (new_state == 11) {
                p0 = g_orbit_param_c * 0.00040000002f;
                p1 = g_orbit_param_d * 0.020000001f;
                p2 = g_orbit_param_e * 6.981318e-06f;
                p3 = g_orbit_param_f * 0.0003490659f;
                ref_L22_003A45F0_00(obj, p0, p1, p2, p3);
                *(float *)(obj + 0x48) = 1.5f;
                *(float *)(vars + 0x138) = 0.6f;
            } else {
                p0 = g_orbit_param_a * 0.00040000002f;
                p1 = g_orbit_param_b * 0.020000001f;
                p2 = g_orbit_param_e * 6.981318e-06f;
                p3 = g_orbit_param_f * 0.0003490659f;
                ref_L22_003A45F0_00(obj, p0, p1, p2, p3);
                *(float *)(obj + 0x48) = 1.3f;
                *(float *)(vars + 0x138) = 0.40000004f;
            }

            value_a = *(float *)(vars + 0x128);
            value_b = *(float *)(vars + 0x134);
            value_a = value_a + value_a;
            value_b = value_b * 8.0f;
            *(float *)(vars + 0x128) = value_a;
            *(float *)(vars + 0x134) = value_b;
            if (*(unsigned char *)(obj + 0x43) != new_state) {
                ref_L22_003A45F0_01(obj, new_state, state_arg1, state_arg2);
            }
        }
    }
    if (*(short *)(vars + 0x34C) != 0) {
        return;
    }
    if (*(unsigned char *)(obj + 0x43) < 11 || *(unsigned char *)(obj + 0x43) > 12) {
        *(float *)(obj + 0x48) = default_scale;
    }
    scale = *(float *)(obj + 0x48);
    *(float *)(*(char **)(vars + 0x440) + 0x48) = scale;
    if (flags & 2) {
        child = *(char **)(vars + 0x440);
        if (child != 0) {
            ref_L22_003A45F0_01(child, new_state, state_arg1, state_arg2);
        }
    }
}
