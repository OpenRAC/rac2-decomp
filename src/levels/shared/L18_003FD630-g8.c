#include "include_asm.h"
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern s32 D_L18_001B0748 __attribute__((sda));
extern f32 D_L18_001B074C __attribute__((sda));
extern f32 D_L18_001B0750 __attribute__((sda));
extern f32 D_L18_001B0754 __attribute__((sda));
extern f32 D_L18_001B0758 __attribute__((sda));
extern f32 D_L18_001B075C __attribute__((sda));
extern f32 D_L18_001B0760 __attribute__((sda));
extern f32 D_L18_001B0764 __attribute__((sda));
extern f32 D_L18_001B0768 __attribute__((sda));
extern s32 D_L18_001B076C __attribute__((sda));
extern s32 D_L18_001B0770 __attribute__((sda));
extern void func_002ACB48(f32 *, f32);
extern void func_002A7A00(float *, float, float);
extern s32 func_002A7820(s32, s32);
extern f32 func_002A7878(f32, f32);
extern void func_L11_00397C08(void *, s32, void *, f32);
extern void func_L11_00397E68(void *, s32, s32, s32, s32, f32, f32);

/* Builds a randomized strip from two control points and two random tangents. */
/* Draws a randomly shaped glowing strip starting at the object effect point. */
void func_L18_003FD630(char *self) {
    f32 control[10][4]; /* ten strip slots; only the first four control points are set here */
    s32 count = D_L18_001B0748;
    Quad points[count];
    char *state = *(char **)(self + 0x68);
    s32 texture;
    f32 width, height;
    qcopy(control[0], (state + 0x90));
    qcopy(control[1], (state + 0x90));
    AddRandomOffsetToVector(control[1], D_L18_001B0768 * *(f32 *)(state + 0xC0));
    RandomDirectionVector(control[2], D_L18_001B0750, D_L18_001B0754);
    RandomDirectionVector(control[3], D_L18_001B0750, D_L18_001B0754);
    texture = RandomIntRange(16, 64);
    width = RandomFloatRange(D_L18_001B0758, D_L18_001B075C);
    height = RandomFloatRange(D_L18_001B0760, D_L18_001B0764);
    BuildJitteredCurvePoints_L11(points, D_L18_001B0748, control, D_L18_001B074C);
    DrawTwoLayerRibbon(points, D_L18_001B0748, texture, D_L18_001B076C, D_L18_001B0770, width, height);
}
