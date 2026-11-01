#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
typedef float f32;
extern u8 *D_L03_001B2A1C __attribute__((sda));
extern s32 D_L03_001B108C __attribute__((sda));
extern u32 D_L03_001B1058 __attribute__((sda));
extern u8 *func_002BDCE8(void *p, float f0, float f1, float f2, int z, void *local,
                         float f3, int v, int t);
extern f32 D_L03_001B1C00 __attribute__((sda));
extern f32 D_L03_001B1C04 __attribute__((sda));
extern void func_002AB650(u8 *a0);
extern s32 func_002B38B8();
extern void func_L00_003294F0(unsigned char *entity, int enabled);
extern u8 *D_L03_001FB5A0[];
extern s32 D_L03_001A8F00 __attribute__((sda));
extern s32 func_3240F0(u8 *a0);

/* Sets the entity up for a shot: the state's own counter, its two blend rates and the
 * frame the shot was prepared on. */
s32 func_PAL_L03_004244D8(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    f32 f0;
    f32 f1;
    s32 v0;

    if (*(s32 *)(state + 0x284) == -1) return 0;
    if (entity[0x20] != 9) return 0;

    if (func_002B38B8() == 0) {
        entity[0xA8] = 0xFF;
        f1 = D_L03_001B1C00 * 0.00040000002f;
        f0 = D_L03_001B1C04 * 0.020000001f;
        v0 = *(s16 *)(state + 0x24);
        *(u16 *)(state + 0x98) = 0;
        *(f32 *)(state + 0x138) = f0;
        *(f32 *)(state + 0x33C) = 6.0f;
        *(f32 *)(state + 0x134) = f1;
        *(f32 *)(state + 0x130) = f1;
        *(f32 *)(state + 0x20) = (f32)v0;
        entity[0xA8] = 0xFF;
        *(u32 *)(entity + 0x98) = *(u32 *)(*(u8 **)(entity + 0x24) + 0x10);
        func_002AB650(entity);
        func_L00_003294F0(entity, 1);
        return 1;
    }
    return 0;
}
