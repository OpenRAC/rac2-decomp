/* func_L07_00323038 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections -g). */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern unsigned int func_L00_0032C638(unsigned int);
extern float func_00283248(float, float);
extern int func_L01_00322288(int, float);
extern void func_002B5BC0(void *, void *, float);
extern float func_0029F530(char *);
extern int func_L07_00321D68(char *, void *);
extern int func_002A88A0(float *, float *, float, float, float);
extern int D_L07_001B1E08 __attribute__((sda));

/* Tunes the speed of an object's jump so it lands at the right place. Returns 1 once the jump has ended. */
int func_L07_00323038(unsigned char *object, float lower, float target, float upper)
{
    float roots[2];
    char *control = (char *)GetObjectVarsWord18((unsigned int)object);
    float current;
    if (!control)
        return 0;
    *(int *)(control + 0xbc) = D_L07_001B1E08;
    if (!(*(int *)(control + 0x38) & 0x10))
        StartMobyEffectFromEntry((int)object, FastMatrixHelperA(*(float *)(control + 0xa0), *(float *)(control + 0xa4)));
    FindGroundBelowObject(object, control, 64.0f);
    current = GetMobyAnimationValue((char *)object);
    if (object[0x42] == object[0x43] && lower <= current && current <= upper) {
        float remaining;
        *(float *)(control + 0xa8) -= *(float *)(control + 0x2c);
        SetControlMotionAndStep((char *)object, control + 0xa0);
        remaining = *(float *)(control + 0xa8);
        if (remaining > 0.0f) {
            float frames = remaining / *(float *)(control + 0x2c);
            float change = target - current;
            change += change;
            change /= frames;
            *(float *)(object + 0x48) = change;
        } else if (*(float *)(object + 0x18) > *(float *)(control + 0x90)) {
            float gravity = *(float *)(control + 0x2c) * -0.5f;
            int count = SolveQuadratic(roots, roots + 1, gravity,
                        remaining - gravity,
                        *(float *)(object + 0x18) - *(float *)(control + 0x90));
            float change;
            remaining = 600.0f;
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
