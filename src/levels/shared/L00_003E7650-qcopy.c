#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

extern char *func_0029EFD0(int size);

extern float func_002A7878(float lo, float hi);

extern int func_002FED90(char *object, int a, float b, float c, float d);

extern void func_002A0F48(char *object);

/* Creates a Mini Nuke projectile at the given place and speed, with a random spin. */
char *func_L00_003E7650(int shooter, TI128 *position, TI128 *velocity)
{
    char *moby;
    char *vars;
    float spinSpeed;
    float lo;
    float hi;

    moby = CreateMoby(0xC07 /* Mini Nuke Projectile */);
    if (moby != 0) {
        short alphaValue = 0xFF;

        vars = *(char **)(moby + 0x68);
        *(short *)(moby + 0x32) = alphaValue;
        *(char *)(moby + 0x30) = alphaValue;
        *(char *)(moby + 0x20) = 0;
        *(TI128 *)(moby + 0x10) = *position;
        *(TI128 *)vars = *velocity;
        *(float *)(moby + 0x2C) = 0.01f;
        lo = 0.052359886f;
        hi = 0.10471977f;
        spinSpeed = RandomFloatRange(lo, hi);
        *(float *)(vars + 0x10) = spinSpeed;
        spinSpeed = RandomFloatRange(lo, hi);
        *(float *)(vars + 0x14) = spinSpeed;
        *(int *)(vars + 0x30) = shooter;
        *(int *)(vars + 0x18) = 0;
        *(int *)(vars + 0x34) = AllocEffectSlot_002FED90(moby, 0, 1.0f, 1.0f, 1.0f);
        func_002A0F48(moby);
    }
    return moby;
}
