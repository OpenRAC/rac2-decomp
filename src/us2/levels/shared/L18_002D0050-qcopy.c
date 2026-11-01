#include "include_asm.h"

#include "common.h"
extern void func_L00_002A6708(void);
extern void func_L00_002A53B8(void);
extern void func_L00_002D24B8(void);
extern s32 func_US2_L18_002E02E8(s32, s32);
extern u8 D_00189E20[];
extern u8 D_00189E20[];
extern u8 D_L18_001B4E00[], D_L18_001B5400[];
extern s32 D_L18_001A8F00[] __attribute__((sda));
extern s32 func_002AB1F0(u8 *);
extern void func_US2_0029C548(s32, s32);
extern void func_L00_002B2BD0(void);
extern void func_L00_002A53B8(void);
extern void func_0028BDB0(u8 *);
extern void func_0028BE00(u8 *);
extern void func_0028C6D0(u8 *);
extern s32 func_0028B3D0(s32, s32, void (*)(u8 *), void (*)(u8 *), void (*)(u8 *), s32, s32);
extern s32 func_L00_002F6B90(u32);
extern void func_L00_002A6708(void);
extern void func_L00_002D24B8(void);
extern s32 func_L00_002A4DB0(char *, s32, s32, s32);
extern void func_L00_002D9D98(void);

void func_US2_L18_002D0050(s32 keep)
{
    u8 *base = D_00189E20;
    u8 *object;
    float *record;
    s32 value;
    s32 mode;
    u8 *attached;
    u8 *restored;
    u8 *current;
    if (base[0x22B4] == 4) {
        record = (float *)func_002AB1F0(*(u8 **)(base + 0x2290));
        if (record) *record = (float)*(s32 *)(base + 0x24CC);
        object = *(u8 **)(base + 0xC18);
        qcopy((base + 0x80), (object + 0x10));
        qcopy((base + 0x90), (object + 0xF0));
        *(s32 *)(base + 0x24CC) = *(s16 *)(base + 0x24D4);
        if (!keep) func_US2_0029C548(0, 0);
        func_L00_002B2BD0();
        *(s16 *)(base + 0x34E) = 1;
        *(s32 *)(base + 0x3A4) &= ~1;
        *(s32 *)(base + 0x3A4) &= ~2;
        *(s32 *)(base + 0x3A0) = 0;
        base[0x22B5] = 0;
    }
    func_L00_002A53B8();
    D_00189E20[0x22B4] = 0;
    func_0028B3D0(35, 0, func_0028BDB0, func_0028BE00, func_0028C6D0, 0, 0);
    func_L00_002F6B90(3);
    attached = *(u8 **)(D_00189E20 + 0xC14);
    if (attached) *(u16 *)(attached + 0x34) &= ~6;
    *(u8 **)(D_00189E20 + 0xC14) = 0;
    func_L00_002A6708();
    restored = *(u8 **)(D_00189E20 + 0xC18);
    *(u8 **)(D_00189E20 + 0x2290) = restored;
    qcopy((restored + 0x10), (D_00189E20 + 0x80));
    *(s32 *)(restored + 0x9C) = 0;
    *(float *)(D_00189E20 + 0xC24) = 1.0f;
    func_L00_002D24B8();
    current = *(u8 **)(D_00189E20 + 0x2290);
    if (current[0x42] != 255) {
        value = func_L00_002A4DB0((char *)current, current[0x42], current[0x40], (s32)D_L18_001B4E00);
        *(s32 *)(*(u8 **)(D_00189E20 + 0x2290) + 0x58) = value;
    }
    current = *(u8 **)(D_00189E20 + 0x2290);
    value = func_L00_002A4DB0((char *)current, current[0x43], current[0x41], (s32)D_L18_001B5400);
    *(s32 *)(*(u8 **)(D_00189E20 + 0x2290) + 0x5C) = value;
    if (*(s32 *)(D_00189E20 + 0x2294) != 0x61) goto reset;
    switch (D_L18_001A8F00[0]) {
    case 2:
    case 6:
        goto done;
    }
reset:
    func_US2_L18_002E02E8(0, 1);
done:
    if (D_00189E20[0x22B4] == 4) func_L00_002D9D98();
}
