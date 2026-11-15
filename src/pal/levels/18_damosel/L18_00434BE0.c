#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
extern u8 D_001C97C0[];
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern u8 D_0019B2E8[];
extern void extermibot_init_parts(u8 *a0);
extern void extermibot_update_hits(u8 *a0);
extern void extermibot_update_states(u8 *a0);
extern void extermibot_aim_torso(u8 *a0);
extern void extermibot_update_parts(u8 *a0);
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern u8 D_00190000[];

void func_PAL_L18_00435260(u8 *a0) {
    u8 v = *(u8 *)(a0 + 0x20);
    if (v == 0) {
        extermibot_init_parts(a0);
        return;
    }
    if (v == 1) return;
    extermibot_update_hits(a0);
    extermibot_update_states(a0);
    extermibot_aim_torso(a0);
    extermibot_update_parts(a0);
}





