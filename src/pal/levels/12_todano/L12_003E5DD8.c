#include "include_asm.h"

#include "common.h"
extern u8 D_L12_001B9E00[];
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern u8 D_L12_00188660[];
extern s32 func_315148();
extern s32 func_32D988();
extern s32 func_2F15C8(void *arg0);
extern s32 func_3205F8(void *arg0, s32 arg1, s32 arg2);
extern s32 func_364DF8(s32 arg0, s32 arg1, void *arg2);
extern s32 D_L12_001B2E9C __attribute__((sda));
extern s32 D_L12_001B2E9C_2;
extern u16 *D_L12_001FB960[];
extern s32 D_001A79F0 __attribute__((sda));
extern s32 func_002A8600(u8 **out, s32 kind, s32 arg2, s32 arg3);
extern s32 func_002A86E8(u8 **out, u32 value, s32 arg2, s32 arg3);
extern u8 D_001A7AF8[] __attribute__((sda));
extern u8 D_001A7A40 MACRO_ADDR;
extern u32 D_001397DC, D_00138324;
extern u8 D_L12_001C0000[];
extern u8 *func_0029EFD0(int);
extern void func_002A7750(void *, s32, s32);
extern u8 *func_00288FB8(int);
extern s32 *D_L12_001FEAC0[];
extern s32 func_002A8AF0(void *, void *, s32);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern void func_002A7750(void *, s32, s32);

u8 *func_PAL_L12_003E5DD8(s32 index, u8 *obj)
{
    u16 *list = D_L12_001FB960[index];
    u16 *entry;
    u8 *found = 0;

    if (list == 0) {
        return 0;
    }
    entry = list;
    do {
        u8 *rec = (u8 *)D_L12_001B2E9C + (*entry & 0x7FFF) * 0x100;

        if (*(s16 *)(rec + 0xAA) == 0xFB4) {
            u8 *vars = *(u8 **)(rec + 0x68);
            s32 *zone = D_L12_001FEAC0[*(s32 *)(vars + 0x138)];

            if (func_002A8AF0(obj + 0x10, zone + 4, zone[0]) != 0) {
                if (rec[0x20] == 9) {
                    *(u16 *)(rec + 0x34) = (*(u16 *)(rec + 0x34) & 0xFFBE) | 0x1000;
                    *(s32 *)(rec + 0x98) = *(s32 *)(*(u8 **)(rec + 0x24) + 0x10);
                    if (rec[0x43] != 5) {
                        func_PAL_002A7E68(rec, 5, 0, 8);
                    }
                    func_002A7750(rec, 10, -1);
                } else if (rec != 0 && rec[0x20] != 0xFE && rec[0x20] != 0xFD) {
                    func_002A7750(rec, 11, 4);
                    if (rec[0x43] != 7) {
                        func_PAL_002A7E68(rec, 7, 0, 0x11);
                    }
                }
                *(u8 **)(vars + 0x374) = obj;
                found = rec;
                break;
            }
        }
    } while ((s16)*entry++ >= 0);
    return found;
}

