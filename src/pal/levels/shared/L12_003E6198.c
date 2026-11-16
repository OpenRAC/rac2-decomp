#include "include_asm.h"
#include "names.h"



typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
extern s32 g_moby_list_start __attribute__((sda));
extern s32 g_hero_l12_lock_flag __attribute__((sda));
extern u8 g_path_shooter_state[];
extern u8 g_path_zone_table[];
extern void func_L12_0031E1D0(s32, s32, s32);

void group_try_claim_attack_slot_pal(s32 a0) {
    s32 s0 = a0;
    s32 s1 = *(u32 *)(s0 + 0x68);
    s32 v = *(s32 *)(*(u32 *)(s1 + 0x294));

    if (v != -1) {
        s32 base = g_moby_list_start;
        u8 *p = (u8 *)((u32)base + (v << 8));

        if (p != 0) {
            u8 t = *(u8 *)(p + 0x20);

            if (t != 0xFE) {
                if (t != 0xFD) {
                    if (v != ((s0 - base) >> 8))
                        return;
                }
            }
        }
    }
    func_L12_0031E1D0(s0, 0xF, 5);
    {
        s32 i = (s0 - g_moby_list_start) >> 8;

        *(u16 *)(s1 + 0x29C) = 0xFA;
        *(s32 *)(*(u32 *)(s1 + 0x294)) = i;
    }
}

