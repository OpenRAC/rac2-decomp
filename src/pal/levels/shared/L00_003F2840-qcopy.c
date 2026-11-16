#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern float math_random_float_range(float,float);
extern int part_alloc_effect_slot(char *,int,float,float,float);
extern void func_002A0F48(char *);

char *gravity_bomb_spawn_projectile_pal(int owner, char *position, char *direction)
{
    char *object = CreateMoby(0xCE4);
    char *state;
    float first,second;
    unsigned char stamp;
    if (object != 0) {
        state = *(char **)(object + 0x68);
        stamp = 0xff;
        *(short *)(object + 0x32) = stamp;
        object[0x30] = stamp;
        object[0x20] = 0;
        *(TI128 *)(object + 0x10) = *(TI128 *)position;
        *(TI128 *)state = *(TI128 *)direction;
        *(float *)(object + 0x2c) = 0.01f;
        first = math_random_float_range(0.062831864f,0.12566373f);
        *(float *)(state + 0x10) = first;
        second = math_random_float_range(0.062831864f,0.12566373f);
        *(int *)(state + 0x30) = owner;
        *(int *)(state + 0x18) = 0;
        *(float *)(state + 0x14) = second;
        *(int *)(state + 0x34) = part_alloc_effect_slot(object,0,1.0f,1.0f,1.0f);
        func_002A0F48(object);
    }
    return object;
}
