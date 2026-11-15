#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern unsigned int moby_get_vars_word_18(unsigned int);
extern float mat_fast_helper_a(float, float);
extern int moby_start_effect_from_entry(int, float);
extern void coll_find_ground_below_object(void *, void *, float);
extern float moby_get_anim_value(char *);
extern int hero_set_control_motion_and_step(char *, void *);
extern int math_solve_quadratic(float *, float *, float, float, float);
extern int D_L07_001B1E08 __attribute__((sda));

int func_PAL_L07_00324F58(unsigned char *object, float lower, float target, float upper)
{
    float roots[2];
    char *control = (char *)moby_get_vars_word_18((unsigned int)object);
    float current;
    if (!control)
        return 0;
    *(int *)(control + 0xbc) = D_L07_001B1E08;
    if (!(*(int *)(control + 0x38) & 0x10))
        moby_start_effect_from_entry((int)object, mat_fast_helper_a(*(float *)(control + 0xa0), *(float *)(control + 0xa4)));
    coll_find_ground_below_object(object, control, 64.0f);
    current = moby_get_anim_value((char *)object);
    if (object[0x42] == object[0x43] && lower <= current && current <= upper) {
        float remaining;
        *(float *)(control + 0xa8) -= *(float *)(control + 0x2c);
        hero_set_control_motion_and_step((char *)object, control + 0xa0);
        remaining = *(float *)(control + 0xa8);
        if (remaining > 0.0f) {
            float frames = remaining / *(float *)(control + 0x2c);
            float change = target - current;
            change += change;
            change /= frames;
            *(float *)(object + 0x48) = change;
        } else if (*(float *)(object + 0x18) > *(float *)(control + 0x90)) {
            float gravity = *(float *)(control + 0x2c) * -0.5f;
            int count = math_solve_quadratic(roots, roots + 1, gravity,
                        remaining - gravity,
                        *(float *)(object + 0x18) - *(float *)(control + 0x90));
            float change;
            remaining = 5e+02f;
            if (count > 0 && roots[0] > 0.0f && roots[0] < 60.0f)
                remaining = roots[0];
            change = upper - current;
            change += change;
            change /= remaining;
            *(float *)(object + 0x48) = change;
        } else {
            *(float *)(object + 0x18) = *(float *)(control + 0x90);
            *(float *)(object + 0x48) = 1.0f;
        }
        if (*(float *)(object + 0x48) > 5.0f)
            *(float *)(object + 0x48) = 5.0f;
        else if (*(float *)(object + 0x48) < 0.0f)
            *(float *)(object + 0x48) = 0.0f;
    } else {
        *(float *)(object + 0x48) = 1.0f;
    }
    if (object[0x60] & 2) {
        Quad *motion = (Quad *)(control + 0xa0);
        *(float *)(object + 0x18) = *(float *)(control + 0x90);
        qzero(motion);
        return 1;
    }
    return 0;
}
