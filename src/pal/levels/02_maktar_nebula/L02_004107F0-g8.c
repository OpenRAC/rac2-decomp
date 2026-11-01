#include "include_asm.h"

#include "common.h"
extern s32 func_00283CF0(float);
extern float func_002A7878(float, float);
extern void *func_002B60B0(u8 *, float, float, float, float);
extern void func_002A04B8(u8 *, s32 *, s32 *, s32 *);
extern void func_PAL_L02_00411DB0(u8 *);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(u8 *);
extern s32 func_002E59B0(s32, s32);
extern s32 func_002E5CF8(s32, s32, char *);
extern void func_002E59F8(s32);
extern void *func_002A9640(void *, u32, s32);
extern float func_PAL_002AA108(u8 *, u8 *);
extern void func_00282F20(float *, float *, float);
extern void func_002A7A00(float *, float, float);
extern void func_00282CC0(float *, float *, float *);
extern float func_00283B98(float, float);
extern void func_PAL_002AC290(s32, char *);
extern void func_002A7750(u8 *, s32, s32);
extern void func_L02_0040CF68(u8 *);
extern u8 D_L02_001BA500[];
extern u8 D_00188660[];
extern float D_L02_001B194C __attribute__((sda));
extern float D_L02_001B1950 __attribute__((sda));
extern float D_L02_001B1954 __attribute__((sda));
extern float D_L02_001B1958 __attribute__((sda));
extern float D_L02_001B1960 __attribute__((sda));
extern float D_L02_001B1964 __attribute__((sda));

/* Maintain the held effect slot and react to contacts with another actor. */
void func_PAL_L02_00411720(u8 *object)
{
    float velocity[4];
    float random[4];
    u8 *state = *(u8 **)(object + 0x68);
    u8 *contact;
    float amount;
    float scale;
    float push;

    if (object[0x20] == 0) {
        *(u8 **)(state + 0x18) = state + 0x60;
        *(float *)(object + 0x2C) *= 0.75f;
        *(s32 *)(state + 0x19C) = -1;
        state[0x48] = func_00283CF0(15.0f);
        state[0x4A] = func_00283CF0(4.0f);
        *(float *)(state + 0x190) = func_002A7878(-*(float *)(state + 0x190), *(float *)(state + 0x190)) * 0.017453294f;
        object[0x30] = 0x80;
        *(s32 *)(state + 0x194) = 1;
        *(float *)(state + 0x198) *= 0.020000001f;
        func_002B60B0(object, 0.040000003f, 2.0000002f, 0.0016755164f, 0.12566373f);
        func_002A04B8(object, (s32 *)(state + 0x1A0), (s32 *)(state + 0x1A4), (s32 *)(state + 0x1A8));
        *(float *)(state + 0x60) = 0.75f;
        *(float *)(state + 0x68) = 0.75f;
        *(s32 *)(state + 0x64) = 0;
        *(s32 *)(state + 0x30) = 0;
        *(u16 *)(state + 0x1B8) = 0;
        *(float *)(state + 0x6C) = 0.5f;
        *(float *)(state + 0x70) = 1.1344641f;
        *(float *)(state + 0x90) = 0.52359885f;
        *(float *)(state + 0x8C) = 0.004f;
        *(u32 *)(state + 0x98) |= 0x14;
        state[0x28] = 3;
        func_PAL_L02_00411DB0(object);
    }
    if (object[0x31] && func_00282E48(object + 0x10, D_L02_001BA500) < 24.0f) {
        func_002A93B0(object);
        object[0x6F] = 0x16;
    }
    if (object[0x95] >= 2) {
        if (!func_002E59B0((s32)object, *(s32 *)(state + 0x19C)))
            *(s32 *)(state + 0x19C) = func_002E5CF8(1, 4, (char *)object);
    } else if (func_002E59B0((s32)object, *(s32 *)(state + 0x19C))) {
        s32 slot = *(s32 *)(state + 0x19C);
        if (slot != -1) {
            u8 *record = D_00188660 + slot * 0x70;
            if (*(u8 **)(record + 0x88) == object && record[0x74])
                func_002E59F8(slot);
        }
        *(s32 *)(state + 0x19C) = -1;
    }
    contact = func_002A9640(object, 0x10000, 0);
    if (contact && *(u8 **)(contact + 0x20)) {
        s16 kind = *(s16 *)(*(u8 **)(contact + 0x20) + 0xAA);
        if (kind == 0xA03)
            *(s32 *)(contact + 0x2C) = 0;
        else if (object[0x31] == 0 && kind == 0xB89)
            *(s32 *)(contact + 0x2C) = 0;
    }
    amount = func_PAL_002AA108(object, contact);
    object[0xA8] = 0xFF;
    if (amount != 0.0f) {
        scale = 0.00040000002f;
        push = D_L02_001B194C * scale;
        *(float *)(state + 0x20) -= amount;
        func_00282F20(velocity, (float *)(contact + 0x10), push);
        func_002A7A00(random, D_L02_001B1950 * scale, D_L02_001B1954 * scale);
        func_00282CC0(velocity, velocity, random);
        velocity[2] = func_002A7878(D_L02_001B1958, D_L02_001B1958) * scale;
        velocity[3] = 5627.925f;
        func_00282CC0((float *)(state + 0x100), (float *)(state + 0x100), velocity);
        func_002A7A00(random, D_L02_001B1960 * 6.981318e-06f, D_L02_001B1964 * 6.981318e-06f);
        *(float *)(state + 0x170) = func_00283B98(*(float *)(state + 0x170), random[0]);
        *(float *)(state + 0x174) = func_00283B98(*(float *)(state + 0x174), random[1]);
        *(float *)(state + 0x178) = func_00283B98(*(float *)(state + 0x178), random[2]);
        func_PAL_002AC290((s32)object, (char *)(state + 0x50));
        func_002A7750(object, 13, 4);
    }
    if (object[0x20] >= 2 && state[0x2E] == 2)
        func_PAL_L02_00411DB0(object);
    func_L02_0040CF68(object);
}
