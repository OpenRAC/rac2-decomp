/* Retained complete C reconstruction, 30 October 2026. NOT MATCHING.
 * Profile: -O2 -G8 -ffunction-sections -g -frac2-hazard-labels.
 * us: 09_dobbo: 440 bytes, expected 444; us2: 09_dobbo: 440 bytes, expected 444; pal: ABSENT.
 * The real pointer result and full integer/FP bank widths are preserved. A new typed bank-
 * interleaving and current hazard-label profile do not resolve the saved-register permutation or
 * missing pre-division nop. Older source remains privately preserved; no instruction padding was
 * inserted.
 * Reopen: Independent original argument-lifetime and division line-boundary evidence.
 * Local placement checks only; no strict linked or native-runtime claim.
 */
#include "common.h"

extern u8 *func_0029EFD0(s32);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern f32 func_00282DF0(void *);
extern s32 func_00283CF0(f32);
extern f32 func_00283CE0(s32);
extern void func_L09_003AEE10(u8 *);
extern s32 func_002E5CF8(s32, s32, u8 *);
extern void func_002A0F48(u8 *);
extern u8 D_0018A0E0[];
extern f32 D_L09_001AF89C __attribute__((sda));

u8 *func_L09_003AE8C8(void *position, f32 size, void *owner, f32 distance,
                     void *direction, f32 speed, s32 kind, f32 life, s32 flags)
{
    u8 *object = func_0029EFD0(0x5DE);
    u8 *vars;
    f32 length, countValue, inverse, scale;
    if (object != 0) {
        vars = *(u8 **)(object + 0x68);
        object[0x30] = 0xFF;
        *(u16 *)(object + 0x34) = 0x100;
        object[0x20] = 0;
        qcopy(vars + 0x30, direction);
        qcopy(object + 0x10, position);
        *(f32 *)(vars + 0x58) = distance;
        qcopy(object + 0xC0, vars + 0x30);
        func_00282DD8(object + 0xD0, object + 0xC0, D_0018A0E0);
        func_00282F20(object + 0xD0, object + 0xD0, -1.0f);
        func_00282DD8(object + 0xE0, object + 0xD0, object + 0xC0);
        length = func_00282DF0(direction);
        *(s32 *)(vars + 0x48) = func_00283CF0(*(f32 *)(vars + 0x58) / length);
        countValue = func_00283CE0(*(s32 *)(vars + 0x48));
        scale = D_L09_001AF89C;
        inverse = 1.0f / countValue;
        *(void **)(vars + 0x40) = owner;
        *(f32 *)(vars + 0x54) = size;
        *(s32 *)(vars + 0x64) = kind;
        *(s32 *)(vars + 0x68) = flags;
        *(f32 *)(vars + 0x60) = speed;
        *(f32 *)(vars + 0x4C) = inverse;
        *(f32 *)(object + 0x2C) = *(f32 *)(*(u8 **)(object + 0x24) + 0x24) * scale;
        object[0x20] = 0;
        *(f32 *)(vars + 0x50) = life;
        func_L09_003AEE10(object);
        func_002E5CF8(0, 0, object);
        func_002A0F48(object);
    }
    return object;
}
