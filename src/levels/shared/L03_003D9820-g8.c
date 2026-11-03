#include "common.h"

typedef struct {
    f32 velocity[4];
    s16 timer;
    s16 count;
    u8 *owner;
    s32 value;
} SpawnVars;

extern u8 *func_0029EFD0(s32);
extern void func_002B37E8(u8 *, u8 *);
extern f32 func_00283248(f32, f32);
extern f32 func_00282E20(void *);
extern f32 D_L03_001B08D8 __attribute__((sda));

u8 *func_L03_003D9820(u8 *owner, void *position, f32 *velocity, s32 value)
{
    u8 *object = func_0029EFD0(0xA72);
    SpawnVars *vars;
    if (object != 0) {
        vars = *(SpawnVars **)(object + 0x68);
        func_002B37E8(object, owner);
        qcopy(object + 0x10, position);
        *(f32 *)(object + 0xF8) = func_00283248(velocity[0], velocity[1]);
        *(f32 *)(object + 0xF4) = -func_00283248(func_00282E20(velocity), velocity[2]);
        qcopy(vars, velocity);
        vars->value = value;
        vars->timer = 0x5A;
        vars->owner = owner;
        vars->count = 0;
        *(f32 *)(object + 0x2C) = *(f32 *)(*(u8 **)(object + 0x24) + 0x24) * D_L03_001B08D8;
    }
    return object;
}
