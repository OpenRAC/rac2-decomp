#include "include_asm.h"

#include "common.h"
extern f32 math_step_value_toward_target(void *, void *, f32, f32, f32, f32);
extern void vec_fast_normalize3(void *, void *, void *, f32);
extern void quaternion_to_rotation_basis(void *, void *);
extern f32 D_L03_001B0B78 __attribute__((sda));
extern f32 D_L03_001B0B7C __attribute__((sda));
extern f32 D_L03_001B0B80 __attribute__((sda));
extern f32 D_L03_001B36B0[] __attribute__((sda));
extern f32 D_L03_001B36C0[] __attribute__((sda));

void func_PAL_L03_003E7C78(u8 *object)
{
    f32 quaternion[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(object + 0x68);
    math_step_value_toward_target(vars + 0x4C, vars + 0x48, 1.0f,
                 D_L03_001B0B78 * 0.00040000002f,
                 D_L03_001B0B7C * 0.00040000002f,
                 D_L03_001B0B80 * 0.020000001f);
    vec_fast_normalize3(quaternion, D_L03_001B36B0, D_L03_001B36C0,
                 *(f32 *)(vars + 0x4C));
    quaternion_to_rotation_basis(quaternion, object + 0xC0);
    if (1.0f <= *(f32 *)(vars + 0x4C)) {
        *(short *)(vars + 0x56) = 1;
        qcopy(D_L03_001B36B0, D_L03_001B36C0);
    }
}
