#include "include_asm.h"
#include "names.h"

extern void object_set_first_float4(char *p, float x, float y, float zero, float zero2);
extern float D_L04_001AE1E0 __attribute__((sda));
extern float D_L04_001AE1E8 __attribute__((sda));
extern float D_L04_001AE1F0 __attribute__((sda));
extern float D_L04_001AE1F8 __attribute__((sda));
extern float D_L04_001AE1E4;
extern float D_L04_001AE1EC;
extern float D_L04_001AE1F4;
extern float D_L04_001AE1FC;
struct pos {
    float x;
    float y;
};

void func_US2_0033FCE8(char *self)
{
    float zero = 0.0f;

    object_set_first_float4(self + 1400, D_L04_001AE1F8 + (*(struct pos **)(self + 728))->x,
            D_L04_001AE1FC + (*(struct pos **)(self + 728))->y, zero, zero);
    object_set_first_float4(self + 1136, D_L04_001AE1E0 + (*(struct pos **)(self + 728))->x,
            D_L04_001AE1E4 + (*(struct pos **)(self + 728))->y, zero, zero);
    object_set_first_float4(self + 1224, D_L04_001AE1E8 + (*(struct pos **)(self + 728))->x,
            D_L04_001AE1EC + (*(struct pos **)(self + 728))->y, zero, zero);
    object_set_first_float4(self + 1312, D_L04_001AE1F0 + (*(struct pos **)(self + 728))->x,
            D_L04_001AE1F4 + (*(struct pos **)(self + 728))->y, zero, zero);
}
