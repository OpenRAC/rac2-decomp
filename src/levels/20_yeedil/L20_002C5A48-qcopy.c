#include "common.h"

extern u8 D_00189E20[];
extern u8 D_L20_001B5600[], D_L20_001B5C00[];
extern s32 D_L20_001A8F00[] __attribute__((sda));
extern void func_0029F338(void *);
extern s32 func_002AB1F0(u8 *);
extern void func_0029B758(s32, s32);
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
extern void func_L20_002D7730(s32, s32);

/* Apart from the leading state-1 block this is the same code as func_L18_002CFF48
   (src/levels/shared/L18_002CFD68-qcopy.c), and it needs the same grouped-copy profile.
   The state-1 block and the rest each take the hero block's address on their own: retail
   rebuilds it from the %hi kept in $s2.  D_L20_001A8F00 is declared as an sda array, as in
   the sibling, which gives retail's lui + lw into the same register. */
void func_L20_002C5A48(s32 keep)
{
    u8 *hero = D_00189E20;
    u8 *base;
    u8 *object;
    float *record;
    s32 value;
    u8 *attached;
    u8 *restored;
    u8 *current;

    if (hero[0x22B4] == 1) {
        *(s32 *)(hero + 0x24D0) = *(s32 *)(hero + 0x24CC);
        *(s32 *)(hero + 0x24CC) = *(s16 *)(hero + 0x24D4);
        if (*(void **)(hero + 0x1860)) {
            func_0029F338(*(void **)(hero + 0x1860));
            *(void **)(hero + 0x1860) = 0;
        }
        if (*(void **)(hero + 0x1864)) {
            func_0029F338(*(void **)(hero + 0x1864));
            *(void **)(hero + 0x1864) = 0;
        }
    }
    base = D_00189E20;
    if (base[0x22B4] == 4) {
        record = (float *)func_002AB1F0(*(u8 **)(base + 0x2290));
        if (record) *record = (float)*(s32 *)(base + 0x24CC);
        object = *(u8 **)(base + 0xC18);
        qcopy((base + 0x80), (object + 0x10));
        qcopy((base + 0x90), (object + 0xF0));
        *(s32 *)(base + 0x24CC) = *(s16 *)(base + 0x24D4);
        if (!keep) func_0029B758(0, 0);
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
        value = func_L00_002A4DB0((char *)current, current[0x42], current[0x40], (s32)D_L20_001B5600);
        *(s32 *)(*(u8 **)(D_00189E20 + 0x2290) + 0x58) = value;
    }
    current = *(u8 **)(D_00189E20 + 0x2290);
    value = func_L00_002A4DB0((char *)current, current[0x43], current[0x41], (s32)D_L20_001B5C00);
    *(s32 *)(*(u8 **)(D_00189E20 + 0x2290) + 0x5C) = value;
    if (*(s32 *)(D_00189E20 + 0x2294) != 0x61) goto reset;
    switch (D_L20_001A8F00[0]) {
    case 2:
    case 6:
        goto done;
    }
reset:
    func_L20_002D7730(0, 1);
done:
    if (D_00189E20[0x22B4] == 4) func_L00_002D9D98();
}
