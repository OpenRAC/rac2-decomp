#include "include_asm.h"

#include "common.h"
extern s32 func_002A8AF0(f32 *point, f32 *vertices, s32 count);
extern u8 D_L11_004465F8[];
extern u8 *D_L11_001FC420[];
extern u8 *D_L11_001B359C __attribute__((section(".sdata")));
extern s32 func_L02_003D77B8(u8 *);
extern s32 func_L02_003D77F8(u8 *);
extern s32 func_417238(s32);
extern s32 func_417270(s32);
extern u8 *D_L11_001FC420[];
extern u8 *D_L11_001B359C;
extern void func_L11_00449878(u8 *);
extern void func_PAL_L11_00451FD0(u8 *);
extern void func_PAL_L11_004589C8(u8 *);
extern void func_PAL_L11_0045A9A8(u8 *);
extern void func_L11_00456540(u8 *);
extern void func_PAL_L11_0043BFF8(u8 *);
extern void func_L11_00439BF0(u8 *);
extern void func_PAL_L11_004400D0(u8 *);
extern void func_L11_003F3098(u8 *);
extern u8 *D_L11_001B359C_base[] __asm__("D_L11_001B359C") __attribute__((sda));
extern u8 *D_L11_001B368C __attribute__((sda));
extern s32 D_L11_001B35B8[] __attribute__((sda));
extern s16 func_L02_004024A0(u8 *);
extern s32 func_L02_003D7300(u8 *);
extern s32 func_L11_00441FB8(u8 *, u8 *, s32);
extern s32 func_L11_0043A800(u8 *);
extern u8 D_00189E20[];
extern u8 D_001A63A8[];

void func_PAL_L11_00446A20(u8 *obj)
{
    s32 index = *(s32 *)(*(u8 **)(obj + 0x68) + 0xC0);
    u16 *p;
    u8 *list;
    u8 *entry;

    if (index == 0xFF)
        return;
    list = D_L11_001FC420[index];
    if (list == 0)
        return;
    p = (u16 *)list;
    do {
        entry = D_L11_001B359C_base[0] + ((*p & 0x7FFF) << 8);
        switch (*(s16 *)(entry + 0xAA)) {
        case 0xD98:
            func_L11_00449878(entry);
            break;
        case 0xDCF:
            func_PAL_L11_00451FD0(entry);
            break;
        case 0xDF4:
            func_PAL_L11_004589C8(entry);
            break;
        case 0xDF7:
            func_PAL_L11_0045A9A8(entry);
            break;
        case 0xDF9:
            func_L11_00456540(entry);
            break;
        case 0xD37:
            func_PAL_L11_0043BFF8(entry);
            break;
        case 0xD4A:
            func_L11_00439BF0(entry);
            break;
        case 0xD4B:
            func_PAL_L11_004400D0(entry);
            break;
        case 0xB3A:
            func_L11_003F3098(entry);
            break;
        }
    } while (*(s16 *)p++ >= 0);
}

