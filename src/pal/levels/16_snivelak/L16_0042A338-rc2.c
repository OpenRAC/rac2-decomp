#include "include_asm.h"

#include "common.h"
extern void ref_L16_00424B48_00(s32, s32, s8 *, s32);

/* After being triggered, slowly sinks the object for a short time and then stops. */
void sinking_l16_platform_update_pal(s8 *moby) {
    s32 counter;
    s32 counter16;
    s32 under_limit;
    f32 new_z;

    if ((*(u8 *)((char *)(moby) + (0x20))) == 0) {
        if ((*(u8 *)((char *)(moby) + (0xBC))) != 0) {
            (*(u8 *)((char *)(moby) + (0x20))) = 1;
            ref_L16_00424B48_00(0, 0, moby, 0xE71);
        }
        (*(s16 *)((char *)(moby) + (0x32))) = 0x80;
    }
    if ((*(u8 *)((char *)(moby) + (0x20))) == 1) {
        new_z = (*(f32 *)((char *)(moby) + (0x18))) - 0.16000001f;
        counter = (*(u16 *)((char *)(moby) + (0x96))) + 1;
        counter16 = counter & 0xFFFF;
        (*(u16 *)((char *)(moby) + (0x96))) = counter;
        under_limit = (u32) counter16 < 0x3CU;
        (*(f32 *)((char *)(moby) + (0x18))) = new_z;
        if (under_limit == 0) {
            (*(u8 *)((char *)(moby) + (0x20))) = 2;
        }
    }
}
