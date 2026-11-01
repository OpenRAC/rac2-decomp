#include "include_asm.h"

#include "common.h"
extern int D_001A79F0 __attribute__((sda));
extern u8 D_0019B2E8[];
extern char *g_pHeroMoby[];
extern s32 func_002A8508(u32, s32);
extern int func_00288D58(void);
extern int func_002E5CF8(int, int, char *);

/* A pickup's states: 0 takes the hero's flags, 1 waits until none of its four
   links is alive (or the zone byte says go), 2 fades it out, 4 is done. */
void func_PAL_L04_0043DD20(u8 *obj)
{
    u8 *links = *(u8 **)(obj + 0x68);
    s32 i;

    if (obj[0x20] == 0) {
        *(u64 *)(obj + 0x38) = *(u64 *)(g_pHeroMoby[0] + 0x38);
        *(u16 *)(obj + 0x34) |= 0x800;
        obj[0x20] = 1;
    }
    if (obj[0x20] == 1) {
        s32 found = 0;
        for (i = 0; i < 4; i++) {
            if (func_002A8508(*(u32 *)(links + 4 * i), -1))
                found = 1;
        }
        if (*(u32 *)(links + 0x10) != 0) {
            if (func_00288D58() != 0) {
                if (func_002A8508(*(u32 *)links, -1) == 0)
                    found = 0;
            }
        }
        if (found == 0 || (D_0019B2E8[obj[0xB0] + (D_001A79F0 << 4)] & 0x80)) {
            func_002E5CF8(0, 0, (char *)obj);
            obj[0x20] = 2;
        }
    }
    if (obj[0x20] == 2) {
        f32 t = *(f32 *)(obj + 0x18);
        if (t >= 30.0f)
            *(f32 *)(obj + 0x18) = t - 0.34000003f;
        if (*(f32 *)(obj + 0x18) < 30.0f)
            obj[0x20] = 4;
    }
}
