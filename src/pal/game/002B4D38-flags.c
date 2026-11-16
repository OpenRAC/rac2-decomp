#include "include_asm.h"
#include "names.h"

extern void FastVecAdd(void *, void *, void *);
typedef int TI16_2B41A8 __attribute__((mode(TI)));
typedef struct { float x, y, z; } Vec3_2B41A8;
extern const Vec3_2B41A8 g_controller_param_vec_a, g_controller_param_vec_b, g_controller_param_vec_c, g_controller_param_vec_d, g_controller_param_vec_e, g_controller_param_vec_f;
extern float math_random_angle(void);
extern void matrix_mul_vec3(void *, void *, void *);

/* Fills in a movement controller block, using the given values or built-in defaults for each setting (PAL). */
void moby_init_controller_params_pal(char *moby, char *controller, char *origin, char *rotation, float *setting_4, float *setting_5, float *setting_6, float *setting_7,
                   float *setting_8, float *setting_9, float *setting_10)
{
    Vec3_2B41A8 v0, v1, v2, v3, v4, v5, v6;
    float *src_a, *src_b, *src_c, *src_d, *src_e, *src_f, *src_g;
    float *out_0, *out_1, *out_2, *out_3, *out_4, *out_5, *out_6, *out_7;
    int i;
    v0 = g_controller_param_vec_a;
    v1 = g_controller_param_vec_b;
    v2 = g_controller_param_vec_c;
    v3 = g_controller_param_vec_d;
    v4 = g_controller_param_vec_e;
    v5 = g_controller_param_vec_d;
    *(unsigned short *)(moby + 0x34) |= 0x100;
    v6 = g_controller_param_vec_f;
    if (origin != 0) {
        matrix_mul_vec3(controller, origin, moby + 0xC0);
        FastVecAdd(controller, controller, moby + 0x10);
        *(TI16_2B41A8 *)(controller + 0x10) = *(TI16_2B41A8 *)origin;
    } else {
        *(TI16_2B41A8 *)controller = *(TI16_2B41A8 *)(moby + 0x10);
    }
    if (rotation != 0) {
        *(TI16_2B41A8 *)(controller + 0x20) = *(TI16_2B41A8 *)rotation;
    } else {
        *(TI16_2B41A8 *)(controller + 0x20) = *(TI16_2B41A8 *)(moby + 0xF0);
    }
    src_f = (float *)&v5;
    src_g = (float *)&v6;
    src_d = (float *)&v3;
    src_e = (float *)&v4;
    src_b = (float *)&v1;
    src_a = (float *)&v0;
    src_c = (float *)&v2;
    if (setting_5) src_g = setting_5;
    if (setting_4) src_f = setting_4;
    if (setting_8) src_c = setting_8;
    if (setting_7) src_b = setting_7;
    if (setting_9) src_e = setting_9;
    if (setting_6) src_a = setting_6;
    if (setting_10) src_d = setting_10;
    out_7 = (float *)(controller + 0x90);
    out_6 = (float *)(controller + 0x9C);
    out_5 = (float *)(controller + 0x84);
    out_4 = (float *)(controller + 0x6C);
    out_3 = (float *)(controller + 0x54);
    out_2 = (float *)(controller + 0x60);
    out_1 = (float *)(controller + 0x48);
    out_0 = (float *)(controller + 0x78);
    for (i = 0; i < 3; i++) {
        *out_0++ = *src_d++;
        *out_1++ = *src_a++;
        *out_2++ = *src_e++;
        *out_3++ = *src_b++;
        *out_4++ = *src_c++;
        *out_5++ = math_random_angle();
        *out_6++ = *src_f++;
        *out_7++ = *src_g++ * 0.0003490659f;
    }
}
