#include "include_asm.h"

#include "common.h"
#define I32(p, o) (*(int *)((p) + (o)))
#define F32(p, o) (*(float *)((p) + (o)))
#define S16(p, o) (*(short *)((p) + (o)))
extern int func_002B3BA8(void *, int, void *, int, float, float);
extern void func_L01_003BD5E8(void *);
extern int func_PAL_002B1A50(void *, void *, int);
extern void func_L01_003BDBB0(void *), func_L01_003BDB28(void *), func_L01_003BE488(void *);
extern int func_00283DB8(void *, float);
extern int func_L00_002FCF18(void *, float, float, float, float, float);
extern u8 D_L01_001C7640[];
extern u8 *func_L01_00333FA8(float, void *, unsigned int, int);
extern int func_00282948(int *);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);

void func_PAL_L01_003C2268(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68), *effect, *entry;
    float sphere[4] __attribute__((aligned(16)));
    float effect_position[4] __attribute__((aligned(16)));
    float *object_position;
    int contact, active;
    func_002B3BA8(object, I32(state, 0x29c), 0, 0, F32(state, 0x22c), 0.0f);
    func_L01_003BD5E8(object);
    F32(object, 0x2c) = F32(*(u8 **)(object + 0x24), 0x24) * 1.25f;
    contact = func_PAL_002B1A50(object, state + 0x50, 0);
    if (contact) {
        if (F32(state, 0x20) <= 0.0f) I32(state, 0xcc) = -1;
        func_L01_003BDBB0(object);
        func_L01_003BDB28(object);
        effect = *(u8 **)(state + 0x290);
        if (effect && effect + 0x20 && effect[0] == 0x57) {
            I32(effect, 0x20) = 0;
            *(u8 **)(state + 0x290) = 0;
        }
    }
    object_position = (float *)(object + 0x10);
    qcopy(sphere, object_position);
    active = object[0x31];
    sphere[3] = 4.0f;
    if ((active || func_00283DB8(sphere, (float)S16(object, 0x32)) != -1)
        && (unsigned int)(object[0x20] - 2) < 7) {
        if (S16(state, 0x202) == -1) {
            qcopy(effect_position, object_position);
            effect_position[2] += 1.0f;
            F32(state, 0x204) = 0.012f;
            S16(state, 0x202) = func_L00_002FCF18(effect_position, 4.0f, 0.0f, 0.012f, 0.010799999f, 0.0036000002f);
        } else {
            F32(state, 0x204) += 0.012f;
            if (F32(state, 0x204) > 1.0f) F32(state, 0x204) = 1.0f;
            entry = D_L01_001C7640 + S16(state, 0x202) * 32;
            F32(entry, 0) = F32(state, 0x204);
            F32(entry, 4) = F32(state, 0x204) * 0.9f;
            F32(entry, 8) = F32(state, 0x204) * 0.3f;
            F32(entry, 0x10) = F32(object, 0x10);
            F32(entry, 0x14) = F32(object, 0x14);
            F32(entry, 0x18) = F32(object, 0x18) + 1.0f;
        }
        if (*(u8 **)(state + 0x290) == 0)
            *(u8 **)(state + 0x290) = func_L01_00333FA8(210000.0f, object, 0x40105070, -1);
    } else {
        effect = *(u8 **)(state + 0x290);
        if (effect && effect[0] == 0x57 && effect + 0x20) {
            I32(effect, 0x20) = 0;
            *(u8 **)(state + 0x290) = 0;
        }
        if (S16(state, 0x202) != -1) func_L01_003BE488(object);
    }
    if (object[0x20] >= 6 && func_00282948((int *)(state + 0x258))) {
        if (F32(state, 0x24c) > 0.5f) F32(state, 0x24c) = func_002A7878(0.0f, 0.4f);
        else F32(state, 0x24c) = func_002A7878(0.6f, 1.0f);
        I32(state, 0x258) = ((s32)(func_002A7820(45, 150)) * 5 + 2) / 6;
    }
    if (object[0x20] == 8) F32(state, 0x28c) = 1.0f;
    else if (object[0x20] >= 6 && func_00282948((int *)(state + 0x25c))) {
        if (F32(state, 0x28c) > -1.75f) F32(state, 0x28c) = func_002A7878(0.5f, 1.1f);
        else F32(state, 0x28c) = func_002A7878(1.6500000953674316f, 5.0f);
        I32(state, 0x25c) = ((s32)(func_002A7820(110, 60)) * 5 + 2) / 6;
    }
}
