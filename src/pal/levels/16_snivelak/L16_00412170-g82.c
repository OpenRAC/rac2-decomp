#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct { TI128 row[4]; } SnivelakMatrix;
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern void *CreateMoby(s32);
extern float math_interpolate_between_limits(s32, s32, float, float);
extern void vec_store_transformed_entry(void *, s32, float, float, void *);
extern void moby_init_child_from_parent(void *, void *);
extern void math_approach_target_with_braking(void *, float, float, float, float);
extern u8 *func_PAL_L00_003FB330(void *, s32, s32, s32, s32, s32, s32, s32, float, float,
                          s32, s32, s32, void *);
extern u8 D_L16_001A8F20[] __attribute__((sda));
extern float D_L16_001B1648 __attribute__((sda));
extern float D_L16_001B1658 __attribute__((sda));
extern float D_L16_001B1668 __attribute__((sda));

u8 *func_PAL_L16_00412A98(u8 *owner, SnivelakMatrix *matrix)
{
    u8 *obj;
    u8 *state;
    u8 *pos;
    float scale;
    s32 n;
    TI128 *dst;
    TI128 *src;
    obj = CreateMoby(0xF4E);
    if (obj) {
        scale = math_interpolate_between_limits(0, 15, 0.125f, 0.3f);
        vec_store_transformed_entry(obj, 0, scale, 0.0f, D_L16_001A8F20);
        state = *(u8 **)(obj + 0x68);
        *(s32 *)(state + 0x68) = -1;
        moby_init_child_from_parent(obj, owner);
        pos = obj + 0x10;
        qcopy(pos, matrix->row);
        func_PAL_L00_003FB330(pos, 0, 0, 0, 0, 20, 45, 1, 2.0f, 20.0f, 1, 0, 0, 0);
        dst = (TI128 *)state;
        src = matrix->row;
        n = 3;
        do { qcopy(dst, src); src++; dst++; } while (--n >= 0);
        math_approach_target_with_braking(state + 0x50, 1.0f, 1.0f,
                      D_L16_001B1648 * 0.00040000002f,
                      D_L16_001B1658 * 0.020000001f);
        if (obj[0x43] != 1) func_PAL_002A7E68(obj, 1, 0, 1);
        *(float *)(obj + 0x2C) = *(float *)(*(u8 **)(obj + 0x24) + 0x24) * D_L16_001B1668;
    }
    return obj;
}
