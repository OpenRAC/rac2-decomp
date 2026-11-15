/* Carried from rac3-decomp (src/boot_elf/text/39AC98.c, func_0039AC98) with rac2's
   offsets; the source's volatile stores are plain here. Starts loading entry A0 of the
   table in D_0014B540 when the load slot (D_001A9330) is free: records the entry, A1 and
   A2 in the slot, and asks func_002B7BC0 for the entry's second part (with func_00294180
   as the callback) when it has one and A3 is 0, else for its first part (func_00294130).
   0 when the entry is empty or the slot busy. */

#include "common.h"

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
} LoadEntry;

typedef struct {
    u8 pad[0x4B3C];
    s32 base;
    LoadEntry el[0x30];
} LoadTable;

typedef struct {
    u8 pad[0x34];
    s32 f34[3];
} LoadOwners;

extern LoadTable D_0014B540;
extern LoadOwners D_00152CD0;
extern s32 D_001A9330 __attribute__((sda));
extern s32 D_001A9334[] __attribute__((sda));
extern s32 func_002B7BC0();
extern void func_00294130();
extern void func_00294180();

/* Queues loading of table entry a0 into slot a1 unless another load is in progress; returns the result. */
s32 func_002942A0(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 t;
    if (D_0014B540.el[a0].f8 != 0) {
        t = D_001A9330;
        if (t == -1) {
            D_001A9330 = a0;
            D_001A9334[0] = a1;
            D_001A9334[1] = a2;
            if (a1 >= 0) {
                D_00152CD0.f34[a1] = t;
            }
            if (D_0014B540.el[a0].f10 != 0 && a3 == 0) {
                return func_002B7BC0(a2, D_0014B540.el[a0].fC + D_0014B540.base, D_0014B540.el[a0].f10, func_00294180, &D_001A9330);
            }
            return func_002B7BC0(a2, D_0014B540.el[a0].f4 + D_0014B540.base, D_0014B540.el[a0].f8, func_00294130, &D_001A9330);
        }
        return 0;
    }
    return 0;
}
