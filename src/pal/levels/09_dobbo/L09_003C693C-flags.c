#include "include_asm.h"

#include "common.h"
extern s32 D_001A79F0 __attribute__((sda));
extern void func_L00_00326048(void *, s32, s32, s32, float);
extern s32 D_L08_001A8F00[] __attribute__((sda));
extern u8 D_001A7A40[] __attribute__((sda));
extern u8 D_L08_001B22E0[] __attribute__((sda));
extern s32 func_L08_00435938(void);
extern u8 D_001A7A00[] __attribute__((sda));
extern u8 D_L08_001A7C80[] __attribute__((sda));
extern u8 D_001395B8[];
extern u8 D_L08_001BFD00[];

/* One resident word, two states, and a 16-byte table entry: hands the entry to
   func_L00_00326048 with an alpha of 0x3D7A35E0. */
void func_PAL_L09_003C693C(u8 *a0)
{
    s32 v = *(s32 *)(a0 + 0x68);

    if (v == 0)
        return;
    func_L00_00326048(a0, v, 0x80AAAAD2, 0x80396464, 0.07330384f);
}
