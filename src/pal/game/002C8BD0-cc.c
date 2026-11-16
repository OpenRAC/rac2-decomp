#include "names.h"
/* func_PAL_002C8BD0, the PAL copy of func_002C7E28: the same C, where scale lifetime / 2; wrap particle (((int)({e}) * 5 + 2) / 6); rewrap func_002A77E0(255); rewrap lifetime. */
typedef int Quadword __attribute__((mode(TI)));
extern unsigned char *part_alloc(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern unsigned char *g_part_tex_spinning_spark;

unsigned char *func_PAL_002C8BD0(Quadword *position, Quadword *velocity, int lifetime) {
    unsigned char *particle = part_alloc(0x63);
    unsigned char *motion;
    if (particle) {
        motion = particle + 0x20;
        particle[9] = FloatToInt(2.0f) + 0x40;
        particle[3] = 0x44;
        particle[1] = 0;
        particle[2] = *g_part_tex_spinning_spark;
        *(float *)(particle + 0xC) = math_random_float_range(0.05f, 0.2f) * 210000.0f;
        particle[8] = math_random_int_below(255);
        *(short *)(particle + 0xA) = (((int)(lifetime) * 5 + 2) / 6);
        *(Quadword *)(particle + 0x10) = *position;
        *(Quadword *)motion = *velocity;
        *(float *)(motion + 0xC) = math_random_float_range(0.6f, 2.6f) * 0.00040000002f;
        *(float *)(motion + 0x18) = *(float *)(particle + 0xC) * 2.0f;
        *(short *)(motion + 0x16) = math_random_int_range(0, 3);
        *(short *)(motion + 0x14) = (((int)(lifetime / 2) * 5 + 2) / 6);
        *(float *)(motion + 0x1C) = math_random_angle();
    }
    return particle;
}
