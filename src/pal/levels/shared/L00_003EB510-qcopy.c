#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern char *CreateMoby(int size);
extern float math_random_float_range(float lo, float hi);
extern int part_alloc_effect_slot(char *object, int a, float b, float c, float d);
extern void func_002A0F48(char *object);

/* Creates a Mini Nuke projectile at the given place and speed, with a random spin. */
char *mini_nuke_projectile_spawn_pal(int shooter, TI128 *position, TI128 *velocity)
{
    char *projectile;
    char *vars;
    float spin;
    float lo;
    float hi;

    projectile = CreateMoby(0xC07);
    if (projectile != 0) {
        short v = 0xFF;

        vars = *(char **)(projectile + 0x68);
        *(short *)(projectile + 0x32) = v;
        *(char *)(projectile + 0x30) = v;
        *(char *)(projectile + 0x20) = 0;
        *(TI128 *)(projectile + 0x10) = *position;
        *(TI128 *)vars = *velocity;
        *(float *)(projectile + 0x2C) = 0.01f;
        lo = 0.062831864f;
        hi = 0.12566373f;
        spin = math_random_float_range(lo, hi);
        *(float *)(vars + 0x10) = spin;
        spin = math_random_float_range(lo, hi);
        *(float *)(vars + 0x14) = spin;
        *(int *)(vars + 0x30) = shooter;
        *(int *)(vars + 0x18) = 0;
        *(int *)(vars + 0x34) = part_alloc_effect_slot(projectile, 0, 1.0f, 1.0f, 1.0f);
        func_002A0F48(projectile);
    }
    return projectile;
}
