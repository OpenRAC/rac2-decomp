#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 prefix[0x1830];
    u8 *controller;
    u8 gap[0x2294 - 0x1834];
    int state;
} ResidentWaterView;
extern ResidentWaterView D_00189E20;
extern int D_L20_001B2330[] SDATA(D_L20_001B2330);
extern u16 D_L20_001B2338[] SDATA(D_L20_001B2338);
extern int D_L20_001B2344 __attribute__((sda));
extern int D_L20_001B2348 __attribute__((sda));
extern u8 *D_L20_001B2F9C __attribute__((sda));
extern u8 D_L20_002AB980[];
extern u8 D_L20_0025DD00[];
extern int D_L20_0025DD60[];
typedef struct { int id, offsets[2], size; } WaterHeaderSlot;
extern WaterHeaderSlot D_L20_002B22E0[];
extern void func_L20_00447908(void);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_PAL_L04_003A47C0(u8 *);
extern void func_L04_003A5C08(u32, float);
extern void func_PAL_L04_003A49E0(char *);
extern void func_L04_003A1FA0(u8 *);
extern void func_L04_003A1FE0(u8 *);
extern void func_L00_003294F0(void *, int);
typedef struct {
    int count, activeCount;
    u8 *tiles;
    u8 *parameters;
    u16 *masks;
    int *counts;
    int *buffer;
    WaterHeaderSlot *slots;
    int *slotCount, *used;
    u8 *owner;
    void (*draw)(void);
    void (*enqueue)(void (*)(void *), void *);
} WaterContext;

void func_PAL_L20_0044D2D0(u8 *object)
{
    WaterContext context;
    u8 *state;
    u8 *controller = D_00189E20.controller;
    int count;
    int remaining;
    int *child;
    int absent;

    if (controller != 0 && *(s16 *)(controller + 0xAA) == 0x45 &&
        controller[0x20] != 0xFE && controller[0x20] != 0xFD &&
        D_00189E20.state == 0x31)
        return;
    state = *(u8 **)(object + 0x68);
    if (state == 0)
        return;
    count = 1;
    if (*(int *)(state + 0x18) != -1)
        count = D_L20_001B2330[*(int *)(state + 0x18)];
    count += *(int *)(state + 0x10);
    context.count = 6;
    context.activeCount = count;
    context.slotCount = &D_L20_001B2344;
    context.used = &D_L20_001B2348;
    context.tiles = D_L20_002AB980;
    context.parameters = D_L20_0025DD00;
    context.masks = D_L20_001B2338;
    context.counts = D_L20_001B2330;
    context.buffer = D_L20_0025DD60;
    context.slots = D_L20_002B22E0;
    context.owner = object;
    context.draw = func_L20_00447908;
    context.enqueue = func_L00_002E6EF8;
    switch (object[0x20]) {
    case 0:
        func_PAL_L04_003A47C0((u8 *)&context);
        func_L04_003A5C08((u32)object, *(float *)(state + 0x28));
    case 1:
        func_PAL_L04_003A49E0((char *)&context);
        break;
    case 2:
        absent = -1;
        func_L04_003A1FA0((u8 *)&context);
        child = (int *)(state + 0x30);
        for (remaining = 3; remaining >= 0; --remaining, ++child) {
            if (*child != absent)
                func_L00_003294F0(D_L20_001B2F9C + (*child << 8), state[0x14]);
        }
        break;
    }
    func_L04_003A1FE0((u8 *)&context);
}
