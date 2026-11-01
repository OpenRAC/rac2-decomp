#include "include_asm.h"

#include "common.h"
extern s32 D_L03_001B2548;
extern u8 *D_L03_001B2A1C;
extern u8 D_001A7AF8[] __attribute__((sda));
extern u8 D_00139568[];
extern s32 D_00139688[];
extern struct { u8 pad[0xE0]; } D_L03_00266DA0[];
extern s16 *D_001FB5A0[];
extern u8 D_00189EA0[];
extern s32 func_00312B58(u8 *obj);
extern void func_L02_003A6FE8(u8 *obj);
extern f32 func_00282E48(u8 *a, u8 *b);
extern void func_L02_002EF388(u8 *obj, u8 *pos, u8 *vel, s32 a3, s32 t0);

/* Every 64th tick: when one of the 56 tracked entries is below a tenth of its limit, wakes the
   objects listed for the state that are in range. */
void func_PAL_L03_003FAFC0(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    s32 low = 0;
    u8 *obj;
    u8 *pos;
    s16 *list;
    s32 i;

    if ((D_L03_001B2548 & 0x3F) == 0) {
        for (i = 0; i < 0x38; i++) {
            if (D_001A7AF8[i] != 0) {
                u8 *e = (u8 *)&D_L03_00266DA0[D_00139568[i]];
                s16 limit = *(s16 *)(e + 0x40);
                if (limit != 0 && (f32)D_00139688[i] < (f32)limit * 0.1f) {
                    low = 1;
                }
            }
        }
    }
    if (low != 0) {
        list = D_001FB5A0[*(s32 *)(state + 0xAC)];
        if (list != 0) {
            do {
                obj = D_L03_001B2A1C + (((u16)*list & 0x7FFF) << 8);
                if (func_00312B58(obj) != 0 && *(s32 *)(*(u8 **)(obj + 0x68) + 0x100) >= 0x33) {
                    pos = obj + 0x10;
                    if (func_00282E48(D_00189EA0, pos) > 3.0f) {
                        func_L02_003A6FE8(obj);
                        func_L02_002EF388(obj, pos, obj + 0xF0, 0, 0);
                    }
                }
            } while (*list++ >= 0);
        }
    }
}
