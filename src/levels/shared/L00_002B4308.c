#include "common.h"
/* Projects the horizontal velocity onto a copied direction before reducing its Z component. */
extern float vec_length_xy(char *);
extern float mat_fast_helper_a(float, float);
extern void FastVecScale(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern void func_001290E0(int *, int *);
extern unsigned char D_00189E20_1[];

/* When the hero runs into a wall, takes away the part of the hero speed that goes into it and slows the hero down a little. */
void hero_cancel_velocity_into_wall(void)
{
    char *hero = (char *)D_00189E20_1;
    float distance;
    float angle;
    float pushAmount;
    float vector[4] __attribute__((aligned(16)));

    if (*(short *)(hero + 0x34E) == 0)
        return;
    if (!(*(float *)(hero + 0x31C) < 0.15f))
        return;
    if (!(0.0f < *(float *)(hero + 0x118)))
        return;
    if (*(unsigned char *)(hero + 0x287) == 0)
        return;
    if (!(0.0f < *(float *)(hero + 0x238)))
        return;
    distance = vec_length_xy(hero + 0x230);
    angle = mat_fast_helper_a(*(float *)(hero + 0x238), distance);
    if (!(angle >= 0.8726646900177002f))
        return;
    qcopy(vector, hero + 0x230);
    vector[2] = 0.0f;
    func_001290E0((int *)vector, (int *)vector);
    pushAmount = -*(float *)(hero + 0xF0) * vector[0] - *(float *)(hero + 0xF4) * vector[1];
    if (pushAmount > 0.0f) {
        FastVecScale((char *)vector, (char *)vector, pushAmount);
        FastVecAdd(hero + 0xF0, hero + 0xF0, (char *)vector);
        *(float *)(hero + 0xF8) -= 0.030000001192092896f;
    }
}
