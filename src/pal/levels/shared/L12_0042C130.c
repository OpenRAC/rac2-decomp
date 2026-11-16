#include "include_asm.h"
#include "names.h"



typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
extern s32 g_moby_list_start __attribute__((sda));
extern s32 g_hero_l12_lock_flag __attribute__((sda));
extern int FastDecTimer(s32);
extern void moby_update_eased_node(s32, s32, s32, f32, f32);
extern void func_PAL_002B14F8(s32, s32, s32, s32, f32);

/* func_L12_00424078 is defined in L12_00424078-g8.c. */

/* func_L12_00426C08 is defined in L12_00426C08-g8.c. */

/* func_L12_004277F0 is defined in L12_004277F0-g8.c. */


void hopping_enemy_tick_timers_pal(s32 a0) {
    s32 s1 = a0;
    s32 s0 = *(u32 *)(s1 + 0x68);

    FastDecTimer(s0 + 0x330);
    FastDecTimer(s0 + 0x332);
    if (*(u16 *)(s1 + 0x96) <= 0xFFFE)
        *(u16 *)(s1 + 0x96) = *(u16 *)(s1 + 0x96) + 1;
    s0 = s0 + 0x280;
    moby_update_eased_node(s1, s0, 0, 0.0432f, 0.43200004f);
    func_PAL_002B14F8(s1, s0, 0, 1, 1.8f);
}

