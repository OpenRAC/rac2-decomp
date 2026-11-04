/* func_PAL_L11_004460C0, the PAL copy of func_L11_00440868: the same C with the callee is PAL's
   func_PAL_L11_003F72D0. */
#include "include_asm.h"
#include "common.h"

extern u8 *D_L11_001FC420[];

extern u8 *D_L11_001B359C __attribute__((section(".sdata")));

extern void func_PAL_L11_003F72D0(u8 *);

extern void func_L11_00439950(u8 *);

u8 *func_PAL_L11_004460C0(u8 *obj, s32 id) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 index = *(s32 *)(state + 0xC0);
    u16 *cursor;
    u8 *record;
    u8 *list;

    if (index == 0xFF) {
        return 0;
    }
    list = D_L11_001FC420[index];
    if (list == 0) {
        return 0;
    }
    cursor = (u16 *)list;
    do {
        u16 value = *cursor & 0x7FFF;
        record = D_L11_001B359C + (value << 8);

        if (record != 0 && record[0x20] != 0xFE && record[0x20] != 0xFD &&
            *(s16 *)(record + 0xAA) == id && record[0x20] == 1) {
            *(u32 *)(record + 0xB8) = (u32)obj;
            switch (id) {
            case 0xD4A:
                func_L11_00439950(record);
                *(s32 *)(state + 0x118) += 1;
                return record;
            case 0xB3A:
                func_PAL_L11_003F72D0(record);
                *(s32 *)(state + 0x11C) += 1;
                return record;
            }
        }
    } while (*(s16 *)cursor++ >= 0);
    return 0;
}
