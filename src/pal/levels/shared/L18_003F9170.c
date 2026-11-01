#include "include_asm.h"

#include "common.h"
extern s32 func_00283CF0(float);
extern void *func_002B60B0(u8 *, float, float, float, float);
extern void func_002A7750(u8 *, s32, s32);
extern void func_L18_003F7590(u8 *);
extern s32 func_L18_0032B768(u8 *, s32, s32);
extern u8 *D_L18_001B281C MACRO_ADDR;
typedef struct {
    u8 reserved00[0x20];
    float animation;
    s16 mode;
    u8 reserved26[2];
    u8 kind, ready;
    u8 reserved2A[6];
    float blend;
    u8 reserved34[0x14];
    u8 duration;
    u8 reserved49;
    u8 speed;
    u8 reserved4B[0x15];
    u8 type;
    u8 reserved61[0x1F];
    float strength, secondary;
    u8 reserved88[4];
    float decay;
    u8 reserved90[8];
    s32 count;
    u8 reserved9C[0x30];
    s32 configuration;
} InitializationFields;

void func_PAL_L18_003F9230(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    s16 mode;
    s32 configuration;
    InitializationFields *settings = (InitializationFields *)state;
    settings->duration = func_00283CF0(15.0f);
    settings->speed = func_00283CF0(6.0f);
    configuration = *(s32 *)(state + 0x260);
    settings->type = 17;
    settings->ready = 1;
    settings->count = 3;
    settings->strength = 0.49000000953674316f;
    settings->secondary = 0.49000000953674316f;
    settings->configuration = configuration;
    settings->decay = 0.4f;
    if (settings->mode == 0) {
        settings->mode = 16;
        settings->animation = 16.0f;
    }
    settings->kind = 3;
    settings->blend = 0.5f;
    state[0x2E] = 1;
    *(float *)(state + 0x134) = 1.4f;
    *(float *)(state + 0x104) = 0.2f;
    *(float *)(state + 0x100) = 0.4f;
    *(float *)(state + 0x12C) = 0.008f;
    *(float *)(state + 0x108) = 2.0f;
    *(float *)(state + 0x10C) = 5.0f;
    *(float *)(state + 0x110) = 1.5707964897155762f;
    func_002B60B0(object, 0.0064000003f, 0.16000001f, 0.005026549f, 0.25132746f);
    if (*(s32 *)(state + 0x260) != -1) *(s32 *)(state + 0x13C) = *(s32 *)(state + 0x260);
    *(float *)(state + 0x268) = *(float *)(object + 0x2C);
    if (*(s32 *)(state + 0x280) != -1) *(u8 **)(state + 0x258) = D_L18_001B281C + (*(s32 *)(state + 0x280) << 8);
    *(s32 *)(object + 0x98) = *(s32 *)(*(u8 **)(object + 0x24) + 0x10);
    func_002A7750(object, 6, 2);
    mode = *(s16 *)(state + 0x296);
    if (mode == 14) {
        if (*(s32 *)(state + 0x26C) != -1) func_002A7750(object, 14, 2);
    } else if (mode == 1) func_L18_003F7590(object);
    else if (mode == 2) func_002A7750(object, 2, 0);
    qcopy((state + 0x210), (object + 0x10));
    qcopy((state + 0x220), (object + 0xF0));
    func_L18_0032B768(object, 0, 3);
}


extern void *func_002A9640(void *, u32, s32);
extern s32 func_PAL_002B1A50(void *, void *, s32);
extern void func_L18_003F7AB8(u8 *);
extern void func_L18_003F74B8(u8 *, s32);
extern void func_PAL_002A7650(u8 *, s32, s32);
extern s32 func_L18_0033B628(s32, s32, s32);
extern s32 func_002B3BA8(u8 *, s32, void *, s32, float, float);
extern void func_L18_003F8E30(u8 *);
extern s32 D_0018C0B4;

void func_PAL_L18_003F9470(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    u8 *contact;
    u8 saved;
    u64 mode;
    contact = func_002A9640(object, 0x10000, 1);
    if (contact && *(u8 **)(contact + 0x20) && *(s16 *)(*(u8 **)(contact + 0x20) + 0xAA) == 0xF9E) {
        if (object[0x20] < 6 || object[0x20] == 19 || object[0x20] == 18) return;
        func_002A7750(object, 18, -1);
        return;
    }
    saved = object[0x94];
    if (func_PAL_002B1A50(object, state + 0x50, 0)) {
        if (object[0x94] == 17 || object[0x94] == 8 || object[0x94] == 9 || object[0x94] == 16 || object[0x94] == 10 || object[0x94] == 7) object[0x94] = saved;
        if (object[0x94] != 14) func_L18_003F7AB8(object);
    }
    object[0xA8] = 255;
    if (*(float *)(object + 0x18) < 90.0f || (*(float *)(state + 0x2A0) != -1.0f && *(float *)(object + 0x18) < *(float *)(state + 0x2A0))) func_L18_003F74B8(object, 0);
    if (state[0x2E] == 2) {
        func_L18_003F74B8(object, 1);
        return;
    }
    contact = *(u8 **)(state + 0x188);
    if (contact && *(s16 *)(contact + 0xAA) == 0xF59) {
        func_PAL_002A7650(object, 0, 1);
        goto stop;
    }
    mode = object[0x20];
    if (*(s32 *)(state + 0x180) > 300 && mode != 2) goto stop;
    if ((u8)mode >= 6 && *(s32 *)(state + 0x260) != -1 && !func_L18_0033B628((s32)(object + 0x10), *(s32 *)(state + 0x260), 0)) {
stop:
        func_L18_003F74B8(object, 0);
        return;
    }
    *(s32 *)(state + 0x248) = func_002B3BA8(object, *(s32 *)(state + 0x240), 0, 0, *(float *)(state + 0x244), 0.0f);
    if (*(u8 **)(state + 0x258)) func_L18_003F8E30(*(u8 **)(state + 0x258));
    if (D_0018C0B4 == 0x6F && (u32)(object[0x20] - 9) < 4) func_002A7750(object, 6, -1);
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L18_003F96E8);

INCLUDE_ASM("asm/pal/levels", func_PAL_L18_003FAD60);
