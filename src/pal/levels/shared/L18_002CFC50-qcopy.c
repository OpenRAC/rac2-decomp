#include "include_asm.h"

#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef struct Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner {
    unsigned char prefix_00[0x120]; void *slots_120[10]; int count_148; int active_14c;
} Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner;
extern void func_PAL_L00_002AF6C0(void);
extern void func_PAL_L00_002B1E88(void);
extern void func_L00_00322EC8(Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *);
extern void func_L00_002D2E68(void);
extern void func_L00_002A6708(void);
extern void func_L00_002A53B8(void);
extern void func_PAL_L18_002D0738(void);
extern void func_L00_002D24B8(void);
extern void func_002A677C(void *);
extern s32 func_PAL_L18_002E01E0(s32, s32);
extern void func_PAL_L00_002D2668(s32, s32, float);
extern u8 D_00189E20[];
extern u8 D_00189E20[];
extern u8 D_L18_001B4E00[], D_L18_001B5400[];
extern s32 D_L18_001A8F00[] __attribute__((sda));
extern s32 func_002AB1F0(u8 *);
extern void func_L00_002A53B8(void);
extern s32 func_0028B3D0(s32, s32, void (*)(u8 *), void (*)(u8 *), void (*)(u8 *), s32, s32);
extern s32 func_L00_002F6B90(u32);
extern void func_L00_002A6708(void);
extern void func_L00_002D24B8(void);
extern s32 func_L00_002A4DB0(char *, s32, s32, s32);

void func_PAL_L18_002CFC50(s32 mode, s32 index, u8 *object)
{
    u8 *base = D_00189E20;
    u8 *current;
    func_PAL_L00_002AF6C0();
    base[0x22B6] = 1;
    func_PAL_L00_002B1E88();
    *(u8 **)(base + 0x2290) = *(u8 **)(base + 0xC18);
    func_L00_00322EC8((Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *)(base + 0x18E0));
    func_L00_00322EC8((Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *)(base + 0x1A30));
    *(s32 *)(*(u8 **)(base + 0x2290) + 0x9C) = -1;
    if (mode != 4 || base[0x22B4] != 4) func_L00_002D2E68();
    func_L00_002A6708();
    func_L00_002A53B8();
    D_00189E20[0x22B4] = mode;
    *(u8 **)(D_00189E20 + 0xC14) = object;
    *(u8 **)(D_00189E20 + 0x2290) = object;
    func_PAL_L18_002D0738();
    *(float *)(D_00189E20 + 0x250) = *(float *)(D_00189E20 + 0x258);
    *(float *)(D_00189E20 + 0x254) = *(float *)(D_00189E20 + 0x25C);
    current = *(u8 **)(D_00189E20 + 0x2290);
    *(u16 *)(current + 0x34) |= 6;
    *(float *)(D_00189E20 + 0xC20) = 1.0f;
    *(float *)(D_00189E20 + 0xC24) = 1.0f;
    func_L00_002D24B8();
    func_002A677C(*(u8 **)(D_00189E20 + 0x2290));
    *(s16 *)(D_00189E20 + 0x24F2) = index;
    if (mode == 4) {
        *(VectorBits *)(D_00189E20 + 0x80) = *(VectorBits *)(object + 0x10);
        *(VectorBits *)(D_00189E20 + 0x90) = *(VectorBits *)(object + 0xF0);
        *(s16 *)(D_00189E20 + 0x24D4) = *(u16 *)(D_00189E20 + 0x24CC);
        *(s32 *)(D_00189E20 + 0x24CC) = 3;
    }
    func_PAL_L18_002E01E0(index, 2);
    if (mode == 4) func_PAL_L00_002D2668(15, 0, 4.0f);
}
