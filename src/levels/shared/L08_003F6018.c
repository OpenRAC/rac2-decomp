#include "common.h"
typedef int SpawnQuad __attribute__((mode(TI)));
extern int func_002A8600(u8 **out, int index, int activate, int reset);
extern float func_00283248(float x, float y);
extern int func_002AB220(u8 *object);
extern int func_002AB1F0(u8 *object);
extern void func_0026FEB8(const char *format, ...);
extern void func_0029F390(u8 *object);
extern void func_002AB650(u8 *object);
extern void func_002A0F48(u8 *object);
extern char D_L08_001B0B68[];
extern char D_L08_001B0BA8[];
extern int D_L08_001B2508 MACRO_ADDR;

/* Bounded view of the owner's two pool slots and their status bytes. */
typedef struct {
    u8 unknown00[0x131];
    u8 activeCount;
    u8 unknown132;
    u8 smallScale;
    int slots[2];
} PoolSlotsPrefix;

u8 *func_L08_003F6018(u8 *owner, SpawnQuad *position, float *direction)
{
    u8 *child;
    PoolSlotsPrefix *state;
    u8 *part;
    u8 *c;
    u8 *head;
    int i;
    if (owner == 0)
        return 0;
    state = *(PoolSlotsPrefix **)(owner + 0x68);
    child = 0;
    for (i = 0; i < 2; i++) {
        if (GetFirstMobyInGroup(&child, state->slots[i], 1, 1) != 0)
            continue;
        state->activeCount++;
        {
            u8 *fresh = child;
            *(SpawnQuad *)(fresh + 0x10) = *position;
            *(int *)(fresh + 0x1c) = 0;
        }
        child[0x20] = 0;
        child[0xbc] = 0;
        *(unsigned short *)(child + 0x34) = *(unsigned short *)(*(u8 **)(child + 0x24) + 0x44);
        *(float *)(child + 0x2c) = *(float *)(*(u8 **)(child + 0x24) + 0x24);
        child[0x30] = 255;
        *(unsigned short *)(child + 0x32) = 255;
        child[0x31] = 1;
        if (*(int *)(*(u8 **)(child + 0x24) + 0x40) != 0)
            *(unsigned short *)(child + 0x34) |= 0x10;
        if (*(u8 *)(*(u8 **)(child + 0x24) + 0xf) != 0)
            *(unsigned short *)(child + 0x34) |= 0x400;
        *(unsigned short *)(child + 0x36) = 0x7f80;
        child[0x61] = 255;
        child[0x62] = 255;
        child[0xa8] = 255;
        child[0x42] = 0;
        child[0x43] = 0;
        child[0x40] = 0;
        child[0x41] = 1;
        *(int *)(child + 0x44) = 0;
        *(float *)(child + 0x48) = 1.0f;
        child[0xa9] = 0;
        *(short *)(child + 0x96) = 0;
        child[0x7f] = 0;
        *(int *)(child + 0xf0) = 0;
        *(int *)(child + 0xf4) = 0;
        *(float *)(child + 0xf8) = func_00283248(direction[0], direction[1]);
        head = (u8 *)func_002AB220(child);
        if (head != 0)
            *(SpawnQuad *)(head + 0x80) = *(SpawnQuad *)direction;
        else
            STUB_printf(D_L08_001B0B68, *(short *)(child + 0xaa), *(short *)(child + 0xb2), D_L08_001B2508);
        if (state->smallScale)
            *(float *)(child + 0x2c) = *(float *)(*(u8 **)(child + 0x24) + 0x24) * 0.1f;
        if (*(short *)(owner + 0xb4) < *(short *)(child + 0xb4))
            *(short *)(child + 0xb4) = *(short *)(owner + 0xb4);
        *(short *)(owner + 0xb4) -= *(short *)(child + 0xb4);
        if (*(short *)(owner + 0xb4) < 0)
            *(short *)(owner + 0xb4) = 0;
        *(u8 **)(child + 0xb8) = owner;
        child[0x6e] = 0;
        child[0x6c] = 255;
        child[0x6d] = 255;
        update_moby_animation_state(child);
        *(int *)(child + 0x98) = *(int *)(*(u8 **)(child + 0x24) + 0x10);
        func_002AB650(child);
        func_002A0F48(child);
        c = child;
        part = (u8 *)func_002AB1F0(c);
        if (part != 0) {
            *(int *)(part + 0x24) = 0;
            *(int *)(part + 0x20) = 0;
            *(float *)part = *(short *)(part + 4);
        }
        return c;
    }
    STUB_printf(D_L08_001B0BA8, *(short *)(owner + 0xb2), D_L08_001B2508);
    return 0;
}
