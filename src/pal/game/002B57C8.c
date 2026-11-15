#include "include_asm.h"
#include "names.h"

extern int D_001A8A5C __attribute__((sda));
extern int D_PAL_001A8C64 __attribute__((sda));

int func_PAL_002B57C8(void) {
    return D_PAL_001A8C64;
}



extern float mat_fast_helper_a(float, float);
extern char *moby_get_controller(void *);
extern float FastAddRotations(float, float);
extern int FastDecTimer(short *);
extern int math_random_int_range(int, int);
extern int moby_step_controller(void *, void *, float);
extern int moby_step_controller(void *, void *, float);

int func_PAL_002B5BA8(char *self, float *target, float amount)
{
    char *data = moby_get_controller(self);
    float angle;
    if (data == 0)
        return 8;
    angle = mat_fast_helper_a(target[0] - *(float *)(self + 0x10),
                         target[1] - *(float *)(self + 0x14));
    angle = FastAddRotations(angle, amount);
    if (*(float *)(data + 0xDC) != 0.0f) {
        angle = FastAddRotations(angle, *(float *)(data + 0xDC));
        if (FastDecTimer((short *)(data + 0xE0))) {
            *(float *)(data + 0xDC) = -*(float *)(data + 0xDC);
            *(short *)(data + 0xE0) = math_random_int_range(*(short *)(data + 0xE2), *(short *)(data + 0xE4));
        }
    }
    return moby_step_controller(self, target, angle);
}


void func_PAL_002B5E10(char *m) {
    moby_step_controller(m, m + 0x10, *(float *)(m + 0xF8));
}

