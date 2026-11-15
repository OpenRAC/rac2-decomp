#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

typedef unsigned int u32;

typedef int s32;

typedef int TI128 __attribute__((mode(TI)));

extern float D_L22_001B11EC __attribute__((sda));

extern u32 D_L22_001B11C8 __attribute__((sda));

extern u32 D_L22_001B11CC __attribute__((sda));

extern u32 D_L22_001B11D0 __attribute__((sda));

extern u32 D_L22_001B11D4 __attribute__((sda));

extern s32 D_L22_001B11D8 __attribute__((sda));

extern u32 D_L22_001B11DC __attribute__((sda));

extern s32 D_L22_001B11E0 __attribute__((sda));

extern u32 D_L22_001B11E4 __attribute__((sda));

extern s32 D_L22_001B11E8 __attribute__((sda));

extern float func_002F3BC8(void *);

extern float func_0031FDE8(void);

extern void func_002F2BB8(void *, s32, u32, s32, float, float, float);

extern void func_002F2990(void *, void *, s32, u32, s32, s32, float, float, float);

/* scrolls the effect's phase, spawns three particles around it, and once the phase passes the
   limit emits three more through the shared emitter with the local direction {0, 0, 0, 1} */
void part_update_scrolling_effect(u8 *obj) {
    float direction[4];
    u8 *vars = *(u8 **)(obj + 0x68);
    float phase;
    float phaseStep;
    float size;

    *(TI128 *)direction = 0;
    direction[3] = 1.0f;
    phase = *(float *)(vars + 0x14) - 0.1f;
    *(float *)(vars + 0x14) = phase;
    if (phase <= -8.0f) {
        *(float *)(vars + 0x14) = phase + 8.0f;
    }
    phaseStep = func_002F3BC8(vars);
    size = D_L22_001B11EC * 0.2f;
    *(float *)(vars + 0x18) = *(float *)(vars + 0x18) + phaseStep;
    func_002F2BB8(obj + 0x10, 0x31, D_L22_001B11C8, 1, size, 0.0f, func_0031FDE8());
    func_002F2BB8(obj + 0x10, 0x31, D_L22_001B11CC, 1, D_L22_001B11EC * 0.1f, 0.0f, func_0031FDE8());
    func_002F2BB8(obj + 0x10, 0x2F, D_L22_001B11D0, 1, D_L22_001B11EC * 0.05f, 0.0f, func_0031FDE8());
    if (*(float *)(vars + 0x18) > 1.0f) {
        func_002F2990(obj, direction, 1, D_L22_001B11D4, D_L22_001B11D8, 0x17, D_L22_001B11EC * 0.02f,
                          D_L22_001B11EC * 0.4f, *(float *)(vars + 0x14));
        func_002F2990(obj, direction, 1, D_L22_001B11DC, D_L22_001B11E0, 0x17, D_L22_001B11EC * 0.07f,
                          D_L22_001B11EC * 0.4f, *(float *)(vars + 0x14));
        func_002F2990(obj, direction, 1, D_L22_001B11E4, D_L22_001B11E8, 0x17, D_L22_001B11EC * 0.07f,
                          D_L22_001B11EC * 0.4f, *(float *)(vars + 0x14));
    }
}
