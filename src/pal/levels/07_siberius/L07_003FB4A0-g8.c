#include "include_asm.h"

#include "common.h"
extern s32 func_002A9640(u8 *, s32, s32);
extern f32 func_PAL_002AA108(u8 *, s32);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern void func_002A7750(u8 *, u8, s32);
extern f32 D_L07_001B0FD0 __attribute__((sda));
typedef struct { u8 pad[0x20]; f32 angle; u8 pad24[12]; u32 flags; } SpinnerState;

void func_PAL_L07_003FB4A0(u8 *a0)
{
    SpinnerState *s1 = *(SpinnerState **)(a0 + 0x68);

    if (*(u8 *)(a0 + 0x20) == 0) {
        f32 scale;
        s1->flags = 0;
        scale = D_L07_001B0FD0;
        *(f32 *)(a0 + 0x2C) = *(f32 *)(*(u8 **)(a0 + 0x24) + 0x24) * scale;
        func_002A7750(a0, 1, -1);
        *(u32 *)(a0 + 0x98) = 0;
        *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 0x41) & 0xEFFF;
        return;
    }
    {
        s32 id = func_002A9640(a0, 0x10000, 0);
        f32 angle = func_PAL_002AA108(a0, id);
        func_002AA2E8(&s1->angle, 0.0f, angle);
    }
    if (s1->angle <= 0.0f)
        func_002A7750(a0, 3, -1);
    *(u8 *)(a0 + 0xA8) = 0xFF;
}

typedef int SibQuad __attribute__((mode(TI)));
typedef union { SibQuad quad; float value[4]; } SibVector;
extern float D_L07_001B0FE0 __attribute__((sda));
extern float D_L07_001B0FE4 __attribute__((sda));
extern void func_00282CF0(void *, void *, void *);
extern float func_002AA548(float *, float *, float, float, float, float);
extern void func_00282F20(void *, void *, float);
extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002AC9F8(float *, float);
extern void func_00282CC0(void *, void *, void *);

/* The incoming second pointer is live at the first vector subtraction. */
void func_PAL_L07_003FB570(u8 *self, float *target)
{
    SibVector offset, velocity, delta, angles, rotationInput;
    float matrix[12] __attribute__((aligned(16)));
    u8 *state;
    u8 *movement;
    u8 *position = self + 0x10;
    float rate, elapsed;
    state = *(u8 **)(self + 0x68);
    func_00282CF0(&offset, target, position);
    rate = D_L07_001B0FE0 * (0.00040000002f);
    elapsed = D_L07_001B0FE4 * (0.020000001f);
    movement = state + 0x50;
    offset.value[2] = 0.0f;
    func_002AA548((float *)(self + 0x18), (float *)(state + 0x5C), *(float *)(state + 0x60), rate, rate, elapsed);
    func_00282F20(&velocity, &offset, elapsed);
    rotationInput.quad = 0;
    rotationInput.value[2] = *(float *)(state + 0x64);
    angles.quad = rotationInput.quad;
    func_002833F0(matrix, &angles);
    func_00283098(&velocity, &velocity, matrix);
    func_00282CF0(&delta, &velocity, movement);
    func_002AC9F8(delta.value, rate);
    func_00282CC0(movement, movement, &delta);
    func_00282CC0(position, position, movement);
}
