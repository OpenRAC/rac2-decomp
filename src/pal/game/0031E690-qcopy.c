#include "include_asm.h"

typedef int Quad __attribute__((mode(TI)));
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern float func_002A7940(void);
extern void func_002AF000(float *, float, float, float);
extern float func_002A78D8(float, float);
extern void func_002C2210(float *, int, int, int, int, float *, float, float, float, int);

/* Throws `count` sparks from the position: each is a random direction and a random drift of
   the position itself, and goes out as a pair of particles, one of each sign. */
void func_PAL_0031E690(float *position, int count)
{
    float dir[4];
    float save[4];
    float f20;
    float f21;
    float f22;
    int sign;
    int i;
    float *sv;

    if (count > 0) {
        i = count;
        sv = save;
        do {
            f22 = func_002A7878(0.1f, 0.25f);
            sign = func_002A77E0(2);
            if (sign == 0)
                sign = sign - 1;
            f21 = func_002A7940();
            f20 = func_002A7878(0.349065899848938f, 1.5358898639678955f);
            func_002AF000(dir, func_002A7878(0.05f, 0.1f), f21, f20);
            *(Quad *)sv = *(Quad *)position;
            position[0] = position[0] + func_002A78D8(0.0f, 0.15f);
            position[1] = position[1] + func_002A78D8(0.0f, 0.15f);
            position[2] = position[2] + func_002A78D8(0.0f, 0.15f);
            func_002C2210(position, 0x19, 0x7F207F7F, 0, sign, dir, f22 * 0.1f, f22, 0.006f, 0);
            func_002C2210(position, 0x19, 0x7F7F7F7F, 1, -sign, dir, f22 * 0.07f, f22 * 0.7f, 0.006f, 0);
        } while (--i != 0);
    }
}
